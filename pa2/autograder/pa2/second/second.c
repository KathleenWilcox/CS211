#include <stdlib.h>
#include <stdio.h>


int get(unsigned short, int);
void findParity(unsigned short);

int main(int argc, char** argv){

    if(argc != 2){
        return 0;
    }   

    int  num = atoi(argv[1]);
     
    findParity(num);
    
    return 0;
}
int get(unsigned short x,int n){ return (x >> n) & 1; }

void findParity(unsigned short x){
  
    int consecutiveOne = 0; 
    int numPairs = 0;
    int i = 0; 
    int count = 0;
    
    while( x != 0){
        i = get(x, 0);
             
        if(i == 1){
            count++;
            
            if(consecutiveOne == 0){
                consecutiveOne = 1;
            }
            else{
                numPairs++;
                consecutiveOne = 0;
            }
        }
    else{
        consecutiveOne = 0;
    }
    
        x = (x >> 1);
    }
    
    if(count % 2 == 0){
        printf("Even-Parity\t%d\n",numPairs);
    }
    else{
        printf("Odd-Parity\t%d\n",numPairs);
    }
}
