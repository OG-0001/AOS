#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define FIFO_NAME "my_named_pipe"  // Name of the FIFO

int main()
{
    pid_t pid;
    int fd;
    char write_msg[] = "Hello from child!";
    char read_msg[100];

    // Create a named pipe (FIFO)
    if (mkfifo(FIFO_NAME, 0666) == -1) {
        printf("mkfifo");
        exit(EXIT_FAILURE);
    }

    // Fork to create a child process
    pid = fork();
    if (pid == -1) {
        printf("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {  // Parent Process
        // Open the FIFO for reading
        fd = open(FIFO_NAME, O_RDONLY);
        if (fd == -1) {
            printf("open");
            exit(EXIT_FAILURE);
        }

        // Read the message from the FIFO
        read(fd, read_msg, sizeof(read_msg));
        printf("Parent received message: %s\n", read_msg);

        // Close the FIFO
        close(fd);
    } 
    else {  // Child Process
        // Open the FIFO for writing
        fd = open(FIFO_NAME, O_WRONLY);
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }

        // Write a message to the FIFO
        write(fd, write_msg, strlen(write_msg) + 1);

        // Close the FIFO
        close(fd);
    }

    // Remove the FIFO file after use
    unlink(FIFO_NAME);

    return 0;
}

