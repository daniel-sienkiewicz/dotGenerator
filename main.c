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
 * @file main.c
 * @author Daniel Sienkiewicz
 * @date 22 June 2015
 * @brief File containing sample main file.
 * @example
 */

#include "dotGenerator.h"
#include "samples.h"

int main(int argc, char *argv[]){

	/// Catching errors
	if (argc < 3) {
		printf ("Usage: %s C_PATH_FILE FUNCTION_NAME\n", argv[0]);
		exit (1);
	}

	// CALL GRAPH PART
	// Execute cFlow for call graph
	cflowFunction(argv[1], argv[2]);
	// Preparing data to insert in DOT file
	prepareData(cflowFile);
	// Creating call graph
	createCallGraph(dotFile, 3);
	// Creating PNG file
	createPng();
	// Cleaning up unnecessary files
	cleanUp();
	
	// CALLER GRAPH PART
	// Execute cFlow for Caller graph
	//cflowCallerFunction(argv[1]);
	// Preparing data to insert in DOT file
	//prepareData(cflowFile);
	// Creating caller graph
	//createCallerGraph(dotFile, 3, argv[2]);
	// Creating PNG file
	//createPng();
	// Cleaning up unnecessary files
	//cleanUp();

	// Testing API
/*	printf("API tests:\n");
	print();
	printf("All functions: %i\n", countAllFunctions());
	printf("Search fuction: ");
	printOne(getObject(5));
	printf("Deleting list... ");
	deleteList();
	printf("All functions: %i\n", countAllFunctions());
*/	
	return 0;
}