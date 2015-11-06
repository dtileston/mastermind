#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <time.h>

#define DIGITS 4
#define BUFSIZE 1000

struct result {
	unsigned int red : 3;
	unsigned int white : 3;
};

struct code {
	unsigned int flag: 1;
};

int computer_play();
int validate_input(char *buf, char *guess);
void check_guess(char *secret, char *guess, struct result *result);

int main(int argc, char **argv)
{
	int autoplay = 0;
	if(argc > 1 && !(autoplay = !strncmp("autoplay", argv[1], 9))) {
		fprintf(stderr, "Usage: %s [autoplay]\n", argv[0]);
		return EX_USAGE;
	}

	srand(time(NULL));
	char secret[DIGITS+1] = {'\0'};
	for(int i=0; i < DIGITS; i++) secret[i] = (rand() % 10) + '0';

	if(autoplay) {
		while(computer_play());
		return 0;
	}
	char guess[DIGITS+1] = {'\0'};
	int guesses = 0;
	struct result result = {.red = 0 , .white = 0};
	int valid_guess = 0;

	while(1)
	{	
		valid_guess = 0;
		while(!valid_guess) {
			char buf[BUFSIZE] ={'\0'};
			printf("Please make a guess (Ctrl+D to exit): ");
			fgets(buf, sizeof(buf), stdin);
			valid_guess = validate_input(buf, guess);
			if(valid_guess < 0) {
				fprintf(stderr, "\nExiting now!\n");
				return 1;
			}
		}
		guesses++;
		check_guess(secret, guess, &result);
		printf("%i red, %i white\n", result.red, result.white);
		if (result.red == 4) {
			printf("That is correct. You got it in %i guess%s.\n", guesses, (guesses == 1 ? "": "es"));
			return 0;
		}
	}
}

/* Return codes:
 * -1: Ctrl+D received as first character
 *  0: invalid guess (non-numeric or not 4 characters long)
 *	1: valid guess
 */
int validate_input(char *buf, char *guess)
{
	if (!buf || !buf[0]) {
		return -1;
	} else if (buf[0] == '\n') {
		return 0;
	} else if (strlen(buf) > 5) {
		fprintf(stderr, "Input too long!\n");
		return 0;
	} else if (strlen(buf) < 5) {
		fprintf(stderr, "Input too short!\n");
		return 0;
	}
	strncpy(guess, buf, DIGITS);
	guess[DIGITS+1] = '\0';
	for(int i=0; i < DIGITS; i++)
	{
		if (guess[i] < '0' || guess[i] > '9') {
			fprintf(stderr, "Non-numerical character detected.\n");
			return 0;
		}
	}
	return 1;
}

void check_guess(char *secret, char *guess, struct result *result)
{
	int digit_counts[10] = {0};
	for(int i=0; i < DIGITS; i++) digit_counts[secret[i]-48]++;

	*result = (struct result) { .red = 0, .white = 0 };
	// red check
	for(int i=0; i < DIGITS; i++)
	{
		if (guess[i] == secret[i]) {
			result->red++;
			digit_counts[guess[i]-'0']--;
		}
	}
	// white check
	for(int i=0; i < DIGITS; i++)
	{
		if (guess[i] != secret[i] && digit_counts[guess[i]-48]) {
			result->white++;
			digit_counts[guess[i]-'0']--;
		}
	}
}

int computer_play()
{
	/* TODO: use Knuth's algorithm
	 * Make first guess 0011
	 * For each possible code, figure out the minimum number of possible solutions it eliminates
	 * Guess the code that eliminates the most possible solutions
	 */
	struct code codes[10000] = {(struct code) {.flag = 1}};
	
	printf("Inside autoplay\n");
	printf("Flag of 0000: %i\n", (int)codes[0].flag);
	return 0;
}
