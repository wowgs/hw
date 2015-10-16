int sign(int x)
{
    int a = ~((x >> 31) & 1);
    a = a + a + !!x;
    return a + 2;
}
