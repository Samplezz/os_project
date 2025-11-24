# Operating System Project

This project contains two parts as per the assignment requirements:
1.  **Banking System (Task 1, Idea 3)**: A file management interface.
2.  **Scheduling Algorithm (Task 2, Idea 3)**: Shortest Job First (Preemptive) simulation.

## Prerequisites
-   **Operating System**: Linux (Ubuntu, Fedora, etc.) or Windows with WSL (Windows Subsystem for Linux).
    -   *Note*: The Banking System uses Linux commands (`ls`, `chmod`, etc.) via `system()` calls, so it **must** be run in a Linux-like environment to work correctly.
-   **Compiler**: GCC (GNU Compiler Collection).

## Setup
1.  Open your terminal (WSL or Linux terminal).
2.  Navigate to the project directory:
    ```bash
    cd /path/to/os_project
    ```
3.  Make the setup script executable:
    ```bash
    chmod +x setup_banking.sh
    ```

## Task 1: Banking System
1.  Compile the program:
    ```bash
    gcc banking_system.c -o banking_system
    ```
2.  Run the program:
    ```bash
    ./banking_system
    ```
3.  **Usage**:
    -   The program will automatically run `./setup_banking.sh` to create the `/bank` directory structure if it doesn't exist.
    -   Follow the on-screen menu (1-11) to perform file operations.
    -   **Note**: All paths should be relative to the current directory (e.g., `./bank/admin`) or absolute.

## Task 2: Scheduling Algorithm (SJF Preemptive)
1.  Compile the program:
    ```bash
    gcc sjf_preemptive.c -o sjf_preemptive
    ```
2.  Run the program:
    ```bash
    ./sjf_preemptive
    ```
3.  **Usage**:
    -   Enter the number of processes.
    -   Enter the Arrival Time and Burst Time for each process when prompted.
    -   The program will display a table with completion, turnaround, waiting, and response times, followed by the averages.

## Files
-   `setup_banking.sh`: Script to initialize the banking directory structure.
-   `banking_system.c`: Source code for the banking system interface.
-   `sjf_preemptive.c`: Source code for the scheduling algorithm.
-   `README.md`: This file.
