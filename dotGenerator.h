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
 * @file dotGenerator.h
 * @author Daniel Sienkiewicz
 * @date 22 June 2015
 * @brief File containing declarations of all functions.
 */

#ifndef DOTGENERATOR_H
#define DOTGENERATOR_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxFunctionName 1000 /**< Maximum function name length*/
#define maxArgName 1000 /**< Maximum function arguments length*/

/// Structure describing function
struct object{
	int id; /**< Function ID in the list*/
	struct object *next; /**< Next element in the list*/
	struct object *prev; /**< Prev element in the list*/
	int spaceCout; /**< How many space - level in graph*/
	char name[maxFunctionName]; /**< Function name*/
	int lineNumber; /**< Line in which start this function*/
	char arguments[maxArgName]; /**< Arguments*/
};

FILE *dotFile; /**< Output file with dot code*/

struct object *head; /**< Head of the functions list*/
struct object *tail; /**< Tail of the functions list*/

/** 
* @details	DEBUG function - Printing all elements in list
* \callgraph
*/
void print();

/** 
* @details 	Creating *.dot file with call graph
* @param      	FILE *     file with cflow data
* \callgraph
*/
void createCallGraph(FILE *, int);

/** 
* @details 	Creating *.dot file with caller graph
* @param      	FILE *     file with cflow data
* \callgraph
*/
void createCallerGraph(FILE *, int, char *);

/** 
* @details 	Creating *.dot file - creating caller graph
* @param      	FILE *     file with cflow data
* \callgraph
*/
void createCaller(struct object *, int, int *, FILE *);

/** 
* @details	Inserting new object into list
* @param   	char[] string with all function data
* \callgraph
*/
void insert(struct object *);

/** 
* @details	Checking if function was added to file
* @return   status if function was added to dot file
* \callgraph
*/
int in(int, int *, int *);

/** 
* @details	API - Return count of all used functions in list
* @return   Count of all functions in the list
* \callgraph
*/
int countAllFunctions();

/** 
* @details	API - Delete main function list
* \callgraph
*/
void deleteList();

/** 
* @details	API - Delete function with id
* @param    int id function to delete from list
* \callgraph
*/
void deleteFunction(int);

/** 
* @details	DEBUG - printing one function
* @param    struct object * struct of function to print
* \callgraph
*/
void printOne(struct object *);

/** 
* @details	API - Return One function with ID
* @param    int id of function to find
* @return   structure with all function data
* \callgraph
*/
struct object * getObject(int);

/** 
* @details	API - Return One function with name
* @param    char * name of function to find
* @return   structure with all function data
* \callgraph
*/
struct object * getObjectN(char *);

#endif /* DOTGENERATOR_H */