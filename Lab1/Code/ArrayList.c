#include "ArrayList.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <memory.h>

ArrayList* ArrayListCreate(int data_size_, int capacity){
    ArrayList* result = (ArrayList*)malloc(sizeof(ArrayList));
    result->current = 0;
    result->size = capacity;
    result->data_size = data_size_;
    result->data = malloc(data_size_*capacity);
    memcmp(result->data, 0, data_size_*capacity);
    return result;
}

void ArrayListDestroy(ArrayList* array){
    assert(array != NULL);
    array->size = 0;
    array->current = 0;
    array->data_size = 0;
    free(array->data);
    array->data = NULL;
}

void ArrayListClear(ArrayList* array){
    for(int i = 0; i < array->current; i++){
        memset(array->data[i], 0, array->data_size);
    }
    array->current = 0;
}

int ArrayListSize(ArrayList* array){
    return array->current;
}

void ArrayListInsert(ArrayList* array, int pos, void* data_){
    assert(array->current >= pos && pos >= 0);
    for(int i = array->current; i > pos; i--){
        memcpy(array->data[i], array->data[i-1], array->data_size);
    }
    memcpy(array->data[pos], data_, array->data_size);
    if(array->current == array->size){
        ArrayListGrow(array);
    }
    return true;
}

void ArrayListRemove(ArrayList* array, int pos){
    assert(array->current > pos && pos >= 0);
    for(int i = pos; i < array->current - 1; i++){
        memcpy(array->data[i], array->data[i+1], array->data_size);
    }
    array->current--;
}

bool ArrayListContains(ArrayList* array, void* data_){
    bool result = false;
    for(int i = 0 ; i < array->current; i++){
        if(memcmp(data_, array->data[i], array->data_size) == 0){
            result = true;
            break;
        }
    }
    return result;
}

void* ArrayListGet(ArrayList* array, int pos){
    assert(array->current > pos && pos >= 0);
    return &(array->data[pos]);
}

static void ArrayListGrow(ArrayList* array){
    array->size = array->size * 2;
    void* new_data = malloc(array->data_size * array->size);
    for(int i = 0; i < current; i++){
        memcpy(new_data[i], array->data[i], array->data_size);
    }
    void* tem = array->data;
    array->data = new_data;
    free(tem);
}

