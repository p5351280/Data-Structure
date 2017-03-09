#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define SIZE 101
#define MAX_STACK 2*SIZE*SIZE
#define A 0
#define B 1
#define MOUSE 2
#define FLOOR 2
#define WALL 'X'
#define ROAD '.'
#define STAIR 'o'
const int dirs[MOUSE][4][2] = {{{0,1},{1,0},{-1,0},{0,-1}},
                               {{0,-1},{-1,0},{1,0},{0,1}}}; //mouse, dir, {y,x}
//A : Right > Down > Up > Left
//B : Left > Up > Down > Right

typedef struct{
    short int z, y, x;
    char dir;
}element;
element stk[MOUSE][MAX_STACK];  //stk[0] for mouse A, stk[1] for mouse B

int top[MOUSE]={-1, -1};    //top[0] for mouse A, top[1] for mouse B
char map[FLOOR][SIZE][SIZE+3]={{{0}}};
bool mark[MOUSE][FLOOR][SIZE][SIZE]={{{false}}};

int main(){
    freopen("maze_Test.txt", "r", stdin);
    freopen("result.txt", "w", stdout);
    int i, step, floor;
    bool found[MOUSE] = {false};
    element current[MOUSE]; //current[0] for mouse A, current[1] for mouse B
    element new;    //after walking

    while(scanf("%d\n", &floor)==1){   //read the input
        floor--;
        for(i=0; i<SIZE; i++){
            fgets(map[floor][i], SIZE+3, stdin);
        }
    }
    if(map[0][1][1] == ROAD){
        ++top[A];                                           //mouse A push (start)
        stk[A][top[A]].y = stk[A][top[A]].x = 1;
        stk[A][top[A]].z = 0;
        stk[A][top[A]].dir = 0;
    }
    if(map[1][99][99] == ROAD){
        ++top[B];                                           //mouse B push (start)
        stk[B][top[B]].y = stk[B][top[B]].x = 99;
        stk[B][top[B]].z = 1;
        stk[B][top[B]].dir = 0;
    }
    bool need_cont = true;  //check if it need to do next step
    for(step=0; need_cont; step++){    //start to walk
        bool have_been[MOUSE]={false};
        while(top[A]>-1){       //for mouse A
            current[A] = stk[A][top[A]];        //pop mouse A
            --top[A];
            mark[A][current[A].z][current[A].y][current[A].x] = true;
            have_been[A] = true;
            printf("Step:%d\t mouse A(%d,%d,%d)", step, current[A].z, current[A].y, current[A].x);
            for(i=current[A].dir; i<4; i++){    //check for every direction, if there is any direction it can go then it will break
                new = current[A];
                new.y = current[A].y + dirs[A][i][0];
                new.x = current[A].x + dirs[A][i][1];
                new.dir = 0;

                if(!mark[A][new.z][new.y][new.x] && map[new.z][new.y][new.x]!=WALL){  //new point never been and isn't wall

                    if(map[new.z][new.y][new.x]==STAIR){    //is stair
                        new.z = 1;  //mouse A go the other floor
                        stk[A][++top[A]] = new;
                    }

                    else if(new.x == stk[B][top[B]].x && new.y == stk[B][top[B]].y && new.z == stk[B][top[B]].z){ //avoid pass by
                        need_cont = false;
                        printf("\nRats met each other in(%d,%d,%d)\n", new.z, new.y, new.x);
                    }

                    else{             //is road
                        if(new.x==99 && new.y==99 && new.z==1){  found[A]=true; need_cont=false; break;}   //A arrived last point
                        if(current[A].dir<3){
                            stk[A][++top[A]] = current[A];  //push the old point into stack, but change its dir to next
                            stk[A][top[A]].dir++;
                        }
                        stk[A][++top[A]] = new; //push the new point into the stack temp, it will pop out soon
                    }
                    break;  //break for
                }
            }
            break;  //break while, so that it go only one step
        }

        while(top[B]>-1){       //for mouse B
            current[B] = stk[B][top[B]];        //pop mouse B
            --top[B];
            mark[B][current[B].z][current[B].y][current[B].x] = true;
            have_been[B] = true;
            printf("\t mouse B(%d,%d,%d)\n", current[B].z, current[B].y, current[B].x);
            for(i=current[B].dir; i<4; i++){
                new = current[B];
                new.y = current[B].y + dirs[B][i][0];
                new.x = current[B].x + dirs[B][i][1];
                new.dir = 0;

                if(!mark[B][new.z][new.y][new.x] && map[new.z][new.y][new.x]!=WALL){  //never been and isn't wall
                    if(map[new.z][new.y][new.x]==STAIR){    //is stair
                        new.z = 0;  //mouse B go the other floor
                        stk[B][++top[B]] = new;
                    }
                    else{             //is road
                        if(new.x==1 && new.y==1 && new.z==0){  found[B]=true; need_cont=false; break;}   //B arrived last point
                        if(current[B].dir<3){
                            stk[B][++top[B]] = current[B];  //push the old point into stack, but change its dir to next
                            stk[B][top[B]].dir++;
                        }
                        stk[B][++top[B]] = new; //push the new point into the stack temp, it will pop out soon
                    }
                    break;
                }
            }
            break;
        }

        if(found[A] && found[B])     printf("\nRats didn't meet each other in the maze because they arrived the same time.\n");
        else if(found[A])    printf("\nRats didn't meet each other in the maze because A arrived.\n");
        else if(found[B])    printf("\nRats didn't meet each other in the maze because B arrived.\n");
        else if(current[A].x==current[B].x && current[A].y==current[B].y && current[A].z==current[B].z){
            need_cont = false;
            printf("\nRats met each other in(%d,%d,%d)\n", current[A].z, current[A].y, current[A].x);
        }
        else if(!have_been[A]){
            printf("\nNo road for mouse A\n");
            break;
        }
        else if(!have_been[B]){
            printf("\nNo road for mouse B\n");
            break;
        }
    }
    return 0;
}
