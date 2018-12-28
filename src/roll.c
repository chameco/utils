#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

char *prompt() {
	char *line = NULL;
	size_t size = 0;
	if (isatty(fileno(stdin))) fputs("> ", stdout);
	int end = getline(&line, &size, stdin);
	if (end != -1) { line[end - 1] = 0; return line; }
	return NULL;
}

int roll(char *spec) {
	int num = 0, die = 0, total = 0;
	char *tmp = NULL;
	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	srand(ts.tv_nsec);
	if ((tmp = strtok(spec, "d")) != NULL) num = atoi(tmp);
	if ((tmp = strtok(NULL, "d")) != NULL) die = atoi(tmp);
	else { total = num; }
	if (die > 0) for (; num > 0; --num) total += 1 + rand() % die;
	return total;
}

void parse(char *spec) {
	printf("rolling %s => ", spec);
	int total = 0;
	char *tmp = NULL, *saveptr;
	if ((tmp = strtok_r(spec, "+", &saveptr)) != NULL) {
		total += roll(tmp);
		while ((tmp = strtok_r(NULL, "+", &saveptr)) != NULL) total += roll(tmp);
	} else total = roll(spec);
	printf("%d\n", total);
}

int main(int argc, char **argv) {
	if (argc == 1) {
		char *line;
		while ((line = prompt())) { parse(line); free(line); }
	}
	else for (int i = 1; i < argc; ++i) parse(argv[i]);
}
