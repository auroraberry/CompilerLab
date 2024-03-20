#include "SyntaxTreePrinter.h"


void printSyntaxTree(Node* node, int depth){
    if(node == NULL){
        return ;
    }
    for(int i = 0; i < depth; i++){
        printf("  ");
    }
    if(!node->is_token){
        printf("%s (%d)\n", node->data.specifier, node->data.lineno);
        for(int i = 0; i < node->child_count; i++){
            printSyntaxTree(node->children[i], depth + 1);
        }
    }
    else{
        
        if(strcmp(node->data.specifier, "ID") == 0){
            printf("%s: ", node->data.specifier);
            printf("%s", node->data.value.string_type);
        }
        else if(strcmp(node->data.specifier, "TYPE") == 0){
            printf("%s: ", node->data.specifier);
            printf("%s", node->data.value.string_type);
        }
        else if(strcmp(node->data.specifier, "INT") == 0){
            printf("%s: ", node->data.specifier);
            printf("%d", node->data.value.int_type);
        }
        else if(strcmp(node->data.specifier, "FLOAT") == 0){
            printf("%s: ", node->data.specifier);
            printf("%.6f", node->data.value.float_type);
        }
        printf("\n");
    }
}