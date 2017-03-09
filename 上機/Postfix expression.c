#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#define MAX 10000

void push(int *top, int *stack, int num){
    stack[++(*top)] = num;
}

int pop(int *top, int *stack){
    int num;
    num = stack[(*top)--];
    return num;
}
int main(){
    char input[MAX];
    int stack[MAX], top=-1;
    while(1){
        gets(input);
        if(input[0] == '0') break;
        int i, a, b;
        for(i=0; i<strlen(input); i++){
            if(isdigit(input[i]))
                push(&top, stack, input[i]-'0');
            else{
                switch(input[i]){
                    case '+':
                        a = pop(&top, stack);
                        b = pop(&top, stack);
                        push(&top, stack, b+a);
                        break;
                    case '-':
                        a = pop(&top, stack);
                        b = pop(&top, stack);
                        push(&top, stack, b-a);
                        break;
                    case '*':
                        a = pop(&top, stack);
                        b = pop(&top, stack);
                        push(&top, stack, b*a);
                        break;
                    case '/':
                        a = pop(&top, stack);
                        b = pop(&top, stack);
                        push(&top, stack, b/a);
                        break;
                    case '%':
                        a = pop(&top, stack);
                        b = pop(&top, stack);
                        push(&top, stack, b%a);
                        break;
                }
            }
        }
        printf("%d\n", pop(&top, stack));
    }
    return 0;
}
