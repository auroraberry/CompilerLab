#ifndef __ARRAYLIST__
#define __ARRAYLIST__
#include <stdbool.h>
typedef struct ArrayList_ ArrayList;


struct ArrayList_
{
    int current;
    int size;
    unsigned int data_size;
    void* data;
};

ArrayList* ArrayListCreate(int data_size_, int capacity);

void ArrayListDestroy(ArrayList* array);

void ArrayListClear(ArrayList* array);

int ArrayListSize(ArrayList* array);

void ArrayListInsert(ArrayList* array, int pos, void* data_);

void ArrayListRemove(ArrayList* array, int pos);

bool ArrayListContains(ArrayList* array, void* data_);

void* ArrayListGet(ArrayList* array, int pos);

static void ArrayListGrow(ArrayList* array);


#endif