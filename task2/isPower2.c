int isPower2(int x)
{
    int a=!!x;
    int b=!((x>>31)&1);
    int q=~(x)+1;
    int c=!((q|x)+~(~x+1)+1);
    return a&b&c;
}
