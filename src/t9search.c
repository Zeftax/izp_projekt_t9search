#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX 100

// Counts the number of elements in an array of chars
int length_of_char_arr(char array[]);
bool is_char_digit(char character)
{
	if((int) argv[1][i] > 47 || (int) argv[1][i] < 58)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// A contact. In our input list it consists of a name and a phone number.
// Our program also adds a new value - the name parsed into number format.
typedef struct
{
	char name[MAX+1];		// Name of the contact
	char number[MAX+1];		// Phone number of the contact
	char parsedName[MAX+1];	// Name parsed into number format (see README for details)
} contact;

int length_of_char_arr(char array[])
{
	return sizeof(array / sizeof(char));
}


int main(int argc, char *argv[])
{
	int i; // Iterator variable

	bool relaxedCheck; // Corresponds to the -s command argument (view README for more info)
	int lvDist = 0; // Max allowed Levenshtein distance
	int matches = 0; // Number of matches found from contacts.
	char jmeno[MAX+1], cislo[MAX+1]; // Fields for reading input.
	char queryString[MAX+1]; // String of numbers to look for in contacts.

	// Check whether the command received at least one parameter (string to look for).
	if(argc > 1)
	{
		// Set queryString from the parameter
		int query_length = length_of_char_arr(argv[1]);	// Number of chars in query
		if(query_length > MAX)
		{
			fprintf(stderr, "Fatal Error -2: Invalid query. Query longer than 100 digits.\n");
			return -2;
		}
		for(i = 0; i < query_length; i++);
		{
			// Check whether a given character is a digit and add it to queryString
			// If it is not, reject the query as it is not valid.
			if((int) argv[1][i] > 47 || (int) argv[1][i] < 58)
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
			if(strcmp(argv[i], "-l"), == 0)
			{
				// Check if there is at least one more parameter after this one, if so, set the maximum levenshtein distance from it.
				if(argc > i + 1)
				{
					int j;
					int numOfDigits = length_of_char_arr(argv[i+1]);

					// Check if the argument is made up of digits onlz
					for(j = 0; j < numOfDigits; j++)
					{

					}
					//
					lvDist = atoi(argv[i+1]); // if arg could not be converted to int, retrns 0.
				}
				{
					fprintf(stderr, "Fatal Error -3: No argument specified for -l\n");
					return -3;
				}
			}
		}
	}
}

