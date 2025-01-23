#include <stdio.h>

#define MAXN 10
#define MAXS 1000
# define INFINITY 100000000

int need_time(const int time[], const int score[], int happy_score, int n);

int main() {
  int n, i, happy_score;
  int time[MAXN], score[MAXN];
  scanf("%d %d", &n, &happy_score);
  for (i = 0; i < n; ++i)
      scanf("%d", &time[i]);
  for (i = 0; i < n; ++i)
      scanf("%d", &score[i]);
  printf("%d\n", need_time(time, score, happy_score, n));
  return 0;
}

// /* Your function will be put here */
int need_time(const int time[], const int score[], int happy_score, int n)
{
  int result[MAXS+1];
  for (int i = 0; i <= happy_score;i++){
    if (score[0] >= i){
      result[i] = time[0];
    }
    else{
      result[i] = INFINITY;
    }
  }
  for (int i = 1; i < n; i++){
    double index[MAXN + 1];
    for (int j = 0; j <= happy_score;j++){
      if(score[i]>=j){
        if(time[i]<result[j])
          index[j] = time[i];
        else
          index[j] = result[j];
      }else{
        if((result[j-score[i]]+time[i])<result[j]){
          index[j] = result[j - score[i]] + time[i];
        }else{
          index[j] = result[j];
        }
      }
    }
    for (int j = 0; j < n;j++){
      result[j] = index[j];
    }
  }
  if(result[happy_score]>=INFINITY)
    return -1;
    else
      return result[happy_score];
}


