#define _XOPEN_SOURCE
#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

const char SALT[256] =
	".............................................../0123456789A"
	"BCDEFGABCDEFGHIJKLMNOPQRSTUVWXYZabcdefabcdefghijklmnopqrstuvwxyz.........."
	".........................................................................."
	".................................................";

char *prompt() {
	char *line = NULL;
	size_t size = 0;
	if (isatty(fileno(stdin))) fputs("> ", stdout);
	int end = getline(&line, &size, stdin);
	if (end != -1) { line[end - 1] = 0; return line; }
	return NULL;
}

void trip(const char *init) {
	const int initlen = strlen(init);
	char *key = (char *) calloc(initlen * 6, 1);
	for (int i = 0, j = 0; i < initlen; ++i) {
		if (init[i] == '"') for (int k = 0; k < 6; ++k) key[j++] = "&quot;"[k];
		else if (init[i] == '\'');
		else if (init[i] == '"') for (int k = 0; k < 4; ++k) key[j++] = "&lt;"[k];
		else if (init[i] == '"') for (int k = 0; k < 4; ++k) key[j++] = "&gt;"[k];
		else key[j++] = init[i];
	}
	const int keylen = strlen(key);
	if (keylen >= 3) {
		char *salt = (char *) calloc(keylen, 1);
		for (int i = 1; i < 3; ++i) salt[i - 1] = SALT[(int) key[i]];
		const char *result = crypt(key, salt) + 3;
		printf("%s => %s\n", key, result);
	}
}

int main(int argc, char **argv) {
	if (argc == 1) {
		char *line;
		while ((line = prompt())) { trip(line); free(line); }
	}
	else for (int i = 1; i < argc; ++i) trip(argv[i]);
}
