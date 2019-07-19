# Life Function Call Tree

This repository offers a small script that easily allows to print a program
run's life function call tree including its function parameter values.

## Getting Started

The script lfct (**l**ife **f**unction **c**all **t**ree) allows to print a
program run's function call tree, together with its function parameter values.
It may be used very similar to tools like *strace*, *ltrace*, *time*, ...:
Just prepend the command line of the program that you wish to get the life
function call tree from with the *lfct* script.

Run the *lfct* script without any parameters to obtain a more
comprehensive description of its usage.

### Prerequisites

The major requirement to use *lfct* with a program is that it must have been
compiled with the *-finstrument-functions* compiler switch, and that it must
contain debug symbols, i.e. it must also be compiled with the *-g* compiler
switch. 

Furthermore, the following tools (and its dependencies) must be availabe on
your system: *bash*, *gcc*, *gdb* and *awk*

### Installing

Just put the *lfct* script whereever you like and make it executable.

### Issues

It would be nice to also have the function return value printed on functioni
exit.

### Development

Have a look at the script, it is short and very well documented. And I'll
be happy to incooperate your improvements, just send a patch or a pull
request.

### Example

Suppose we have the folliwing code in ```factorial.c```:

```c
#include <stdlib.h>
#include <stdio.h>
int factorial(int i) {
	return i == 0 ? 1 : factorial(i - 1) * i;
}
void print(int i) {
	printf("%d\n", i);
	fflush(stdout);
}
int main(int argc, char *argv[]) {
	print(argc == 2 ? factorial(atoi(argv[1])) : -1);
	return 0;
}
```
We build it like this:

```
$ gcc -g -finstrument-functions -O0  factorial.c -o factorial
```

If we run it, it just prints the factorial of the number being passed:

```
$ ./factorial 4
24
```
If we run it under the control of *lfct*, we see the run's nicely formatted
function call tree with the program's output intermingled right at the very
location where it is printed:

```
$ ./lfct ./factorial 4
{ main(argc=2, argv=0x7fffffffe0a8) at /home/christof/Temp/fac.c:10
	{ factorial(i=4) at /home/christof/Temp/fac.c:3
		{ factorial(i=3) at /home/christof/Temp/fac.c:3
			{ factorial(i=2) at /home/christof/Temp/fac.c:3
				{ factorial(i=1) at /home/christof/Temp/fac.c:3
					{ factorial(i=0) at /home/christof/Temp/fac.c:3
					} factorial(i=0) at /home/christof/Temp/fac.c:4
				} factorial(i=1) at /home/christof/Temp/fac.c:4
			} factorial(i=2) at /home/christof/Temp/fac.c:4
		} factorial(i=3) at /home/christof/Temp/fac.c:4
	} factorial(i=4) at /home/christof/Temp/fac.c:4
	{ print(i=24) at /home/christof/Temp/fac.c:6
24
	} print(i=24) at /home/christof/Temp/fac.c:8
} main(argc=2, argv=0x7fffffffe0a8) at /home/christof/Temp/fac.c:12
[Inferior 1 (process 27656) exited normally]
(gdb) (gdb) 

```

Instead, you may just run ```make``` in the ```examples``` folder to run all
the steps described above.

Finally note that the function call tree is printed in green to distinghuish it
from the programs output. Unfortunately, github's Markdown interpreter has no
way to show this, which is why the example shown above is all in one color.

## Author

* **Christof Warlich**

## Acknowledgments

While the Web is full of rather half-hearted ideas on how to easily print a life
function call tree, two of them inspired me most:

* http://people.redhat.com/jkratoch/itrace.c

  This little C program almost does what my *lfct* script is doing: It prints
  a nicely looking function call tree of programs running under its
  control. Furthermore, it also requires these programs to contain debugging
  symbols and to be compiled with *-finstrument-functions*. But it only prints
  the function names without their current parameter values, significanty
  limiting its usefulness.

* https://stackoverflow.com/a/311912

  This answer shows how to employ gdb to get a list of all called functions
  with their parameter values. But since the functions are just a plain list,
  i.e. are not shown as a tree that clearly indicated which functions call
  which subfunctions, the output is hard to read to almost useless.

The approach that I have implemented just combines the two ideas above in a
rather polished way that makes it very easy to use. 
