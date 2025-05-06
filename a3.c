#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>

int main(int argc,char *argv[])
{
    struct stat stats;
    char *path;
    DIR *dir;
    struct dirent *entry;

    if(argc>2)
    {
        printf("enter only one argument\n");
        return 1;
    }

    path=argv[1];
    dir=opendir(path);

    if(!dir)
    {
        printf("%s does not exist\n",path);
        return 1;
    }

    while((entry=readdir(dir))!=NULL)
    {
        printf("%s\n",entry->d_name);
    }
    closedir(dir);
    
}