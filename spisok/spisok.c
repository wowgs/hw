#include <stdio.h>
typedef struct lol
{
    int num;
    struct lol *next;
} lol;

lol head;
lol* last = &head;

int d;

void a()
{
    scanf ("%d",&d);
    lol *elem = (lol*) malloc(sizeof(lol));
    if (elem == NULL)
    {
        printf("ALLAAAARM!!!!1!\a1");
        exit(-1);
    }
    elem -> num = d;
    elem -> next = NULL;
    last -> next = elem;
    last = elem;
}

void r()
{
    scanf ("%d",&d);
    lol *pr = &head;
    if (pr -> next != 0)
    {
        while (pr -> next -> num != d)
        {
            pr = pr -> next;
            if (pr -> next == NULL) break;
        }
        if (pr -> next != NULL)
        {
            lol *qwe = pr -> next -> next;
            free(pr -> next);
            pr -> next = qwe;
            if (qwe == NULL) last = pr;
        }
    }
}

void p()
{
    lol *pr = head.next;
    while (pr != NULL)
    {
        printf("%d ",pr -> num);
        pr = pr -> next;
    }
    printf("\n");
}

void q()
{
    lol *pr = &head;
    lol *del;
    while (pr -> next != NULL)
    {
        del = pr -> next;
        free (pr);
        pr = del;
    }
    free (last);
    return 0;
}

void next()
{
    head.next = NULL;
    char f;

    scanf("%c",&f);
    while (f != 'q')
    {
        if (f =='a')
        {
            a();
        }
        if (f == 'r')
        {
            r();
        }
        if (f == 'p')
        {
            p();
        }
        scanf(" %c",&f);
    }
    q();
    return 0;
}

int find_cycle(lol *first)
{
    lol *fast, *slow;
    fast = first;
    slow = first;
    int pause = 0;
    while (1)
    {
        if (!fast)
            return 0;
        if (pause)
            slow = slow -> next;
        pause = !pause;
        fast = fast -> next;
        if (fast == slow)
            return 1;
    }
}
int main()
{
    next();
}
