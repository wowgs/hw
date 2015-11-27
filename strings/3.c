void six()
{
    printf("Type number of strings\n");
    int n;
    scanf("%d",&n);
    char otv[256];
    int x, i;
    char q;
    scanf("%c", &q);
    for (x = 0; x < 256; x++)
    {
        otv[x] = 0;
    }
    for (x = 0; x < n; x++)
    {
        scanf("%c", &q);
        i = 0;
        while (q != '\n')
        {
            otv[i] = ((int)otv[i]) ^ (int)q;
            i++;
            scanf("%c", &q);
        }
    }
    i = 0;
    while (otv[i] != 0)
    {
        printf("%c", otv[i]);
        i++;
    }
    printf("\n");
    return;
}
