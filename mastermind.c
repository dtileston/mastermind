#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <time.h>

#define DIGITS 4
#define BUFSIZE 100

struct result {
	char red;
	char white;
};

struct code {
	char flag;
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

	// Computer will play
	if(autoplay) {
		while(computer_play());
		return 0;
	}

	// Human will play
	char guess[DIGITS+1] = {'\0'};
	int guesses = 0;
	struct result result = {.red = 0 , .white = 0};
	int valid_guess = 0;

	while(1)
	{	
		valid_guess = 0;
		while(!valid_guess) {
			char buf[BUFSIZE] = {'\0'};
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
			break;
		}
	}
	return 0;
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
	// track how many of each digit are accounted for
	int digit_counts[10] = {0};
	for(int i=0; i < DIGITS; i++) digit_counts[secret[i]-'0']++;

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
	printf("Inside autoplay\n");
/*
	// Create the set S of 1296 possible codes, 1111,1112,.., 6666.
	struct code codes[10000] = {(struct code) {.flag = 1}};
	
	struct result result = { .red = 0, .white = 0 };

	// Start with initial guess 1122 (Knuth gives examples showing that some other first guesses such as 1123, 1234 do not win in five tries on every code).
	check_guess("1122", 
	while(result.red != 4) {

	//Play the guess to get a response of colored and white pegs.
	//If the response is four colored pegs, the game is won, the algorithm terminates.
	//Otherwise, remove from S any code that would not give the same response if it (the guess) were the code.
	//Apply minimax technique to find a next guess as follows: For each possible guess, that is, any unused code of the 1296 not just those in S, calculate how many possibilities in S would be eliminated for each possible colored/white peg score. The score of a guess is the minimum number of possibilities it might eliminate from S. A single pass through S for each unused code of the 1296 will provide a hit count for each colored/white peg score found; the colored/white peg score with the highest hit count will eliminate the fewest possibilities; calculate the score of a guess by using "minimum eliminated" = "count of elements in S" - (minus) "highest hit count". From the set of guesses with the maximum score, select one as the next guess, choosing a member of S whenever possible. (Knuth follows the convention of choosing the guess with the least numeric value e.g. 2345 is lower than 3456. Knuth also gives an example showing that in some cases no member of S will be among the highest scoring guesses and thus the guess cannot win on the next turn, yet will be necessary to assure a win in five.)
Repeat from step 3.
	 //For each possible code, figure out the minimum number of possible solutions it eliminates
	 //Guess the code that eliminates the most possible solutions

	}
	
	printf("Flag of 0000: %i\n", (int)codes[0].flag);
*/
	return 0;
}
