#*.dot file generator

##Files
* fileGenerator.sh - main script which generate all needed files
* dotGenerator.c - C program which generate .dot file from cflow file

##Usage
~~~
$ sh fileGenerator.sh C_FILE_PATH FUNCTION_NAME
~~~
###Example:
~~~
$ sh fileGenerator.sh test1.c funkcja1

Creating CFLOW file... OK
Compilation... OK
Creating .dot file... OK

The end
~~~

###Help
~~~
$ sh fileGenerator.sh --help
 - attempt to capture frames
 
 [options] application [arguments]
 
options:
-h, --help              show brief help
-c, --compile=FILE      compile dot Generator
~~~

Now you can see graph of usage your function in [$outputImage](fileGenerator.sh)

##Requirements
* Cflow package
* dot package
* GCC compiler
* Bash

##Author
[Daniel Sienkiewicz](mailto:sienkiewicz@project-midas.com)