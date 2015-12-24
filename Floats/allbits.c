#include <stdio.h>
void print(int sgn,int exp,int mnt)
{
    if (exp == 255)
    {
        if (mnt == 0)
        {
            if (sgn == 0)
            {
                printf("+inf");
            }
            else
            {
                printf("-inf");
            }
        }
        else
        {
            printf("NaN");
        }
    }
    else
    {
        printf("(-1)^%d * 1.%d * 2 ^ %d", sgn, mnt, exp - 127);
    }
    printf("\n");
}
void floatBits1(float a)
{
    union lol
    {
        float a;
        int b;
    } q;
    q.a = a;
    int h = q.b;
    print((q.b >> 31) & 1,(q.b >> 23) & 255, q.b & (1 << 23) - 1);
}
void floatBits2(float a)
{
    union lol
    {
        float x;
        struct
        {
            unsigned int c:23;
            unsigned int b:8;
            unsigned int a:1;

        } y;
    } q;
    q.x = a;
    print((int) -q.y.a,(int) q.y.b,(int) q.y.c);

}
void floatBits3(float a)
{
    int tmp = *((int*)(&a));
    print((tmp >> 31) & 1,(tmp >> 23) & 255, tmp & (1 << 23) - 1);
}
int main()
{
    float a,b;
    scanf("%f%f",&a,&b);
    floatBits1(a/b);
    floatBits2(a/b);
    floatBits3(a/b);
    return 0;
}
