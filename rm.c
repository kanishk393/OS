#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    if (argv[1] == NULL) {
        printf("rm: missing operand\n");
        printf("Try 'rm --help' for more information.\n");
        exit(1);
    } else if (strcmp(argv[1], "-i") == 0) {
        if (access(argv[2], F_OK) == 0) {
            printf("rm: remove file '%s'? (y/n) ", argv[2]);
            char ans;
            scanf("%c", &ans);
            if (ans == 'y') {
                int del = remove(argv[2]);
            }
        } else {
            printf("rm: cannot remove '%s': No such file or directory\n", argv[2]);
            exit(1);
        }
    } else if (strcmp(argv[1], "-d") == 0) {
        DIR* dir = opendir(argv[2]);
        if (dir) {
            int del = rmdir(argv[2]);
            if (del) {
                printf("rm: cannot remove '%s': Directory not empty\n", argv[2]);
            }
            closedir(dir);
        } else {
            printf("rm: cannot remove '%s': No such file or directory\n", argv[2]);
        }
    } else {
        for (int i = 1; argv[i] != NULL; i++) {
            int del = remove(argv[i]);
            if (del) {
                printf("rm: cannot remove '%s': No such file or directory\n", argv[i]);
                continue;
            }
        }
    }
    return 0;
}