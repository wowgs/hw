int logicalShift(int x, int n)
{
    int q = x >> n;
    int j = !(n + ~0 + 1);
    int z = ~(((1 << 31) >> (n + ~0 + j)) << j);
    return q & z;
}
