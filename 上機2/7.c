#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 100
typedef struct{
    int floor;
    int count;
}Data;
Data lift[MAX];
int main(){
    int floor, start, target, value[MAX], visit[MAX]={0}, success=0;
    scanf("%d%d%d", &floor, &start, &target);
    int i;
    for(i=1; i<=floor; i++)
        scanf("%d", value+i);
    int rear=-1, front=-1;
    memset(lift, 0, sizeof(lift));
    lift[++rear].floor = start;
    while(rear!=front){
        Data temp;
        temp = lift[++front];
        visit[temp.floor]=1;
        int up=temp.floor+value[temp.floor], down=temp.floor-value[temp.floor];
        if(up==target || down==target){
            success = 1;
            printf("%d\n", temp.count+1);
            break;
        }
        if(up>0 && up<=floor && !visit[up]){
            lift[++rear].floor=up;
            lift[rear].count=temp.count+1;
        }
        if(down>0 && down<=floor && !visit[down]){
            lift[++rear].floor=down;
            lift[rear].count=temp.count+1;
        }
    }
    if(!success)    printf("-1\n");
    return 0;
}
