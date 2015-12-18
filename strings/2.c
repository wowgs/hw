#define hash_const 31
#define size_of_arr 100003
#define max_str_size 256

unsigned int bin(int q)
{
    if (q == 0) return 1;
    if (q == 1) return hash_const;
    if (q % 2 == 1)
    {
        int j = bin(q / 2);
        return j * j * hash_const;
    }
    int j = bin(q / 2);
    return j * j;
}

int hash (char* s)
{
    unsigned int q = 0;
    int x = 0;
    while (*(s + x) != '\0')
    {
        q = (q + (bin(x) * (int)(*s + x)) % size_of_arr) % size_of_arr;
        x++;
    }
    return q;
}

void penta()
{
    int n;
    printf("Type number of strings\n");
    scanf("%d", &n);
    printf("Type strings:\n");
    int ar[size_of_arr];
    int h[n];
    char st[n][max_str_size];
    char q;
    scanf("%c", &q);
    int x, y, i;
    for (x = 0; x < size_of_arr; x++)
    {
        ar[x] = 0;
    }
    for (x = 0; x < n; x++)
    {
        i = 0;
        scanf("%c", &q);
        while (q != '\n')
        {
            st[x][i] = q;
            i++;
            scanf("%c", &q);
        }
        st[x][i] = '\0';
        h[x] = hash(st[x]);
        ar[h[x]]++;
    }
    i = 0;
    q = st[0][i];
    printf("The answer is:\n");
    for (x = 0; x < n; x++)
    {
        if (ar[h[x]] > 0)
        {
            i = 0;
            q = st[x][i];
            while (q != '\0')
            {
                printf("%c", q);
                i++;
                q = st[x][i];
            }
            printf(" - %d\n", ar[h[x]]);
            ar[h[x]] = 0;
        }
    }
    return;
}

int main()
{
    penta();
    return 0;
}
