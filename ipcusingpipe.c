#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MSG_SIZE 50

int main() {
    int pipe_fd[2]; // File descriptors for the pipe
    pid_t child_pid;
    char message[MSG_SIZE];

    // Create a pipe
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Create a child process
    child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // This is the child process
        close(pipe_fd[1]); // Close the write end of the pipe in the child

        // Read the message from the pipe
        read(pipe_fd[0], message, MSG_SIZE);
        printf("Child Process Received: %s\n", message);

        close(pipe_fd[0]); // Close the read end of the pipe in the child
    } else {
        // This is the parent process
        close(pipe_fd[0]); // Close the read end of the pipe in the parent

        // Send a message to the child process through the pipe
        char *parent_message = "Hello, Child!";
        write(pipe_fd[1], parent_message, strlen(parent_message) + 1);

        close(pipe_fd[1]); // Close the write end of the pipe in the parent
    }

    return 0;
}
