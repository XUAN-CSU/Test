#include <stdio.h>

int test(int a)
{
	return a + 2;
}

int main()
{
	int a = 10;
	printf("a : %d\n", a);
	a = test(a);
	printf("a : %d\n", a);

	return 0;
}

