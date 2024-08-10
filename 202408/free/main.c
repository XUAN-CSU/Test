#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *buff;
	char ch[] = "wlc\0";
	buff = ch;
	printf("This is test for buff %s\n", buff);
	printf("This is test for buff %s\n", buff);
	free(buff);
	printf("This is test for buff %s\n", buff);

	return 0;
}
