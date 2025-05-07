#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>  
#include <string.h>


#define FIFO_NAME "myfifo"
#define BUFFER_SIZE 100

int main() {
    char buffer[BUFFER_SIZE];
    pid_t pid;

    // Create the named pipe (FIFO)
    if (mkfifo(FIFO_NAME, 0666) == -1) {
        perror("mkfifo");
        // If FIFO already exists, we ignore the error
    }

    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    else if (pid > 0) {
        // Parent process: Write to FIFO
        int fd;
        printf("Parent: Enter a message: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        fd = open(FIFO_NAME, O_WRONLY);
        write(fd, buffer, strlen(buffer) + 1);
        close(fd);

        wait(NULL); // Wait for child to finish
    }

    else {
        // Child process: Read from FIFO
        int fd;
        fd = open(FIFO_NAME, O_RDONLY);
        read(fd, buffer, BUFFER_SIZE);
        printf("Child: Received message: %s\n", buffer);
        close(fd);
    }

    // Remove the FIFO
    unlink(FIFO_NAME);

    return 0;
}

