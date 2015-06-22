#*.dot file generator

##Usage
~~~
$ ./dotGenerator C_FILE_PATH FUNCTION_NAME line args
~~~

All nedded function are located in dotGenerator.h. In your programm you should use if you would like get call graph:
~~~
// Execute cFlow for call graph
cflowFunction(argv[1], argv[2]);
// Preparing data to insert in DOT file
prepareData(cflowFile);
// Creating call graph
createCallGraph(dotFile, 2);
// Creating PNG file
createPng();
~~~
or if you would like get caller graph:
~~~
// Execute cFlow for Caller graph
cflowCallerFunction(argv[1]);
// Preparing data to insert in DOT file
prepareData(cflowFile);
// Creating caller graph
createCallerGraph(dotFile, 2, argv[2]);
// Creating PNG file
createPng();
~~~

##Parameters
* 0 - only function name
* 1 - function name and arguments
* 2 - function name and arguments as arrows labels
* 3 - function name with line number and arguments as separate records

###Sample Compilation
~~~
$ gcc -Wall samples.c dotGenerator.c main.c -o dotGenerator
~~~

###Example execute:
~~~
$ ./dotGenerator test.c 0

Executing: cflow --output=cflowFile --main=funkcja1 test.c

Generate PNG file and cleaning Up...

All functions:
Name: funkcja1 Space: 0 LineNumber: 35 Args: 
Name: funkcja7 Space: 4 LineNumber: 10 Args: void
Name: funkcja4 Space: 8 LineNumber: 22 Args: void
Name: funkcja2 Space: 12 LineNumber: 32 Args: void
Name: funkcja7 Space: 8 LineNumber: 10 Args: void
Name: funkcja2 Space: 4 LineNumber: 32 Args: void
Name: funkcja3 Space: 4 LineNumber: 26 Args: void
Name: funkcja4 Space: 8 LineNumber: 22 Args: void
Name: funkcja2 Space: 12 LineNumber: 32 Args: void
Name: funkcja6 Space: 8 LineNumber: 15 Args: void
Name: funkcja1 Space: 12 LineNumber: 35 Args: 
~~~

Now you can see call graph/caller graph of usage your function in outputImage

##Requirements
* Cflow package
* dot package
* GCC compiler

##Documentation
[Link](http://dotgenerator.sienkiewicz.ovh/)
##Author
[Daniel Sienkiewicz](mailto:sienkiewicz@project-midas.com)