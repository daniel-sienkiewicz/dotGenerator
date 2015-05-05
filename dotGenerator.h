#ifndef DOTGENERATOR_H
#define DOTGENERATOR_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxFunctionName 1000
#define maxArgName 1000

// Function
struct object{
	int id;
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
void print();
void createDotFile(FILE *, int);
void insert(char [], int);
void prepareData(FILE *);
void cflowFunction(char *, char *);
void createPng();
void checkStatus(int);
int countAllFunctions();
void deleteList();
void deleteFunction(int);
void printOne(struct object *);
struct object * getObject(int);


// DEBUG function
// Printing all elements in list
void print(){
	struct object *jumper;
	jumper = head;
	printf("All functions:\n");
	while(jumper != NULL){
		printOne(jumper);
		jumper = jumper->next;
	}
	printf("\n");
}

// DEBUG Print one function with arguments
void printOne(struct object * jumper){
	printf("ID: %i Name: %s Space: %i LineNumber: %i Args: %s\n", jumper->id, jumper->name, jumper->spaceCout, jumper->lineNumber, jumper->arguments);
}

// Inserting new object into list
void insert(char name[], int spaceCout){
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
	jumper = head;
	while(jumper != NULL){
		if(jumper->lineNumber == newObject->lineNumber)
			newObject->uniq = 0;
		newObject->id = jumper-> id + 1;
		jumper = jumper->next;
	}

	//if list is empty
	if(head == NULL){
		newObject->id = 1;
		head = newObject;
		(head)->next = NULL;
		tail = head;
		return;
	} else {
		(tail)->next = newObject;
		(tail) = newObject;
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

		for(i = iterator; i < maxFunctionName; i++){
			name[i - iterator] = arr[i];
		}

		insert(name, spaceCout);
		spaceCout = 0;
		iterator = 0;

		for(i = 0; i < maxFunctionName; i++){
			arr[i] = 0;
		}
	}
}

// Creating *.dot file - main algorithm
void createDotFile(FILE *dotFile, int version){
	printf("Version: %i\n", version);
	// Preparing data to insert in DOT file
	prepareData(cflowFile);

	struct object *jumper; // root
	struct object *tmp; // childrens
	jumper = head;
	tmp = (head)->next;

	// dot requrements in file
	fprintf(dotFile, "digraph FlowGraph {\n");
	
	if(version == 1 || version == 3){
		fprintf(dotFile, "label=\"%s (%s)\";labelloc=t;labeljust=l;fontname=Helvetica;fontsize=10;fontcolor=\"#000000\";", jumper->name, jumper->arguments);
		fprintf(dotFile, "\t%s [label=\"line: %i\\n %s \" shape=ellipse, height=0.2,style=\"filled\", color=\"#000000\", fontcolor=\"#FFFFFF\", fontname=Helvetica];\n", jumper->name, jumper->lineNumber, jumper->name);
	} else{
		fprintf(dotFile, "\t%s [label=\"%s\" shape=ellipse, height=0.2,style=\"filled\", color=\"#000000\", fontcolor=\"#FFFFFF\", fontname=Helvetica];\n", jumper->name, jumper->name);
	}

	jumper = jumper -> next;

	while(jumper != NULL){
		if(jumper->uniq && jumper->lineNumber != 0){
			if(version == 1){
				fprintf(dotFile, "\t%s [label=\"line: %i\\n %s\", shape=record, fontname=Helvetica];\n", jumper->name, jumper->lineNumber, jumper->name);
			} else{
				fprintf(dotFile, "\t%s [label=\"%s\", shape=record, fontname=Helvetica];\n", jumper->name, jumper->name);
			}
		} else{
			if(!strcmp(jumper->name,"exit") || !strcmp(jumper->name,"return")){
				fprintf(dotFile, "\t%s [label=\"%s\", shape=record, color=\"#FF00FF\", style=\"filled\",color=\"#FF0000\", fontname=Helvetica];\n", jumper->name, jumper->name);
			} else{
				fprintf(dotFile, "\t%s [label=\"%s\", shape=record, color=\"#FF00FF\", fontname=Helvetica];\n", jumper->name, jumper->name);
			}
		}
		jumper = jumper -> next;
	}

	jumper = head;

	fprintf(dotFile, "\n");
	while(jumper != NULL){
		tmp = jumper->next;
		while(tmp != NULL && jumper->spaceCout != tmp->spaceCout){
			if(jumper->spaceCout + 4 == tmp->spaceCout){
				if(version == 3){
					if(strcmp("", tmp->arguments)){
						fprintf(dotFile, "\t%s%s [label=\"%s\", fontsize=\"8\", fontname=Helvetica];\n", jumper->name, tmp->name, tmp->arguments);
						fprintf(dotFile, "\t%s -> %s%s ->%s;\n", jumper->name, jumper->name, tmp->name, tmp->name);
					} else{
						fprintf(dotFile, "\t%s -> %s;\n", jumper->name, tmp->name);
					}
				} else if(version == 2){
					fprintf(dotFile, "\t%s -> %s [label=\"%s\", fontsize=\"8\", fontname=Helvetica];\n", jumper->name, tmp->name, tmp->arguments);
				} else{
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

// Some API

// Return count of all used functions in list
int countAllFunctions(){
	struct object *jumper;
	jumper = head;
	int count = 0;

	while(jumper != NULL){
		count++;	
		jumper = jumper->next;
	}

	return count;
}

// Delete main function list
void deleteList(){
	//TO DO!!!!!!
	printf("Done\n");
}

// Delete function with id
void deleteFunction(int id){
	//TO DO!!!!!!!

	struct object *jumper;
	jumper = head;

	while(jumper != NULL){

		jumper = jumper->next;
	}

	if(jumper == NULL){
		printf("Function with ID: %i doesn't exist in list\n", id);
	}
}

// Return One function with ID
struct object * getObject(int id){
	struct object *jumper;
	jumper = head;

	while(jumper != NULL && jumper->id != id){
		jumper = jumper->next;
	}

	return jumper;
}

#endif