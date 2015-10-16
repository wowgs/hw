int bitXor(int a, int b)
{
    int z = (~a) & b;
    int t = (~b) & a;
    return ~(~z & ~t);
}
