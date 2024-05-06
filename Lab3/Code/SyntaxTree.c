//
// Created by aurora on 3/14/24.
//

#include "SyntaxTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


void initSemanticInfo(Node* node){
    node->inh_semantics.specifier_type = createSemanticType(NONE);
    node->syn_semantics.semantic_type = createSemanticType(NONE);
    node->syn_semantics.canBeLeftVal = false;
}


Node* createTokenNode(int ln, Type val, char* spec){
    Node* node = (Node*)malloc(sizeof(Node));
    node->data.lineno = ln;
    node->data.value = val;
    node->data.specifier = (char*)malloc(strlen(spec));
    strcpy(node->data.specifier, spec);
    node->is_token = true;
    node->child_count = 0;
    node->children = NULL;
    node->is_translated = false;

    #ifdef __SYMBOLTABLE__
        initSemanticInfo(node);
    #endif
    
    return node;
}


Node* createVariableNode(int ln, Type val, char* spec, int count, Node** kids){
    Node* node = (Node*)malloc(sizeof(Node));
    node->data.lineno = ln;
    node->data.value = val;
    node->data.specifier = (char*)malloc(strlen(spec));
    strcpy(node->data.specifier, spec);
    node->is_token = false;
    node->child_count = count;
    node->children = (Node**)malloc(sizeof(Node*)*count);
    for(int i = 0; i < count; i++){
        node->children[i] = kids[i];
    }
    node->is_translated = false;

    #ifdef __SYMBOLTABLE__
        initSemanticInfo(node);
    #endif
    
    return node;
}