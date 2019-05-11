#include <stdlib.h>
#include <stdio.h>


int get(unsigned short, int);
void isPalindrome(unsigned short);

int main(int argc, char** argv){

    if(argc != 2){
        return 0;
    }   
    
    unsigned short num = atoi(argv[1]);
    
    isPalindrome(num);
    
    return 0;
}
int get(unsigned short x, int n){   return (x >> n) &1; }
void isPalindrome(unsigned short num){
 
    int i = 0; 
    int j = 15 - i;

        while( i < j){   
            int bit1 = get(num, i);
            int bit2 = get(num , j);

            if(bit1 != bit2){
                printf("Not-Palindrome\n");
                return;
            }

            i++;
            j = 15 - i;
        }    
    printf("Is-Palindrome\n");
}
