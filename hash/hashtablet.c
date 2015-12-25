#include <stdio.h>
#include <time.h>
#define no_key -1;
const int MAX = 10000000;
const int SIZE = 100003;
const int small_SIZE = 1709;
const int lol_SIZE = 1;
const char min_mal = 'a';
const char max_mal = 'z';
const char min_big = 'A';
const char max_big = 'Z';
const char razn = 'a' - 'A';
typedef struct elem
{
    char *key;
    int val;
    struct elem *next;
} elem;

typedef struct hash_table
{
    int size;
    elem **arr;
    int (*hash_func)(char*);
} hash_table;

hash_table* create_new_hash_table(int (*hash_func)(char*), int length)
{
    hash_table *new_hash_table = (hash_table*) malloc (sizeof(hash_table));
    if (!new_hash_table)
    {
        printf("Not enough memory\a");
        exit(1);
    }
    new_hash_table -> size = length;
    new_hash_table -> arr = (elem**) calloc(length, sizeof(elem*));
    if (!(new_hash_table -> arr))
    {
        printf("Not enough memory\a");
        exit(1);
    }
    new_hash_table -> hash_func = hash_func;
    return new_hash_table;
}

void delete_hash_table(hash_table *h_t)
{
    int i;
    for (i = 0; i < h_t -> size; i++)
    {
        elem *tmp;
        elem *cur = (h_t -> arr) [i];
        while (cur)
        {
            tmp = cur -> next;
            free(cur);
            cur = tmp;
        }
    }
    free(h_t -> arr);
    free(h_t);
}

elem *new_elem(char* key,int val)
{
    elem *tmp = malloc(sizeof(elem));
    if (!tmp)
    {
        printf("Not enough memory\a");
        exit(1);
    }
    tmp -> key = strdup(key);
    tmp -> val = val;
    tmp -> next = NULL;
    return tmp;
}

void set(hash_table *h_t, char *key, int val)
{
    int cur_hash = (h_t -> hash_func)(key)  % (h_t -> size);
    if (cur_hash < 0) cur_hash = -cur_hash;
    elem *cur_elem = (h_t -> arr) [cur_hash];
    if (!cur_elem)
    {
        (h_t -> arr) [cur_hash] = new_elem(key,val);
    }
    else
    {
        elem *par;
        while (cur_elem)
        {
            if ((strcmp(cur_elem -> key, key)==0))
            {
                cur_elem -> val = val;
                return;
            }
            par = cur_elem;
            cur_elem = cur_elem -> next;
        }
        par -> next = new_elem (key, val);
    }
}

int get_val(hash_table *h_t, char* key)
{
    int cur_hash = (h_t -> hash_func)(key) % (h_t -> size);
    if (cur_hash < 0) cur_hash = -cur_hash;
    elem *tmp = (h_t -> arr) [cur_hash];
    while (tmp)
    {
        if ((strcmp(key,tmp -> key)==0))
        {
            return tmp -> val;
        }
        tmp = tmp -> next;
    }
    return no_key;
}

void delete_key(hash_table *h_t, char* key)
{
    int cur_hash = (h_t -> hash_func)(key) % (h_t -> size);
    if (cur_hash < 0) cur_hash = -cur_hash;
    elem *tmp = (h_t -> arr) [cur_hash];
    elem *last = NULL;
    if (!tmp) return;
    while (strcmp(key,tmp -> key)!=0)
    {
        if (!(tmp -> next))
        {
            return;
        }
        last = tmp;
        tmp = tmp -> next;
    }
    if (!last)
    {
        free(tmp);
        (h_t -> arr) [cur_hash] = NULL;
        return;
    }
    last -> next = tmp -> next;
    free(tmp);
}

void information(hash_table *h_t)
{
    float average = 0;
    int num_of_filled = 0;
    int all_words = 0;
    int max_length = 0;
    int min_length = MAX;
    int i;
    for (i = 0; i < h_t -> size; i++)
    {
        elem *tmp = (h_t -> arr) [i];
        int here = 0;
        while (tmp)
        {
            here++;
            all_words++;
            tmp = tmp -> next;
        }
        max_length = max_length > here ? max_length : here;
        if (here) min_length = min_length < here ? min_length : here;
        average = average + here;
        if (here) num_of_filled++;
    }
    average = average / num_of_filled;
    printf("\nSome statistic:\n");
    printf("Number of occupied chains - %d\n",num_of_filled);
    printf("Number of words - %d\n",all_words);
    printf("The average length of chain is - %f\n",average);
    printf("Maximum length of chain - %d\n",max_length);
    printf("Minimum length of chain - %d\n\n",min_length);
}

int HashRs(char *str)
{

	const unsigned int b = 378551;
	unsigned int a = 63689;
	unsigned int hash_cur = 0;

	for(; *str; str++)
	{
		hash_cur = hash_cur * a + (unsigned char)(*str);
		a *= b;
	}
	return hash_cur;

}

int hash_lol (char* s)
{
    return 0;
}

int hash_sum (char* s)
{
    int sum = 0;
    for (; *s; s++)
    {
        sum = sum +(int) *s;
    }
    return sum;
}

void add(hash_table *h_t, char* key)
{
    int cur_hash = (h_t -> hash_func)(key) % (h_t -> size);
    if (cur_hash < 0) cur_hash = -cur_hash;
    elem *tmp = (h_t -> arr) [cur_hash];
    if (!tmp) {(h_t -> arr) [cur_hash] = new_elem(key, 1);}
    else
    {
        elem *par;
        while (tmp!=NULL)
        {
            if ((strcmp(key, tmp -> key)==0))
            {
                (tmp -> val) ++;
                return;
            }

            par = tmp;
            tmp = tmp -> next;
        }
        par -> next = new_elem (key, 1);
    }
}

char check_char(char q)
{
    if ((q >= min_mal && q <= max_mal) | (q >= min_big && q <=max_big)) return 1;
    return 0;
}

void debug(hash_table *ht)
{
    printf("---DEBUG---\n");
    int i;
    for (i = 0; i < ht->size; ++i)
    {
        elem *item = ht->arr[i];
        if (item == NULL)
            continue;
        printf("%d: ", i);
        while (item != NULL)
        {
            printf("['%s', %d]->", item->key, item->val);
            item = item->next;
        }
        printf("NULL\n");
    }
    printf("---DEBUG---\n");
}

int main()
{
    FILE *text = freopen("text.in","r",stdin);
    if (!text)
    {
        printf("Error: cannot open input file");
        exit(1);
    }
    FILE *out_put = freopen("book.out","w",stdout);
    if (!out_put)
    {
        printf("Error: cannot open or rewrite output file");
        exit(1);
    }
    double start = clock();
    hash_table* h_t = create_new_hash_table(HashRs, SIZE);
    char q;
    char word[256];
    int i = 0;
    do
    {
        q = getchar();
        if (check_char(q))
        {
            if (q <= 'Z') q = q + razn;
            word[i] = q;
            i++;
        }
        else
        {
            if (i)
            {
                word[i] = 0;
                add(h_t, word);
            }
            i = 0;

        }

    } while (q!=EOF);
    information(h_t);
    printf("Time is - %f\n",(clock()-start)/CLOCKS_PER_SEC);
    return 0;

}
