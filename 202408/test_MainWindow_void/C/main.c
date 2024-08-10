#include <stdio.h>

int g_int_a = 10;

void foo()
{
    printf("This is foo()\n");
    g_int_a++;
}

void test()
{
    printf("Begin foo(), g_int_a : %d\n", g_int_a);
    void foo();
    printf("End foo(), g_int_a : %d\n", g_int_a);
}

int main()
{
    test();
    return 0;
}

