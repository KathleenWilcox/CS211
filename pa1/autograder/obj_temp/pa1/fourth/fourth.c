#include <stdio.h>
#include <stdlib.h>


void printArray(int**, int, int);
void multiply(int**,int**,int,int,int);
void freeMatricies(int**, int**,int,int);
int main(int argc, char** argv){

    if(argc != 2){
        
        printf("Incorrect number of arguements.");
    }

    FILE* f;
    
    f = fopen(argv[1], "r");

    if( f == NULL){
        
        printf("File does not exist.");
        exit(1);
    }

    int row1;
    int col1;
    int row2;
    int col2;
     

    fscanf(f,"%d %d",&row1, &col1);
    

    int** matrix1 = (int**) malloc(sizeof(int*)*row1);
    
    int i = 0;
    int j = 0;

    for(i = 0; i < row1; i++){
        matrix1[i] = (int*) malloc(sizeof(int)*col1);
    }
    
    for(i = 0; i < row1; i++){
        for(j = 0; j < col1; j++){
            fscanf(f, "%d", &matrix1[i][j]);         
        }
    }
   // printArray(matrix1, row1, col1);
  
    
    fscanf(f,"%d %d",&row2, &col2);
    
 
    int** matrix2 = (int**) malloc(sizeof(int*)*row2);
    
    i = 0;
    j = 0;

    for(i = 0; i < row2; i++){
        matrix2[i] = (int*) malloc(sizeof(int)*col2);
    }
    
    for(i = 0; i < row2; i++){
        for(j = 0; j < col2; j++){
            fscanf(f, "%d", &matrix2[i][j]);         
        }
    }
    //printArray(matrix2, row2, col2);
    
    if(col1 != row2){
        printf("bad-matrices\n");
        return 0;
    }
    
    multiply(matrix1, matrix2, row1,row2,col2);
    freeMatricies(matrix1, matrix2, row1, row2);
    fclose(f);
}
void printArray(int** matrix, int rows, int cols){

    int i = 0;
    int j = 0;

    for(i = 0; i < rows; i++){
        for(j = 0; j < cols; j++){
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }

}
void multiply(int** matrix1, int** matrix2, int row1, int row2, int col2){
    
    int i = 0; 
    int j = 0;
    int k = 0;
    int sum =0;

    for( i = 0; i< row1; i++){
        for(j = 0; j < col2; j++){
            for(k = 0; k < row2; k++){
                sum += matrix1[i][k] * matrix2[k][j];
            }
            printf("%d",sum);
            if((j == col2 - 1) && (i == row1-1)){
            }else printf("\t");
            sum = 0;
        }
        if(i != row1-1)
            printf("\n");
            
    }

}
void freeMatricies(int** matrix1, int** matrix2, int row1, int row2){

    int i = 0;
    int j = 0;
    for(i = 0; i < row1; i++){
        free(matrix1[i]);
    }   
    free(matrix1);
    
    for(j = 0; j< row2; j++){
        free(matrix2[j]);
    }
    free(matrix2);
}





