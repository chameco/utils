#define _GNU_SOURCE
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

static inline void say(const char *msg) { puts(msg); fflush(stdout); }
static char *execute(char *cmd, char **args) {
	int redirect[2];
	if (pipe(redirect) < 0) return NULL;
	pid_t proc = 0;
	if ((proc = fork()) == 0) {
		close(redirect[0]);
		dup2(redirect[1], STDOUT_FILENO);
		close(redirect[1]);
		execvp(cmd, args);
		exit(1);
	} else {
		close(redirect[1]);
		FILE *f = fdopen(redirect[0], "r");
		char *line = NULL;
		size_t size = 0;
		if (getline(&line, &size, f) == -1) { free(line); return NULL; }
		waitpid(proc, NULL, 0);
		return line;
	}
}

static void pass(const char *msg) { (void) msg; }
static void pong(const char *msg) { (void) msg; say("pong"); }
static void help(const char *msg) { (void) msg; say("Not even a thousand deaths would be fitting punishment for thy sins! I shall smite thee, and in Hell I shall torture thee over and over! After an aeon, I shall reincarnate thee, and thy lives shall be those of endless torment, thy bodies tortured in life and thy souls in death! The same shall come to thy children, and thy children's children, throughout all eternity until the end of time! Feel the wrath of my divine lightning, and plummet into the bowels of hell, burning in its unending flames! Demons! Evil humans, who have sold thy souls to demons!"); }
static void roguelike(const char *msg) { (void) msg; say("not a roguelike"); }
static void navyseal(const char *msg) {
	(void) msg;
	say("What the fuck did you just fucking say about me, you little bitch?"); sleep(2);
	say("I'll have you know I graduated top of my class in the Navy Seals, and I've been involved in numerous secret raids on Al-Quaeda, and I have over 300 confirmed kills."); sleep(2);
	say("I am trained in gorilla warfare and I'm the top sniper in the entire US armed forces."); sleep(2);
	say("You are nothing to me but just another target."); sleep(2);
	say("I will wipe you the fuck out with precision the likes of which has never been seen before on this Earth, mark my fucking words."); sleep(2);
	say("You think you can get away with saying that shit to me over the Internet?"); sleep(2);
	say("Think again, fucker."); sleep(2);
	say("As we speak I am contacting my secret network of spies across the USA and your IP is being traced right now so you better prepare for the storm, maggot."); sleep(2);
	say("The storm that wipes out the pathetic little thing you call your life."); sleep(2);
	say("You're fucking dead, kid."); sleep(2);
	say("I can be anywhere, anytime, and I can kill you in over seven hundred ways, and that's just with my bare hands."); sleep(2);
	say(" Not only am I extensively trained in unarmed combat, but I have access to the entire arsenal of the United States Marine Corps and I will use it to its full extent to wipe your miserable ass off the face of the continent, you little shit."); sleep(2);
	say("If only you could have known what unholy retribution your little \"clever\" comment was about to bring down upon you, maybe you would have held your fucking tongue."); sleep(2);
	say("But you couldn't, you didn't, and now you're paying the price, you goddamn idiot."); sleep(2);
	say("I will shit fury all over you and you will drown in it."); sleep(2);
	say("You're fucking dead, kiddo.");
}
static void tripcode(const char *msg) {
	char *post = strchr(msg, '!');
	if (post == NULL) return;
	char *t = strchr(post, ' ');
	if (t == NULL || strlen(t + 1) == 0) return;
	char *args[] = { "trip", t + 1, NULL };
	char *resp = execute("trip", args);
	printf("%s", resp);
	fflush(stdout);
	free(resp);
}

typedef void (*action)(const char *);
struct { const char *trigger; action response; } HANDLERS[] = {
	{ "<YHVH_>", pass },
	{ "!ping", pong },
	{ "!help", help },
	{ "roguelike?", roguelike },
	{ "this bot", navyseal }, { "the bot", navyseal }, { "yhvh", navyseal },
	{ "!tripcode", tripcode },

	{ NULL, NULL },
};

int main() {
	while (1) {
		char *msg = NULL;
		size_t size = 0;
		int end = getline(&msg, &size, stdin);
		if (end == -1) return 0;
		else msg[end - 1] = 0;

		for (int i = 0; HANDLERS[i].trigger != NULL; ++i) {
			if (strcasestr(msg, HANDLERS[i].trigger) != NULL) {
				HANDLERS[i].response(msg);
				break;
			}
		}

		free(msg);
	}

	return 0;
}
