size_t my_strlen(char* src)
{
    int x = 0;
    while (*(src+x) != '\0')
    {
        x++;
    }
    return x;
}

int my_strcmp (char* s1, char* s2)
{
    int x;
    for (x = 0; x > -1; x++)
    {
        if (*(s1 + x) > *(s2 + x)) return 1;
        if (*(s2 + x) > *(s1 + x)) return -1;
        if (*(s1 + x) == '\0' && *(s2 + x) == '\0') return 0;
    }
}

void my_strcpy (char* dst, char* src)
{
    int x = 0;
    while (*(src + x) != '\0')
    {
        *(dst + x) = *(src + x);
        ++x;
    }
    *(dst + x) = *(src + x);
    return;
}

void my_strcat (char *dst, char* src)
{
    int x = 0, y = 0;
    while (*(dst + x) != '\0')
    {
        ++x;
    }
    while (*(src + y) != '\0')
    {
        *(dst + x + y) = *(src + y);
        ++y;
    }
    *(dst + x + y) = *(src + y);
    return;
}
