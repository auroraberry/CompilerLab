#include "semantic.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>
#include <assert.h>


void printError(int error_type, int lineno, char* msg){
    printf("Error type %d at Line%d: %s\n", error_type, lineno, msg);
}

// node is ID
bool variableUsageBeforeDefinition(Node* node){
    int index = TableContains(node->data.value.string_type);
    if(index == -1) // not find ID definition
    {
        printError(1, node->data.lineno, "variable usage before definition!");
        return true;
    }
    else if(TableGet(index)->type->kind == FUNC) // ID is not variable, is function
    {
        printError(1, node->data.lineno, "variable usage before definition!");
        return true;
    }
    return false;
}

// ID LP ArgList/empty RP
// node is ID
bool functionUsageBeforeDefinition(Node* node){
    int index = TableContains(node->data.value.string_type);
    if(index == -1) // not find ID definition
    {
        printError(2, node->data.lineno, "function usage before definition!");
        return true;
    }
    else if(TableGet(index)->type->kind != FUNC) // ID is not function
    {
        printError(2, node->data.lineno, "function usage before definition!");
        return true;
    }
    return false;
}

// variable and function can not be the same name
// node is ID
bool variableDoubleDefinition(Node* node){
    if(TableContains(node->data.value.string_type) != -1){
        printError(3, node->data.lineno, "variable double definition!");   
        return true;     
    }
    return false;
}

//FunDec → ID LP VarList RP | ID LP RP
//node is ID
bool functionDoubleDefinition(Node* node){
    if(TableContains(node->data.value.string_type) != -1){
        printError(4, node->data.lineno, "function double definition!"); 
        return true; 
    }
    return false;
}

// exp = exp
// node is left and right
bool typesNotMatchInAssignOP(Node* left, Node* right){
    if(!isSameType(handleExp(left), handleExp(right))){
        printError(5, left->data.lineno, "the types besides assign op not match!");
        return true;          
    }
    return false;
}


// exp should record if it can be left value
bool rightValInLeftOfAssignOP(Node* node){
    if(!node->syn_semantics.canBeLeftVal){
        printError(6, node->data.lineno, "right value in the left of assign op!"); 
        return true;         
    }
    return false;
}

bool isLogicOP(Node* op){
    return strcmp(op->data.specifier, "AND") == 0 || strcmp(op->data.specifier, "OR") == 0 || strcmp(op->data.specifier, "RELOP") == 0 || strcmp(op->data.specifier, "NOT") == 0 || strcmp(op->data.specifier, "MINUS") == 0;
}

bool isArithmeticOP(Node* op){
    return strcmp(op->data.specifier, "PLUS") == 0 || strcmp(op->data.specifier, "MINUS") == 0 || strcmp(op->data.specifier, "STAR") == 0 || strcmp(op->data.specifier, "DIV") == 0 ;
}

bool OperandNotMatchOP(Node* left, Node* op, Node* right){
    if(strcmp(op->data.specifier, "MINUS") == 0){
        if(left == NULL) // minus x
        {
            SemanticType type = handleExp(right);
            if(type->kind != BASIC || type->val.basic_val->basic_type != INT){
                printError(7, right->data.lineno, "operand does not match op!");
                return true;          
            }
        }
        else // x - y
        {
            SemanticType left_type = handleExp(left);
            SemanticType right_type = handleExp(right);
            if(left_type->kind != BASIC || right_type->kind != BASIC || !isSameType(left_type, right_type)){
                printError(7, right->data.lineno, "operand does not match op!");  
                return true;        
            }
        }
    }
    else if(isLogicOP(op)){
        if(left == NULL) // not
        {
            SemanticType type = handleExp(right);
            if(type->kind != BASIC || type->val.basic_val->basic_type != INT){
                printError(7, right->data.lineno, "operand does not match op!");  
                return true;        
            }
        }
        else // and / or
        {
            SemanticType left_type = handleExp(left);
            SemanticType right_type = handleExp(right);
            if(!isSameType(left_type, right_type) || left_type->kind != BASIC || left_type->val.basic_val->basic_type != INT){
                printError(7, right->data.lineno, "operand does not match op!"); 
                return true;         
            }
        }
    }
    else if(isArithmeticOP(op)){
        SemanticType left_type = handleExp(left);
        SemanticType right_type = handleExp(right);
        if(!isSameType(left_type, right_type) || left_type->kind != BASIC){
            printError(7, right->data.lineno, "operand does not match op!");
            return true;          
        }
    }
    return false;
}

// Stmt → RETURN Exp SEMI
// node is exp
bool returnTypeNotMatchDefinition(Node* node, SemanticType return_type){
    SemanticType type = handleExp(node);
    if(!isSameType(type, return_type)){
        printError(8, node->data.lineno, "return type not match definition!");  
        return true;        
    }
    return false;
}

// Exp → ID LP Args RP
// the node is the function ID, and args is handled by handleArgs
bool argListNotMatchDefinition(Node* node, ArgList args){
    ArgList params = handleExpID(node)->val.function->next;
    while(params != NULL && args != NULL){
        if(!isSameType(params->type, args->type)){
            printError(9, node->data.lineno, "argList not match definition!");  
            return true;        
        }
        params = params->next;
        args = args->next;
    }
    if(params == NULL && args == NULL){
        return false;
    }
    printError(9, node->data.lineno, "argList not match definition!");  
    return true;
}

// [...] for non-array variable
// Exp → Exp LB Exp RB
// node is exp before LB 
bool nonArrayVariableUsingArrayAccess(Node* node){
    if(handleExp(node)->kind != ARRAY){
        printError(10, node->data.lineno, "using [] for non-array variable!");  
        return true;
    } 
    return false;
}

// Exp → ID LP Args RP | ID LP RP
// () for non-function varible
// node is ID
bool nonFuncVariableUsingFuncCall(Node* node){
    if(handleExpID(node)->kind != FUNC){
        printError(11, node->data.lineno, "using () for non-function variable!");  
        return true;
    }
    return false;
}

// Exp → Exp LB Exp RB
// node is exp after LB
bool nonIntInArrayAccess(Node* node){
    SemanticType type = handleExp(node);
    if(!(type->kind == BASIC && type->val.basic_val->basic_type == INT)){
        printError(12, node->data.lineno, "non-INT variable in []!");
        return true;  
    }
    return false;
}

// exp.ID
// node is exp
bool nonStructVariableUsingDot(Node* node){
    if(!(handleExp(node)->kind == STRUCT)){
        printError(13, node->data.lineno, "non-STRUCT variable using \'.\'!"); 
        return true; 
    }
    return false;
}
// node is ID
bool usingNonDefinitionFiled(Node* exp, Node* id){
    SemanticType type = handleExp(exp);
    assert(type->val.structure != NULL);
    FieldList fields = type->val.structure->next;
    while(fields != NULL){
        if(strcmp(id->data.value.string_type, fields->name) == 0){
            return false;
        }
        fields = fields->next;
    }
    printError(14, node->data.lineno, "using undefined field!");  
    return true;
}


// the inner ID of struct field definition
bool doubleDefinitionOfStructField(Node* node){
    FieldList fields = node->inh_semantics.specifier_type->val.structure;
    assert(fields != NULL);
    fields = fields->next;
    while(fields != NULL){
        if(strcmp(fields->name, node->data.value.string_type) == 0){
            printError(15, node->data.lineno, "double definition of struct field!");
            return true;  
        }
        fields = fields->next;
    }
    return false;
}

// the node is dec
bool initializeFiledWhileDefinition(Node* node){
    if(node->child_count == 3){
        printError(15, node->data.lineno, "initialize struct filed in definition!");
        return true;
    }
    return false;
}

// StructSpecifier → STRUCT OptTag LC DefList RC
// OptTag → ID
// the node is ID
bool structDoubleDefinition(Node* node){
    if(TableContains(node->data.value.string_type) != -1){
        printError(16, node->data.lineno, "double definition of struct!");
        return true;
    }
    return false;
}

// StructSpecifier → STRUCT OptTag LC DefList RC | STRUCT Tag
// Tag → ID
// the node is ID
// just judge the second production
bool variableDefinitionUsingUndefinedStruct(Node* node){
    int index = TableContains(node->data.value.string_type);
    if(index == -1) // not find ID definition
    {
        printError(17, node->data.lineno, "using undefined struct to define variable!");
        return true;
    }
    else if(TableGet(index)->type->kind != STRUCT) // ID is struct
    {
        printError(17, node->data.lineno, "using undefined struct to define variable!");
        return true;
    }
    return false;
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
    SemanticType type = handleSpecifier(node->children[0]);
    if(strcmp(node->children[1], "ExtDecList") == 0){
        copySemanticType(type, node->children[1]->inh_semantics.specifier_type);
        handleExtDecList(node->children[1]);
    }
    else if(strcmp(node->children[1], "FunDec") == 0){
        copySemanticType(type, node->children[1]->inh_semantics.specifier_type);
        copySemanticType(type, node->children[2]->inh_semantics.specifier_type);
        handleFunDec(node->children[1]);
        handleCompSt(node->children[2]);
    }
}

void handleExtDecList(Node* node){
    SemanticType specifier = node->inh_semantics.specifier_type;
    copySemanticType(specifier, node->children[0]->inh_semantics.specifier_type);
    handleVarDec(node->children[0]);
    if(node->child_count == 3){
        copySemanticType(specifier, node->children[2]->inh_semantics.specifier_type);
        handleExtDecList(node->children[2]);
    }
}


// handle specifier
SemanticType handleSpecifier(Node* node){
    if(strcmp(node->children[0]->data.specifier,"TYPE")){
        SemanticType type = createSemanticType(BASIC);
        if(strcmp(node->children[0]->data.value.string_type, "int")){
            type->val.basic_val->basic_type = INT;
        }
        else 
        {
            type->val.basic_val->basic_type = FLOAT;
        }
        return type;
    }
    else{
        return handleStructSpecifier(node->children[0]);
    }
}

SemanticType handleStructSpecifier(Node* node){
    SemanticType type = createSemanticType(STRUCT);
    if(node->child_count == 2) // handle StructSpecifier → STRUCT Tag 
    {
        char* struct_name = handleTag(node->children[1]);
        if(!variableDefinitionUsingUndefinedStruct(node->children[1])){
            copySemanticType(TableGet(struct_name, type));
        }
        else{
            type->kind = ERROR; // using undefined struct variable
        }
        return type;
    }
    else // handle StructSpecifier → STRUCT OptTag LC DefList RC 
         // struct definition 
    {
        // construct field list
        Node* def_list = node->children[3];
        copySemanticType(type, def_list->inh_semantics.specifier_type);
        handleDefList(def_list);
        copyStructure(def_list->syn_semantics.semantic_type->val.structure, type->val.structure);

        // OptTag == NULL not record in symbol table
        if(node->children[1]->child_count == 0)  
        {}
        // record in symbol table
        else
        {
            char* name = handleOptTag(node->children[1]);
            if(structDoubleDefinition(name))
            {
                type->kind = ERROR;
            }
            else
            {
                addSymbolPair(name, type);
            }
        }
        return type;
    }
}

char* handleOptTag(Node* node){
    if(node->child_count == 0){
        return NULL;
    }
    char* result = (char*)malloc(strlen(node->children[0]->data.value.string_type) + 1);
    strcpy(result, node->children[0]->data.value.string_type);
    return result;
}

char* handleTag(Node* node){
    char* result = (char*)malloc(strlen(node->children[0]->data.value.string_type) + 1);
    strcpy(result, node->children[0]->data.value.string_type);
    return result;
}


// handle declaration
SymbolPair handleVarDec(Node* node){
    SemanticType specifier = node->inh_semantics.specifier_type;
    char* name = (char*)malloc
}

SymbolPair handleFunDec(Node* node){

}

ArgList handleVarList(Node* node){

}

ArgList handleParamDec(Node* node){
    SemanticType type = handleSpecifier(node->children[0]);
    ArgList result = createArgList();
    copySemanticType(type, node->children[1]->inh_semantics.specifier_type);
    SymbolPair pair = handleVarDec(node->children[1]);
    strcpy(result->name, pair->name);
    copySemanticType(pair->type, result->type);
    return result;
}



// handle statements
void handleCompSt(Node* node);

void handleStmtList(Node* node);

void handleStmt(Node* node);


void handleStructDefLsit(Node* node){

}



// handle local definition
void handleDefList(Node* node){
    // handle deflist in struct definition
    if(node->inh_semantics.specifier_type->kind == STRUCT)
    {

    }
}

void handleDef(Node* node);

void handleDecList(Node* node);

void handleDec(Node* node);




// handle expression
// setting whether the node can be left value
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






