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
	int uniq; /**< If function is uniq in the list*/
	char arguments[maxArgName]; /**< Arguments*/
};

/// Structure describing functions names
struct names{
	char name[maxFunctionName]; /**< Function name*/
	struct names *next; /**< Next element in the list*/
	struct names *prev; /**< Prev element in the list*/
};

FILE *cflowFile; /**< File with cflow data*/
FILE *dotFile; /**< Output file with dot code*/

struct object *head; /**< Head of the functions list*/
struct object *tail; /**< Tail of the functions list*/

struct names *headN; /**< Head of the names list*/
struct names *tailN; /**< Tail of the names list*/

/** 
* @details	DEBUG function - Printing all elements in list
*/
void print();

/** 
* @details 	Creating *.dot file with call graph
* @param      	FILE *     file with cflow data
*/
void createCallGraph(FILE *, int);

/** 
* @details 	Creating *.dot file with caller graph
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
void insert(struct object *);

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
* @details	DEBUG - printing one function
* @param    struct object * struct of function to print
*/
void printOne(struct object *);

/** 
* @details	API - Return One function with ID
* @param    int id of function to find
* @return   structure with all function data
*/
struct object * getObject(int);

/** 
* @details	API - Return One function with name
* @param    char * name of function to find
* @return   structure with all function data
*/
struct object * getObjectN(char *);

/** 
* @details	API - Return list with names of all functions
* @return   structure with all functions names
*/
struct names * getAllNames();

#endif /* DOTGENERATOR_H */