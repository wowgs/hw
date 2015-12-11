#include <stdio.h>
void first()
{
    char ex, tmp;
    scanf("%c",&ex);
    while((tmp = getchar()) != EOF)
    {
        if (tmp != ex)
        {
            printf("%c",tmp);
        }
    }
}
int second(char* num1, char* num2)
{
    int x,l1,l2;
    for (x = 0; x > -1; x++)
    {
        printf("look - %c\n",*(num1 + x));
        if (*(num1 + x) == 0)
        {
            l1 = x;
            break;
        }
    }
    for (x = 0; x > -1; x++)
    {
        if (*(num2 + x) == 0)
        {
            l2 = x;
            break;
        }
    }
    printf("%d xuy %d \n",l1,l2);
    if (l1 > l2) return -1;
    if (l1 == l2)
    {
        for (x = 0; x < l1; x++)
        {
            if (*(num1 + x) > *(num2 + x))
            {
                return -1;
            }
            if (*(num1 + x) < *(num2 + x))
            {
                return 1;
            }
        }
        return 0;

    }
    return 1;
}
void third()
{
    FILE* f = fopen("input.txt","r");
    char a,b;
    a = 0;
    _Bool flag = 0;
    while ((b = fgetc(f)) != EOF)
    {
        if ((a == '/' && b == '/') && flag == 0)
        {
            flag = 1;
        }
        else
        {
            if (flag == 1)
            {
                printf("%c",b);
                if (b == '\n')
                {
                    flag = 0;
                }
            }
        }
        a = b;
    }
    fclose(f);
    return;
}
