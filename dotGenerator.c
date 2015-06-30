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
 * @file dotGenerator.c
 * @author Daniel Sienkiewicz
 * @date 22 June 2015
 * @brief File containing definicion of all functions.
 */

#include "dotGenerator.h"

void insert(struct object * newObject){
	struct object *jumper = (struct object *)malloc(sizeof(struct object));
	newObject->next = NULL;
	newObject->uniq = 1;

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
		(head)->prev = NULL;
		tail = head;
		tail->next = NULL;
		tail->prev = NULL;
		free(jumper);
		return;
	} else {
		(tail)->next = newObject;
		newObject->prev = tail;
		(tail) = newObject;
		free(jumper);
		return;
	}
}

void createCallGraph(FILE *dotFile, int version){
	printf("Version: %i\n", version);

	struct object *jumper = (struct object *)malloc(sizeof(struct object)); // root
	struct object *tmp = (struct object *)malloc(sizeof(struct object)); // childrens
	jumper = head;
	tmp = (head)->next;

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

	fprintf(dotFile, "}");

	// Cleaning up
	fclose(cflowFile);
	system("rm cflowFile");
	fclose(dotFile);
	free(jumper);
	free(tmp);
	deleteList();
}

void createCaller(struct object * ob, int version){
	struct object *jumper = ob;

	while(jumper->spaceCout != 0){
		while(ob->spaceCout - jumper->spaceCout == 0){
			jumper = jumper->prev;
		}

		if(version == 3){
			fprintf(dotFile, "\t%s [label=\"%s\", shape=record, fontname=Helvetica];\n", jumper->name, jumper->name);
			if(strcmp("", ob->arguments)){
				fprintf(dotFile, "\t%s%s [label=\"%s\", fontsize=\"8\", fontname=Helvetica];\n", jumper->name, ob->name, jumper->arguments);
				fprintf(dotFile, "\t%s -> %s%s ->%s;\n", jumper->name, jumper->name, ob->name, ob->name);
			} else{
				fprintf(dotFile, "\t%s -> %s;\n", jumper->name, ob->name);
			}
		} else if(version == 2){
			fprintf(dotFile, "\t%s [label=\"%s\", shape=record, fontname=Helvetica];\n", jumper->name, jumper->name);
			fprintf(dotFile, "\t%s -> %s [label=\"%s\", fontsize=\"8\", fontname=Helvetica];\n", jumper->name, ob->name, ob->arguments);
		} else{
			fprintf(dotFile, "\t%s [label=\"line: %i\\n %s\", shape=record, fontname=Helvetica];\n", jumper->name, jumper->lineNumber, jumper->name);
			fprintf(dotFile, "\t%s -> %s;\n", jumper->name, ob->name);
		}

		ob = jumper;		
	}
}

void createCallerGraph(FILE *dotFile, int version, char *argv2){
	printf("Version: %i\n", version);

	struct object *jumper = (struct object *)malloc(sizeof(struct object)); // root
	jumper = head;
	
	fprintf(dotFile, "digraph FlowGraph {\n");

	if(version == 1 || version == 3){
		fprintf(dotFile, "label=\"%s (%s)\";labelloc=t;labeljust=l;fontname=Helvetica;fontsize=10;fontcolor=\"#000000\";", getObjectN(argv2)->name, getObjectN(argv2)->arguments);
		fprintf(dotFile, "\t%s [label=\"line: %i\\n %s \" shape=ellipse, height=0.2,style=\"filled\", color=\"#000000\", fontcolor=\"#FFFFFF\", fontname=Helvetica];\n", getObjectN(argv2)->name, getObjectN(argv2)->lineNumber, getObjectN(argv2)->name);
	} else{
		fprintf(dotFile, "\t%s [label=\"%s\" shape=ellipse, height=0.2,style=\"filled\", color=\"#000000\", fontcolor=\"#FFFFFF\", fontname=Helvetica];\n", getObjectN(argv2)->name, getObjectN(argv2)->name);
	}

	fprintf(dotFile, "\n");
	while(jumper != NULL){
		if(!strcmp(jumper->name, argv2)){
			createCaller(jumper, version);
		}
		jumper = jumper -> next;
	}

	fprintf(dotFile, "}");

	// Cleaning up
	fclose(cflowFile);
	system("rm cflowFile");
	fclose(dotFile);
	free(jumper);
	deleteList();
}

void checkStatus(int status){
	if(status != 0){
		printf("Error %i\n", status);
		exit(1);
	}
}

// Some API
int countAllFunctions(){
	struct object *jumper = (struct object *)malloc(sizeof(struct object));
	jumper = head;
	int count = 0;

	while(jumper != NULL){
		count++;	
		jumper = jumper->next;
	}
	
	free(jumper);
	return count;
}

void deleteList(){
	struct object *jumper = (struct object *)malloc(sizeof(struct object));
	struct object *tmp = (struct object *)malloc(sizeof(struct object));
	jumper = head;

	while(jumper != NULL){
		tmp = jumper;
		jumper = jumper->next;
		deleteFunction(tmp->id);
	}

	free(jumper);
	printf("Done\n");
}

void deleteFunction(int id){
	struct object *jumper = (struct object *)malloc(sizeof(struct object));
	struct object *tmp = (struct object *)malloc(sizeof(struct object));
	
	if(head->id == id){
		tmp = head;
		head = head->next;
		free(tmp);		
	} else{
		for(jumper = head; jumper->next != NULL; jumper = jumper -> next){
			if(jumper->next->id == id){
				tmp = jumper->next;
				if(jumper->next->next != NULL)
					jumper->next = jumper->next->next;
				else{
					jumper->next = tail;
				}
				free(tmp);	
			}
		}
	}
	free(jumper);
}

struct object * getObject(int id){
	struct object *jumper = (struct object *)malloc(sizeof(struct object));
	jumper = head;

	while(jumper != NULL && jumper->id != id){
		jumper = jumper->next;
	}

	return jumper;
}

struct object * getObjectN(char *argv2){
	struct object *jumper = (struct object *)malloc(sizeof(struct object));
	jumper = head;

	while(jumper != NULL && strcmp(jumper->name, argv2)){
		jumper = jumper->next;
	}

	return jumper;
}

void print(){
	struct object *jumper = (struct object *)malloc(sizeof(struct object));
	jumper = head;
	printf("All functions:\n");
	while(jumper != NULL){
		printOne(jumper);
		jumper = jumper->next;
	}
	printf("\n");
	free(jumper);
}

void printOne(struct object * jumper){
	if(jumper != NULL){
		printf("ID: %i Name: %s Space: %i LineNumber: %i Args: %s\n", jumper->id, jumper->name, jumper->spaceCout, jumper->lineNumber, jumper->arguments);
	} else{
		printf("NULL\n");
	}
}

struct names * getAllNames(){
	struct object * jumper = (struct object *)malloc(sizeof(struct object));
	jumper = head;
	while(jumper != NULL){
		struct names * one = (struct names *)malloc(sizeof(struct names));
	
		//one->name = jumper->name;
		
		//if list is empty
		if(head == NULL){
			headN = one;
			(headN)->next = NULL;
			(headN)->prev = NULL;
			tailN = headN;
			tailN->next = NULL;
			tailN->prev = NULL;
		} else {
			(tailN)->next = one;
			one->prev = tailN;
			(tailN) = one;
		}
		
		jumper = jumper->next;
	}

	free(jumper);
	return headN;
}