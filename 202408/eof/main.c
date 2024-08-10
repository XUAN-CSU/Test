#include <stdio.h>

void test()
{
	int ch;
	while ((ch = getc(stdin)) != EOF) {
		if (ch == 'w') 
			printf("%c\n", ch);
		else if (ch == '\n') {
			continue;
		} else {
			printf("Your character is : %c\n", ch);
		}
	}
	printf("Test while\n");
}
	int main()
{
	test();

	return 0;
}

