#*.dot file generator

##Usage
~~~
$ ./dotGenerator C_FILE_PATH FUNCTION_NAME line args
~~~

All nedded function are located in dotGenerator.h - [example](main.c). In your programm you should use if you would like get call graph:
~~~
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
~~~
or if you would like get caller graph:
~~~
// CALLER GRAPH PART
// Execute cFlow for Caller graph
cflowCallerFunction(argv[1]);
// Preparing data to insert in DOT file
prepareData(cflowFile);
// Creating caller graph
createCallerGraph(dotFile, 3, argv[2]);
// Creating PNG file
createPng();
// Cleaning up unnecessary files
cleanUp();
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
$ ./dotGenerator test.c createCallGrapha

Executing: cflow --output=cflowFile --main=createCallGrapha dotGenerator.c

Version: 3
Done
Generate PNG file and cleaning Up...
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