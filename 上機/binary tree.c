#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#define MAX 10000
#define TARGET_ONLY_CHILD ((target->left) ? (target->left) : (target->right))

typedef struct node* node_ptr;
typedef struct node{
    int data;
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

void delete(node_ptr target){
    if(!target->left && !target->right){
        if(target->parent->left == target)    target->parent->left = NULL;
        else    target->parent->right = NULL;
    }
    else if(!target->left || !target->right){
        TARGET_ONLY_CHILD->parent = target->parent;
        if(target->parent->left == target)  target->parent->left = TARGET_ONLY_CHILD;
        else    target->parent->right = TARGET_ONLY_CHILD;
    }
    else{
        node_ptr temp;
        temp = target->right;
        while(temp->left) temp = temp->left;
        target->data = temp->data;
        delete(temp);
    }
}

void insert(int num, node_ptr *root){
    node_ptr temp, ptr;
    temp = malloc(sizeof(Node));
    temp->data = num;
    temp->left = NULL;
    temp->right = NULL;
    temp->parent = NULL;
    if(!*root)   *root = temp;
    else{
        ptr = *root;
        while(ptr){
            if(ptr->data == num){
                printf("%d already in the tree\n", num);
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

void pre(node_ptr root){
    if(root){
        printf("%d ", root->data);
        pre(root->left);
        pre(root->right);
    }
}

void in(node_ptr root){
    if(root){
        in(root->left);
        printf("%d ", root->data);
        in(root->right);
    }
}

void post(node_ptr root){
    if(root){
        post(root->left);
        post(root->right);
        printf("%d ", root->data);
    }
}

int main(){
    int num;
    node_ptr root = NULL, judge;
    while(scanf("%d", &num)){
        if(num == 0)    break;
        insert(num, &root);
    }
    pre(root);
    judge = search(13, root);
    if(!judge)  printf("Can't find 13 in the tree.\n");
    delete(judge);
    printf("\n\n\n\n");
    pre(root);
    return 0;
}
