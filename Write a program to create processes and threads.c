#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// Function to be executed by the thread
void* thread_function(void* arg) {
    printf("Thread: Hello from the thread!\n");
    return NULL;
}

int main() {
    pid_t pid;
    pthread_t thread;

    // Create a new process
    pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        printf("Child Process: Hello from the child process!\n");

        // Create a new thread in the child process
        if (pthread_create(&thread, NULL, thread_function, NULL) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }

        // Wait for the thread to finish
        if (pthread_join(thread, NULL) != 0) {
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }

        printf("Child Process: Thread has finished execution.\n");
    } else {
        // Parent process
        printf("Parent Process: Hello from the parent process!\n");

        // Wait for the child process to finish
        if (wait(NULL) < 0) {
            perror("wait");
            exit(EXIT_FAILURE);
        }

        printf("Parent Process: Child process has finished execution.\n");
    }

    return 0;
}