#include <stdio.h>
union lol
{
    float a;
    int b;
};
int floatBits1(float a)
{
    union lol q;
    q.a = a;
    int h = q.b;
    int x;
    for (x = 31; x >=0; x--)
    {
        printf("%d", (h >> x) & 1);
    }
}
