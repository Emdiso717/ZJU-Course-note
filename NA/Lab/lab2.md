### 6-2 Root of a Polynomial

<font face="微软雅黑" size = 2>


A polynomial of degree n has the common form as $p(x)=c_nx^n+c_{n−1}x^{n−1}+⋯+c_1x+c_0$. Your task is to write a function to find a root of a given polynomial in a given interval.

#### Format of function:
double Polynomial_Root(int n, double c[], double a, double b, double EPS);where int n is the degree of the polynomial; double c[] is an array of n+1 coefficients $c_n, c_{n−1},..., c_1, and ~c_0$ of the given polynomial; double a and b are the two end-points of the given interval; and double EPS is the accuracy of the root.
The function must return the root.
Note: It is guaranteed that a unique real number r exists in the given interval such that p(r)=0.

#### Sample program of judge:
```c{.line-numbers}
#include <stdio.h>
#include <math.h>

#define ZERO 1e-13 /* X is considered to be 0 if |X|<ZERO */
#define MAXN 11    /* Max Polynomial Degree + 1 */

double Polynomial_Root(int n, double c[], double a, double b, double EPS);

int main()
{
    int n;
    double c[MAXN], a, b;
    double EPS = 0.00005;
    int i;

    scanf("%d", &n);
    for (i=n; i>=0; i--) 
        scanf("%lf", &c[i]);
    scanf("%lf %lf", &a, &b);
    printf("%.4f\n", Polynomial_Root(n, c, a, b, EPS));

    return 0;
}

/* Your function will be put here */
```

#### Sample Input:
```
2 1 1.5 -1
0 2
```
#### Sample Output:
```
0.5000
```


#### 思路分析
- 最初的想法是直接使用二分法找到所有的解，但是发现会有两个测试点不能通过。于是尝试使用牛顿迭代法但是还是不能通过，在上课老师的提醒下，会出现重根的情况，需要更加优化的算法，于是在网上搜到了[牛顿迭代法在单根与重根的对比](https://blog.csdn.net/mzrcsdn/article/details/135600604)。
- ##### 为什么牛顿收敛不行
  - 本来认为普通的牛顿迭代法是能够解决重根问题的，在阅读之后便找到了一些问题。$g(x)=x-\frac{f(x)}{f'(x)}$,是满足不动点迭代的式子，于是是否能够收敛于该式子的一阶导数密切相关 $g'(x)=\frac{f''(x)f(x)}{f'(x)^2}$,如果是有重根的话可以改写 $f(x)=(x-x_*)^m\phi(x)~~f'(x)=m(x-x_*)^{m-1}\phi(x)+\phi'(x)*(x-x_*)^m$ 而 $g'(x_*)=\lim\limits_{h->0}\frac{g(x+h)-g(x)}{h}=1-\frac{1}{m}$,可知道当在$x_*$这个附近区间内所有的点的导数在m很大时会接近于1，会出现无法收敛的情况。
- ##### 对牛顿收敛的改进
  - $f(x)=(x-x_*)^m\phi(x)~~~ f(x)^{\frac{1}{m}}=(x-x_*)h(x)^{\frac{1}{m}}$,建立了新的函数 $g(x)=f(x)^{\frac{1}{m}} ~~~ g(x_*)=0$,所以对于$g(x)$会有一个新的迭代关系式$u(x)=x-\frac{g(x)}{g'(x)}=x-\frac{f(x)}{f'(x)}=x-m\frac{(x-x_*)\phi(x)}{m\phi(x)+(x-x_*)h'(x)},令h(x)=\frac{(x-x_*)\phi(x)}{m\phi(x)+(x-x_*)h'(x)}~~~h(x_*)=0$ 也为 $h(x)$ 的根，故根据$h(x)$再次建立一个牛顿迭代式子，于是$x_{k+1}=x_{k}-\frac{f(x)f'(x)}{f'(x)^2-f(x)f''(x)}$
