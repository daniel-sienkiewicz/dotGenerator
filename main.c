#include "dotGenerator.h"

int main(int argc, char *argv[]){

	/// Catching errors
	if (argc < 3) {
		printf ("Usage: %s C_PATH_FILE FUNCTION_NAME\n", argv[0]);
		exit (1);
	}

	// Execute cFlow
	cflowFunction(argv[1], argv[2]);
	
	// Creating DOT file with data
	createDotFile(dotFile, 0);

	// DEBUG
	print();

	// Testing Api
	printf("API tests:\n");
	printf("All functions: %i\n", countAllFunctions());
	printf("Deleting list... ");
	deleteList();
	deleteFunction(15);

	// DEBUG
	print();

	printf("Search fuction: ");
	printOne(getObject(5));
	return 0;
}