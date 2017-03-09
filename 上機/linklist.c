#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#define MAX 10000
typedef struct node *node_ptr;
typedef struct node{
    int data;
    node_ptr next;
}Node;

void push(int num, node_ptr *top){
    node_ptr temp;
    temp = malloc(sizeof(Node));
    temp->next = *top;
    temp->data = num;
    *top = temp;
}

int pop(node_ptr *top){
    int num;
    node_ptr temp = *top;
    if(!*top){
        printf("Empty list!\n");
        return 0;
    }
    else{
        num = (*top)->data;
        *top = (*top)->next;
    }
    free(temp);
    return num;
}

void invert(node_ptr *root){
    node_ptr back, mid, lead;
    mid = NULL;
    lead = *root;
    while(lead){
        back = mid;
        mid = lead;
        lead = lead->next;
        mid->next = back;
    }
    *root = mid;
}

void print(node_ptr root){
    while(root){
        printf("%d ", root->data);
        root = root->next;
    }
    printf("\n");
}

int main(){
    node_ptr top=NULL;
    int i, num;
    while(1){
        scanf("%d", &i);
        switch(i){
            case 1:
                scanf("%d", &num);
                push(num, &top);
                break;
            case 2:
                printf("%d\n", pop(&top));
                break;
            case 3:
                invert(&top);
                break;
            case 4:
                print(top);
                break;
        }
    }
    return 0;
}
