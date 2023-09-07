#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid;
    int status;

    // Create a child process
    child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(1);
    } else if (child_pid == 0) {
        // This code is executed by the child process
        printf("Child process is running (PID: %d)\n", getpid());
        sleep(2);  // Simulate some work
        printf("Child process is done\n");
        exit(42);  // Exit with a status code
    } else {
        // This code is executed by the parent process
        printf("Parent process waiting for the child (PID: %d) to terminate...\n", child_pid);

        // Use waitpid to wait for the specific child process to terminate
        if (waitpid(child_pid, &status, 0) == -1) {
            perror("waitpid");
            exit(1);
        }

        if (WIFEXITED(status)) {
            printf("Child process (PID: %d) exited with status: %d\n", child_pid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child process (PID: %d) terminated by signal: %d\n", child_pid, WTERMSIG(status));
        }
    }

    return 0;
}
