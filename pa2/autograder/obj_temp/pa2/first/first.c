#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int set(unsigned short, int, int);
int get(unsigned short, int);
int  comp(unsigned short, int);


int main(int argc, char** argv){


    if(argc != 2){
        return 0;
    }
    
    FILE* f = fopen(argv[1], "r");

    char setstr[] = "set";
    char compstr[] = "comp";
    char getstr[] = "get";
    char* request = (char*) malloc(sizeof(char)*5);
    unsigned short x; 
    fscanf(f, "%hu", &x);
    int n, v;

    
    if(f == NULL){
        return 0;
    }
    
    while(fscanf(f,"%s %d %d\n", request, &n, &v)!= EOF){
               
        if(strcmp(request,setstr)== 0){
            x = set(x, n, v);
            printf("%d\n",x);
        }
        else if(strcmp(request,getstr) == 0){
            printf("%d\n", get(x,n));
        }
        else if(strcmp(request,compstr) == 0){
            x= comp(x,n);
            printf("%d\n", x); 
        }
    }
    
    fclose(f);
    free(request);  
    return 0;
}
int set(unsigned short x,int n,int v){
    
    if(v == 0){ 
        return x & ~(1 << n);   
    }   
        return x |(1 << n);
        

}

int get(unsigned short x, int n){

    return((x >> n) &1);
    

}
int comp(unsigned short x, int n){
    
    int bit = !(get(x, n));
    //printf("this bit we are taking comp of: %d\n", bit);
    return  set(x, n, bit);

}











