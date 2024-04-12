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
        case ARRAY: return isSameType(type1->val.array.elem, type2->val.array.elem);
        case STRUCT: {
            FieldList f1 = type1->val.structure;
            FieldList f2 = type2->val.structure;
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
            printf("Error type of definition!\n");
            return false;
        }
    }
}

void initTable(){
    if(symbol_table != NULL){
        freeTable();
    }
    symbol_table = ArrayListCreate(sizeof(struct SymbolPair_), 100); 
}

void freeTable(){
    ArrayListDestroy(symbol_table);
}

bool TableContains(SymbolPair symbol_pair){
    assert(symbol_pair != NULL);
    return TableContains(symbol_pair->name, symbol_pair->type);
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

bool TableContains(char* name, SemanticType type){
    assert(name != NULL && type != NULL);
    int size = ArrayListSize(symbol_table);
    SymbolPair pair;
    bool result = false;
    for(int i = 0; i < size; i++){
        pair = ArrayListGet(symbol_table, i);
        if(strcmp(pair->name, name) == 0 && isSameType(pair->type, type)){
            result = true;
            break;
        }
    }
    return result;
}


bool addSymbolPair(char* name, SemanticType type){
    if(TableContains(name) == -1){
        return false;
    }
    SymbolPair symbol_pair = (SymbolPair)malloc(sizeof(struct SymbolPair_));
    symbol_pair->name = name;
    symbol_pair->type = type;
    ArrayListInsert(symbol_table, ArrayListGet(symbol_table, ArrayListSize(symbol_table)), symbol_pair);
    return true;
}

SymbolPair TableGet(int index){
    return (SymbolPair)ArrayListGet(symbol_table, index);
}

SymbolPair TableGet(char* name){
    int i = TableContains(name);
    assert(i != -1);
    return TableGet(i);
}