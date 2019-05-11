#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "first.h"
unsigned long long int** prefetchCache;
unsigned long long int** cache;
int hits=0;
int misses=0;
int sets=0;
int blockSize= 0;
int cacheSize =0;
int reads = 0;
int writes = 0;
int prefetchHits = 0;
int prefetchMisses  = 0;
int prefetchReads = 0;
int prefetchWrites = 0;
int nway = 0;

int main(int argc, char** argv){

    
    if(argc != 6){
        printf("error"); 
        return 0;
    }

    int sizeCache = atoi(argv[1]);    
    if(powerOfTwo(sizeCache) == 0){
        printf("error");
        return 0;
    }
    nway = getAssoc(argv[2]);
    
    if(nway != -1 && nway!= -2){
        if(powerOfTwo(nway) == 0){
            printf("error");
            return 0;
        }
    }

    int sizeBlock = atoi(argv[4]);
    
    if(powerOfTwo(sizeBlock) == 0){
        printf("error");
        return 0;
     }

    blockSize = sizeBlock;
    cacheSize = sizeCache;

    buildCache(sizeCache, sizeBlock);

    char idc[500];
    char request;
    char stringAddress[500];

    int blockOffset = log2(sizeBlock);
    int indexOffset = log2(sets);
    unsigned long long int myTag;
    int readLocation;
    int writeLocation;

    FILE* f = fopen(argv[5], "r");
    if(f == NULL){
        printf("error");
        return 0;
    }

    while(fscanf(f,"%s %c %s",idc,&request,stringAddress) == 3){
 
        unsigned long long int address = strtol(stringAddress,NULL,16);
        if(request == 'R'){
        unsigned long long int index = getIndex(address,blockOffset,indexOffset);
        readLocation =  searchCache(cache,address,nway,index,blockOffset,indexOffset);
            if(readLocation >= 0){
                hits++;
                resortCache(cache,index,readLocation);
            }   
            else{
                myTag = getTag(address,blockOffset,indexOffset);
                misses++;
                reads++;
                lruInsert(cache,address,blockSize,nway,index,myTag);
            }      
        }
        else {
            unsigned long long int index = getIndex(address,blockOffset,indexOffset);
            writeLocation = searchCache(cache, address, nway, index,blockOffset,indexOffset);           
            if(writeLocation >= 0){
                hits++;
                writes++;
                resortCache(cache,index,writeLocation);
            }
            else{
                myTag = getTag(address, blockOffset,indexOffset);
                misses++;
                writes++;
                reads++;
                lruInsert(cache,address,blockSize,nway,index,myTag);   
            }
        }

        //prefetch

        if(request == 'R'){
            unsigned long long int index = getIndex(address,blockOffset,indexOffset);
            readLocation =  searchCache(prefetchCache,address,nway,index,blockOffset,indexOffset);
            if(readLocation >= 0){
                prefetchHits++;
                resortCache(prefetchCache,index,readLocation);
            }   
            else{
                myTag = getTag(address,blockOffset,indexOffset);
                prefetchMisses++;
                prefetchReads++;
                lruInsert(prefetchCache,address,blockSize,nway,index,myTag);

                address += blockSize;
                unsigned long long int idx = getIndex(address, blockOffset, indexOffset);
                unsigned long long int tag = getTag(address, blockOffset, indexOffset);

                int writeLocation = searchCache(prefetchCache, address, nway, idx, blockOffset,indexOffset);

                if(writeLocation < 0) {
                    prefetchReads++;
                    lruInsert(prefetchCache, address, blockSize, nway, idx, tag);
                }
            }      
        }
        else {
            unsigned long long int index = getIndex(address,blockOffset,indexOffset);
            writeLocation = searchCache(prefetchCache, address, nway, index,blockOffset,indexOffset);           
            if(writeLocation >= 0){
                prefetchHits++;
                prefetchWrites++;
                resortCache(prefetchCache,index,writeLocation);
            }
            else{
                myTag = getTag(address, blockOffset,indexOffset);
                prefetchMisses++;
                prefetchWrites++;
                prefetchReads++;
                lruInsert(prefetchCache,address,blockSize,nway,index,myTag);   

                address += blockSize;
                unsigned long long int idx = getIndex(address, blockOffset, indexOffset);
                unsigned long long int tag = getTag(address, blockOffset, indexOffset);

                writeLocation = searchCache(prefetchCache, address, nway, idx, blockOffset,indexOffset);
                if(writeLocation < 0) {
                    prefetchReads++;
                    lruInsert(prefetchCache, address, blockSize, nway, idx, tag);
                }
            }
        }
        
    } 
    fclose(f);
    freeCache();
    printf("no-prefetch\n");
    printf("Memory reads: %d\n", reads);
    printf("Memory writes: %d\n", writes); 
    printf("Cache hits: %d\n", hits); 
    printf("Cache misses: %d\n", misses);
    printf("with-prefetch\n");   
    printf("Memory reads: %d\n", prefetchReads);
    printf("Memory writes: %d\n", prefetchWrites); 
    printf("Cache hits: %d\n", prefetchHits); 
    printf("Cache misses: %d\n", prefetchMisses);

    return 0;
}
void buildCache(int cacheSize, int blockSize){

    if(nway == -1){
        sets = (cacheSize/blockSize);
        nway = 1;
    }
    if(nway == -2){
        sets = 1;
        nway = cacheSize/blockSize;  
    }
    else{
        sets = (cacheSize/(blockSize*nway));
    }
    cache = (unsigned long long int**) malloc(sizeof(unsigned long long int*)*sets);
    prefetchCache  = (unsigned long long int**) malloc(sizeof(unsigned long long int*)*sets);
    int i;

    for(i = 0; i < sets; i++){
        cache[i] = (unsigned long long int*) malloc(sizeof(unsigned long long int)*nway);
        prefetchCache[i] = (unsigned long long int*) malloc(sizeof(unsigned long long int)*nway);
    }    
}
int searchCache(unsigned long long int** cache, unsigned long long int address,int nway,unsigned long long int index, int blockOffset, int setOffset){

    unsigned long long int tag = getTag(address,blockOffset,setOffset);
    int blockNum = 0;

        for(blockNum = 0; blockNum < nway; blockNum++){
            if(cache[index][blockNum] == tag){
                return blockNum;
            }
        }
        return -1;
}

unsigned long long int getIndex(unsigned long long int address, int blockOffset, int indexOffset){

    unsigned long long int setIndex = (address >> blockOffset) & ((1 << indexOffset) - 1);
    return setIndex;
}

unsigned long long int getTag(unsigned long long int address, int blockOffset, int setOffset){
    
    return  address >> (blockOffset+setOffset);
}
void lruInsert(unsigned long long int** cache, unsigned long long int address, int blockSize, int nway, unsigned long long int index, unsigned long long int tag){

    int blockNum = 0;
    
    for(blockNum = nway - 1; blockNum > 0; blockNum--){
        cache[index][blockNum] = cache[index][blockNum-1];
    }   
        cache[index][0] = tag;

}
void resortCache(unsigned long long int** cache,unsigned long long int index,int blockNum){
    unsigned long long int moveToFront = cache[index][blockNum];
    int i = 0;
    for(i = blockNum; i > 0; i--){
        cache[index][i] = cache[index][i-1];
    }
    cache[index][0] = moveToFront;
}
void freeCache(){

    int i = 0;

    for(i = 0; i < sets; i ++){
            free(cache[i]);
            free(prefetchCache[i]);
    }
   free(cache);
   free(prefetchCache);
}
















