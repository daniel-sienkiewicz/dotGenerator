#ifndef DOTGENERATOR_H
#define DOTGENERATOR_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxFunctionName 1000
#define maxArgName 1000

// Function
struct object{
	struct object *next; // Next element in the list
	int spaceCout; // How many space - level in graph
	char name[maxFunctionName]; // Function name
	int lineNumber; // Line in which start this function
	int uniq; // if function in uniq in the list
	char arguments[maxArgName]; // list of function arguments
};

FILE *cflowFile;
FILE *dotFile;

struct object *head; // Head of the functions list
struct object *tail; // Tail of the functions list

// List of functions
void print(struct object **, struct object **);
void createDotFile(struct object **, struct object **, FILE *, char *, char *);
void insert(struct object **, struct object **, char [], int);
void prepareData(FILE *);
void cflowFunction(char *, char *);
void createPng();
void checkStatus(int);

// DEBUG function
// Printing all elements in list
void print(struct object **start, struct object **end){
	struct object *jumper;
	jumper = *start;
	printf("All functions:\n");
	while(jumper != NULL){
		printf("Name: %s Space: %i LineNumber: %i Args: %s\n", jumper->name, jumper->spaceCout, jumper->lineNumber, jumper->arguments);
		jumper = jumper->next;
	}
	printf("\n");
}

// Inserting new object into list
void insert(struct object **start, struct object **end, char name[], int spaceCout){
	int i = 0;
	int first = 0;

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

	i++;
	
	// Search argument list
	while(name[i] != 40){ // 40 = '('
		i++;
	}

	i++;

	while(name[i] != 41){ // 40 = ')'
		newObject->arguments[first] = name[i];
		i++;
		first++;
	}

	while(name[i] != 58 && i < maxFunctionName){
		i++;
	}

	// Search line numer
	if(i < maxFunctionName){
		i++;
		while(name[i] != 62){ // 62 = '>'
			newObject->lineNumber = newObject->lineNumber * 10 + (name[i] - 48);
			i++;
		}
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
	char arr[maxFunctionName];
	int spaceCout = 0;
	int iterator = 0;
	char name[maxFunctionName];
	int i;

	while(fgets(arr, maxFunctionName, cflowFile) != NULL){

		// Counting space char
		while(arr[iterator] == ' '){
			spaceCout++;
			iterator++;
		}

		//i = iterator;

		for(i = iterator; i < maxFunctionName; i++){
			name[i - iterator] = arr[i];
		}

		insert(&head, &tail, name, spaceCout);
		spaceCout = 0;
		iterator = 0;

		for(i = 0; i < maxFunctionName; i++){
			arr[i] = 0;
		}
	}
}

// Creating *.dot file - main algorithm
void createDotFile(struct object **start, struct object **end, FILE *dotFile, char *argv3, char *argv4){
	// Preparing data to insert in DOT file
	prepareData(cflowFile);

	struct object *jumper; // root
	struct object *tmp; // childrens
	jumper = *start;
	tmp = (*start)->next;

	// dot requrements in file
	fprintf(dotFile, "digraph FlowGraph {\nlabel=\"%s (%s)\";labelloc=t;labeljust=l;fontname=Helvetica;fontsize=10;fontcolor=\"#000000\";", jumper->name, jumper->arguments);

	if((argv3 != NULL && !strcmp(argv3, "line")) || (argv4 != NULL &&!strcmp(argv4, "line"))){
		fprintf(dotFile, "\t%s [label=\"line: %i\\n %s \" shape=ellipse, height=0.2,style=\"filled\", color=\"#000000\", fontcolor=\"#FFFFFF\"];\n", jumper->name, jumper->lineNumber, jumper->name);
	}else{
		fprintf(dotFile, "\t%s [label=\"%s\" shape=ellipse, height=0.2,style=\"filled\", color=\"#000000\", fontcolor=\"#FFFFFF\"];\n", jumper->name, jumper->name);
	}

	jumper = jumper -> next;

	while(jumper != NULL){
		if(jumper->uniq && jumper->lineNumber != 0){
			if((argv3 != NULL && !strcmp(argv3, "line")) || (argv4 != NULL &&!strcmp(argv4, "line"))){
				fprintf(dotFile, "\t%s [label=\"line: %i\\n %s\" shape=record];\n", jumper->name, jumper->lineNumber, jumper->name);
			}
			else{
				fprintf(dotFile, "\t%s [label=\"%s\" shape=record];\n", jumper->name, jumper->name);
			}
		}else{
			if(!strcmp(jumper->name,"exit") || !strcmp(jumper->name,"return")){
				fprintf(dotFile, "\t%s [label=\"%s\", shape=record, color=\"#FF00FF\", style=\"filled\",color=\"#FF0000\"];\n", jumper->name, jumper->name);
			}else{
				fprintf(dotFile, "\t%s [label=\"%s\", shape=record, color=\"#FF00FF\"];\n", jumper->name, jumper->name);
			}
		}
		jumper = jumper -> next;
	}

	jumper = *start;

	fprintf(dotFile, "\n");
	while(jumper != NULL){
		tmp = jumper->next;
		while(tmp != NULL && jumper->spaceCout != tmp->spaceCout){
			if(jumper->spaceCout + 4 == tmp->spaceCout){
				if((argv3 != NULL && !strcmp(argv3, "args")) || (argv4 != NULL &&!strcmp(argv4, "args"))){
					fprintf(dotFile, "\t%s -> %s [label=\"%s\", fontsize=\"8\"];\n", jumper->name, tmp->name, tmp->arguments);
				}
				else{
					fprintf(dotFile, "\t%s -> %s;\n", jumper->name, tmp->name);
				}
			}

			tmp = tmp ->next;
		}
		jumper = jumper -> next;
	}

	// dot requrements in file
	fprintf(dotFile, "}");

	// Closing opened files
	fclose(cflowFile);
	system("rm cflowFile");
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
	checkStatus(status);
}

void checkStatus(int status){
	if(status != 0){
		printf("Error %i\n", status);
		exit(1);
	}
}
#endif