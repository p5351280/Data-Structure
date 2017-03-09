#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#define MAX 10000

int order(char s){
    switch (s) {
        case '+':
        case '-':
            return 1;
            break;
        case '*':
        case '/':
            return 2;
            break;
        case '^':
            return 3;
            break;
    }
    return 0;
}
int main(){
    int ncase;
    scanf("%d", &ncase);
    while(ncase--){
        char s[MAX], stack[MAX];
        int top=-1, i;
        scanf("%s", s);
        for(i=0; i<strlen(s); i++){
            if(isalpha(s[i]) || isdigit(s[i]))
                printf("%c", s[i]);
            else{
                if(s[i] == ')'){
                    while(stack[top] != '(')
                        printf("%c", stack[top--]);
                    top--;
                }
                else if(s[i] == '('){
                    stack[++top] = s[i];
                }
                else if(order(s[i]) > order(stack[top])){
                    stack[++top] = s[i];
                }
                else{
                    while(order(s[i]) <= order(stack[top]) && top>-1)
                        printf("%c", stack[top--]);
                    stack[++top] = s[i];
                }
            }
        }
        for(i=top; i>-1; i--)
            printf("%c", stack[i]);
        printf("\n");
    }
    return 0;
}
