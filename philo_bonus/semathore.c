#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>  // For O_CREAT and O_EXCL
#include <sys/stat.h> // For mode constants

int main() {
    // 1. Create a semaphore with initial value 0
    sem_t *sem = sem_open("mysemaphore", O_CREAT, 0644, 0);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork(); // 2. Fork a child process

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process
        printf("Child: Waiting for semaphore...\n");

        // 3. Child waits for semaphore (will block until parent calls sem_post)
        sem_wait(sem);

        printf("Child: Received signal from semaphore! Proceeding...\n");

        // Close the semaphore in the child process
        sem_close(sem);
        exit(EXIT_SUCCESS);
    } else { // Parent process
        sleep(2); // Simulate some work

        printf("Parent: Releasing semaphore...\n");
        sem_post(sem); // 4. Parent releases semaphore, allowing child to proceed

        wait(NULL); // Wait for child to finish

        // Cleanup: Close and unlink semaphore
        sem_close(sem);
        sem_unlink("/mysemaphore");

        printf("Parent: Semaphore cleaned up and exiting.\n");
    }

    return 0;
}
