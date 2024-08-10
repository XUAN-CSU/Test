#include <stdio.h>
#include <stdlib.h>

int main()
{
	int a = rand() % 100;
	int b = rand() % 1000;
	int c = rand() % 10000;
	
	printf("rand() %% 100 : %d\n", a);
	printf("rand() %% 1000 : %d\n", b);
	printf("rand() %% 10000 : %d\n", c);
	return 0;
}
