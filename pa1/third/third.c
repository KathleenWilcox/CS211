#include <stdio.h>
#include <stdlib.h>
#define TABLE_SIZE 10000




typedef struct _node{

int data;
struct _node* next;

}node;


node* insert(node*, int);
void search(node*,int);
void freeTable(node**);



int collisionCount = 0;
int searchCount = 0;





int main(int argc, char** argv){

    
    if(argc != 2){
        
        printf("incorrect number of arguemnts.");
        exit(1);
    
    }

    FILE* f;
    
    f = fopen(argv[1],"r");
    

    if(f == NULL){
    
        exit(1);
    }

    
    char request;
    int num;
    node** hTable = (node**) malloc(sizeof(node*)*TABLE_SIZE);
    
    while(fscanf(f,"%c %d\n", &request, &num) != EOF){

        if(request == 'i'){
            

            int index = abs(num) % TABLE_SIZE;

            hTable[index] = insert(hTable[index], num);
        
        }
        if(request == 's'){

            int index = abs(num) % TABLE_SIZE;
            search(hTable[index], num);

        }
    }

   /* 
    fscanf(f,"%c %d", &request, &num);
        if(request == 'i'){
            int index = abs(num) % TABLE_SIZE;
            hTable[index] = insert(hTable[index], num);
        }
        if(request == 's'){

            int index = abs(num) % TABLE_SIZE;
            search(hTable[index], num);

        }

    */
        printf("%d\n%d\n",collisionCount, searchCount);
        freeTable(hTable);
        free(hTable);
        fclose(f);
}



node* insert(node* front, int num){

    if(front == NULL){
    
        node* newFront = (node*) malloc(sizeof(node));
        newFront->data = num;
        newFront->next = NULL;
        return newFront;
    }
    
    node* new = (node*) malloc(sizeof(node));
    new->data = num;
    new->next = front;
    collisionCount++;
    return new;

}
void search(node* front, int num){
    
    if(front == NULL){
        return;
    }


    node* ptr = front;
    
    for( ptr = front; ptr != NULL; ptr= ptr->next){
        
        if(ptr->data == num){
     //       printf("search for%d\n", num); 
            searchCount++;
            return; 
        }
    }
}
void freeTable(node** table){

    int index = 0;
    node* ptr = NULL;
    node* prev  = NULL;
 
    for(index = 0; index < TABLE_SIZE; index++){
        ptr = table[index];
        prev = NULL;
        while(ptr != NULL){
            
            if(prev != NULL){
                free(prev);
            }
            prev = ptr;
            ptr = ptr->next;
        }
        if(prev != NULL){
            free(prev);
        }

    }
} 
    


