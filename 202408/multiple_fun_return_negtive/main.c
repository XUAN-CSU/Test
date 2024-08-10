#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
    int h;
    int w;
} ST_INFO;

static int change_x(ST_INFO *p, int new_x)
{
    if (NULL == p || new_x < 0 ) {
        return -1;
    }

    p->x = new_x;
    return 0;
}

static int change_y(ST_INFO *p, int new_y)
{
    if (NULL == p || new_y < 0 ) {
        return -1;
    }

    p->y = new_y;
    return 0;
}

static int change_h(ST_INFO *p, int new_h)
{
    if (NULL == p || new_h < 0 ) {
        return -1;
    }

    p->h = new_h;
    return 0;
}

static int change_w(ST_INFO *p, int new_w)
{
    if (NULL == p || new_w < 0 ) {
        return -1;
    }

    p->w = new_w;
    return 0;
}

int change_parameter(ST_INFO *p)
{
    int ret = 0;
    if (change_x(p, 10) < 0)        ret += (-1 << 1);
    if (change_y(p, 20) < 0)        ret += (-1 << 1);
    if (change_h(NULL, 30) < 0)     ret += (-1 << 2);
    if (change_w(NULL, 40) < 0)     ret += (-1 << 3);
    if (change_w(NULL, 40) < 0)     ret += (-1 << 4);
    if (change_w(NULL, 40) < 0)     ret += (-1 << 5);

    return ret;
}

int main()
{
    ST_INFO *info = (ST_INFO*)malloc(sizeof(ST_INFO));

    int ret = change_parameter(info);
    if (ret < 0) {
        printf("ret of the change_parameter : %d\n", ret);
    } else {
        printf("INFO_x : %d\n", info->x);
        printf("INFO_y : %d\n", info->y);
        printf("INFO_h : %d\n", info->h);
        printf("INFO_w : %d\n", info->w);
    }

    return 0;
}


