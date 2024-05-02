//
// Created by aurora on 3/14/24.
//

#include "SyntaxTree.h"


Node* createTokenNode(int ln, Type val, char* spec){
    Node* node = (Node*)malloc(sizeof(Node));
    node->data.lineno = ln;
    node->data.value = val;
    node->data.specifier = (char*)malloc(strlen(spec));
    strcpy(node->data.specifier, spec);
    node->is_token = true;
    node->child_count = 0;
    node->children = NULL;
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
    return node;
}