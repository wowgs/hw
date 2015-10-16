int fitsBits(int x, int n)
{
    int a = x >> n + ~0;
    return ((!a) | (!~a));
}
