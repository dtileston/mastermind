CFLAGS=-std=c11 -Wall -Wextra -pedantic -Werror 

.PHONY: clean

mastermind: mastermind.o

debug: CFLAGS+=-g
debug: mastermind

clean:
	-rm *.o
