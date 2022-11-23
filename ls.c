#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    int flag = 0;
    DIR* d;
    struct dirent *dir;
    d = opendir(".");
    if (argv[1] != NULL) {
        if (strcmp(argv[1], "-1") == 0) {
            if (d) {
                while ((dir = readdir(d)) != NULL) {
                    if (dir->d_name[0] != '.') 
                        printf("%s\n", dir->d_name);
                }
            }
        } else if (strcmp(argv[1], "-a") == 0) {
            while ((dir = readdir(d)) != NULL) {
                printf("%s\t", dir->d_name);
            }
            printf("\n");
        } else if (argv[1][0] == '-') {
                printf("ls: invalid option -- '%s\n", argv[1]);
                printf("Try 'ls --help' for more information.\n");
                exit(1);
        } else {
            while ((dir = readdir(d)) != NULL) {
                if (strcmp(dir->d_name, argv[1]) == 0) {
                    printf("%s\n", argv[1]);
                    flag = 1;
                }
            }
            if (flag != 1) {
                printf("ls: cannot access '%s", argv[1]);
                printf("': No such file or directory\n");
                exit(1);
            }
        }
    } else {
        if (d) {
            while ((dir = readdir(d)) != NULL) {
                if (dir->d_name[0] != '.') 
                    printf("%s\t", dir->d_name);
            }
        }
        printf("\n");
    }
    closedir(d);
}
