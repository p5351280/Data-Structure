#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#define MAX 100

int main(){
    char p[MAX];
    int f[MAX], i, j;
    scanf("%s", p);
    f[0] = -1;
    for(i=1; i<strlen(p); i++){
        j = f[i-1];
        while(j>-1 && p[j+1] != p[i])
            j = f[j];
        if(p[j+1] == p[i])
            f[i] = j+1;
        else
            f[i] = -1;
    }
    for(i=0; i<strlen(p); i++)  printf("%d ", f[i]);
    return 0;
}

