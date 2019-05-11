#include <stdio.h>
#include <stdlib.h>

typedef struct _node{

    int data;
    struct _node *next;
}node;


node* insert(node*, int);
void delete(node*, int);
void printList(node*);
void freeList(node*);
int main(int argc, char** argv){

    if(argc != 2){
        printf("Wrong Number of arguments.");
    }


   char request;
   int num;
   FILE *f;
   

    f = fopen(argv[1], "r"); //opens file
    
    if(f == NULL){ //checks for a null/empty file
        printf("error");
        return 0;
    }

    node* front = NULL; // front of the LL

    while(fscanf(f,"%c %d\n",&request, &num) != EOF){ // scans through the file
        
           // if(front != NULL) { printList(front); } 
        
//        printf("%c, %d\n",request, num);
 
       if(request == 'i'){ // if request is insert 
           // printf("request i\n");     
            if(front == NULL){
                front = (node*) malloc(sizeof(node));
                front->data = num;
                front->next = NULL;
            }
            else{
             //    printf("insert\n");
                 front = insert(front, num);
                }              
        }
            
        if(request == 'd'){

            if(front == NULL){
                continue; 
            }
           // printf("request d\n");     

           // printf("delete\n");           
                if(num == front->data){
                    front = front->next;
                }
                else{ 
             //           printf("delete\n");
                        delete(front, num);
                    }
                
                
                
                
         }


        // what is syntax for next item in scanner
    
   
    }    

        

   // find number of nums in LL and print LL
 
      node* list = front;
      int numItems = 0;
    for( list = front; list!= NULL; list = list->next){
                numItems++;
     } 
               
       printf("%d\n",numItems);
       
    if(front != NULL)
        printList(front);
    freeList(front);
    fclose(f);
      return 0;
}

void printList(node* front){
   node* ptr = front;
   int prevVal = front->data;
    printf("%d\t",prevVal);
   while(ptr!= NULL){
        if(prevVal != ptr->data){
             printf("%d\t", ptr->data);
        }
        prevVal = ptr->data;
        ptr = ptr->next;
    }
    printf("\n");
}
void freeList(node* list){
    
    node* ptr = list;
    node* prev = NULL;

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










node* insert(node* front, int num){
    
            node* ptr = front;
            node* prev = NULL;

            while(ptr != NULL){
                if(num <= ptr->data && ptr == front){
                  node* newNode = (node*) malloc(sizeof(node));
                  newNode->data = num;
                  newNode->next = ptr;
                  front = newNode;
                  break;
                }
                
               else  if( num <= ptr->data){ 
                   node* new = (node*) malloc(sizeof(node));
                   new->data = num;
                   new->next = ptr;
                   prev->next = new;
                   break;
                } 
                
                prev = ptr;
                ptr = ptr->next;
                  
             }
             if(ptr == NULL){
                node* insert = (node*) malloc(sizeof(node));
                insert->data = num;
                prev->next = insert;
                insert->next= NULL;
            }
        return front;
}
void delete(node* front, int num){


            node* ptr = front;
            node* prev = NULL;
            
                
                while( ptr != NULL){
                
                    if(num == ptr->data){
                        prev->next = ptr->next;
                        free(ptr);
                        break;
                    }
                    
                    prev = ptr; 
                    ptr = ptr->next;

                }
}
















