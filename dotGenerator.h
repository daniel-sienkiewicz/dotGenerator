#ifndef DOTGENERATOR_H
#define DOTGENERATOR_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxFunctionName 100
#define maxArgName 100
// Argument of function
struct sysFun{
	struct sysFun *next; // Next element in the list
	char name[maxArgName]; // Argument name
};

// Function
struct object{
	struct object *next; // Next element in the list
	int spaceCout; // How many space - lewel in graph
	char name[maxFunctionName]; // Function name
	int lineNumber; // Line in which start this function
	int uniq; // if function in uniq in the list
};

FILE *cflowFile;
FILE *dotFile;

struct object *head; // Head of the functions list
struct object *tail; // Tail of the functions list

struct sysFun *sysHead; // Head of the sysFun list
struct sysFun *sysTail; // Tail of the sysFun list

// List of functions
void print(struct object **, struct object **);
void init(struct sysFun **, struct sysFun **, char []);
int in(struct sysFun **, struct sysFun **, char []);
void createDotFile(struct object **, struct object **, FILE *);
void insert(struct object **, struct object **, char [], int);
void prepareData(FILE *);
void cflowFunction(char *, char *);
void startInit();
void createPng();
void checkStatus(int);

// DEBUG function
// Printing all elements in list
void print(struct object **start, struct object **end){
	struct object *jumper;
	jumper = *start;
	printf("All functions:\n");
	while(jumper != NULL){
		printf("Name: %s Space: %i LineNumber: %i\n", jumper->name, jumper->spaceCout, jumper->lineNumber);
		jumper = jumper->next;
	}
	printf("\n");
}

void init(struct sysFun **start, struct sysFun **end, char name[]){
	struct sysFun *newObject = NULL;
	newObject = (struct sysFun *)malloc(sizeof(struct sysFun));
	newObject->next = NULL;
	int i = 0;

	while(name[i] != '\0'){
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

void startInit(){
	// List of sample system functions
	init(&sysHead, &sysTail, "malloc");
	init(&sysHead, &sysTail, "sizeof");
	init(&sysHead, &sysTail, "fprintf");
	init(&sysHead, &sysTail, "printf");
	init(&sysHead, &sysTail, "fopen");
	init(&sysHead, &sysTail, "fclose");
	init(&sysHead, &sysTail, "fgets");
	init(&sysHead, &sysTail, "funkcja5");
}

// Inserting new object into list
void insert(struct object **start, struct object **end, char name[], int spaceCout){
	int i = 0, msc = 1;

	struct object *newObject = NULL;
	newObject = (struct object *)malloc(sizeof(struct object));
	newObject->next = NULL;

	newObject->spaceCout = spaceCout;
	newObject->lineNumber = 0;
	newObject->uniq = 1;

	// Search function name
	while(name[i] != 40) { // 40 = '('
		newObject->name[i] = name[i];
		i++;
	}

	//Search line number
	while(name[i] != 58){ // 58 = ':'
		i++;
	}

	i++;

	while(name[i] != 62){ // 62 = '>'
		newObject->lineNumber = newObject->lineNumber * msc + name[i] - 48;
		msc *= 10;
		i++;
	}

	struct object *jumper;
	jumper = *start;
	while(jumper != NULL){
		if(jumper->lineNumber == newObject->lineNumber)
			newObject->uniq = 0;
		jumper = jumper->next;
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

// Check if function is in system functions
int in(struct sysFun **start, struct sysFun **end, char name[]){
	int check = 1;
	struct sysFun *jumper;
	jumper = *start;
	
	while(jumper != NULL && check != 0){
		check = strcmp (name, jumper->name);
		jumper = jumper->next;
	}

	return !check;
}

// Creating *.dot file - main algorithm
void createDotFile(struct object **start, struct object **end, FILE *dotFile){
	startInit();
	// Preparing data to insert in DOT file
	prepareData(cflowFile);

	struct object *jumper; // root
	struct object *tmp; // childrens
	jumper = *start;
	tmp = (*start)->next;

	// dot requrements in file
	fprintf(dotFile, "digraph FlowGraph {\n");

	fprintf(dotFile, "\t%s [label=\"%s line: %i\" shape=ellipse, height=0.2,style=\"filled\", color=\"#000000\", fontcolor=\"#FFFFFF\"];\n", jumper->name, jumper->name, jumper->lineNumber);
	jumper = jumper -> next;

	while(jumper != NULL){
		if(jumper->uniq){
			if(in(&sysHead, &sysTail, jumper->name)){
				fprintf(dotFile, "\t%s [label=\"{<f0> %s|<f1> line: %i}\" shape=record, color=\"#0040FF\"];\n", jumper->name, jumper->name, jumper->lineNumber);
			}
			else
				fprintf(dotFile, "\t%s [label=\"{<f0> %s|<f1> line: %i}\" shape=record];\n", jumper->name, jumper->name, jumper->lineNumber);
		}
		jumper = jumper -> next;
	}

	jumper = *start;

	fprintf(dotFile, "\n");
	while(jumper != NULL){
		tmp = jumper->next;
		while(tmp != NULL && jumper->spaceCout != tmp->spaceCout){
			if(jumper->spaceCout + 4 == tmp->spaceCout){
				fprintf(dotFile, "\t%s -> %s;\n", jumper->name, tmp->name);
			}

			tmp = tmp ->next;
		}
		jumper = jumper -> next;
	}

	// dot requrements in file
	fprintf(dotFile, "}");

	// Closing opened files
	fclose(cflowFile);
	fclose(dotFile);
	createPng();
}

// Execute cFlow
void cflowFunction(char *argv, char *argv2){
	char command[BUFSIZ];
	int status = 0;


	strcpy (command, "cflow --output=cflowFile --main=");
	strcat (command, argv2);
	strcat (command, " ");
  	strcat (command, argv);

  	printf("\nExecuting: %s\n\n", command);
    status = system(command);
    checkStatus(status);

    // Opening needed files
	cflowFile = fopen ("cflowFile", "r");
	dotFile = fopen("out.dot", "w+");
	
	// Catching errors
	if (cflowFile == NULL || dotFile == NULL) {
		perror("Error: ");
		exit (1);
	}
}

// Creating PNG file and Cleaning up
void createPng(){
	int status = 0;
	printf("Generate PNG file and cleaning Up...\n\n");
	status = system("dot -Tpng out.dot > out.png");
	status = status + system("rm cflowFile out.dot");
	checkStatus(status);
}

void checkStatus(int status){
	if(status != 0){
		printf("Error\n");
		exit(1);
	}
}
#endif