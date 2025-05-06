//Q9 unnamd pipe

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFEER_SIZE 100

int main()
{
    int fd[2];
    pid_t pid;
    char write_msg[] = "Hello from child!";
    char read_msg[BUFEER_SIZE];

    if(pipe(fd)==-1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid=fork();
    if(pid<0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if(pid==0)
    {
        close(fd[0]);
        write(fd[1],write_msg,strlen(write_msg)+1);
        close(fd[1]);
    }
    else{
        close(fd[1]);
        read(fd[0],read_msg,BUFEER_SIZE);
        printf("parent received: %s\n",read_msg);
        close(fd[0]);
        

    }
}