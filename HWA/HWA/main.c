#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define wall 1
#define road 0
#define stair 5

#define MAZE_row 101
#define MAZE_col 101


typedef struct locate {
    int z, x, y ;
    int dir;
} locate;
 int maze[2][110][110];
 int dir_A[4][2]= {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};   //(0,1)-> RIGHT (1,0)-> DOWN (0,-1)-> LEFT (-1,0)-> UP
 int dir_B[4][2]= {{0, -1}, {-1, 0}, {1, 0}, {0, 1}};

void read_maze()
{

    FILE *fptr;
    fptr = fopen("mazeB.txt","r");
    int i=2;

    while(i--){
        int j=0,k=0;
        int floor;
        char a[200];

        fscanf(fptr,"%d\n", &floor);
             floor--;
        //printf("g");


        for ( j = 0; j < MAZE_row; j++) {

            fgets(a, 200, fptr);
        //     printf("%s", a);

            for (k = 0; k < MAZE_col; k++) {
                if (a[k] == 'o')
                    maze[floor][j][k] = stair;
                else if (a[k] == '.')
                    maze[floor][j][k] = road;
                else if (a[k] == 'X')
                    maze[floor][j][k] = wall;

            }
        }

    }
     fclose(fptr);
}

int main()
{
    FILE *ptr;
    ptr = fopen("result1.txt","w");

    read_maze();                                // get maze from file


    locate stackA[MAZE_row * MAZE_col *2];
    locate stackB[MAZE_row * MAZE_col *2];

    locate ratA = {0, 1, 1, 0};        // the location where ratA and ratB start
    locate ratB = {1, 99, 99, 0};
    int posA = 0, posB = 0;

    stackA[posA++]=ratA;
    stackB[posB++]=ratB;

    bool A_has_visited[2][MAZE_row][MAZE_col], B_has_visited[2][MAZE_row][MAZE_col];
    memset(A_has_visited, 0, sizeof(A_has_visited));
    memset(B_has_visited, 0, sizeof(B_has_visited));


    bool need_continue = true; //If one of rats get the goal or meets each other, it stops
    int count=1;
    for (count=1;need_continue;count++) {
        bool have_been[2]={false};
        int A_reach_goal = 0;
        int B_reach_goal = 0;
        locate cur;

        while(posA > 0){     // walk rat A
            cur = stackA[posA-1];
            A_has_visited[cur.z][cur.x][cur.y] = true;
            have_been[0] = true;
        int pass_or_not=0;
        int i=0;
            for (i = cur.dir; i<4; i++) {

                locate tmp = cur;
                tmp.x = cur.x + dir_A[i][0];
                tmp.y = cur.y + dir_A[i][1];
                tmp.dir = 0;
                // printf("tmp -> %d %d %d %d\n", tmp.f, tmp.x, tmp.y, tmp.next_dir);
                if (A_has_visited[tmp.z][tmp.x][tmp.y] == false && maze[tmp.z][tmp.x][tmp.y] != wall){

                        if (maze[tmp.z][tmp.x][tmp.y] == stair) {   // RatA go up the stair

                        tmp.z = 1;
                    }
                    else {
                        stackA[posA - 1].dir = i + 1;          //the every place of direction ratA has visited
                    }

                    pass_or_not = 1;
                    stackA[posA++] = tmp;
                    break;
                }
            }
            if (pass_or_not == 0){     //rat go back
                posA--;
                break;
            }
            if (stackA[posA - 1].z == 1 && stackA[posA - 1].x == 99 && stackA[posA - 1].y == 99){    //ratA get the goal
                A_reach_goal = 1;
                need_continue = false;
                break;
            }
             else
            {
                break;
            }
        }



        while (posB > 0) {        //walk rat B
            cur = stackB[posB - 1];
            B_has_visited[cur.z][cur.x][cur.y] = true;
            // printf("%d %d %d %d\n", cur.z, cur.x, cur.y, cur.dir);
            have_been[1] = true;
            int pass_or_not=0;
            int i;
            for (i = cur.dir; i < 4; i++) {

                locate tmp = cur;
                tmp.x = cur.x + dir_B[i][0];
                tmp.y = cur.y + dir_B[i][1];
                tmp.dir = 0;

                // printf(" %d %d %d %d\n", tmp.z, tmp.x, tmp.y, tmp.dir);
                if (maze[tmp.z][tmp.x][tmp.y] != wall && B_has_visited[tmp.z][tmp.x][tmp.y] == false) {

                          if (maze[tmp.z][tmp.x][tmp.y] == stair ) {  //ratB go down the stair

                            tmp.z = 0;
                      }
                    else
                    {
                        stackB[posB - 1].dir = i + 1;    //the every place of direction ratB has visited
                    }

                    stackB[posB++] = tmp;
                    pass_or_not = 1;
                    break;
                }
            }
            if (pass_or_not == 0) {       //rat go back
                posB--;
                break;
            }
            if (stackB[posB - 1].z == 0 && stackB[posB - 1].x == 1 && stackB[posB - 1].y == 1) {    //ratB get the goal
                 B_reach_goal = 1;
                need_continue = false;
                break;
            }
             else
            {
                break;
           }
        }


         if (stackA[posA - 1].z == stackB[posB - 1].z && stackA[posA - 1].x == stackB[posB - 1].x && stackA[posA - 1].y == stackB[posB - 1].y)
        {
            fprintf(ptr,"Rats met each other in(%d,%d,%d)\n", stackB[posB].z,stackB[posB - 1].x, stackB[posB - 1].y);
            printf("%d", count);
            need_continue = false;
        }
        else if (A_reach_goal || B_reach_goal) {
            fprintf(ptr,"Rats didn't meet each other in the maze.\n");
            printf("%d", count);
            need_continue = false;
        }
        else if(!have_been[0]){
            printf("\nNo road for mouse A\n");
            break;
        }
        else if(!have_been[1]){
            printf("\nNo road for mouse B\n");
            break;
        }
        else {
            fprintf(ptr,"%dratA(%d,%d,%d)\n", count, stackA[posA - 1].z, stackA[posA - 1].x,stackA[posA - 1].y);
            fprintf(ptr,"ratB(%d,%d,%d)\n", stackB[posB - 1].z, stackB[posB - 1].x,stackB[posB - 1].y);
        }

    }


    fclose(ptr);

    return 0;
}
