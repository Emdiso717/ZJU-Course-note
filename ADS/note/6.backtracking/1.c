#include <stdio.h>
#include<math.h>
int result[100][100];
int r_i = 0;
int backtracing(int a, int n, int m, int l, int *say, int *p, int *tf)
{
    if (a > n)
    {
        int check = 0;
        int nm = 0, nl = 0, same = 0;
        for (int i = 1; i <= n; i++)
        {
            if (p[i] < 0)
                nm++;
            if (tf[i] == 2)
                nl++;
            if (p[i] < 0 && tf[i] == 2)
            {
                check = 1;
                same++;
            }       
        }
        if (check == 1 && nm == m && nl == l && same != m)
        {
            check = 2;
        }
        if (check == 2)
        {
            int k = 0;
            for (int i = 1; i <= n; i++)
                if (p[i] < 0)
                {
                    result[r_i][k] = i;
                    k++;
                }
            r_i++;
        }
        return 0;
    }
    for (int i = 1; i >= -1; i = i - 2)
    {
        int nm = 0, nl = 0, same = 0;
        for (int j = 1; j <= a; j++)
        {
            if (p[j] < 0)
                nm++;
            if (tf[j] == 2)
                nl++;
            if (p[j] < 0 && tf[j] == 2)
            {
                same++;
            }       
        }
        if (i < 0 && nm + 1 > m)
            return 0;
        if (i < 0 && n - a + nm + 1 < m)
            return 0;
        if (i > 0 && (n - a + nm) < m)
            continue;
        int fake = 0;
        for (int j = 1; j <= n; j++)
        {

            if (say[j] == -i * a)
                fake++;
        }
        if (i<0&&fake + nl > l)
            return 0;
        if (i>0&&fake + nl > l)
            continue;
        p[a] = i;
        for (int j = 1; j <= n; j++)
        {
            if (say[j] == i * a)
            {
                tf[j] = 1;
            }
            else if (say[j] == -i * a)
                tf[j] = 2;
        }
        int check = backtracing(a + 1, n, m, l, say, p, tf);
        if (check == 1)
            return 1;
        else
        {
            p[a] = 0;
            for (int j = 1; j <= n; j++)
            {
                if (abs(say[j]) == a)
                    tf[j] = 0;
            }
        }
    }
    return 0;
}
int main()
{
    int n, m, l;
    scanf("%d %d %d", &n, &m, &l);
    int say[n + 1], p[n + 1], tf[n + 1];
    for (int i = 1; i <= n;i++)
    {
        scanf("%d", &say[i]);
        p[i] = 0;
        tf[i] = 0;
    }
    backtracing(1, n, m, l, say, p, tf);
    if (r_i == 0)
    {
        printf("No Solution");
        return 0;
    }
    int max[m], max_i = 0;
    for (int i = 0; i < m; i++)
    {
        max[i] = result[0][i];
    }
    for (int i = 1; i < r_i; i++)
    {
        int large = 0;
        for (int j = m - 1; j >= 0; j--)
        {
            if (result[i][j] > max[j])
            {
                large++;
                break;
            }
            else if (result[i][j] < max[j])
            {
                large = 0;
                break;
            }
        }
        if (large != 0)
        {
            for (int j = 0; j < m; j++)
                max[j] = result[i][j];
            max_i = i;
        }
    }
    printf("%d", result[max_i][m - 1]);
    for (int i = m - 2; i >= 0; i--)
        printf(" %d", result[max_i][i]);
} 
