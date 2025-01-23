#include <stdio.h>
#define INFINITY __INT32_MAX__
int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    int heap[m], state[m];
    for (int i = 0; i < m; i++)
    {
        heap[i] = INFINITY;
        state[i] = 1;
    }
    int temp = 0, last = INFINITY;
    for (int i = 0; i < n; i++)
    {
        int temp_k;
        scanf("%d", &temp_k);
        if (i < m)
        {
            heap[temp] = temp_k;
            temp++;
        }
        else
        {
            int min_t = -1, min = INFINITY;
            for (int j = 0; j < m; j++)
            {
                if (min > heap[j] && state[j] == 1)
                {
                    min = heap[j];
                    min_t = j;
                }
            }
            if (min_t != -1)
            {
                if (i != m)
                    printf(" %d", min);
                else
                    printf("%d", min);
                temp = min_t;
                last = min;
            }
            else
            {
                for (int j = 0; j < m; j++)
                {
                    state[j] = 1;
                    if (min > heap[j])
                    {
                        min = heap[j];
                        min_t = j;
                    }
                }
                printf("\n%d", min);
                temp = min_t;
                last = min;
            }
            heap[temp] = temp_k;
            if (temp_k < last)
            {
                state[temp] = -1;
            }
        }
    }
    int first_line = 0;
    if (n < m)
    {
        m = n;
        first_line = 1;
    }
    for (int i = 0; i < m; i++)
    {
        int min_t = -1, min = INFINITY;
        for (int j = 0; j < m; j++)
        {
            if (min > heap[j] && state[j] == 1)
            {
                min = heap[j];
                min_t = j;
            }
        }
        if (min_t != -1)
        {
            if (first_line == 1 && i == 0)
                printf("%d", min);
            else
                printf(" %d", min);
            temp = min_t;
            last = min;
            heap[min_t] = INFINITY;
        }
        else
        {
            for (int j = 0; j < m; j++)
            {
                state[j] = 1;
                if (min > heap[j])
                {
                    min = heap[j];
                    min_t = j;
                }
            }
            printf("\n%d", min);
            temp = min_t;
            last = min;
            heap[min_t] = INFINITY;
        }
    }
}