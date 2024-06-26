### 6-1 Numerical Summation of a Series

<font face="微软雅黑" size = 2>

Produce a table of the values of the series for $\phi(x)=\sum_{k=1}^{\infty}\frac{1}{k(k+x)}....(1)$ the 3001 values of x, $x = 0.0, 0.1, 0.2, ..., 300.00$ . All entries of the table must have an absolute error less than $10^{−10}$. This problem is based on a problem from Hamming (1962), when mainframes were very slow by today's microcomputer standards.

```c{.line-numbers}
void Series_Sum( double sum[] );
```

where double $sum[]$ is an array of 3001 entries, each contains a value of $\phi(x) ~~for ~x = 0.0, 0.1, 0.2, ..., 300.00$.

```c{.line-numbers}
#include <stdio.h>

void Series_Sum( double sum[] );

int main()
{
    int i;
    double x, sum[3001];
    
    Series_Sum( sum );

    x = 0.0;
    for (i=0; i<3001; i++)
        printf("%6.2f %16.12f\n", x + (double)i * 0.10, sum[i]);

    return 0;
}

/* Your function will be put here */
```

#### Sample Output:
```
0.00   1.644934066848
0.10   1.534607244904
...
1.00   1.000000000000
...
2.00   0.750000000000
...
300.00   0.020942212934
```
#### Hint:
The problem with summing the sequence in equation (1) is that too many terms may be required to complete the summation in the given time. Additionally, if enough terms were to be summed, roundoff would render any typical double precision computation useless for the desired precision.
To improve the convergence of the summation process note that $\frac{1}{k(k+1)}=\frac{1}{k}-\frac{1}{k+1}.....(2)$ which implies $\phi(1)=1.0$. One can then produce a series for $\phi(x)−\phi(1)$ which converges faster than the original series. This series not only converges much faster, it also reduces roundoff loss.
This process of finding a faster converging series may be repeated again on the second series to produce a third sequence, which converges even more rapidly than the second.
The following equation is helpful in determining how may items are required in summing the series above.

$$
\sum_{k=n}^{\infty}\frac{1}{k^r}<\int_{n-1}^{\infty}\frac{1}{x^r}dx~~for~k>1~and~r\geq1...(3)
$$

</font>


#### 思路分析
如果直接计算计算量会非常大，所以按照提示来计算，用一个方便计算的$x$取整数的情况为基准去计算每一个小数的情况。
最初的想法是 $\phi(x)=\phi(1)+\sum_{k=1}^{\infty}\frac{1-x}{k(k+x)(k+1)}$ 只需要转化为 $\sum_{k=1}^{\infty}\frac{1-x}{k(k+x)(k+1)}=\sum_{k=1}^{n}\frac{1-x}{k(k+x)(k+1)}+\sum_{k=n}^{\infty}\frac{1-x}{k(k+x)(k+1)}$ ，使得余项$\sum_{k=n}^{\infty}\frac{1-x}{k(k+x)(k+1)}\leq10^{-10}$即可。
但是仔细考虑，发现这个算法计算量还是很大，距离1的距离越远算需要的计算量就会越来越大，但是相对于直接相加有了部分的优化。
于是有了新的想法，用每一个整数去限制周围的小数：
设 $x=m+q,m整数,q小数$ 进一步将公式转化为 $\phi(x)=\phi(m)-\sum_{k=1}^{\infty}\frac{q}{k(k+x)(k+m)}$ ,和上述的想法一样，再对余项进行限制，但是经过尝试之后发现分母为2次的逼近还是比较慢，于是就想到再用更加快的逼近，将分母改用为3次。
设 $\alpha(x)=\sum_{k=1}^{\infty}\frac{1}{k(k+x)(k+m)}$ 、
将原式子转化为 $\phi(x)=\phi(m)-q\alpha(x)$ 
于是就有 $\alpha(x)=\alpha(m+1)+\sum_{k=1}^{\infty}\frac{1-q}{k(k+x)(k+m)(k+m+1)}$
计算 $\alpha(m+1)=\sum_{k=1}^{\infty}\frac{1}{k(k+m+1)(k+m)}=\sum_{k=1}^{\infty}(\frac{1}{k(k+m)}-\frac{1}{k(k+m+1)})=\phi(m)-phi(m+1)$
原式转化：$\phi(x)=\phi(m)-q(\phi(m)-phi(m+1))-q\sum_{k=1}^{\infty}\frac{1-q}{k(k+x)(k+m)(k+m+1)}$
只需要按照最开始的思路解决余项即可
$q\sum_{k=1}^{\infty}\frac{1-q}{k(k+x)(k+m)(k+m+1)}=q\sum_{k=1}^{n}\frac{1-q}{k(k+x)(k+m)(k+m+1)}+q\sum_{k=n+1}^{\infty}\frac{1-q}{k(k+x)(k+m)(k+m+1)}$
$q\sum_{k=n+1}^{\infty}\frac{1-q}{k(k+x)(k+m)(k+m+1)}<q\sum_{k=n+1}^{\infty}\frac{1-q}{k^4}<q\int_{n}^{\infty}\frac{1}{x^4}=q\frac{(1-q)}{-3x^3}$
只需使 $q\frac{(1-q)}{3x^3} \leq 10^-10$ 为结束条件即可
