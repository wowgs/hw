int getByte(int x,int n)
{
    int q=(x>>(n<<3));
    return q&255;
}
