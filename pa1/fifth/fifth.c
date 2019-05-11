#include <stdio.h>
#include <stdlib.h>
#include<ctype.h>


void findVowels(char*);
int main(int argc, char** argv){

    if(argc == 1){
        printf("Incorrect number of arguments.");
    }
    
   int i = 0; 
   for(i = 1; i < argc; i++){
        findVowels(argv[i]);
    }
    printf("\n");
}
void findVowels(char* word){

    int x = 0;

    while(word[x] != '\0'){
        if((word[x] == 'A') ||(word[x] == 'a') ||(word[x] == 'E') ||(word[x] == 'e') ||(word[x] == 'I') ||(word[x] == 'i') ||(word[x] == 'O') ||(word[x] == 'o') ||(word[x] == 'U') ||(word[x] == 'u')) 
            printf("%c",word[x]);
        x++;
    }


}
