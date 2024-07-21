#include <stdio.h>

void fcfs(int processes[], int n, int burst_time[]) {
    int waiting_time[n], turnaround_time[n], total_waiting_time = 0, total_turnaround_time = 0;
    waiting_time[0] = 0;
    for (int i = 1; i < n; i++) {
        waiting_time[i] = burst_time[i - 1] + waiting_time[i - 1];
        total_waiting_time += waiting_time[i];
    }

    // Calculating turnaround time
    for (int i = 0; i < n; i++) {
        turnaround_time[i] = burst_time[i] + waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }

    // Printing results
    printf("First Come, First Served (FCFS) scheduling Algorithm\n");
    printf("----------------------------------------------------\n");
    printf("Process\t Burst Time\t Waiting Time\t Turnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t %d\t\t %d\t\t %d\n", processes[i], burst_time[i], waiting_time[i], turnaround_time[i]);
    }
    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
    printf("\n");
}

// Function to implement SJF scheduling
void sjf(int processes[], int n, int burst_time[]) {
    int waiting_time[n], turnaround_time[n], total_waiting_time = 0, total_turnaround_time = 0;

    // Sorting burst time and processes using selection sort
    for (int i = 0; i < n; i++) {
        int shortest_job_index = i;
        for (int j = i + 1; j < n; j++) {
            if (burst_time[j] < burst_time[shortest_job_index]) {
                shortest_job_index = j;
            }
        }

        // Swapping burst time
        int temp = burst_time[i];
        burst_time[i] = burst_time[shortest_job_index];
        burst_time[shortest_job_index] = temp;

        // Swapping processes
        temp = processes[i];
        processes[i] = processes[shortest_job_index];
        processes[shortest_job_index] = temp;
    }

    // Calculating waiting time
    waiting_time[0] = 0;
    for (int i = 1; i < n; i++) {
        waiting_time[i] = burst_time[i - 1] + waiting_time[i - 1];
        total_waiting_time += waiting_time[i];
    }

    // Calculating turnaround time
    for (int i = 0; i < n; i++) {
        turnaround_time[i] = burst_time[i] + waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }

    // Printing results
    printf("Shortest Job First (SJF) scheduling Algorithm\n");
    printf("----------------------------------------------------\n");
    printf("Process\t Burst Time\t Waiting Time\t Turnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t %d\t\t %d\t\t %d\n", processes[i], burst_time[i], waiting_time[i], turnaround_time[i]);
    }
    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
    printf("\n");
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processes[n], burst_time[n];
    printf("Enter the burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
        processes[i] = i + 1;
    }

    fcfs(processes, n, burst_time);

    // Reset burst times and processes for SJF calculation
    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;
    }

    sjf(processes, n, burst_time);

    return 0;
}
