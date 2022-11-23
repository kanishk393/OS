#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	int check;
	int flag = 0;
	if (argv[1] == NULL) {
		printf("mkdir: missing operand\nTry 'mkdir --help' for more information.\n");
		exit(1);
	} else if (strcmp(argv[1], "-v") == 0) {
		check = mkdir(argv[2], 0777);
		if (check) {
		printf("mkdir: cannot create directory %s\n", argv[2]);
		exit(1);
		} else {
			printf("mkdir: created directory '%s\n", argv[2]);
		}
	} else {
		for (int i = 1; argv[i] != NULL; i++) {
			check = mkdir(argv[i], 0777);
			if (check) {
			printf("mkdir: cannot create directory %s\n", argv[i]);
			continue;
			}
		}
	}
}
