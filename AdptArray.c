#include <stdio.h>
#include <stdlib.h>
#include "AdptArray.h"
#include <assert.h>
#include <memory.h>
#include <limits.h>
int max =0;
typedef struct AdptArray_
{
    int length;
    PElement * itemArray;
    COPY_FUNC copyFunc;
    DEL_FUNC delFunc;
    PRINT_FUNC printFunc;

}ADAPT_ARRAY;


PAdptArray CreateAdptArray(COPY_FUNC copy , DEL_FUNC del , PRINT_FUNC print){
    PAdptArray adaptP;
    if(adaptP=(PAdptArray)malloc(sizeof(ADAPT_ARRAY))){
        max=0;
        adaptP->itemArray=NULL;
        adaptP->copyFunc=copy;
        adaptP->delFunc=del;
        adaptP->printFunc=print;
        adaptP->length=INT_MIN;
        return adaptP;
    }
    else{
        return NULL;
    }
}

//Need to revisit this code and review it again now fails on harry potter probably because of if cond
Result SetAdptArrayAt(PAdptArray arr , int index  , PElement item){
    if(!item){return FAIL;}
    if(index<0){return FAIL;}
    if(arr){
    if(index>arr->length){arr->length = index+1;}
    if(index>=max){
        PElement * new_array = NULL;
        int old= max;
        if(max==0&&index==0){max = 2;}
        else{max = index*2;}
        if(new_array = (PElement *) calloc(max,sizeof(PElement))){
            memcpy(new_array,arr->itemArray,old*sizeof(PElement));
            free(arr->itemArray);
            arr->itemArray=new_array;
            arr->itemArray[index]=arr->copyFunc(item);
        }else{
            return FAIL;
        }
    } else if(index>0&&index<max){
        if(arr->itemArray[index]){
            arr->delFunc(arr->itemArray[index]);
            arr->itemArray[index]=arr->copyFunc(item);
        }else{
            arr->itemArray[index]=arr->copyFunc(item);
        }
    }return SUCCESS;
    }else{
        return FAIL;
    }
    }

void DeleteAdptArray(PAdptArray arr){
    if(arr){
    for(int i=0 ; i<arr->length;i++){
        if(arr->itemArray[i]){
            arr->delFunc(arr->itemArray[i]);
        }
    }
    free(arr->itemArray);
    free(arr);
    }
}

PElement GetAdptArrayAt(PAdptArray arr, int index){
    if(arr&&arr->itemArray){
    if(index < max && index >=0){
        if(arr->itemArray[index]){
        return arr->copyFunc(arr->itemArray[index]);
        }
    }
}
else{return NULL;}
}
int GetAdptArraySize(PAdptArray arr){
    if(arr&&arr->itemArray){
    return arr->length;}
    else{
        return NULL;
    }
}

void PrintDB(PAdptArray arr){
    if(arr&&arr->itemArray){
    for(int i=0;i<arr->length;i++){
        if(arr->itemArray[i]){
        arr->printFunc(arr->itemArray[i]);}
    }
    }
}
