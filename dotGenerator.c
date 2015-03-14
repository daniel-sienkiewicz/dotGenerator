// This is program to generate dot code from flow file

#include <stdio.h>
#include <stdlib.h>

void printFile(FILE *clowFile){
	char arr[100];
	printf("\nCFLOW file:\n");
	while(fgets(arr, 100, clowFile) != NULL)
        printf("%s", arr);
}

int main(int argc, char *argv[]){
	FILE *clowFile;

	if (argc < 2) {
      fprintf (stderr, "Usage: %s CFLOW file name\n", argv[0]);
      exit (1);
    }

   clowFile = fopen (argv[1], "r");
   
    if (clowFile == NULL) {
      perror("Error: ");
      exit (1);
    }

    // DEBUG
    printFile(clowFile);

    fclose (clowFile);
	return 0;
}