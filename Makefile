CFLAGS=-std=c11 -Wall -Wextra -pedantic  -Werror -Wwrite-strings -Wfloat-equal -Waggregate-return -Winline  -Wstack-usage=1024

.PHONY: clean

mastermind: mastermind.o

debug: CFLAGS+=-g
debug: mastermind

clean:
	-rm *.o
