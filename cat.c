#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>

int main(int argc, char* argv[]) {
    FILE* file;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    int lineCount = 1;
    if (strcmp(argv[1], "-n") == 0) {
        file = fopen(argv[2], "r");
        if (file == NULL) {
            printf("cat: %s", argv[2]);
            printf(": No such file or directory\n");
            exit(1);
        }
        while ((read = getline(&line, &len, file)) != -1) {
            if (line == NULL) {
                printf("%d\n", lineCount);
            } else {
                printf("%d  %s", lineCount, line);
            }
            lineCount++;
        }
	    fclose(file);
    } else if (strcmp((argv[1]), ">>") == 0) {
        file = fopen(argv[2], "a");
        char* str = readline((""));
        fprintf(file, "%s", str);
        fclose(file);
    } else if (argv[1][0] == '-') { 
        printf("cat: invalid option -- '%s\n", argv[1]);
        printf("Try 'cat --help' for more information.\n");
        exit(1);
    } else {
        file = fopen(argv[1], "r");
        if (file == NULL) {
            printf("cat: %s", argv[1]);
            printf(": No such file or directory\n");
            exit(1);
        }
        while ((read = getline(&line, &len, file)) != -1) {
            if (line == NULL) {
                printf("\n");
            } else {
                printf("%s", line);
            }
        }
	    fclose(file);
    }
	return 0;
}
