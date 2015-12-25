#include <stdio.h>

typedef struct lol
{
    int val;
    struct lol* right;
    struct lol* left;
    struct lol* par;
} lol;


lol* findval(int x,lol* tmp)
{
    if (tmp == NULL)
    {
        return NULL;
    }
    if (tmp -> val == x)
    {
        return tmp;
    }
    else
    {
        if (x > tmp -> val)
        {
            return findval(x, tmp -> right);
        }
        if (x < tmp -> val)
        {
            return findval(x, tmp -> left);
        }
    }
}

lol* findpar(int x, lol* tmp)
{
    if (tmp == NULL) return;
    lol* next;
    if (x > tmp -> val)
    {
        next = tmp -> right;
    }
    else
    {
        next = tmp -> left;
    }
    if (next == NULL)
    {
        return tmp;
    }
    else
    {
        return findpar(x, next);
    }
}

void add(int x,lol** head)
{
    if (!(*head))
    {
        *head = (lol*) malloc(sizeof(lol));
        if (!(*head))
        {
            printf("Not enough memory");
            exit(1);
        }
        (*head) -> val = x;
        (*head) -> left = NULL;
        (*head) -> right = NULL;
        (*head) -> par = NULL;
        return;
    }

    if (findval(x, *head) == NULL)
    {
        lol* par = findpar(x , *head);
        lol* cur = (lol*) calloc(1,sizeof(lol));
        if (cur == NULL)
        {
            printf("ALLAAAARM!!!!1!\a1");
            exit(-1);
        }
        cur -> val = x;
        cur -> par = par;
        if (x >= par -> val)
        {
            par -> right = cur;
        }
        else
        {
            par -> left = cur;
        }
    }
}

void pop(int x,lol** head)
{
    if (!(*head)) return;
    lol* cur = findval(x, *head);
    if (cur != NULL)
    {
        if (cur -> right != NULL)
        {
            lol* next = cur -> right;
            while (next -> left != NULL)
            {
                next = next -> left;
            }
            if (next -> par != cur)
            {
                next -> par -> left = next -> right;
            }
            else
            {
                cur -> right = next -> right;
            }
            cur -> val = next -> val;
            free (next);
        }
        else
        {
            if (cur == *head)
            {
                if (cur -> left == NULL)
                {
                    *head = NULL;
                    return;
                }
                else
                {
                    (*head) -> val = (*head) -> left -> val;
                    (*head) -> right = (*head) -> left -> right;
                    lol* del = (*head) -> left;
                    (*head) -> left = (*head) -> left -> left;
                    free(del);
                }
            }
            if (cur -> val >= cur -> par -> val)
            {
                cur -> par -> right = cur -> left;
                free (cur);
            }
            else
            {
                cur -> par -> left = cur -> left;
                free (cur);
            }
        }
    }
}

void printleft(lol* tmp)
{
    if (!tmp)
    {
        return;
    }
    if (tmp -> left != NULL)
    {
        printleft(tmp -> left);
    }
        printf("%d ",tmp -> val);
    if (tmp -> right != NULL)
    {
        printleft(tmp -> right);
    }
}

void printright(lol* tmp)
{
    if (!tmp)
    {
        return;
    }
    if (tmp -> right != NULL)
    {
        printright(tmp -> right);
    }
        printf("%d ",tmp -> val);
    if (tmp -> left != NULL)
    {
        printright(tmp -> left);
    }
}

void print(lol* tmp)
{
    if (tmp == NULL)
    {
        printf("NULL");
        return;
    }
    printf("(%d ",tmp -> val);
    print(tmp -> left);
    printf(" ");
    print(tmp -> right);
    printf(")");
}

int main()
{
    lol* head = NULL;
    int x;
    int d;
    for (x = 0; x < 5; x++)
    {
        scanf("%d",&d);
        add(d,&head);

    }
    print(head);
    printf("\n");
    pop(2,&head);
    print(head);
    printf("\n");
    printleft(head);
    printf("\n");
    printright(head);
    return 0;
}
