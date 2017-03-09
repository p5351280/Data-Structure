#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#define MAX 100
typedef struct node *ptr;
typedef struct node{
    int data;
    ptr next;
}Node;
int main(){
    ptr seq[MAX] = {NULL}, x, y, top;
    bool out[MAX] = {false};
    int i, j, n;
    scanf("%d", &n);
    while(1){
        scanf("%d%d", &i, &j);
        if(i<0){break;}
        x = (ptr)malloc(sizeof(Node));
        x->data = j;    x->next = seq[i];     seq[i] = x;
        x = (ptr)malloc(sizeof(Node));
        x->data = i;    x->next = seq[j];     seq[j] = x;
    }
    for(i=0; i<n; i++){
        if(!out[i]){
            printf("\nNew class: %d", i);
            out[i] = true;
            x = seq[i]; top = NULL;
            while(1){
                while(x){
                    j = x->data;
                    if(!out[j]){
                        printf(" %d", j);
                        out[j] = true;
                        y = x->next;
                        x->next = top;
                        top = x;
                        x = y;
                    }
                    else
                        x = x->next;
                }
                if(!top)    break;
                else{
                    x = seq[top->data];
                    top = top->next;
                }
            }
        }
    }
    return 0;
}

/*
 12
 0 4
 3 1
 6 10
 8 9
 7 4
 6 8
 3 5
 2 11
 11 0
 -1 -1
*/
