#include <stdio.h>
void floatBits3(float a)
{
    int b,x;
    int *h;
    h = &a;
    b = *h;
    for (x = 31; x >= 0; x--)
    {
        printf("%d", (b >> x) & 1);
    }
    return;
}
