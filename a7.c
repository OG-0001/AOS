/*Q7.Write a program in C to print the size of a regular file. 
Accept the file name from  user using command line argument.*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc,char *argv[])
{
    struct stat sb;
    int ret;
    if(argc != 2)
    {
        printf("Usage:%s<file>\n",argv[0]);
        return 1;
    }

    ret=stat(argv[1],&sb);
    if(ret)
    {
        perror("stat");
        return 1;
    }
    printf("Size of %s:%lld bytes\n",argv[1],sb.st_size);
    return 0;
}