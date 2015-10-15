int bang(int x)
{
    int a=((x>>31)&1);
    int b=((~(x)+1)>>31)&1;
    return 2 + ~(a | b);
}
