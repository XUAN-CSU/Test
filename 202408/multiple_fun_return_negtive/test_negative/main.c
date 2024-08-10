#include <stdio.h>

void test()
{
    int a = -1;
    int b = 0;
     b = a << 1;
     printf("a : %d\n", a);
     printf("b : %d\n", b);
}

int main()
{
    test();
    
    return 0;
}
