#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
    int data;
    struct _node* left;
    struct _node* right;
}node;


node* insert(node*, int);
void print(node*);
void freeTheTree(node*);

int main(int argc, char** argv){
    
    if(argc != 2){
        printf("Incorrect number of arguments.");
        return 0;
    }
    
    FILE* f;
    f = fopen(argv[1], "r");
    if(f == NULL){
        printf("File does not exist.");
        return 0;
    }

    char request;
    int num;
    node* BST = NULL;

    while(fscanf(f,"%c %d\n",&request, &num) != EOF){
        if(request == 'i'){
            BST  =  insert(BST, num);
        }
    }
    print(BST);
    freeTheTree(BST);
    printf("\n");
    fclose(f);
}
node* insert(node* BST, int num){

    if(BST == NULL){
        node* firstInsert = (node*) malloc(sizeof(node));
        firstInsert->data = num;
        firstInsert->left = NULL;
        firstInsert->right = NULL;
        return firstInsert;
    }
    
    node* ptr = BST;
    node* parent = NULL;    
    int left = 0; 
    while(ptr != NULL){
        
        if(ptr->data == num){
            return BST;
        }else if(ptr->data > num){
            parent = ptr;
            left = 1;
            ptr = ptr->left;
        }else if(ptr->data < num){
            parent = ptr;
            left = 0;
            ptr = ptr->right;
        }
    }
    

    node* temp = (node*) malloc(sizeof(node));
    temp->data = num;
    temp->left = NULL;
    temp->right = NULL;
    if( left == 0 ){
        parent->right = temp;   
    }else{
        parent->left = temp;        
    }
    
    return BST;
}
void print(node* root){
    if(root == NULL){
        return;
    }
    
    print(root->left);
    printf("%d\t", root->data);
    print(root->right);

}
void freeTheTree(node* BST){
    if(BST == NULL){
        return;
    }

    freeTheTree(BST->left);
    freeTheTree(BST->right);
    free(BST);
}


