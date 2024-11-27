#include <stdio.h>

struct Process {
    int pid;
    int burst_time;
    int waiting_time;
    int turnaround_time;
};

void calculateWaitingTime(struct Process proc[], int n) {
    proc[0].waiting_time = 0;
    for (int i = 1; i < n; i++) {
        proc[i].waiting_time = proc[i-1].waiting_time + proc[i-1].burst_time;
    }
}

void calculateTurnaroundTime(struct Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].turnaround_time = proc[i].waiting_time + proc[i].burst_time;
    }
}

void printProcesses(struct Process proc[], int n) {
    printf("PID\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].burst_time, proc[i].waiting_time, proc[i].turnaround_time);
    }
}

void FCFS(struct Process proc[], int n) {
    calculateWaitingTime(proc, n);
    calculateTurnaroundTime(proc, n);
    printf("FCFS Scheduling:\n");
    printProcesses(proc, n);
}

void SJF(struct Process proc[], int n) {
    struct Process temp;
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (proc[i].burst_time > proc[j].burst_time) {
                temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
    calculateWaitingTime(proc, n);
    calculateTurnaroundTime(proc, n);
    printf("SJF Scheduling:\n");
    printProcesses(proc, n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process proc[n];
    for (int i = 0; i < n; i++) {
        proc[i].pid = i+1;
        printf("Enter burst time for process %d: ", i+1);
        scanf("%d", &proc[i].burst_time);
    }

    FCFS(proc, n);
    SJF(proc, n);

    return 0;
}