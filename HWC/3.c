#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX 500
#define INFINITY 999999

//find the smallest distance from start (not yet visit)
int choose(int* distance, int size, bool* visit){
    int i, min = INFINITY, u=-1;
    for(i=1; i<=size; i++){
        if(distance[i]<min && !visit[i]){
            min = distance[i];
            u = i;
        }
    }
    return u;
}

int main(){
    while(1){
        int cost[MAX][MAX] = {{0}}, distance[MAX] = {0};
        bool visit[MAX] = {0};
        char file[MAX], *find;
        printf("Please input file name:");
        fgets(file, MAX, stdin);
        find = strchr(file, '\n');
        *find = '\0';
        FILE* fin = fopen(file, "r");
        int size, count, i, j;
        fscanf(fin, "%d", &size);
        for(i=1; i<=size; i++)
            for(j=1; j<=size; j++){
                fscanf(fin, "%d", &cost[i][j]);
                if(!cost[i][j])     //don't have edge between i and j
                    cost[i][j] = INFINITY;
            }
        int start, end;
        printf("Enter two vertices <start end>:");
        scanf("%d%d", &start, &end);
        getchar();
        for(i=1; i<=size; i++)
            distance[i] = cost[start][i];   //distance from start vertex
        distance[start] = 0;
        visit[start] = true;
        count = 1;
        while(count < size-1){
            int u;
            u = choose(distance, size, visit);  //choose the next vertices
            if(u<0) break;
//            printf("%d\t",u);
            visit[u] = true;
            for(i=1; i<=size; i++){
                if(!visit[i])   //avoid circular
                    if(distance[u]+cost[u][i] < distance[i])	//Dijkstra
                        distance[i] = distance[u]+cost[u][i];
//                    printf("%d %d\t", i, distance[i]);
            }
            count++;
//            printf("\n");
        }
        if(distance[end] == INFINITY)
            printf("The cost from %d to %d is : -1\n\n", start, end);
        else
            printf("The cost from %d to %d is : %d\n\n", start, end, distance[end]);
    }
    return 0;
}

 /*
/Users/Shuo-En/Downloads/DS HWC/3 - Dijkstra/input.txt
 */

