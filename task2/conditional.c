int conditional(int x, int y, int z)
{
    return ((~!!x+1)&y)+((~!x+1)&z);
}
