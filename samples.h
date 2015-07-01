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
 * @file samples.h
 * @author Daniel Sienkiewicz
 * @date 22 June 2015
 * @brief File containing declarations of all sample functions.
 * @example
 */

#ifndef SAMPLES_H
#define SAMPLES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *cflowFile; /**< File with cflow data*/ 

/** 
* @details	Checking status of executed command
* @param	int status of exetucted commend to check
* @see      http://pl.wikibooks.org/wiki/C/system
*/
void checkStatus(int);

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
* @details	Creating list with names of executed functions
* @param    FILE *     file with cflow data
*/
void prepareData(FILE *);

/** 
* @details Creating PNG file
*/
void createPng();

/** 
* @details Cleaning up unnecessary files
*/
void cleanUp();

#endif /* SAMPLES_H */