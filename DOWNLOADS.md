
# Downloads

# GIT repository


The GIT repository for dotGenerator is hosted on GitHub. In this repository you can be find the latest version of dotGenerator.

If you have GIT installed, you should do the following to get the initial copy of the repository:
~~~
git clone https://github.com/henio180/dotGenerator.git
cd dotGenerator
~~~

After that you can use
~~~
gcc -Wall dotGenerator.c main.c -o dotGenerator
~~~

Example execute:
~~~
$ ./dotGenerator test.c 0
~~~

Parameters
* 0 - only function name
* 1 - function name and arguments
* 2 - function name and arguments as arrows labels
* 3 - function name with line number and arguments as separate records

Public access to the GIT repository is read-only at the moment. So it is not possible to commit changes, but you can send me patches (use diff -u) if you think they should end up in the mainline, and I'll review and include them.