/****************************************************************************
 * Copyright (C) 2015 by Daniel Sienkiewicz                                 *
 *                                                                          *
 * This file is part of dotGenerator                                        *
 *                                                                          *
 *   DotGenerator is free software: you can redistribute it and/or modify it*
 *   under the terms of the GNU Lesser General Public License as published  *
 *   by the Free Software Foundation, either version 3 of the License, or   *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   DotGenerator is distributed in the hope that it will be useful,        *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU Lesser General Public License for more details.                    *
 *                                                                          *
 *   You should have received a copy of the GNU Lesser General Public       *
 *   License along with Box. If not, see <http://www.gnu.org/licenses/>.    *
 ****************************************************************************/

/**
 * @file dotGesamples.c
 * @author Daniel Sienkiewicz
 * @date 22 June 2015
 * @brief File containing definicion of all sample functions.
 * @example
 */

#include "samples.h"
#include "dotGenerator.h"

void prepareData(FILE *cflowFile){
	char arr[maxFunctionName];
	int spaceCout = 0;
	int iterator = 0;
	char name[maxFunctionName];
	int i, first = 0, j = 0;

	while(fgets(arr, maxFunctionName, cflowFile) != NULL){

		// Counting space char
		while(arr[iterator] == ' '){
			spaceCout++;
			iterator++;
		}

		for(i = iterator; i < maxFunctionName; i++){
			name[i - iterator] = arr[i];
		}

		struct object *newObject = NULL;
		newObject = (struct object *)malloc(sizeof(struct object));
		newObject->spaceCout = spaceCout;

		j = 0;
		
		// Search function name
		while(name[j] != 40) { // 40 = '('
			newObject->name[j] = name[j];
			j++;
		}

		j++;
		
		// Search argument list
		while(name[j] != 40){ // 40 = '('
			j++;
		}

		j++;

		while(name[j] != 41){ // 40 = ')'
			newObject->arguments[first] = name[j];
			j++;
			first++;
		}

		while(name[j] != 58 && j < maxFunctionName){
			j++;
		}

		// Search line numer
		if(j < maxFunctionName){
			j++;
			while(name[j] != 62){ // 62 = '>'
				newObject->lineNumber = newObject->lineNumber * 10 + (name[j] - 48);
				j++;
			}
		}		

		insert(newObject);
		spaceCout = 0;
		iterator = 0;

		for(i = 0; i < maxFunctionName; i++){
			arr[i] = 0;
		}
	}
}

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

void cflowCallerFunction(char *argv){
	char command[BUFSIZ];
	int status = 0;

	strcpy (command, "cflow --output=cflowFile");
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

void createPng(){
	int status = 0;
	printf("Generate PNG file and cleaning Up...\n\n");
	status = system("dot -Tpng out.dot > out.png");
	checkStatus(status);
}