#include <stdio.h>
#include <string.h>

#include "comm_type.h"

int foo(int a, int b)
{
    return a + b;
}
int main()
{
    int a = 10;
    int b = 20;
    int ret = foo(a, b);
    WLC_LOGI("WLC test function foo return, ret [%d]\n", ret);

    return 0;
}

