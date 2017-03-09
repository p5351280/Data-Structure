#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#define MAX 100

void insert(int num, int *now, int *heap){
    int i = ++(*now);
    heap[i] = num;
    while(i!=1 && heap[i] < heap[i/2]){
        heap[i] = heap[i/2];
        heap[i/2] = num;
        i/=2;
    }
    heap[i] = num;
}

int delete(int now, int *heap){
    int num = heap[1], temp = heap[now], i=1;
    heap[1] = heap[now];
    while(heap[i] > heap[i*2] || heap[i] > heap[i*2+1]){
        if(i*2 >= now)  break;
        int smaller;
        smaller = heap[i*2] < heap[i*2+1] ? i*2 : i*2+1;
        heap[i] = heap[smaller];
        heap[smaller] = temp;
        i*=2;
    }
    return num;
}

int main(){
    int heap[MAX], now=0, num, i;
    while(scanf("%d", &num)){
        if(!num)    break;
        insert(num, &now, heap);
    }
    for(i=1; i<=now; i++)  printf("%d ", heap[i]);  printf("\n");
    while(now){
        printf("%d ", delete(now--, heap));
    }
    return 0;
}

//4 37 79 43 65 26 68 21 7 2 0
