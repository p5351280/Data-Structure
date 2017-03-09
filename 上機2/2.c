#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 100


int main(){
    int size, map[MAX][MAX];
    scanf("%d", &size);
    int i, j, out[MAX]={0}, in[MAX]={0};
    for(i=0; i<size; i++){
        for(j=0; j<size; j++){
            scanf("%d", map[i]+j);
            if(map[i][j]){
                out[i]++;
                in[j]++;
            }
        }
    }
    return 0;
}
