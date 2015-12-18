#include <stdio.h>

typedef struct lol
{
    int val;
    struct lol* right;
    struct lol* left;
    struct lol* par;
} lol;

lol head;
int size;

lol* findval(int x,lol* tmp)
{
    if (size == 0) return;
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
        return NULL;
    }
}

lol* findpar(int x, lol* tmp)
{
    if (size == 0) return;
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

void add(int x)
{
    if (size == 0)
    {
        head.val = x;
        size++;
        return;
    }
    if (findval(x, &head) == NULL)
    {
        lol* par = findpar(x , &head);
        lol* cur = (lol*) calloc(1,sizeof(lol));
        if (elem == NULL)
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
    size++;
}

void pop(int x)
{
    if (size == 0) return;
    lol* cur = findval(x,&head);
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
            if (cur == &head)
            {
                if (cur -> left == NULL)
                {
                    size--;
                    return;
                }
                else
                {
                    head.val = head.left -> val;
                    head.right = head.left -> right;
                    lol* del = head.left;
                    head.left = head.left -> left;
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
    size--;
}

void printleft(lol* tmp)
{
    if (size == 0)
    {
        printf("NULL");
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
    if (size == 0)
    {
        printf("NULL");
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
    if (size == 0)
    {
        printf("NULL");
        return;
    }
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

void kek()
{
    head.val = 0;
    head.right = NULL;
    head.left = NULL;
    head.par = NULL;
    size = 0;
}

int main()
{
    kek();
    int x;
    int d;
    for (x = 0; x < 5; x++)
    {
        scanf("%d",&d);
        add(d);
    }
    printright(&head);
    return 0;
}
