#include<stdio.h>
#define MAXN 500
double money = 0;
double D[MAXN];
double P[MAXN];
double maxdistance=0;
int greedy(double c,double d,double da,int n,int k,double remain){
    double maxd = c * da;
    int maxk = -1;
    double minp = 1000000000;
    int minpi = 0;
    int first = 0;
    double lessp = 1000000000;
    int lesspi = 0;
    for (int i = k+1; i < n; i++){
        if (D[i] <= D[k] + maxd)
        {
            maxk = i;
        }else{
            break;
        }
        if (first == 0 && P[i] <= P[k]){
            lessp = P[k];
            first = 1;
            lesspi = i;
        }
        if (P[i] < minp)
        {
            minp = P[i];
            minpi = i;
        }
    }
    if (maxk == -1){
        if (maxd + D[k] < d){
            maxdistance = maxd + D[k];
            return -1;
        }
        else{
            double m = (d - D[k]) / da-remain;
            if (m > 0){
                money += m * P[k];
                return 1;
            }else{
                return -1;
            }
        }
    }
    if (minp <= P[k]){
        double m = (D[lesspi] - D[k]) / da - remain;
        if (m > 0){
            money += m * P[k];
            remain = 0;
        }else{
            remain = -m;
        }
        k = lesspi;
    }else{
        if (D[k] + maxd <= d){
            money += (c - remain) * P[k];
            remain = c - (D[minpi] - D[k]) / da;
            k = minpi;
        }else{
            double m = (d - D[k]) / da - remain;
            if (m > 0){
                money += m * P[k];
                return 1;
            }else{
                return 1;
            }
        }
    }
    if (greedy(c, d, da, n, k, remain) == 1)
        return 1;
    else
        return -1;
}
int main(){
    double c, d, da;
    int n;
    scanf("%lf %lf %lf %d", &c, &d, &da, &n);
    for (int i = 0; i < n;i++){
        scanf("%lf %lf", &P[i], &D[i]);
    }
    for (int i = 0; i < n - 1; i++){
        for (int j = 0; j < n - i - 1; j++){
            if(D[j]>D[j+1]){
                double temp = D[j];
                D[j] = D[j + 1];
                D[j + 1] = temp;
                double temp2 = P[j];
                P[j] = P[j + 1];
                P[j + 1] = temp2;
            }
        }
    }
    if (D[0] != 0)
    {
        printf("The maximum travel distance = 0.00");
        return 0;
    }
    if (greedy(c, d, da, n, 0, 0) == 1)
        printf("%.2lf", money);
    else{
        printf("The maximum travel distance = %.2lf", maxdistance);
    }
}