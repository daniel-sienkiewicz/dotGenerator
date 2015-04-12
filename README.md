#*.dot file generator

##Files
* dotGenerator.c - C program which generate .dot file from cflow file

##Usage
~~~
$ ./dotGenerator C_FILE_PATH
~~~
###Example:
~~~
$ ./dotGenerator test.c
~~~

Now you can see graph of usage your function in [$outputImage](fileGenerator.sh)

##Requirements
* Cflow package
* dot package
* GCC compiler

##Author
[Daniel Sienkiewicz](mailto:sienkiewicz@project-midas.com)