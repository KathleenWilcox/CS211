
#include <stdio.h>
#include <stdlib.h>




void first(char*); /*shows that function will be declared later*/
int* sortArrayAsc(int*, int);
int* sortArrayDesc(int*, int);

int main(int argc,char** argv){

    if(argc != 2){ /* ./first first.c has two arguemts, must make sure that correct num of args are inputted */
    
    printf("wrong number of arguments\n");     
     return 1;
    }
    
    first(argv[1]); /* argv[1] is the name of the file (i.e the second arguement) */

    return 0;
 
}

void first(char* file){

    int numEvens = 0;
    FILE* f;
    
    /* opening file */
    f = fopen(file, "r");

    if( f == NULL){
        printf("No such file.");
        exit(1);
    }

    int n = 0; /* going to be the size of the array*/
    fscanf(f, "%d", &n); /* gives n a value */
    int* nums = (int*) malloc(sizeof(int)*n); /* creates array of size n */
    //printf("%d\n",n);

    int i = 0;

    for(i = 0; i < n; i++){
        fscanf(f, "%d", &nums[i]); /* scans through file, puts each number in array */
        
        if(nums[i] % 2 == 0)
            numEvens++;
     } 
      
    fclose(f);

    int* evens = (int*) malloc(sizeof(int)*numEvens);
    int* odds = (int*) malloc(sizeof(int)*(n-numEvens));

    int j = 0;
    int evenIndex = 0;
    int oddIndex = 0;

    for( j = 0; j < n; j++){
        if(nums[j] % 2 == 0){
            evens[evenIndex] = nums[j];
            evenIndex++;
        }else{

            odds[oddIndex] = nums[j];
            oddIndex++;
        }
    }
    evens = sortArrayAsc(evens, numEvens);
    odds = sortArrayDesc(odds, n-numEvens);

   i = 0;
   for(i =0; i < numEvens; i++)
    {
        printf("%d\t", evens[i]);
    }
    
    j = 0;
    for(j = 0; j < (n-numEvens); j++){
        printf("%d\t", odds[j]);
    }

    printf("\n");
    
    free(evens);
    free(odds);
    free(nums);

}
int* sortArrayAsc(int* arr, int n ){

  int i = 0;
  for( i = 1; i < n; i++){
        int left = i - 1;
        int curr = i;



      while(left >= 0 && arr[curr] < arr[left]){
          int temp = arr[curr];
          arr[curr] = arr[left];
          arr[left] = temp;

          left--;
          curr = left + 1;
           
        } 
    }

    return arr;
}
int* sortArrayDesc(int* arr, int n ){

  int i = 0;
  for(i = 1; i < n; i++){
        int left = i - 1;
        int curr = i;

      while(left >= 0 && arr[curr] > arr[left]){
          int temp = arr[curr];
          arr[curr] = arr[left];
          arr[left] = temp;

          left--;
          curr = left + 1;

        }
    }

    return arr;


}


    



    






















