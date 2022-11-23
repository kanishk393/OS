#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]) {
    time_t t, y;
    t = time(NULL);
    if (argv[1] == NULL) {
        printf("%s", ctime(&t));
    } else if (strcmp(argv[1], "--date=\"yesterday\"") == 0) {
        if (argv[2] == NULL) {
            y = t - 24*60*60;
            printf("%s", ctime(&y));
        } else {
            printf("date: invalid date '%s", argv[2]);
            printf("\n");
        }
    } else if (strcmp(argv[1], "--date=\"tomorrow\"") == 0) {
        if (argv[2] == NULL) {
            y = t + 24*60*60;
            printf("%s", ctime(&y));
        } else {
            printf("date: invalid date '%s", argv[2]);
            printf("\n");
        }
    } else if (argv[1][0] == '-') {
        printf("date: invalid option -- '%s\n'", argv[1]);
        printf("Try 'date --help' for more information.\n");
        exit(1);
    } else {
        printf("date: invalid date '%s", argv[1]);
        printf("\n");
    }
}
