/*
*	Author xborov08
*	Title Project 1
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Does the given char have a value representing a digit between 0 and 9?
bool is_char_digit(char character);

// Does a given string contain the query substring?
// If skipchars is true, the query does not have to appear in one piece - can be scattered throughout.
bool string_contains_query(char string[], char query[], bool skipChars);

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

bool is_char_digit(char character)
{
	if((int) character > 47 && (int)character < 58)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool string_contains_query(char string[], char query[], bool skipChars)
{
	int i;
	int foundChars = 0;	// number of characters from the query that have been found in the string
	int queryLen = strlen(query);	// number of characters in the query

	// We will go through the entire string and each time we find a char from the query we increase the counter and go look for the next char (they have to bee in order)
	// Depending on skipChars we can reset foundChars and start searching anew once we find a non-matching char.
	for(i = 0; (long unsigned int) i < strlen(string); i++)
	{
		if(string[i] == query[foundChars])
		{
			foundChars++;

			// Last char has been found.
			if(foundChars == queryLen)
			{
				return true;
			}
		}
		// If skipping chars is not allowed and we have not found a match, return to start of querySearch + 1.
		else if (!skipChars)
		{
			i = i - foundChars; // set I t obeginning of current query + 1
			foundChars = 0; // reset query counter
		}
	}

	return false;
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

	// Go through all chars in input, if they match a character inputtable by t9 or a space, add their number to the output.
	for(i = j = 0; (long unsigned int) i < strlen(input); i++)
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
		else if(strchr(" ", input[i]) != NULL)
		{
			output[j] = ' ';
			j++;
		}
	}
}

int main(int argc, char *argv[])
{
	bool reached_eof = false;	// Loop control variable for reading the input.
	int i;	// Iterator variable

	bool relaxedCheck = false;	// Corresponds to the -s command argument (view README for more info)
	int matches = 0;	// Number of matches found from contacts.
	char queryString[101] = {};		// String of numbers to look for in contacts.

	// First we check all the parameters and take relevant info from it
	// Go through command arguments and take appropriate actions (view README for more info on each argument)
	if(argc > 1)
	{
		for(i = 1; i < argc - 1; i++)
		{
			// skip characters
			if(strcmp(argv[i], "-s") == 0)
			{
				relaxedCheck = true;
			}
			else
			{
				fprintf(stderr, "Fatal Error -3: Invalid argument. %s is not a valid argument.\n", argv[i]);
				return -3;
			}
		}

		// Set queryString from the parameter
		int query_length = strlen(argv[argc-1]);	// Number of chars in query
		if(query_length > 100)
		{
			fprintf(stderr, "Fatal Error -1: Invalid query. Query longer than 100 digits.\n");
			return -1;
		}

		for(i = 0; i < query_length; i++)
		{
			// Check whether a given character is a digit and add it to queryString
			// If it is not, reject the query as it is not valid.
			if(is_char_digit(argv[argc-1][i]))
			{
				queryString[i] = argv[argc-1][i];
			}
			else
			{
				fprintf(stderr, "Fatal Error -1: Invalid query. %c is not a digit.\n", argv[1][i]);
				return -1;
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

		// If the query is empty, or either the name or numbers match the query, print them on screen and increase the matches found counter.
		if(strlen(queryString) == 0 || string_contains_query(parsedName, queryString, relaxedCheck) || string_contains_query(parsedNumber, queryString, relaxedCheck))
		{
			matches++;
			printf("%s, %s\n", name, number);
		}
	}

	// If no matches have been found, print Not found message
	if(matches == 0)
	{
		printf("Not found\n");
	}
}

