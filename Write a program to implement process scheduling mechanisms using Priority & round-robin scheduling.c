#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;
    int burst_time;
    int priority;
    int remaining_time;
} Process;

void priority_scheduling(Process processes[], int n) {
    int i, j;
    Process temp;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (processes[i].priority > processes[j].priority) {
                temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    printf("Priority Scheduling:\n");
    for (i = 0; i < n; i++) {
        printf("Process %d with priority %d\n", processes[i].pid, processes[i].priority);
    }
}

void round_robin_scheduling(Process processes[], int n, int quantum) {
    int time = 0, i;
    int done = 0;

    printf("Round Robin Scheduling:\n");
    while (!done) {
        done = 1;
        for (i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {
                done = 0;
                if (processes[i].remaining_time > quantum) {
                    time += quantum;
                    processes[i].remaining_time -= quantum;
                } else {
                    time += processes[i].remaining_time;
                    processes[i].remaining_time = 0;
                    printf("Process %d finished at time %d\n", processes[i].pid, time);
                }
            }
        }
    }
}

int main() {
    int n, i, quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    for (i = 0; i < n; i++) {
        printf("Enter burst time and priority for process %d: ", i + 1);
        scanf("%d %d", &processes[i].burst_time, &processes[i].priority);
        processes[i].pid = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
    }

    priority_scheduling(processes, n);

    printf("Enter the time quantum for Round Robin scheduling: ");
    scanf("%d", &quantum);

    round_robin_scheduling(processes, n, quantum);

    return 0;
}