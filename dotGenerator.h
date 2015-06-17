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
 *   License along with Box.  If not, see <http://www.gnu.org/licenses/>.   *
 ****************************************************************************/

/**
 * @file dotGenerator.h
 * @author Daniel Sienkiewicz
 * @date 10 May 2015
 * @brief File containing declarations of all functions.
 */

#ifndef DOTGENERATOR_H
#define DOTGENERATOR_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxFunctionName 1000 /**< Maximum function name*/
#define maxArgName 1000 /**< Maximum arguments length*/

/// Structure which describe function
struct object{
	int id; /**< Function id in the list*/
	struct object *next; /**< Next element in the list*/
	struct object *prev; /**< Prev element in the list*/
	int spaceCout; /**< How many space - level in graph*/
	char name[maxFunctionName]; /**< Function name*/
	int lineNumber; /**< Line in which start this function*/
	int uniq; /**< if function in uniq in the list*/
	char arguments[maxArgName]; /**< list of function arguments*/
};

FILE *cflowFile; /**< File with cflow data*/
FILE *dotFile; /**< Output file with dot code*/

struct object *head; /**< Head of the functions list*/
struct object *tail; /**< Tail of the functions list*/

// List of functions
/** 
* @details	DEBUG function Printing all elements in list
*/
void print();

/** 
* @details 	Creating *.dot file - creating call graph
* @param      	FILE *     file with cflow data
*/
void createCallGraph(FILE *, int);

/** 
* @details 	Creating *.dot file - creating caller graph
* @param      	FILE *     file with cflow data
*/
void createCallerGraph(FILE *, int, char *);

/** 
* @details 	Creating *.dot file - creating caller graph
* @param      	FILE *     file with cflow data
*/
void createCaller(struct object *, int);

/** 
* @details	Inserting new object into list
* @param   	char[] string with all function data
* \callgraph
*/
void insert(char [], int);

/** 
* @details	Creating list with names of executed functions
* @param    FILE *     file with cflow data
*/
void prepareData(FILE *);

/** 
* @details	Execute cFlow for call graph
* @param	char * char * argument to execute cflow
*/
void cflowFunction(char *, char *);

/** 
* @details	Execute cFlow for caller graph
* @param	char * char * argument to execute cflow
*/
void cflowCallerFunction(char *);

/** 
* @details Creating PNG file and Cleaning up
*/
void createPng();

/** 
* @details	Checking status of executed command
* @param	int status of exetucted commend to check
* @see      http://pl.wikibooks.org/wiki/C/system
*/
void checkStatus(int);

/** 
* @details	API - Return count of all used functions in list
* @return   Count of all functions in the list
*/
int countAllFunctions();

/** 
* @details	API - Delete main function list
*/
void deleteList();

/** 
* @details	API - Delete function with id
* @param    int id function to delete from list
*/
void deleteFunction(int);

/** 
* @details	DEBUG function Printing one fonction
* @param    struct object * struct of function to print
*/
void printOne(struct object *);

/** 
* @details	API - Return One function with ID
* @param    int id of function to find
* @return   structure with all function data
*/
struct object * getObject(int);

#endif /* DOTGENERATOR_H */