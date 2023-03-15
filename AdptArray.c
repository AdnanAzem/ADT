#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AdptArray.h"

#define MAX_ELEMENTS 1


// we use a structure to hold the data of each ADT varaivle instead of the globals
struct AdptArray_ {
    int size;
    int capacity;
    PElement *data;
    COPY_FUNC copyFunc;
    DEL_FUNC delFunc;
    PRINT_FUNC printFunc;
};

// init the array
void init(PAdptArray adptArray, COPY_FUNC copyFunc, DEL_FUNC delFunc,PRINT_FUNC printFunc){
    adptArray->size = 0;
    adptArray->capacity = MAX_ELEMENTS;
    adptArray->data[0] = NULL;
    adptArray->copyFunc = copyFunc;
    adptArray->delFunc = delFunc;
    adptArray->printFunc = printFunc;
}

// Function to create an array that nothing inside
PAdptArray CreateAdptArray(COPY_FUNC copyFunc, DEL_FUNC delFunc,PRINT_FUNC printFunc){
    PAdptArray adptArray = (PAdptArray) malloc(sizeof(struct AdptArray_));
    if(adptArray == NULL){
        return NULL;
    }
    adptArray->data = (PElement) malloc(MAX_ELEMENTS * sizeof(PElement));
    if(adptArray->data == NULL){
        free(adptArray);
        return NULL;
    }
    init(adptArray, copyFunc, delFunc, printFunc);
}

// Function to delete the array
void DeleteAdptArray(PAdptArray adptArray){
    if (adptArray == NULL)
        return;
    for (int i = 0; i < adptArray->size; ++i) {
        if (adptArray->data[i] != NULL) {
            adptArray->delFunc(adptArray->data[i]);
        }
        continue;
    }
    free(adptArray->data);
    free(adptArray);

}

// Function to set a copy of the element in a specific place
Result SetAdptArrayAt(PAdptArray adptArray, int pos, PElement element){
    if(pos < 0) return FAIL;
    if(pos > adptArray->capacity){
        PElement* newData = (PElement*) realloc(adptArray->data, (pos+1) * (sizeof (PElement)));
        if(newData == NULL) return FAIL;
        for (int i = adptArray->capacity; i < pos+1; i++) newData[i] = NULL;
        adptArray->data = newData;
        adptArray->capacity = (pos+1);
    }
    if (adptArray->data[pos] != NULL) adptArray->delFunc(adptArray->data[pos]);
    adptArray->data[pos] = adptArray->copyFunc(element);
    adptArray->size = adptArray->capacity;
    return SUCCESS;
}

// Function to get a copy element 
PElement GetAdptArrayAt(PAdptArray adptArray, int pos){
    ((pos < 0 || pos > adptArray->capacity || adptArray->data[pos] == NULL) ? NULL : adptArray->copyFunc(adptArray->data[pos]));
    // if(pos < 0 || pos > adptArray->capacity || adptArray->data[pos] == NULL){
    //     return NULL;
    // }
    // return adptArray->copyFunc(adptArray->data[pos]);

}

// Function to get the size of the array 
int GetAdptArraySize(PAdptArray adptArray){
    (adptArray == NULL ? -1 : adptArray->size);
}

// Function to print the elements of the array
void PrintDB(PAdptArray adptArray){
    for(int i = 0; i < adptArray->size; i++){
        // (adptArray->data[i] != NULL ? adptArray->printFunc(adptArray->data[i]) : continue );
        if(adptArray->data[i] != NULL){
            adptArray->printFunc(adptArray->data[i]);; 
        }
        continue;
    }
    


}