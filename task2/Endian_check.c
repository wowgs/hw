union lol
{
    int x;
    char q[sizeof(int)];
};
char* Endian_check(void)
{
    union lol b;
    b.x=1;
    return b.q[0] ? "little" : "big";
}
