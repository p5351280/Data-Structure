#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#define MAX 3

void insert(int num, int front, int *rear, int *queue){
    if(front == (*rear+1) % MAX)    printf("Full\n");
    else{
        *rear = (*rear+1) %MAX;
        queue[*rear] = num;
    }
}

int delete(int *front, int rear, int *queue){
    if(*front == rear)  printf("Empty\n");
    else{
        *front = (*front+1) %MAX;
        return queue[*front];
    }
    return -1;
}

int main(){
    int queue[MAX]={0}, front=0, rear=0, n, num, i;
    while(scanf("%d", &n)){
        if(!n)  break;
        if(n == 1){  scanf("%d", &num); insert(num, front, &rear, queue);}
        else    delete(&front, rear, queue);
        
        if(rear<front){
            for(i=front+1; i<MAX; i++)    printf("%d", queue[i]);
            for(i=0; i<=rear; i++)   printf("%d", queue[i]);
        }
        else
            for(i=(front+1)%MAX; i<=rear; i++)    printf("%d", queue[i]);
        printf("\n");
    }
    return 0;
}
