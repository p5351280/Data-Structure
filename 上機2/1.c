#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int main(){

    int count[MAX]={0}, a=0;
    int matrix[MAX][MAX]={0};
    int i, j;
    for(i=0; i<14; i++){
        for(j=0; j<14; j++){
            scanf("%d", matrix[i]+j);
            if(matrix[i][j])
                count[j]++;
        }
    }
    while(1){
        for(i=0; i<14, count[i]!=0; i++);
        if(i==14)   break;
        printf("%c ", 'A'+i);
        count[i]=-1;
        for(j=0; j<14; j++)
            if(matrix[i][j])
                count[j]--;
    }
    return 0;
}

/*
0 0 1 0 0 0 0 0 0 0 0 0 0 0
0 0 1 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 1 1 0 0 0 0 0 0
0 0 0 0 1 0 0 0 0 0 0 0 0 0
0 0 0 0 0 1 0 0 0 0 0 0 0 0
0 0 0 0 0 0 1 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 1 1 0 1 1 0
0 0 0 0 0 0 0 0 1 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 1 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 1
0 0 0 0 0 0 0 0 0 0 0 0 0 0
*/
