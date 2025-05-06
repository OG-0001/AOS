/*Q8. Write a program in C to count the number of files in directory. 
Accept the file name from  user using command line argument.*/

#include<dirent.h>
#include<stdio.h>

int main()
{
    DIR *dir;
    struct dirent *ent;
    int found=0;
    char dir_path[256];

    printf("Enter the Directory path: ");
    scanf("%s", dir_path);

    dir =opendir(dir_path);
    if(dir==NULL)
    {
        printf("error opening directory\n");
        return 1;
    }
    while((ent=readdir(dir))!=NULL)
    {
        if(ent->d_type==DT_DIR)
        {
            continue;
        }
        found++;

    }
    closedir(dir);
    printf("Number of files is %s:%d\n",dir_path,found);
    return 0;
}