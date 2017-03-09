#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 10

void swap(int *a, int *b){
    int temp;
    temp = *a; *a=*b; *b=temp;
}

void quick(int num[], int left, int right){
    int i=left+1, j=right, pivot=num[left];
    if(left>=right) return;
    do{
        while(num[i]<pivot) i++;
        while(num[j]>pivot) j--;
        if(i<j)
            swap(num+i, num+j);
    }while(i<j);
    swap(num+left, num+j);
    for(i=0; i<MAX; i++)    printf("%d ", num[i]);
    printf("\n");
    quick(num, left, j-1);
    quick(num, j+1, right);
}

int main(){
    int i, num[MAX];
    for(i=0; i<MAX; i++)    scanf("%d", num+i);
    quick(num, 0, MAX-1);
    for(i=0; i<MAX; i++)    printf("%d ", num[i]);
    return 0;
}
