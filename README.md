#*.dot file generator

##Files
* dotGenerator.c - C program which generate .dot file from cflow file

##Usage
~~~
$ ./dotGenerator C_FILE_PATH FUNCTION_NAME line args
~~~

All nedded function are located in [dotGenerator.h](dotGenerator.h). In your programm you should use:
~~~
// Execute cFlow
cflowFunction(argv[1], argv[2]);

// Creating DOT file with data
createDotFile(&head, &tail, dotFile);
~~~

##Parameters
* line - insertline numbers
* args - insert function arguments 
~~~
$ ./dotGenerator test.c funkcja1 line args
~~~

###Example:
~~~
$ ./dotGenerator test.c funkcja1 line args

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

Now you can see graph of usage your function in outputImage

##Requirements
* Cflow package
* dot package
* GCC compiler

##Author
[Daniel Sienkiewicz](mailto:sienkiewicz@project-midas.com)