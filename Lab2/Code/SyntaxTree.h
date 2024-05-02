//
// Created by aurora on 3/14/24.
//

#ifndef CPLAB_SYNTAXTREE_H
#define CPLAB_SYNTAXTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "SymbolTable.h"

typedef union Type
{
    int int_type;
    float float_type;
    char* string_type;
} Type;


typedef struct NodeData
{
    int lineno;
    Type value;
    char* specifier; // eg. "ID" "INT" "TYPE" "EXPLIST"
} NodeData;

//synthesize attribute
typedef struct SynSemanticInfo
{
    SemanticType semantic_type;
    bool canBeLeftVal; // only address
} SynSemanticInfo;

//inherited attribute
typedef struct InhSemanticInfo
{
    SemanticType specifier_type;
} InhSemanticInfo;

typedef struct Node
{
    NodeData data;
    bool is_token; 
    int child_count;
    struct Node** children; // create children nodes by count

    #ifdef __SYMBOLTABLE__
    SynSemanticInfo syn_semantics;
    InhSemanticInfo inh_semantics; //inherited attribute
    #endif
} Node;

#ifdef __SYMBOLTABLE__
void initSemanticInfo(Node* node);
#endif

Node* createTokenNode(int ln, Type val, char* spec);

Node* createVariableNode(int ln, Type val, char* spec, int count, Node** kids);



#endif //CPLAB_SYNTAXTREE_H
