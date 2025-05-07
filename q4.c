#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <directory> <filename>\n", argv[0]);
        return 1;
    }
    DIR *dir = opendir(argv[1]);
    if (!dir) {
        perror("opendir");
        return 1;
    }
    struct dirent *entry;
    int found = 0;
    char filepath[1024];
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, argv[2]) == 0) {
            found = 1;
            snprintf(filepath, sizeof(filepath), "%s/%s", argv[1], argv[2]);
            break;
        }
    }
    closedir(dir);

    if (!found) {
        printf("%s is not in %s\n", argv[2], argv[1]);
        return 1;
    }
    struct stat fileStat;
    if (stat(filepath, &fileStat) < 0) {
        perror("stat");
        return 1;
    }

    if (S_ISREG(fileStat.st_mode)) {
        printf("%s is a regular file.\n", argv[2]);
    } else if (S_ISDIR(fileStat.st_mode)) {
        printf("%s is a directory.\n", argv[2]);
    } else {
        printf("%s is neither a regular file nor a directory.\n", argv[2]);
    }
    printf("User permissions: ");
    printf("%c", (fileStat.st_mode & S_IRUSR) ? 'r' : '-');
    printf("%c", (fileStat.st_mode & S_IWUSR) ? 'w' : '-');
    printf("%c\n", (fileStat.st_mode & S_IXUSR) ? 'x' : '-');

    return 0;
}

