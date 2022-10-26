#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Does the given char have a value representing a digit between 0 and 9?
bool is_char_digit(char character);

/* Reads a line from the standard input and saves it to array. Trims if line is longer than 100 characters
 *Returns:
 	* 0: Scanned succesfuly.
	*-1: Reached EOF.
	* 1: Had to trim the end.
 * If both condition -1 and 1 are fulfilled, -1 is returned as it has higher priority.
*/
int scan_line(char array[]);

// Parse string into numbers only format (see README). Ignoring all special and white characters
void parse_string(char input[], char output[]);

// A contact. In our input list it consists of a name and a phone number.
// Our program also adds a new value - the name parsed into number format.
typedef struct
{
	char name[101];			// Name of the contact
	char number[101];		// Phone number of the contact
	char parsedNumber[101];	// Parsed phone number of the contact
	char parsedName[101];	// Name parsed into number format (see README for details)
} contact;

bool is_char_digit(char character)
{
	if((int) character > 47 || character < 58)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int scan_line(char array[])
{
	char ln_of_chk;	// After reading a line, try to scan a character into this. If it is not \n, we didnt read the whole line.

	// Read line, if EOF, return -1
	if(scanf("%100[^\n]%c\n", array, &ln_of_chk) == EOF)
	{
		return -1;
	}

	// Check to see if whole line was read, or if it had overflown.
	// If it did indeed overflow, replace last three chars with ... to indicate incomplete entry and move on to the next line.
	// This does mean that these discarded characters will not be searchable, but I still find this approach more eloquent than just stopping the execution.
	if(ln_of_chk != '\n')
	{
		array[100] = array[99] = array[98] = '.';	// replace last three chars with ...
		scanf("%*[^\n]\n");	// skip to a new line
		return 1;
	}
	return 0;
}

void parse_string(char input[], char output[])
{
	int i, j;	// Since some characters from input arent saved into the output, the active index of them can be different.

	for(i = j = 0; i < strlen(input); i++)
	{
		if(strchr("0+", input[i]) != NULL)
		{
			output[j] = '0';
			j++;
		}
		else if(strchr("1", input[i]) != NULL)
		{
			output[j] = '1';
			j++;
		}
		else if(strchr("2aAbBcC", input[i]) != NULL)
		{
			output[j] = '2';
			j++;
		}
		else if(strchr("3dDeEfF", input[i]) != NULL)
		{
			output[j] = '3';
			j++;
		}
		else if(strchr("4gGhHiI", input[i]) != NULL)
		{
			output[j] = '4';
			j++;
		}
		else if(strchr("5jJkKlL", input[i]) != NULL)
		{
			output[j] = '5';
			j++;
		}
		else if(strchr("6mMnNoO", input[i]) != NULL)
		{
			output[j] = '6';
			j++;
		}
		else if(strchr("7pPqQrRsS", input[i]) != NULL)
		{
			output[j] = '7';
			j++;
		}
		else if(strchr("8tTuUvV", input[i]) != NULL)
		{
			output[j] = '8';
			j++;
		}
		else if(strchr("9wWxXyYzZ", input[i]) != NULL)
		{
			output[j] = '9';
			j++;
		}
	}
}

int main(int argc, char *argv[])
{
	bool reached_eof = false;	// Loop control variable for reading the input.
	int i;	// Iterator variable

	bool relaxedCheck;	// Corresponds to the -s command argument (view README for more info)
	int lvDist = 0;		// Max allowed Levenshtein distance
	int matches = 0;	// Number of matches found from contacts.
	char queryString[101];		// String of numbers to look for in contacts.

	// First we check all the parameters and take relevant info from it
	// Check whether the command received at least one parameter (string to look for).
	if(argc > 1)
	{
		// Set queryString from the parameter
		int query_length = strlen(argv[1]);	// Number of chars in query
		if(query_length > 100)
		{
			fprintf(stderr, "Fatal Error -2: Invalid query. Query longer than 100 digits.\n");
			return -2;
		}

		for(i = 0; i < query_length; i++)
		{
			// Check whether a given character is a digit and add it to queryString
			// If it is not, reject the query as it is not valid.
			if(is_char_digit(argv[1][i]))
			{
				queryString[i] = argv[1][i];
			}
			else
			{
				fprintf(stderr, "Fatal Error -2: Invalid query. %c is not a digit.\n", argv[1][i]);
				return -2;
			}
		}
	}
	else
	{
		fprintf(stderr, "Fatal Error -1: No query specified.\n");
		return -1;
	}

	// Go through command arguments and take appropriate actions (view README for more info on each argument)
	if(argc > 2)
	{
		for(i = 2; i < argc; i++)
		{
			// skip characters
			if(strcmp(argv[i], "-s") == 0)
			{
				printf("-s arg supplied\n");
			}
			// levenshtein distance
			if(strcmp(argv[i], "-l") == 0)
			{
				// Check if there is at least one more parameter after this one, if so, set the maximum levenshtein distance from it.
				if(argc > i + 1)
				{
					int j;
					int numOfDigits = strlen(argv[i+1]);

					// Check if the argument is made up of digits only
					for(j = 0; j < numOfDigits; j++)
					{
						if(!is_char_digit(argv[i+1][j]))
						{
							fprintf(stderr, "Fatal Error -4: Invalid argument. l distance must be a non-negative integer.\n");
						}
					}

					// If it passed the check, save it.
					lvDist = atoi(argv[i+1]); // if arg could not be converted to int, retrns 0.
				}
				{
					fprintf(stderr, "Fatal Error -3: No argument specified for -l\n");
					return -3;
				}
			}
		}
	}

	// Now we go through all the lines in the file and see if we can find any matches.
	while(!reached_eof)
	{
		char name[101] = {}, number[101] = {};	// Arrays for reading input.
		char parsedName[101] = {}, parsedNumber[101] = {};	// Arrays for parsed input (used for comparing with query).

		// Read name, if EOF, quit
		if(scan_line(name) == -1)
		{
			reached_eof = true;
			break;
		}
		// Read the number as well
		if(scan_line(number) == -1)
		{
			reached_eof = true;
			break;
		}

		// Convert the name and number into numbers representation
		parse_string(name, parsedName);
		parse_string(number, parsedNumber);

		printf("%s\n", name);
		printf("%s\n", parsedName);
		printf("%s\n", number);
		printf("%s\n", parsedNumber);
	}
}

