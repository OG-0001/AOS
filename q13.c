#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

int count = 0;

void handler(int signo) {
    count++;
    char* msg = "SIGINT signal occurred\n";
    write(STDOUT_FILENO, msg, strlen(msg));

    if (count >= 6) {
        char* exit_msg = "Exiting after 6 SIGINTs...\n";
        write(STDOUT_FILENO, exit_msg, strlen(exit_msg));
        exit(0);
    }
}

int main(void) {
    // Set up handler for SIGINT
    signal(SIGINT, handler);

    // Ignore SIGTSTP
    if (signal(SIGTSTP, SIG_IGN) == SIG_ERR) {
        perror("Cannot ignore SIGTSTP");
        exit(EXIT_FAILURE);
    }

    int n = 0;
    while (1) {
        printf("\n%d Hello Pid=%d\n", n++, getpid());
        sleep(2);
    }

    return 0;
}

