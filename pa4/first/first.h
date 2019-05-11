#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<ctype.h>

void freeCache();
void buildCache(int, int);
int searchCache(unsigned long long int**, unsigned long long int,int,unsigned long long int,int,int);
unsigned long long int getIndex(unsigned  long long int,int,int);
unsigned long long int getTag(unsigned long long int, int,int);
void lruInsert(unsigned long long int**,unsigned long long int,int,int,unsigned long long int,unsigned long long int);
void resortCache(unsigned long long int**, unsigned long long int, int);
int check_if_in_cache(unsigned long long int** , unsigned long long int ,int ,unsigned long long int , unsigned long long int );
int getAssoc(char*);
//void printCache(unsigned long long int**,int);
void prefetchInsert(unsigned long long int**,int,unsigned long long int,unsigned long long int,int,int,unsigned long long int);
int getAssoc(char* assoc){
    // printf("associativity: %s\n", assoc);
    
    if(strcmp(assoc, "direct") == 0) return -1;
    else if(strcmp(assoc, "assoc") == 0) return -2;

    char* checkAssoc = (char*) malloc(sizeof(char)*strlen(assoc)+1);
    strcpy(checkAssoc, assoc);
    char* strtoken = strtok(checkAssoc, ":");
    strtoken = strtok(NULL, ":");
     return atoi(strtoken);
   // free(strtoken);
   // free(checkAssoc);    

}
int powerOfTwo(int n){
    if(n <= 0){ //this test will not work for negative numbers and if n is zero
        return 0;
    }
    return ((n & (n-1)) == 0);
}
