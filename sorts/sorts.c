#include <stdio.h>
#include <stdlib.h>
#include <time.h>
const int num_of_tests = 9;
const int size_of_arrays[] = {5, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};
const int module = 100000;

void count_sort(int* arr, int size)
{
    int *count_array = (int*) malloc((module + 0) * sizeof(int));
    if (count_array == NULL)
    {
        printf("Not enough memory\a");
        exit(-1);
    }
    int x, y = 0;
    for (x = 0; x < size; x++)
    {
        count_array[arr[x]]++;
    }
    free(count_array);
}

void square_sort(int* arr, int size)
{
    if (size > 1e5) return;
    int i, j = 0;
    for (i = 0; i < size-1; i++)
    {
         for (j = 0; j < size-i-1; j++)
         {
             if (arr[j] > arr[j+1])
             {
                int tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
             }
         }
    }
}

void quick_sort(int* arr, int size)
{
    long i = 0, j = size - 1;
    int tmp, p;
    p = arr[(j + i) / 2];
    do
    {
        while (arr[i] < p) i++;
        while (arr[j] > p) j--;

        if (i <= j)
        {
          tmp = arr[i];
          arr[i] = arr[j];
          arr[j] = tmp;
          i++;
          j--;
        }
    } while (i <= j);
    if (j > 0) quick_sort(arr, j);
    if (size > i) quick_sort(arr + i, size - i);
}

int main()
{

    void (*sorts[])(int* arr,int size) = {count_sort, quick_sort, square_sort};
    size_t num_of_func = sizeof(sorts)/sizeof(sorts[0]);
    int x,y = 0;
    for (x = 0; x < (int) num_of_func; x++)
    {
        for (y = 0; y < num_of_tests; y++)
        {
            int *a = (int*) malloc(size_of_arrays[y] * sizeof(int));
            if (a == NULL)
            {
                printf("Not enough memory\a");
                exit(-1);
            }
            srand(time(NULL));
            int i;
            for (i = 0; i < size_of_arrays[y]; ++i)
                a[i] = rand() % module;
            double start = clock();
            sorts[x](a, size_of_arrays[y]);
            double end = (clock() - start) / CLOCKS_PER_SEC;
            printf("%d, %d - %f\n", x, size_of_arrays[y], end);
            free(a);

        }
    }
    return 0;
}
//                      5      10       1000        1e4         1e5         1e6         1e7         1e8
// counting_sort        0       0          0          0           0         0.01        0.02        0.22
// quick_sort           0       0          0          0         0.01        0.12       1.215       12.486
// bubble_sort          0       0          0        0.24        28.3        NaN         NaN         NaN
