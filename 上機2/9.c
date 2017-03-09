#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 100
#define INF 99999

int main(){
    int size, map[MAX][MAX], start, visit[MAX]={0}, sum=0;
    scanf("%d", &size);
    int i, j, k;
    for(i=1; i<=size; i++)
        for(j=1; j<=size; j++){
            scanf("%d", map[i]+j);
            if(!map[i][j])
                map[i][j]=INF;
        }
    scanf("%d", &start);
    visit[start] = 1;
    for(i=1; i<size; i++){
        int min=INF, u=0, v=0;
        for(j=1; j<=size; j++){
            if(visit[j]){
                for(k=1; k<=size; k++){
                    if(!visit[k])
                        if(map[j][k]<min){
                            min=map[j][k];
                            u=j;
                            v=k;
                        }
                }
            }
        }
        visit[v]=1;
        printf("%d:<%d,%d> %d\n", i, u, v, map[u][v]);
        sum+=map[u][v];
        map[u][v]=INF;
    }
    printf("%d\n", sum);
    return 0;
}
