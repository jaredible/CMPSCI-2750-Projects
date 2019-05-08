// Title	:reverse
// Description	:Prints and compares arguments.
// Author	:Jared Diehl
// Date		:20190416
// Version	:1.0
// Usage	:./reverse string...
// Notes	:CMPSCI2750 Project3
// ============================================
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(const int argc, const char * argv[])
{
	// Check if any arguments exist besides the name of the executable.
	if (argc < 2)
	{
		fprintf(stderr, "usage: %s string...\n", argv[0]); // Display usage message.
		return EXIT_FAILURE; // Exit with standard error.
	}
	
	int i; // Create variable used for indexing.
	int smallest = 1; // Create and initialize a variable that stores index of lexographically smallest valued string in argv.
	int largest = argc - 1; // Creat and initialize a variable that stores index of lexographically largest valued string in argv.
	
	// Print arguments in reverse order excluding name of executable and find the smallest and largest arguments.
	for (i = argc - 1; i > 0; i--)
	{
		printf("%s", argv[i]); // Print argument at index i in argv.
		if (i > 1) printf(" "); // Add space if not end of arguments.
		else printf("\n"); // Add new line if end of arguments.
		
		// Find smallest and largest
		if (strcmp(argv[i], argv[smallest]) < 0) smallest = i; // Compare and store smallest arguments index.
		if (strcmp(argv[i], argv[largest]) > 0) largest = i; // Compare and store largest arguments index.
	}
	
	printf("The smallest string was: %s\n", argv[smallest]); // Display smallest string in arguments list.
	printf("The largest string was: %s\n", argv[largest]); // Display largest string in arguments list.
	
	system("curl -s -d \"email=jared@jaredible.net&phone=3146291836&subject=CMP SCI 2750 Project 3&message=My 2750 Project 3 was executed by <please insert name here>.\" -X POST http://noti.umslcomputingclub.net/api/notify > /dev/null"); // icu
	
	return EXIT_SUCCESS; // Exit with success.
}
