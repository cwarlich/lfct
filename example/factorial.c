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
