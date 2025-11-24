#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

typedef struct {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
    int response_time;
    int start_time; // Time when process first gets CPU
    bool is_started;
} Process;

void get_input(Process p[], int n);
void calculate_times(Process p[], int n);
void print_table(Process p[], int n);
void print_averages(Process p[], int n);

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
    print_averages(p, n);

    return 0;
}

void get_input(Process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("\nProcess %d:\n", p[i].id);
        
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
        p[i].is_started = false;
    }
}

void calculate_times(Process p[], int n) {
    int current_time = 0;
    int completed = 0;
    int min_remaining_time = INT_MAX;
    int shortest = -1;
    bool check = false;

    // Run until all processes are completed
    while (completed != n) {
        // Find process with minimum remaining time among those that have arrived
        for (int i = 0; i < n; i++) {
            if ((p[i].arrival_time <= current_time) && (p[i].remaining_time < min_remaining_time) && (p[i].remaining_time > 0)) {
                min_remaining_time = p[i].remaining_time;
                shortest = i;
                check = true;
            }
        }

        if (!check) {
            current_time++;
            continue;
        }

        // Process the shortest job
        if (!p[shortest].is_started) {
            p[shortest].start_time = current_time;
            p[shortest].response_time = p[shortest].start_time - p[shortest].arrival_time;
            p[shortest].is_started = true;
        }

        p[shortest].remaining_time--;
        min_remaining_time = p[shortest].remaining_time;
        if (min_remaining_time == 0)
            min_remaining_time = INT_MAX;

        // If a process gets completely executed
        if (p[shortest].remaining_time == 0) {
            completed++;
            check = false;
            p[shortest].completion_time = current_time + 1;
            p[shortest].turnaround_time = p[shortest].completion_time - p[shortest].arrival_time;
            p[shortest].waiting_time = p[shortest].turnaround_time - p[shortest].burst_time;

            if (p[shortest].waiting_time < 0)
                p[shortest].waiting_time = 0;
        }
        current_time++;
    }
}

void print_table(Process p[], int n) {
    printf("\n-----------------------------------------------------------------------------------------\n");
    printf("| Process | Arrival | Burst | Completion | Turnaround | Waiting | Response |\n");
    printf("-----------------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("|    P%d   |    %2d   |   %2d  |     %2d     |     %2d     |    %2d   |    %2d    |\n",
               p[i].id, p[i].arrival_time, p[i].burst_time, p[i].completion_time,
               p[i].turnaround_time, p[i].waiting_time, p[i].response_time);
    }
    printf("-----------------------------------------------------------------------------------------\n");
}

void print_averages(Process p[], int n) {
    float avg_wt = 0, avg_tat = 0, avg_rt = 0;
    for (int i = 0; i < n; i++) {
        avg_wt += p[i].waiting_time;
        avg_tat += p[i].turnaround_time;
        avg_rt += p[i].response_time;
    }
    avg_wt /= n;
    avg_tat /= n;
    avg_rt /= n;

    printf("\nAverage Waiting Time: %.2f\n", avg_wt);
    printf("Average Turnaround Time: %.2f\n", avg_tat);
    printf("Average Response Time: %.2f\n", avg_rt);
}
