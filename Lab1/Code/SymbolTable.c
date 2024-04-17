#include "SymbolTable.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

SymbolTable symbol_table = NULL;

bool isSameType(SemanticType type1, SemanticType type2){
    if(type1 == NULL && type2 == NULL){
        return true;
    }
    else if(type1 == NULL || type2 == NULL){
        return false;
    }
    // not NULL
    else{
        if(type1->kind != type2->kind){
            return false;
        }
        switch (type1->kind)
        {
        case BASIC: return type1->val.basic_val->basic_type == type2->val.basic_val->basic_type;
        case ARRAY: return isSameType(type1->val.array->elem, type2->val.array->elem);
        case STRUCTURE: {
            FieldList f1 = type1->val.structure->type->val.structure;
            FieldList f2 = type2->val.structure->type->val.structure;
            while(f1 != NULL && f2 != NULL){
                if(isSameType(f1->type, f2->type)){
                    f1 = f1->next;
                    f2 = f2->next;
                }
                else{
                    return false;
                }
            }
            if(f1 == NULL && f2 == NULL){
                return true;
            }
            return false;
        }
        case ERROR: return true;
        case FUNC: {
            ArgList a1 = type1->val.function;
            ArgList a2 = type2->val.function;
            while(a1 != NULL && a2 != NULL){
                if(isSameType(a1->type, a2->type)){
                    a1 = a1->next;
                    a2 = a2->next;
                }
                else{
                    return false;
                }
            }
            if(a1 == NULL && a2 == NULL){
                return true;
            }
            return false;
        }
        default:
            //printf("Error type of definition!\n");
            return false;
        }
    }
}

void initTable(){
    if(symbol_table != NULL){
        freeTable();
    }
    memset(handle, 0, 1000);
    symbol_table = ArrayListCreate(sizeof(struct SymbolPair_), 100); 
}

void freeTable(){
    ArrayListDestroy(symbol_table);
}


// return -1 if not contains, else return index
int TableContains(char* name){
    assert(name != NULL);
    int size = ArrayListSize(symbol_table);
    int result = -1;
    SymbolPair pair;
    for(int i = 0; i < size; i++){
        pair = ArrayListGet(symbol_table, i);
        if(strcmp(pair->name, name) == 0){
            result = i;
            break;
        }
    }
    return result;
}



bool addSymbolPair(char* name, SemanticType type){
    if(TableContains(name) != -1){
        return false;
    }
    SymbolPair symbol_pair = createSymbolPair();
    symbol_pair->name = name;
    symbol_pair->type = type;
    ArrayListInsert(symbol_table, ArrayListSize(symbol_table), (void *)symbol_pair);
    return true;
}

SymbolPair TableGetByIndex(int index){
    return (SymbolPair)ArrayListGet(symbol_table, index);
}

SymbolPair TableGet(char* name){
    int i = TableContains(name);
    assert(i != -1);
    return TableGetByIndex(i);
}

SemanticType createSemanticType(enum Kind kind){
    SemanticType type = (SemanticType)malloc(sizeof(struct Type_));
    memset(type, 0, sizeof(struct Type_));
    type->kind = kind;
    switch (kind)
    {
        case BASIC: type->val.basic_val = createBasicVal();break;
        case FUNC: type->val.function = createArgList();break;
        case STRUCTURE: type->val.structure = createFieldList();break;
        case ARRAY: type->val.array = createArray();break;
        default:
            break;
    }
    return type;
}

BasicVal createBasicVal(){
    BasicVal basic = (BasicVal)malloc(sizeof(struct BasicVal_));
    memset(basic, 0, sizeof(struct BasicVal_));
    return basic;
}

Array createArray(){
    Array array = (Array)malloc(sizeof(struct Array_));
    memset(array, 0, sizeof(struct Array_));
    array->elem = createSemanticType(NONE);
    return array;
}

FieldList createFieldList(){
    FieldList fields = (FieldList)malloc(sizeof(struct FieldList_));
    memset(fields, 0, sizeof(struct FieldList_));
    fields->type = createSemanticType(NONE);
    fields->name = createCharName();
    return fields;
}

ArgList createArgList(){
    ArgList args = (ArgList)malloc(sizeof(struct ArgList_));
    memset(args, 0, sizeof(struct ArgList_));
    args->type = createSemanticType(NONE);
    args->name = createCharName();
    return args;
}

SymbolPair createSymbolPair(){
    SymbolPair pair = (SymbolPair)malloc(sizeof(struct SymbolPair_));
    memset(pair, 0, sizeof(struct SymbolPair_));
    return pair;
}

char* createCharName(){
    char* result = (char*)malloc(100);
    memset(result, 0, 100);
    return result;
}


// helper function
void copySemanticType(SemanticType src, SemanticType dest){
    assert(src != NULL && dest != NULL);
    switch (src->kind)
    {
        case BASIC: dest->val.basic_val = createBasicVal();copyBasicVal(src->val.basic_val, dest->val.basic_val); break;
        case STRUCTURE: dest->val.structure = createFieldList();copyStructure(src->val.structure, dest->val.structure); break;
        case FUNC: dest->val.function = createArgList();;copyFunction(src->val.function, dest->val.function);break;
        case ARRAY: dest->val.array = createArray();copyArray(src->val.array, dest->val.array);break;
        default:
            break;
    }
    dest->kind = src->kind;
}
void copyStructure(FieldList src, FieldList dest){
    if(src == NULL){
        return ;
    }
    strcpy(dest->name, src->name);
    copySemanticType(src->type, dest->type);
    if(src->next != NULL){
        dest->next = createFieldList();
        copyStructure(src->next, dest->next);
    }
}
void copyArray(Array src, Array dest){
    if(src == NULL){
        return;
    }
    assert(dest != NULL);
    dest->size = src->size;
    copySemanticType(src->elem, dest->elem);
}
void copyFunction(ArgList src, ArgList dest){
    assert(src != NULL && dest != NULL);
    strcpy(dest->name, src->name);
    copySemanticType(src->type, dest->type);
    if(src->next != NULL){
        dest->next = createArgList();
        copyFunction(src->next, dest->next);
    }
}
void copyBasicVal(BasicVal src, BasicVal dest){
    assert(src != NULL && dest != NULL);
    dest->basic_type = src->basic_type;
    dest->val = src->val;
}
