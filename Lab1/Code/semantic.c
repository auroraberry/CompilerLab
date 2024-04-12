#include "semantic.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>
#include <assert.h>

SemanticType handleSpecifier(Node* node){
    SemanticType type = (SemanticType)malloc(sizeof(struct Type_));
    
}

void printError(int error_type, int lineno, char* msg){
    printf("Error type %d at Line%d: %s\n", error_type, lineno, msg);
}

// node is ID
void variableUsageBeforeDefinition(Node* node){
    int index = TableContains(node->data.value.string_type);
    if(index == -1) // not find ID definition
    {
        printError(1, node->data.lineno, "variable usage before definition!");
    }
    else if(TableGet(index)->type->kind == FUNC) // ID is not variable, is function
    {
       printError(1, node->data.lineno, "variable usage before definition!");
    }
}

// ID LP ArgList/empty RP
// node is ID
void functionUsageBeforeDefinition(Node* node){
    int index = TableContains(node->data.value.string_type);
    if(index == -1) // not find ID definition
    {
       printError(2, node->data.lineno, "function usage before definition!");
    }
    else if(TableGet(index)->type->kind != FUNC) // ID is not function
    {
       printError(2, node->data.lineno, "function usage before definition!");
    }
}

// variable and function can not be the same name
// node is ID
void variableDoubleDefinition(Node* node){
    if(TableContains(node->data.value.string_type) != -1){
        printError(3, node->data.lineno, "variable double definition!");        
    }
}

//FunDec → ID LP VarList RP | ID LP RP
//node is ID
void functionDoubleDefinition(Node* node){
    if(TableContains(node->data.value.string_type) != -1){
        printError(4, node->data.lineno, "function double definition!");  
    }
}

// exp = exp
// node is left and right
void typesNotMatchInAssignOP(Node* left, Node* right){
    if(!isSameType(handleExp(left), handleExp(right))){
        printError(5, left->data.lineno, "the types besides assign op not match!");          
    }
}


// exp should record if it can be left value
void rightValInLeftOfAssignOP(Node* node){
    if(!node->syn_semantics.canBeLeftVal){
        printError(6, node->data.lineno, "right value in the left of assign op!");          
    }
}

void isLogicOP(Node* op){
    return strcmp(op->data.specifier, "AND") == 0 || strcmp(op->data.specifier, "OR") == 0 || strcmp(op->data.specifier, "RELOP") == 0 || strcmp(op->data.specifier, "NOT") == 0 || strcmp(op->data.specifier, "MINUS") == 0;
}

void isArithmeticOP(Node* op){
    return strcmp(op->data.specifier, "PLUS") == 0 || strcmp(op->data.specifier, "MINUS") == 0 || strcmp(op->data.specifier, "STAR") == 0 || strcmp(op->data.specifier, "DIV") == 0 ;
}

void OperandNotMatchOP(Node* left, Node* op, Node* right){
    if(strcmp(op->data.specifier, "MINUS") == 0){
        if(left == NULL) // minus x
        {
            SemanticType type = handleExp(right);
            if(type->kind != BASIC || type->val.basic_val->basic_type != INT){
                printError(7, right->data.lineno, "operand does not match op!");          
            }
        }
        else // x - y
        {
            SemanticType left_type = handleExp(left);
            SemanticType right_type = handleExp(right);
            if(left_type->kind != BASIC || right_type->kind != BASIC || !isSameType(left_type, right_type)){
                printError(7, right->data.lineno, "operand does not match op!");          
            }
        }
    }
    else if(isLogicOP(op)){
        if(left == NULL) // not
        {
            SemanticType type = handleExp(right);
            if(type->kind != BASIC || type->val.basic_val->basic_type != INT){
                printError(7, right->data.lineno, "operand does not match op!");          
            }
        }
        else // and / or
        {
            SemanticType left_type = handleExp(left);
            SemanticType right_type = handleExp(right);
            if(!isSameType(left_type, right_type) || left_type->kind != BASIC || left_type->val.basic_val->basic_type != INT){
                printError(7, right->data.lineno, "operand does not match op!");          
            }
        }
    }
    else if(isArithmeticOP(op)){
        SemanticType left_type = handleExp(left);
        SemanticType right_type = handleExp(right);
        if(!isSameType(left_type, right_type) || left_type->kind != BASIC){
            printError(7, right->data.lineno, "operand does not match op!");          
        }
    }
}

// Stmt → RETURN Exp SEMI
// node is exp
void returnTypeNotMatchDefinition(Node* node, SemanticType return_type){
    SemanticType type = handleExp(node);
    if(!isSameType(type, return_type)){
        printError(8, node->data.lineno, "return type not match definition!");          
    }
}

// Exp → ID LP Args RP
// the node is the function ID, and args is handled by handleArgs
void argListNotMatchDefinition(Node* node, ArgList args){
    ArgList params = handleExpID(node)->val.function->next;
    while(params != NULL && args != NULL){
        if(!isSameType(params->type, args->type)){
            printError(9, node->data.lineno, "argList not match definition!");  
            return;        
        }
        params = params->next;
        args = args->next;
    }
    if(params == NULL && args == NULL){
        return;
    }
    printError(9, node->data.lineno, "argList not match definition!");  
}

// [...] for non-array variable
// Exp → Exp LB Exp RB
// node is exp before LB 
void nonArrayVariableUsingArrayAccess(Node* node){
    if(handleExp(node)->kind != ARRAY){
        printError(10, node->data.lineno, "using [] for non-array variable!");  
    } 
}

// Exp → ID LP Args RP | ID LP RP
// () for non-function varible
// node is ID
void nonFuncVariableUsingFuncCall(Node* node){
    if(handleExpID(node)->kind != FUNC){
        printError(11, node->data.lineno, "using () for non-function variable!");  
    }
}

// Exp → Exp LB Exp RB
// node is exp after LB
void nonIntInArrayAccess(Node* node){
    SemanticType type = handleExp(node);
    if(!(type->kind == BASIC && type->val.basic_val->basic_type == INT)){
        printError(12, node->data.lineno, "non-INT variable in []!");  
    }
}

// exp.ID
// node is exp
void nonStructVariableUsingDot(Node* node){
    if(!(handleExp(node)->kind == STRUCT)){
        printError(13, node->data.lineno, "non-STRUCT variable using \'.\'!");  
    }
}
// node is ID
void usingNonDefinitionFiled(Node* exp, Node* id){
    SemanticType type = handleExp(exp);
    assert(type->val.structure != NULL);
    FieldList fields = type->val.structure->next;
    while(fields != NULL){
        if(strcmp(id->data.value.string_type, fields->name) == 0){
            return;
        }
        fields = fields->next;
    }
    printError(14, node->data.lineno, "using undefined field!");  
}


// the inner ID of struct field definition
void doubleDefinitionOfStructField(Node* node){
    FieldList fields = node->inh_semantics.definition_info.field_list;
    assert(fields != NULL);
    fields = fields->next;
    while(fields != NULL){
        if(strcmp(fields->name, node->data.value.string_type) == 0){
            printError(15, node->data.lineno, "double definition of struct field!");
            return;  
        }
        fields = fields->next;
    }

}

// the node is dec
void initializeFiledWhileDefinition(Node* node){
    if(node->child_count == 3){
        printError(15, node->data.lineno, "initialize struct filed in definition!");
    }
}

// StructSpecifier → STRUCT OptTag LC DefList RC
// OptTag → ID
// the node is ID
void structDoubleDefinition(Node* node){
    if(TableContains(node->data.value.string_type) != -1){
        printError(16, node->data.lineno, "double definition of struct!");
    }
}

// StructSpecifier → STRUCT OptTag LC DefList RC | STRUCT Tag
// Tag → ID
// the node is ID
// just judge the second production
void variableDefinitionUsingUndefinedStruct(Node* node){
    int index = TableContains(node->data.value.string_type);
    if(index == -1) // not find ID definition
    {
        printError(17, node->data.lineno, "using undefined struct to define variable!");
    }
    else if(TableGet(index)->type->kind != STRUCT) // ID is struct
    {
        printError(17, node->data.lineno, "using undefined struct to define variable!");
    }
}



// handle program
void handleProgram(Node* node){
    handleExtDefList(node->children[0]);
}

void handleExtDefList(Node* node){
    if(node != NULL){
        handleExtDef(node->children[0]);
        handleExtDefList(node->children[1]);
    }
}

void handleExtDef(Node* node){
    
}

void handleExtDecList(Node* node){

}


// handle specifier
SemanticType handleSpecifier(Node* node);

SemanticType handleStructSpecifier(Node* node);

char* handleOptTag(Node* node);

char* handleTag(Node* node);


// handle declaration
SymbolPair handleVarDec(Node* node);

SymbolPair handleFunDec(Node* node);

ArgList handleVarList(Node* node);

ArgList handleParamDec(Node* node);



void handleCompSt(Node* node);

void handleStmtList(Node* node);

void handleStmt(Node* node);



void handleDefList(Node* node);

void handleDef(Node* node);

void handleDecList(Node* node);

void handleDec(Node* node);




SemanticType handleExp(Node* node);

SemanticType handleExpASSIGNOP(Node* left, Node* right);

SemanticType handleExpAND(Node* left, Node* right);

SemanticType handleExpOR(Node* left, Node* right);

SemanticType handleExpRELOP(Node* left, Node* right);

SemanticType handleExpMATH(Node* left, Node* right);

SemanticType handleExpLPRP(Node* node);

SemanticType handleExpMinus(Node* node);

SemanticType handleExpNOT(Node* node);

SemanticType handleExpFuncCall(Node* node);

SemanticType handleExpArray(Node* node);

SemanticType handleExpStruct(Node* node);

SemanticType handleExpID(Node* node){
    if(variableUsageBeforeDefinition(node)){
        printError(1, node->data.lineno, "variable usage before definition!");
    }
    return TableGet(node->data.value.string_type);
}

SemanticType handleExpINT(Node* node){
    SemanticType type = (SemanticType)malloc(sizeof(struct Type_));
    type->kind = BASIC;
    type->val.basic_val->basic_type = INT;
    type->val.basic_val->val = node->data.value.int_type;
    return type;
}

SemanticType handleExpFLOAT(Node* node){
    SemanticType type = (SemanticType)malloc(sizeof(struct Type_));
    type->kind = BASIC;
    type->val.basic_val->basic_type = FLOAT;
    type->val.basic_val->val = node->data.value.float_type;
    return type;
}
