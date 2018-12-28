#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#define MAX_WORDS 10000

char WORDS[MAX_WORDS][32];
unsigned int WORD_COUNT = 0;
char CONSONANTS[] = "bcdfghjklmnpqrstvwxz";
char VOWELS[] = "aeiouy";

void load_words(const char *path) {
	FILE *f = fopen(path, "r");
	while (fgets(WORDS[WORD_COUNT++], 32, f) != NULL && WORD_COUNT < MAX_WORDS)
		WORDS[WORD_COUNT-1][strlen(WORDS[WORD_COUNT-1])-1] = 0x0;
	fclose(f);
}

int isin(char c, char *s) {
	for (size_t i = 0; i < strlen(s); ++i) {
		if (c == s[i]) return 1;
	}
	return 0;
}

void scramble(char *word, int len) {
	int pos = rand() % len;
	if (isin(word[pos], CONSONANTS)) word[pos] = CONSONANTS[rand() % strlen(CONSONANTS)] - 'a' + 'A';
	else if (isin(word[pos], VOWELS)) word[pos] = VOWELS[rand() % strlen(VOWELS)] - 'a' + 'A';
}

void scramble_words() {
	for (unsigned int i = 0; i < WORD_COUNT; ++i) {
		scramble(WORDS[i], strlen(WORDS[i]));
	}
}

const char *gen_word() { return WORDS[rand() % WORD_COUNT]; }

int main() {
	load_words("/home/samuel/share/misc/dict.txt");
	scramble_words();
	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	srand(ts.tv_nsec);
	printf("%s%s%s%s%s%s\n", gen_word(), gen_word(), gen_word(), gen_word(), gen_word(), gen_word());
	return EXIT_SUCCESS;
}
