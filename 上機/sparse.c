#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#define MAX 100

typedef struct element{
    int row;
    int col;
    int value;
}Element;

int compare(int a, int b){
    if(a>b) return 1;
    if(a<b) return -1;
    return 0;
}

void transpose(Element *matrix, Element *new){
    int count_row[MAX]={0}, start_row[MAX]={0};
    int num = matrix[0].value, i, temp;
    for(i=1; i<=num; i++)
        count_row[matrix[i].col]++;
    start_row[0] = 1;
    for(i=1; i<matrix[0].col; i++)
        start_row[i] = start_row[i-1]+count_row[i-1];
    new[0].row = matrix[0].row;
    new[0].col = matrix[0].col;
    new[0].value = matrix[0].value;
    for(i=1; i<=matrix[0].value; i++){
        temp = start_row[matrix[i].col]++;
        new[temp].col = matrix[i].row;
        new[temp].row = matrix[i].col;
        new[temp].value = matrix[i].value;
    }
}

void storesum(Element *ans, int *totalD, int row, int column, int *sum){
    if(*sum){
        if(*totalD<MAX){
            ans[++*totalD].row = row;
            ans[*totalD].col = column;
            ans[*totalD].value = *sum;
            *sum = 0;
        }
    }
}
void mult(Element *a, Element *b, Element *ans){
    Element newb[MAX];
    memset(newb, 0, sizeof(Element)*MAX);
    transpose(b, newb);
    int row=a[1].row, column=b[1].row, totalA=a[0].value, totalB=b[0].value, totalD=0, rowbegin=1, sum=0, i, j;
    a[totalA+1].row = a[0].row;
    newb[totalB+1].row = b[0].col;
    newb[totalB+1].col = 0;
    for(i=1; i<=totalA;){
        column = newb[1].row;
        for(j=1; j<=totalB+1;){
            if(row != a[i].row){
                storesum(ans, &totalD, row, column, &sum);
                i = rowbegin;
                for(;newb[j].row == column; j++);
                column = newb[j].row;
            }
            else if(column != newb[j].row){
                storesum(ans, &totalD, row, column, &sum);
                i = rowbegin;
                column = newb[j].row;
            }
            else switch(compare(a[i].col, newb[j].col)){
                case 0:
                    sum += a[i++].value * newb[j++].value;
                    break;
                case 1:
                    j++;
                    break;
                case -1:
                    i++;
                    break;
            }
        }
        for(; a[i].row == row; i++);
        rowbegin = i;
        row = a[i].row;
    }
    ans[0].row = a[0].row;
    ans[0].col = b[0].col;
    ans[0].value = totalD;
}

int main(){
    Element matrix[MAX], new[MAX], ans[MAX];
    memset(ans, 0, MAX*sizeof(Element));
    int i;
    for(i=0; i<9; i++)
        scanf("%d%d%d", &matrix[i].row, &matrix[i].col, &matrix[i].value);
    transpose(matrix, new);
    mult(matrix, new, ans);
    for(i=0; i<12; i++)
        printf("%d %d %d\n", ans[i].row, ans[i].col, ans[i].value);
    return 0;
}
