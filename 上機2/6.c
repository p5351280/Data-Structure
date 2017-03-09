#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 10
int count = 0, target=0, value[MAX], n;

void dfs(int sum, int now, bool choose){
    if(sum > target)    return;
    if(now >= n) return;
    if(choose){
        sum += value[now];
        if(sum == target){
            count++;
            return;
        }
    }
    dfs(sum, now+1, true);
    dfs(sum, now+1, false);
}

int main(){
    scanf("%d%d", &target, &n);
    int i;
    for(i=0; i<n; i++)
        scanf("%d", value+i);
    dfs(0, 0, false);
    dfs(0, 0, true);
    printf("%d\n", count);
    return 0;
}
