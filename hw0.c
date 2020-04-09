/*
 * 1. This Program is Developed Solely by Myself: yes
 * 2. Student ID: 107061207
 * 3. OJ ID: DS2107061207
 * 4. OJ SID: 2133717
 * 5. OJ Score: 10
 */

#include <stdio.h>

int max = 0, N, K;

void choose(int sum_w, int value_sum, int item_num,int *weight, int *value);

int main(void)
{
    int i;

    scanf("%d %d", &N, &K);

    int weight[N], value[N];
    
    for(i = 0; i < N; i++){
        scanf("%d %d", &value[i], &weight[i]);
    }
    choose( K, 0, N - 1, weight, value);
    printf("%d", max);
    return 0;
}

void choose(int sum_w, int value_sum, int item_num,int *weight, int *value)
{
    if(sum_w > K)
        return;
    if(item_num == -1 && value_sum > max){
        max = value_sum;
        return;
    }
	else if(item_num == -1){
		return;
	}
    if(item_num == N - 1){
        sum_w = 0;
    }
    choose(sum_w, value_sum, item_num - 1, weight, value);
    choose(sum_w + weight[item_num], value_sum + value[item_num], item_num - 1, weight, value);
    
}