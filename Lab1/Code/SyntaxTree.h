//
// Created by aurora on 3/14/24.
//

#ifndef CPLAB_SYNTAXTREE_H
#define CPLAB_SYNTAXTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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


typedef struct Node
{
    NodeData data;
    bool is_token; 
    int child_count;
    struct Node** children; // create children nodes by count
} Node;



Node* createTokenNode(int ln, Type val, char* spec);

Node* createVariableNode(int ln, Type val, char* spec, int count, Node** kids);



#endif //CPLAB_SYNTAXTREE_H
