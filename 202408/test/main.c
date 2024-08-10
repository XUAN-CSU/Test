#include <stdio.h>
#include <stdlib.h>

int main()
{
	int a = 10;
	int *p = malloc(sizeof(int));
	
	p = &a;
	printf("%p\n", p);

	printf("Test a : = %d\n", a);
	printf("Size of int : %ld, Size of int * : %ld\n", sizeof(int), sizeof(int*));


	return 0;
}
