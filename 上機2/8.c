#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 100
#define INF 99999
int cost[MAX][MAX], start, end, size, distance[MAX], visit[MAX];

int find(){
    int u=-1, min=INF;
    int i;
    for(i=1; i<=size; i++){
        if(!visit[i] && distance[i]<min){
            min=distance[i];
            u=i;
        }
    }
    return u;
}

int main(){
    int i, j;
    scanf("%d", &size);
    for(i=1; i<=size; i++)
        for(j=1; j<=size; j++){
            scanf("%d", cost[i]+j);
            if(!cost[i][j])
                cost[i][j]=INF;
        }
    scanf("%d%d", &start, &end);
    for(i=1; i<=size; i++)
        distance[i] = cost[start][i];
    distance[start]=0;
    visit[start]=1;
    int count=0;
    while(count<size-1){
        int next=find();
        if(next<0)  break;
        visit[next]=1;
        for(i=1; i<=size; i++){
            if(!visit[i])
                if(distance[next]+cost[next][i]<distance[i])
                    distance[i]=distance[next]+cost[next][i];
        }
        count++;
    }
    if(distance[end]==INF)
        printf("-1\n");
    else
        printf("%d\n", distance[end]);
    return 0;
}
