#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define SIZE 10
#define MAX_STACK SIZE*SIZE
#define WALL '1'
#define ROAD '0'
const int dirs[4][2] = {{0,1},{1,0},{0,-1},{-1,0}}; //{y,x}
//Right > Down > Left > Up

typedef struct{
    short int y, x;
    char dir;
}element;
element stk[MAX_STACK];

int top=-1;
char map[SIZE][SIZE+3]={{0}};
bool mark[SIZE][SIZE]={{false}};

int main(){
    FILE *fptr=fopen("6input.txt","r");
    int i, first=1;
    element current;
    element new;
    for(i=0; i<10; i++)
        fgets(map[i], SIZE+3, fptr);
    if(map[1][1] == ROAD){
        ++top;
        stk[top].y = stk[top].x = 1;
        stk[top].dir = 0;
    }
    bool need_cont = true;  //check if it need to do next step
    while(top>-1 && need_cont){
        current = stk[top--];
        mark[current.y][current.x] = true;
        if(first){
            printf("(%d,%d)", current.x, current.y);
            first=0;
        }
        else printf(",(%d,%d)", current.x, current.y);
        for(i=current.dir; i<4; i++){    //check for every direction
            new = current;
            new.y = current.y + dirs[i][0];
            new.x = current.x + dirs[i][1];
            new.dir = 0;
            if(!mark[new.y][new.x] && map[new.y][new.x]==ROAD){  //new point never been and is road
                if(new.x==8 && new.y==8){ printf(",(%d,%d)", new.x, new.y); need_cont=false; break;}   //arrived last point
                if(current.dir<3){
                    stk[++top] = current;  //push the old point into stack, but change its dir to next
                    stk[top].dir++;
                }
                stk[++top] = new;
                break;
            }
        }
    }
    return 0;
}
