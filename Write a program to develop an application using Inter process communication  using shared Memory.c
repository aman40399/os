#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define SHM_SIZE 1024  // Size of the shared memory

int main() {
    key_t key;
    int shmid;
    char *data;

    // Generate a unique key for the shared memory segment
    if ((key = ftok("shmfile", 65)) == -1) {
        perror("ftok");
        exit(1);
    }

    // Create the shared memory segment
    if ((shmid = shmget(key, SHM_SIZE, 0644 | IPC_CREAT)) == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach to the shared memory segment
    data = (char *)shmat(shmid, (void *)0, 0);
    if (data == (char *)(-1)) {
        perror("shmat");
        exit(1);
    }

    // Fork a child process
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        printf("Child process writing to shared memory...\n");
        strncpy(data, "Hello from child process!", SHM_SIZE);
        printf("Child process wrote: %s\n", data);
    } else if (pid > 0) {
        // Parent process
        wait(NULL);  // Wait for the child process to complete
        printf("Parent process reading from shared memory...\n");
        printf("Parent process read: %s\n", data);

        // Detach from the shared memory segment
        if (shmdt(data) == -1) {
            perror("shmdt");
            exit(1);
        }

        // Destroy the shared memory segment
        if (shmctl(shmid, IPC_RMID, NULL) == -1) {
            perror("shmctl");
            exit(1);
        }
    } else {
        perror("fork");
        exit(1);
    }

    return 0;
}