int logicalShift(int x,int n)
{
    int q=x>>n;
    int z=~((1<<31)>>n+~0);
    return z&q;
}
