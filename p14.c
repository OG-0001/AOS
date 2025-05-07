#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
int quit_count = 0;
// Handler for SIGQUIT
void handle_sigquit(int sig) {
    quit_count++;
    if (quit_count < 6) {
        printf("SIGQUIT signal occurred (%d time(s))\n", quit_count);
    } else {
        printf("SIGQUIT signal occurred 6th time. Exiting...\n");
        exit(0);
    }
}
int main() {
    // Set custom handler for SIGQUIT
    signal(SIGQUIT, handle_sigquit);
    // Ignore SIGTSTP
    signal(SIGTSTP, SIG_IGN);
    // Keep program running and waiting for signals
    while (1) {
        pause();  // Wait for a signal
    }
    return 0;
}

