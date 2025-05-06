#include <stdio.h>      
#include <fcntl.h>     
#include <stdlib.h>    
#include <sys/types.h>   
#include <unistd.h>    

char buffer[2048];
int version = 1;

int main(int argc, char *argv[])
{
    void copy(int,int);
    int fdold,fdnew;

    if(argc!=3)
    {
        printf("Need 2 arguments for copy program\n");
        exit(1);
    }
    fdold=create(argv[1],0666);
    if(fdold==-1)
    {
        printf("Cannot open file: %s\n",argv[1]);
        exit(1);

    }

    fdnew=open(argv[2],O_RDONLY);
    if(fdnew==-1)
    {
        printf("Cannot create file: %s\n",argv[2]);
        exit(1);
    }

    copy(fdold,fdnew);
    return 0;

}
void copy(int old,int new)
{
    int count;
    while ((count=read(old,buffer,sizeof(buffer)))>0)
    {
        write(new,buffer,count);
    }
    
}