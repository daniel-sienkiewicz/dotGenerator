// This is program to generate dot code from cflow file
#include "dotGenerator.h"

int main(int argc, char *argv[]){

	// Catching errors
	if (argc < 3) {
		printf ("Usage: %s C_PATH_FILE FUNCTION_NAME\n", argv[0]);
		exit (1);
	}

	// Execute cFlow
	cflowFunction(argv[1], argv[2]);
	
	// Creating DOT file with data
	createDotFile(&head, &tail, dotFile, argv[3], argv[4]);

	// DEBUG
	print(&head, &tail);

	return 0;
}