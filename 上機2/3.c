#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 5

int main(){
    int matrix[MAX][MAX]={0}, ans[MAX][MAX]={0};
    int i, j, k;
    for(i=0; i<MAX; i++)    for(j=0; j<MAX; j++)    scanf("%d", matrix[i]+j);
    for(i=0; i<MAX; i++)    for(j=0; j<MAX; j++)    ans[i][j] = matrix[i][j];
    for(k=0; k<MAX; k++)
        for(i=0; i<MAX; i++)
            for(j=0; j<MAX; j++)
                if(ans[i][k] && ans[k][j])
                    ans[i][j] = 1;
    for(i=0; i<MAX; i++){
        for(j=0; j<MAX; j++)
            printf("%d ", ans[i][j]);
        printf("\n");
    }
    
    return 0;
}
