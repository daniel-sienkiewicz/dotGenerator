// This is program to generate dot code from cflow file
#include "dotGenerator.h"

int main(int argc, char *argv[]){

	// Catching errors
	if (argc < 2) {
		printf ("Usage: %s CFLOW file name\n", argv[0]);
		exit (1);
	}

	// Execute cFlow
	cflowFunction();
	
	// Creating DOT file with data
	createDotFile(&head, &tail, dotFile);

	// DEBUG
	print(&head, &tail);

	return 0;
}