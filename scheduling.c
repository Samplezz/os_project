#include <stdio.h>
#include <limits.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int start_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
    int response_time;
    int is_started;
} Process;

void get_input(Process p[], int n);
void calculate_times(Process p[], int n);
void print_table(Process p[], int n);

int main() {
    int n;

    printf("Enter the number of processes: ");
    while (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input. Please enter a positive integer: ");
        while (getchar() != '\n'); // Clear buffer
    }

    Process p[n];
    get_input(p, n);
    calculate_times(p, n);
    print_table(p, n);

    return 0;
}

void get_input(Process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nProcess %d:\n", p[i].pid);
        
        printf("  Arrival Time: ");
        while (scanf("%d", &p[i].arrival_time) != 1 || p[i].arrival_time < 0) {
            printf("  Invalid input. Enter a non-negative integer: ");
            while (getchar() != '\n');
        }

        printf("  Burst Time: ");
        while (scanf("%d", &p[i].burst_time) != 1 || p[i].burst_time <= 0) {
            printf("  Invalid input. Enter a positive integer: ");
            while (getchar() != '\n');
        }

        p[i].remaining_time = p[i].burst_time;
        p[i].is_started = 0;
    }
}

void calculate_times(Process p[], int n) {
    int current_time = 0;
    int completed = 0;
    int min_remaining_time;
    int shortest = -1;
    int finish_time;
    int check = 0;

    // Run until all processes are completed
    while (completed != n) {
        min_remaining_time = INT_MAX;
        shortest = -1;
        check = 0;

        // Find process with minimum remaining time among those that have arrived
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && p[i].remaining_time > 0) {
                if (p[i].remaining_time < min_remaining_time) {
                    min_remaining_time = p[i].remaining_time;
                    shortest = i;
                    check = 1;
                }
                // If remaining times are equal, pick the one that arrived earlier (FCFS tie-breaking)
                if (p[i].remaining_time == min_remaining_time) {
                    if (shortest == -1 || p[i].arrival_time < p[shortest].arrival_time) {
                        shortest = i;
                    }
                }
            }
        }

        if (check == 0) {
            current_time++;
            continue;
        }

        // If this is the first time the process is running, set response time
        if (p[shortest].is_started == 0) {
            p[shortest].start_time = current_time;
            p[shortest].response_time = current_time - p[shortest].arrival_time;
            p[shortest].is_started = 1;
        }

        // Execute the process for 1 unit of time
        p[shortest].remaining_time--;
        current_time++;

        // If process is finished
        if (p[shortest].remaining_time == 0) {
            completed++;
            finish_time = current_time;
            p[shortest].completion_time = finish_time;
            p[shortest].turnaround_time = p[shortest].completion_time - p[shortest].arrival_time;
            p[shortest].waiting_time = p[shortest].turnaround_time - p[shortest].burst_time;
        }
    }
}

void print_table(Process p[], int n) {
    float avg_waiting_time = 0;
    float avg_turnaround_time = 0;
    float avg_response_time = 0;

    printf("\n=====================================================================================\n");
    printf("| PID | Arrival | Burst | Completion | Turnaround | Waiting | Response |\n");
    printf("|-----|---------|-------|------------|------------|---------|----------|\n");

    for (int i = 0; i < n; i++) {
        printf("| %3d | %7d | %5d | %10d | %10d | %7d | %8d |\n",
               p[i].pid, p[i].arrival_time, p[i].burst_time, p[i].completion_time,
               p[i].turnaround_time, p[i].waiting_time, p[i].response_time);

        avg_waiting_time += p[i].waiting_time;
        avg_turnaround_time += p[i].turnaround_time;
        avg_response_time += p[i].response_time;
    }

    printf("=====================================================================================\n");
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time / n);
    printf("Average Response Time: %.2f\n", avg_response_time / n);
}
