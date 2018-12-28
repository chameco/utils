#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char **argv) {
	if (argc < 3) {
		fprintf(stderr, "Usage: %s num command args+\n", argv[0]);
		return 1;
	}
	for (int num = atoi(argv[1]); num > 0; --num) {
		if (fork() == 0) {
			execvp(argv[2], argv + 2);
			fprintf(stderr, "Failed to invoke %s with arguments", argv[2]);
			for (int i = 0; i + 2 < argc; ++i) {
				fprintf(stderr, " %s", (argv + 2)[i]);
			}
			fprintf(stderr, "\n");
			exit(1);
		} else wait(NULL);
	}
}
