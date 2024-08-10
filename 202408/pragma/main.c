#include <stdio.h>

typedef struct {
	char ch;
	int age;
} ST_PERSON;

#pragma pack(8)
typedef struct {
	char ch;
	int age;
} ST_STUDENT;
#pragma pack()

int main()
{
	ST_PERSON p1;
	ST_STUDENT s1;
	printf("size with no pragma: %ld\n", sizeof(p1));
	printf("size with pragma: %ld\n", sizeof(s1));

	return 0;
}
