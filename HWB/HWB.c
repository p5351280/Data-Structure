#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#define MAX 10000
#define TARGET_ONLY_CHILD ((target->left) ? (target->left) : (target->right))

typedef struct node* node_ptr;
typedef struct node{
    int data;
    bool visit;
    node_ptr left;
    node_ptr right;
    node_ptr parent;
}Node;

node_ptr search(int num, node_ptr root){
    while(root){
        if(num == root->data)   return root;
        else if(num > root->data)    root = root->right;
        else    root = root->left;
    }
    return NULL;
}

void delete(node_ptr target, node_ptr *root){
    
    /* have no child */
    if(!target->left && !target->right){
        if(!target->parent) *root = NULL;
        else if(target->parent->left == target)    target->parent->left = NULL;
        else    target->parent->right = NULL;
    }
    
    /* have a child */
    else if(!target->left || !target->right){
        TARGET_ONLY_CHILD->parent = target->parent;
        if(!target->parent) *root = TARGET_ONLY_CHILD;
        else if(target->parent->left == target)  target->parent->left = TARGET_ONLY_CHILD;
        else    target->parent->right = TARGET_ONLY_CHILD;
    }
    
    /* have two child */
    else{
        node_ptr temp;
        temp = target->right;
        while(temp->left) temp = temp->left;
        target->data = temp->data;
        delete(temp, root);
    }
}

void insert(int num, node_ptr *root){
    node_ptr temp, ptr;
    temp = malloc(sizeof(Node));
    temp->data = num;
    temp->visit = false;
    temp->left = NULL;
    temp->right = NULL;
    temp->parent = NULL;
    if(!*root)   *root = temp;
    else{
        ptr = *root;
        while(ptr){
            if(ptr->data == num){
                printf("%d already in the tree!\n", num);
                break;
            }
            else if(ptr->data > num){
                if(ptr->left)
                    ptr = ptr->left;
                else{
                    temp->parent = ptr;
                    ptr->left = temp;
                    break;
                }
                
            }
            else{
                if(ptr->right)
                    ptr = ptr->right;
                else{
                    temp->parent = ptr;
                    ptr->right = temp;
                    break;
                }
            }
        }
    }
}

void pre_order(node_ptr root){
    if(root){
        printf("%d ", root->data);
        pre_order(root->left);
        pre_order(root->right);
    }
}

void in_order(node_ptr root){
    if(root){
        in_order(root->left);
        printf("%d ", root->data);
        in_order(root->right);
    }
}

void post_order(node_ptr root){
    if(root){
        post_order(root->left);
        post_order(root->right);
        printf("%d ", root->data);
    }
}

void level_order(node_ptr root){
    if(!root){
        return;
    }
        
    node_ptr *queue;
    int n=1000;
    queue=malloc(sizeof(Node)*n);
    int rear=0,front=0;
    queue[front++]=root;
    while(1){
        node_ptr ptr;
        ptr=queue[rear++];
        if(rear>front)
            break;
        printf("%d ",ptr->data);
        if((front+1)==n){
            n=n*2;
            queue = realloc(queue,sizeof(Node)*n);
        }
        if(ptr->left){
            queue[front++]=ptr->left;
        }
        if(ptr->right){
            queue[front++]=ptr->right;
        }
    }
}

void binary_tree(){
    int choose, num;
    node_ptr root = NULL, judge;
    while(1){
        printf("(1)Insert (2)Search (3)Delete (4)Inorder (5)Levelorder (6)Back to menu : ");
        scanf("%d", &choose);
        switch (choose) {
            case 1:
                printf("Enter the number you want to insert : ");
                scanf("%d", &num);
                insert(num, &root);
                break;
                
            case 2:
                printf("Enter the number you want to search : ");
                scanf("%d", &num);
                judge = search(num, root);
                if(judge)   printf("Find %d!\n", num);
                else        printf("No find %d!\n", num);
                break;
                
            case 3:
                printf("Enter the number you want to delete : ");
                scanf("%d", &num);
                judge = search(num, root);
                if(judge){
                    delete(judge, &root);
                    printf("Success delete %d!\n", num);
                }
                else
                    printf("No find %d!\n", num);
                break;
                
            case 4:
                in_order(root);
                printf("\n");
                break;
                
            case 5:
                level_order(root);
                printf("\n");
                break;
                
            case 6:
                return;
                break;
                
            default:
                printf("Wrong choose!\n");
                break;
        }
    }
}

bool check_bomb(int num, int bomb){
    while(num){
        if(num%10 == bomb)
            return true;
        else
            num/=10;
    }
    return false;
}

bool search_path(node_ptr root, int bomb, int target, int *count, int *path){
    while(root){
        
        /* check for bomb */
        if(check_bomb(root->data, bomb)){
            if(!root->visit){    //if it hasn't visit
                root->visit = true;
                if(!root->left && !root->right)
                    continue;
                else if(root->left)
                    delete(root->left, &root);
                else
                    delete(root->right, &root);
            }
        }
        
        /* start to check path */
        if(root->data == target){
            path[(*count)++] = root->data;
            return true;
        }
        else if(root->data < target){
            if(root->right){
                path[(*count)++] = root->data;
                root = root->right;
            }
            else
                return false;
        }
        else{
            if(root->left){
                path[(*count)++] = root->data;
                root = root->left;
            }
            else
                return false;
        }
    }
    return 0;
}

void treasure_hunter(){
    while(1){
        /* input data from file */
        node_ptr root = NULL;
        printf("input the file name : ");
        char file[100];
        scanf("%s", file);
        int num;
        FILE* fin = fopen(file, "r");
        while(fscanf(fin, "%d", &num)==1)
            insert(num, &root);
        if(fin) printf("Load file success\n");
        fclose(fin);

        /* user input */
        int key, treasure, bomb;
        printf("Please input the key location : ");
        scanf("%d",&key);
        printf("Please input the treasure location : ");
        scanf(" %d",&treasure);
        do{
            printf("Please input the bomb number (0~9) : ");
            scanf("%d",&bomb);
            if(bomb/10 || bomb<0) printf("ERROR! Please check bomb number\n");
        } while(bomb/10 || bomb<0);
        
        /* key path */
        int k_path[MAX]={0};
        int k_count = 0;
        bool k_find;
        k_find = search_path(root, bomb, key, &k_count, k_path);
        
        /* treasure path */
        int t_path[MAX]={0};
        int t_count = 0;
        bool t_find;
        t_find = search_path(root, bomb, treasure, &t_count, t_path);
        
        /* check for overlap */
        int same=0;
        while(same<k_count && same<t_count){
            if(k_path[same] == t_path[same])
                same++;
            else
                break;
        }
        
        /* find the road for both */
        if(k_find && t_find){
            printf("Adventurer successfully found the treasure.\n");
            int k=k_count, t=t_count;
            int j;
            printf("%d",k_path[0]);
            for(j=1; j<k; j++)
                printf("->%d",k_path[j]);
            for(j=k-2; j>=same-1; j--)
                printf("->%d",k_path[j]);
            for(j=same; j<t; j++)
                printf("->%d",t_path[j]);
            printf("\n");
        }
        
        /* key isn't find */
        else if(!k_find)
            printf("key is not found.\n");
        
        /* treasure isn't find */
        else
            printf("treasure is not found.\n");
        
        printf("(1)Continue (2)Back to menu: ");
        int choose;
        scanf("%d", &choose);
        switch(choose){
            case 1:
                break;
            case 2:
                return;
                break;
            default:
                printf("Wrong input\n");
                break;
        }
    }

}
int main(){
    int choose;
    while(1){
        printf("(1)Binary Search Tree (2)Treasure Hunter (3)Exit: ");
        scanf("%d", &choose);
        switch(choose){
            case 1:
                binary_tree();
                break;
            case 2:
                treasure_hunter();
                break;
            case 3:
                return 0;
            default:
                printf("Wrong input\n");
                break;
        }
    }
    return 0;
}
///Users/Shuo-En/Downloads/HWB/exmap3.txt
