#include <stdio.h>
#include <string.h>

int main()
{
    char src[] = "Hello,World!";
    char dest[10];
    printf("before strncpy src     : %s\n", src);
    strncpy(dest, src, 20);     // Dangerous: 20 > sizeof(dest)

    // Ensure null termination manually

    //printf("src     : %s\n", src);
    //printf("dest    : %s\n", dest);
    dest[sizeof(dest) - 1] = '\0';
    printf("after strncpy src      : %s\n", src);
    printf("after strncpy dest     : %s\n", dest);

    return 0;
}
