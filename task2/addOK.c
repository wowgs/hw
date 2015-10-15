int addOK(int a,int b)
{
    int x=a+b;
    int q=(x>>31)&1;
    int w=(a>>31)&1;
    int e=(b>>31)&1;
    return (!(q ^ w)) | (!(q ^ e));
}
