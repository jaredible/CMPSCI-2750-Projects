// Title	:reverser
// Description	:Store reversed lines of input file into output file. Lines are space seperated positive integers. Will not store number if number already exists on line when reading line from input file.
// Author	:Jared Diehl
// Date		:20190430
// Version	:1.0
// Usage	:./reverser [-i inputFileName] [-o outputFileName]
// Notes	:CMPSCI2750 Project4

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack.h"

#define MAX_LINE_LENGTH 80

/* Shows an optional error message, show usage, and exit with failure. */
void terminate(const char* exeName, const char* message)
{
	if (message != NULL) fprintf(stdout, "%s\n", message); // Display optional error message
	fprintf(stdout, "Usage: %s [-i inputFileName] [-o outputFileName]\n", exeName); // Display usage message
	exit(EXIT_FAILURE); // Exit with failure
}

/* Removes whitespace from beginning and ending of string parameter. */
char *trim(char *str)
{
	char *end;
	/* skip leading whitespace */
	while (isspace(*str))
		str++;
	
	/* remove trailing whitespace */
	end = str + strlen(str) - 1;
	while (end > str && isspace(*end))
		end--;
	
	/* write null character */
	*(end + 1) = '\0';
	return str;
}

/* Checks if string parameter is numeric. */
int isNumeric(const char *str)
{
	/* loop every char */
	while (*str != '\0')
	{
		if (*str < '0' || *str > '9') return 0; // if char not a digit
		str++;
	}
	return 1; // is numeric
}

/* Reverses lines of input file and outputs to an output file. Lines are space seperated positive integers. Will not store number if number already exists on line when reading line from input file. */
void reverse(const char *inputFileName, const char *outputFileName, char exeName[])
{
	FILE *inputFile = fopen(inputFileName, "r"); // Open input file
	FILE *outputFile = fopen(outputFileName, "a"); // Open output file
	
	if (inputFile != NULL) // Check if input file object exists
	{
		char line[MAX_LINE_LENGTH + 1]; // Create line buffer with a max value
		while (fgets(line, sizeof line, inputFile) != NULL) // Read line
		{
			struct Stack *stack = createStack(MAX_LINE_LENGTH / 2); // Create a stack for storing numbers
			
			char *token = strtok(trim(line), " "); // Get line and first token // TODO: Why removing trim() allows a non-digit to be found by isNumeric() below?
			while (token != NULL) // Loop through space seperated line
			{
				if (!isNumeric(token)) terminate(exeName, "Found a non-digit!"); // Check if token is numeric and if not terminate with error
				push(stack, atoi(token)); // Push token to stack
				token = strtok(NULL, " "); // Get next token
			}
			
			if (outputFile != NULL) // Check if output file object exists
			{
				while (!isEmpty(stack)) // Loop through stack until empty
				{
					fprintf(outputFile, "%d ", pop(stack)); // Write number to file and pop stack
				}
				
				fprintf(outputFile, "\n"); // New line
			}
			else
			{
				perror(outputFileName); // Display error of output file
				exit(EXIT_FAILURE); // Terminate
			}
			
			free(stack); // Remove stack from memory
		}
		
		fclose(inputFile); // Close input file connection
		if (outputFile != NULL) fclose(outputFile); // If output file object exists, close output file connection
	}
	else
	{
		perror(inputFileName); // Display error of input file
		exit(EXIT_FAILURE); // Terminate
	}
}

/* Declare main function */
int main(const int argc, char* const argv[])
{
	char* inputFileName = "input.txt"; // Initialize with default input file
	char* outputFileName = "output.txt"; // Initialize with default output file
	
	/* get options */
	int opt;
	while ((opt = getopt(argc, argv, "hi:o:")) != -1) // Get options using getopt
		switch (opt) // Switch statement for option
		{
			case 'h': // Print and exit before setting input and outputs
				fprintf(stdout, "Usage: %s [-i inputFileName] [-o outputFileName]\n", argv[0]); // Display usage message
				exit(EXIT_SUCCESS); // Exit with success
				break;
			case 'i':
				inputFileName = optarg; // If i chosen then inputFileName = that argument value
				break;
			case 'o':
				outputFileName = optarg; // If o chosen then outputFileName = that argument value
				break;
			default: /* ? */
				terminate(argv[0], "Unknown argument!"); // When an unknown argument is found, display usage message and terminate
				break;
		}
	
	if (access(inputFileName, F_OK) == -1) terminate(argv[0], "Input file does not exist!"); // Display usage message and terminate if input file doesn't exist
	
	if (optind != argc) terminate(argv[0], "Incorrect number of arguments!"); // Check if there are an incorrect amount of arguments and that they're mapped, if not, display usage message and terminate
	
	remove(outputFileName); // Remove output file
	
	reverse(inputFileName, outputFileName, argv[0]); // Reverse lines
	
	exit(EXIT_SUCCESS); // Exit with success
}
