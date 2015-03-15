// This is program to generate dot code from flow file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxFunctionName 100

struct object{
	struct object *next; // Next element in the list
	int spaceCout; // How many space - lewel in graph
	char name[maxFunctionName]; // Function name
};

struct object *head; // Head of the list
struct object *tail; // Tail fo teh list

// DEBUG function
// Printing all elements in list
void print(struct object **start, struct object **end){
	struct object *jumper;
	jumper = *start;
	while(jumper != NULL){
		printf("%i ", jumper->spaceCout);
		printf("%s \n", jumper->name);
		jumper = jumper->next;
	}
	printf("\n");
}

// Inserting new object into list
void insert(struct object **start, struct object **end, char name[], int spaceCout){
	int i = 0;

	struct object *newObject = NULL;
	newObject = (struct object *)malloc(sizeof(struct object));
	newObject->next = NULL;

	newObject->spaceCout = spaceCout;
	while(name[i] != 40) { // 40 = '('
		newObject->name[i] = name[i];
		i++;
	}

	//if list is empty
	if(*start == NULL){
		*start = newObject;
		(*start)->next = NULL;
		*end = *start;
		return;
	} else {
		(*end)->next = newObject;
		(*end) = newObject;
		return;
	}	
}

// Creating *.dot file - main algorithm
void createDotFile(struct object **start, struct object **end, FILE *dotFile){
	struct object *jumper; // root
	struct object *tmp; // childrens
	jumper = *start;
	tmp = (*start)->next;

	// dot requrements in file
	fprintf(dotFile, "strict graph {");

	while(jumper != NULL){
		tmp = jumper->next;
		while(tmp != NULL && jumper->spaceCout != tmp->spaceCout){
			if(jumper->spaceCout + 4 == tmp->spaceCout){
				fprintf(dotFile, "%s -- %s\n", jumper->name, tmp->name);
			}

			tmp = tmp ->next;
		}
		jumper = jumper -> next;
	}

	// dot requrements in file
	fprintf(dotFile, "}");	
}

// Creating list with names of executed functions
void prepareData(FILE *cflowFile){
	char arr[300];
	int spaceCout = 0;
	int iterator = 0;
	char name[maxFunctionName];
	int i;

	while(fgets(arr, 300, cflowFile) != NULL){
		
		// Counting space char
		while(arr[iterator] == ' '){
			spaceCout++;
			iterator++;
		}

		i = iterator;

		while(arr[i] != 41){ // 41 = ')'
			name[i - iterator] = arr[i];
			i++;
		}

		insert(&head, &tail, name, spaceCout);
		spaceCout = 0;
		iterator = 0;
	}
}

int main(int argc, char *argv[]){
	FILE *cflowFile;
	FILE *dotFile;

	// Catching errors
	if (argc < 2) {
		printf ("Usage: %s CFLOW file name\n", argv[0]);
		exit (1);
	}

	// Opening needed files
	cflowFile = fopen (argv[1], "r");
	dotFile = fopen("out.dot", "w+");

	// Catching errors
	if (cflowFile == NULL || dotFile == NULL) {
		perror("Error: ");
		exit (1);
	}

	prepareData(cflowFile);

	// DEBUG
	// print(&head, &tail);
	
	createDotFile(&head, &tail, dotFile);

	// Closing opened files
	fclose(cflowFile);
	fclose(dotFile);
	return 0;
}