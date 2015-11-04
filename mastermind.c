#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <time.h>

#define DIGITS 4
#define BUFSIZE 1000

struct code {
	_Bool flag;
	int code : 14;
};

struct result {
	unsigned int red : 3;
	unsigned int white : 3;
};

int autoplay(struct code *codes);
void check_guess(char *secret, char *guess, struct result *result);

int main(int argc, char **argv)
{
	_Bool autoplay = 0;
	if(argc > 1 && !(autoplay = !strncmp("autoplay", argv[1], 9))) {
		fprintf(stderr, "Usage: %s [autoplay]\n", argv[0]);
		return EX_USAGE;
	}
	
	/*if(autoplay) {
		// Initialize set of codes for autoplay
		struct code *codes[10000];
		for(int i=0; i < 10000; i++) *codes[i] = (struct code) { .code = i };
	} */

	srand(time(NULL));
	char secret[DIGITS+1] = {rand() % 10, rand() % 10, rand() % 10, rand() % 10, '\0'};
	for(int i=0; i < DIGITS; i++) secret[i] += 48;
	int guesses = 0;
	struct result result = {.red = 0 , .white = 0};

	while(1)
	{
		char buf[BUFSIZE] = {0};
		char guess[DIGITS+1] = {0};
		char c;
		int i = 0;

		printf("Please make a guess: ");
		while((c = getchar()) != '\n' && c != EOF) buf[i++] = c;
		strncat(guess, buf, DIGITS);
		/* TODO: validate user input */
		guesses++;

		check_guess(secret, guess, &result);
		printf("%i red, %i white\n", result.red, result.white);
		if (result.red == 4) {
			printf("That is correct. You got it in %i guess%s.\n", guesses, (guesses == 1 ? "": "es"));
			return 0;
		}
	}
}

void check_guess(char *secret, char *guess, struct result *result)
{
	int digit_counts[10] = {0};
	for(int i=0; i < DIGITS; i++) digit_counts[secret[i]-48]++;

	*result = (struct result) { .red = 0, .white = 0 };
	// red check
	for(int i=0; i < DIGITS; i++)
	{
		if (guess[i] && guess[i] == secret[i]) {
			result->red++;
			digit_counts[guess[i]-48]--;
		}
	}
	// white check
	for(int i=0; i < DIGITS; i++)
	{
		if (guess[i] && guess[i] != secret[i] && digit_counts[guess[i]-48]) {
			result->white++;
			digit_counts[guess[i]-48]--;
		}
	}
}

int autoplay(struct code *codes)
{
	return codes->flag;
	
}
