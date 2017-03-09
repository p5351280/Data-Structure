#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX 500
#define INFINITY 999999999

int main(){
    while(1){
        int cost[MAX][MAX] = {{0}};
        bool visit[MAX] = {0};
        char file[MAX], *find;
        printf("Please input file name:");
        fgets(file, MAX, stdin);
        find = strchr(file, '\n');
        *find = '\0';
        FILE* fin = fopen(file, "r");
        int size, count=1, start, sum=0, i, j;
        fscanf(fin, "%d", &size);
        for(i=1; i<=size; i++)
            for(j=1; j<=size; j++){
                fscanf(fin, "%d", &cost[i][j]);
                if(!cost[i][j])     //don't have edge between i and j
                    cost[i][j] = INFINITY;
            }
        fscanf(fin, "%d", &start);
        visit[start] = true;    //the start point
        printf("\nThe edges of Minimum Cost Spanning Tree are\n");
        while(count < size){    //there will have size-1 edges
            int min = INFINITY, u = 0, v = 0;
            for(i=1; i<=size; i++){
                if(!visit[i])   continue;   //the start point should be visited before
                for(j=1; j<=size; j++){
                    if(cost[i][j] < min && !visit[j]){  //!visit[j] => avoid circular
                        u = i;
                        v = j;
                        min = cost[i][j];
                    }
                }
            }
            printf(" Edge %d :<%d %d> cost %d\n", count++, u, v, cost[u][v]);
            sum += cost[u][v];
            cost[u][v] = INFINITY;
            visit[v] = true;
        }
        printf(" Minimum Cost = %d\n\n", sum);
    }
    return 0;
}

 /*
/Users/Shuo-En/Downloads/DS HWC/2 - Prim/input.txt
/Users/Shuo-En/Downloads/DS HWC/2 - Prim/input2.txt
 */

