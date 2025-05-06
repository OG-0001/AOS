#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define BUF_LEN 1000

int main(int arc,char *argv[])
{
    char *cwd;
    cwd=getcwd(NULL, 0);
    if(!getcwd(cwd,BUF_LEN))
    {
        perror("getcwd");
        exit(EXIT_FAILURE);
    }
    printf("Current Working Directory: %s\n", cwd); 
}