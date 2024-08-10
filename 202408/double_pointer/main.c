#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int age;
    char ch;
} ST_PERSON;

int change_age(ST_PERSON *p, int age)
{
    if (NULL == p || age <= 0) {
        return -1;
    }

    p->age = age;
}

int main()
{
    // ST_PERSON p1 = {18, 'w'};
    ST_PERSON *p1 = (ST_PERSON *)malloc(sizeof(ST_PERSON));
    p1->age = 18;
    p1->ch = 'w';
    printf("Before chage, Person %c's age : %d\n", p1->ch, p1->age);
    change_age(p1, 20);
    printf("After change, Person %c's age : %d\n", p1->ch, p1->age);

    return 0;
}




