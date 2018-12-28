CC = gcc
CFLAGS = -Iinclude -std=c11 -g -Wall -Wextra -Werror
LDFLAGS = -static

BINS = bin/gods bin/pass bin/trip bin/roll bin/repeat bin/yhvh

vpath %.c src

.PHONY: all

all: $(BINS)

bin/%: src/%.c
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@

bin/trip: src/trip.c
	$(CC) $(CFLAGS) -lcrypt $< -o $@

clean:
	rm bin/* -rf
