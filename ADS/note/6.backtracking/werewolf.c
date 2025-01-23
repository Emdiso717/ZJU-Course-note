#include <stdio.h>
#include<math.h>
int check(int a, int say, int n, int i, int m, int l, int nofw, int nofl, int *p)
{
    if (i == 1)
    {
        if ((n - a + nofl) < l)
            return 0;
    }
    else
    {
        if (nofl + 1 > l)
            return 0;
        if ((n - a + nofl + 1) < l)
            return 0;
        say = -say;
    }
    if (say * p[abs(say)] < 0)
        return 0;
    if (p[abs(say)] == 0)
    {
        if (say > 0)
        {
            if ((n - a + nofw) < m)
                return 0;
        }
        else
        {
            if(nofw + 1 > m)
                return 0;
            if ((n - a + nofw + 1) < m)
                return 0;
        }
    }
    return 1;
}

int backtracing(int a, int n, int m, int l, int *say, int *p, int *tf, int nofw, int nofl)
{
    for (int i = 1; i <= 2; i++)
    {
        int ok = check(a, say[a], n, i, m, l, nofw, nofl, p);
        if(ok)
        {
            int zero = 0;
            if (p[abs(say[a])] == 0)
            {
                p[abs(say[a])] = say[a];
                if (say[a] < 0)
                    nofw++;
                zero = 1;
            } 
            tf[a] = i;
            if (i == 2)
                nofl++;
            if (a == n)
            {
                int check = 0;
                for (int j = 1; j <= n; j++)
                {
                    if (p[i] < 0 && tf[i] == 2)
                    {
                        check++;
                        break;
                    }
                }
                if (check != 0)
                {
                    for (int i = 1; i <= n;i++)
                        if (p[i] < 0)
                            printf("%d ", i);
                }
                tf[a] = 0;
                if (i == 2)
                    nofl--;
                if (zero == 1)
                {
                    p[abs(say[a])] = 0;
                    if (say[a] < 0)
                        nofw--;
                }
                    return 0;
            }
            else
            {
                int check = backtracing(a + 1, n, m, l, say, p, tf, nofw, nofl);
                if (check == 0)
                {
                    tf[a] = 0;
                    if (i == 2)
                        nofl--;
                    if (zero == 1)
                    {
                        p[abs(say[a])] = 0;
                        if (say[a] < 0)
                            nofw--;
                    }
                }
                else
                    return 1;
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
    int nofw = 0, nofl = 0;
    for (int i = 1; i <= n;i++)
    {
        scanf("%d", &say[i]);
        p[i] = 0;
        tf[i] = 0;
    }
    backtracing(1, n, m, l, say, p, tf, nofw, nofl);
}