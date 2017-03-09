#include <stdio.h>
#include <string.h>
#define MAX 500
#define INFINITY 999999999

int find_root(int i, int* parent){
    while(parent[i])    //if parent[i]=0, i is the root of the tree
        i = parent[i];
    return i;
}

int check_root(int i, int j, int* parent){
    if(i == j)  return 0;   //have the same root
    else{   //have no the same root
        parent[j] = i;  //set i as j's parent
        return 1;
    }
}

int main(){
    while(1){
        int cost[MAX][MAX]={{0}}, parent[MAX]={0};
        char file[MAX], *find;
        printf("Please input file name:");
        fgets(file, MAX, stdin);
        find = strchr(file, '\n');
        *find = '\0';
        FILE* fin = fopen(file, "r");
        int size, count=1, sum=0, i, j;
        fscanf(fin, "%d", &size);
        for(i=1; i<=size; i++)
            for(j=1; j<=size; j++){
                fscanf(fin, "%d", &cost[i][j]);
                if(!cost[i][j]) //don't have edge between i and j
                    cost[i][j] = INFINITY;
            }
        printf("\nThe edges of Minimum Cost Spanning Tree are\n");
        while(count < size){    //there will have size-1 edges
            int min = INFINITY, u=0, v=0, a=0, b=0; //a and b store the edge's start and end
            for(i=1; i<=size; i++)  //find minimum
                for(j=1; j<=size; j++){
                    if(cost[i][j] < min){
                        u = a = i;
                        v = b = j;
                        min = cost[i][j];
                    }
                }
            u = find_root(u, parent);   //make sure the root of spanning tree for u
            v = find_root(v, parent);   //make sure the root of spanning tree for v
            if(check_root(u, v, parent)){ //if have cycle(u and v has same root) will return 0
                printf(" Edge %d :<%d %d> cost %d\n", count++, a, b, cost[a][b]);
                sum += cost[a][b];
            }
            cost[a][b] = cost[b][a] = INFINITY;
        }
        printf(" Minimum Cost = %d\n\n", sum);
    }
    return 0;
}

///Users/Shuo-En/Downloads/DS HWC/1 - kruskal/input.txt

