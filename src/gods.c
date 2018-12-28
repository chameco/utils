#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

extern char **environ;

typedef enum {SUN=0, MON, TUE, WED, THU, FRI, SAT} day;

day get_day() {
	time_t t = time(NULL);
	struct tm *tm = localtime(&t);
	return tm->tm_wday;
}

void setroot(char *str) {
	int pid = fork();
	if (pid == 0) execve("/usr/bin/xsetroot", (char *const []){"/usr/bin/xsetroot", "-name", str, NULL}, environ);
	else waitpid(pid, NULL, 0);
}

int main() {
	char buffer[32];
	time_t timer;
	while (1) {
		time(&timer);
		strftime(buffer, 32, "%m/%d %H:%M", localtime(&timer));
		setroot(buffer);
		sleep(10);
	}
	return EXIT_FAILURE;
}
