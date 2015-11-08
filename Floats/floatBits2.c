#include <stdio.h>
struct ints
{
    unsigned int c:23;
    unsigned int b:8;
    unsigned int a:1;

};
union lol
{
    float x;
    struct ints y;
};
void floatBits2(float a)
{
    union lol q;
    q.x = a;
    int i;
    printf("%d",q.y.a & 1);
    for (i = 7; i >= 0; i--)
    {
        printf("%d",(q.y.b >> i) & 1);
    }
    for (i = 22; i >= 0; i--)
    {
        printf("%d",(q.y.c >> i) & 1);
    }
    return;
}
