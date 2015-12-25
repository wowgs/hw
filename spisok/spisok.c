#include <stdio.h>
typedef struct lol
{
    int num;
    struct lol *next;
} lol;

lol* add(lol* head)
{
    int d;
    scanf ("%d",&d);
    lol *elem = (lol*) malloc(sizeof(lol));
    if (elem == NULL)
    {
        printf("ALLAAAARM!!!!1!\a1");
        exit(-1);
    }
    elem -> num = d;
    elem -> next = head -> next;
    head -> next = elem;

}

lol* remove_elem(lol* head)
{
    int d;
    scanf ("%d",&d);
    lol *pr = head;
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
        }
    }
}

void print(lol* head)
{
    lol *pr = head -> next;
    while (pr != NULL)
    {
        printf("%d ",pr -> num);
        pr = pr -> next;
    }
    printf("\n");
}

void quit(lol* head)
{
    lol *pr = head;
    lol *del;
    while (pr -> next != NULL)
    {
        del = pr -> next;
        free (pr);
        pr = del;
    }
    free(pr);
    free(head);
    return 0;
}

void next()
{
    lol *head = (lol*) malloc(sizeof(lol));
    if (!head)
    {
        printf("Not enough memory");
        exit(1);
    }
    head -> next = NULL;
    char f;

    scanf("%c",&f);
    while (f != 'q')
    {
        if (f =='a')
        {
            add(head);
        }
        if (f == 'r')
        {
            remove_elem(head);
        }
        if (f == 'p')
        {
            print(head);
        }
        scanf(" %c",&f);
    }
    quit(head);
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
    return 0;
}
