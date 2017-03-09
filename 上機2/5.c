#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 10
#define INF 9999999
int size, map[MAX][MAX], parent[MAX]={0};

int find_root(int i){
    while(parent[i])
        i = parent[i];
    return i;
}

int check_root(int a, int b){
    if(a==b)    return 0;
    parent[b] = a;
    return 1;
}

int main(){
    int i, j, sum=0;
    scanf("%d", &size);
    for(i=1; i<=size; i++)
        for(j=1; j<=size; j++){
            scanf("%d", map[i]+j);
            if(!map[i][j])
                map[i][j]=INF;
        }
    int count=1;
    while(count<size){
        int min=INF, a=0, b=0, u=0, v=0;
        for(i=1; i<=size; i++){
            for(j=1; j<=size; j++){
                if(map[i][j] < min){
                    a = u = i;
                    b = v = j;
                    min = map[i][j];
                }
            }
        }
        u = find_root(u);
        v = find_root(v);
        if(check_root(u, v)){
            printf("Edge %d :<%d %d> cost %d\n", count++, a, b, map[a][b]);
            sum += map[a][b];
        }
        map[a][b] = map[b][a] = INF;
    }
    printf(" Minimum Cost = %d\n\n", sum);
    return 0;
}
