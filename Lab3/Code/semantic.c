#include "semantic.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>
#include <assert.h>
#include "SymbolTable.h"
#include "SyntaxTree.h"
#include "IR.h"

extern bool handle[1000];

bool has_handle(int lineno) {
    if (handle[lineno]) {
        return true;
    }
    handle[lineno] = true;
    return false;
}

void printError(int error_type, int lineno, char *msg) {
    if (!has_handle(lineno)) {
        printf("Error type %d at Line %d: %s\n", error_type, lineno, msg);
    }
}

// node is ID
bool variableUsageBeforeDefinition(Node *node) {
    int index = TableContains(node->data.value.string_type);
    if (index == -1) // not find ID definition
    {
        printError(1, node->data.lineno, "variable usage before definition!");
        return true;
    } else if (TableGetByIndex(index)->type->kind == FUNC) // ID is not variable, is function
    {
        printError(1, node->data.lineno, "variable usage before definition!");
        return true;
    }
    return false;
}

// ID LP ArgList/empty RP
// node is ID
bool functionUsageBeforeDefinition(Node *node) {
    int index = TableContains(node->data.value.string_type);
    if (index == -1) // not find ID definition
    {
        printError(2, node->data.lineno, "function usage before definition!");
        return true;
    } /*else if (TableGetByIndex(index)->type->kind != FUNC) // ID is not function
    {
        printError(2, node->data.lineno, "function usage before definition!");
        return true;
    }*/
    return false;
}

// variable and function can not be the same name
// node is ID
bool variableDoubleDefinition(Node *node) {
    if (TableContains(node->data.value.string_type) != -1) {
        printError(3, node->data.lineno, "variable double definition!");
        return true;
    }
    return false;
}

//FunDec → ID LP VarList RP | ID LP RP
//node is ID
bool functionDoubleDefinition(Node *node) {
    if (TableContains(node->data.value.string_type) != -1) {
        printError(4, node->data.lineno, "function double definition!");
        return true;
    }
    return false;
}

// exp = exp
// node is left and right
bool typesNotMatchInAssignOP(Node *left, Node *right) {
    if (!isSameType(left->syn_semantics.semantic_type, right->syn_semantics.semantic_type)) {
        printError(5, left->data.lineno, "the types besides assign op not match!");
        return true;
    }
    return false;
}


// exp should record if it can be left value
bool rightValInLeftOfAssignOP(Node *node) {
    if (!node->syn_semantics.canBeLeftVal) {
        printError(6, node->data.lineno, "right value in the left of assign op!");
        return true;
    }
    return false;
}

bool isLogicOP(Node *op) {
    return strcmp(op->data.specifier, "AND") == 0 || strcmp(op->data.specifier, "OR") == 0 ||
           strcmp(op->data.specifier, "RELOP") == 0 || strcmp(op->data.specifier, "NOT") == 0 ||
           strcmp(op->data.specifier, "MINUS") == 0;
}

bool isArithmeticOP(Node *op) {
    return strcmp(op->data.specifier, "PLUS") == 0 || strcmp(op->data.specifier, "MINUS") == 0 ||
           strcmp(op->data.specifier, "STAR") == 0 || strcmp(op->data.specifier, "DIV") == 0;
}

bool OperandNotMatchOP(Node *left, Node *right, Node *op) {
    if (strcmp(op->data.specifier, "MINUS") == 0) {
        if (left == NULL) // minus x
        {
            SemanticType type = right->syn_semantics.semantic_type;
            if (type->kind != BASIC) {
                printError(7, right->data.lineno, "operand does not match op!");
                return true;
            }
        } else // x - y
        {
            SemanticType left_type = left->syn_semantics.semantic_type;
            SemanticType right_type = right->syn_semantics.semantic_type;
            if (left_type->kind != BASIC || right_type->kind != BASIC || !isSameType(left_type, right_type)) {
                printError(7, right->data.lineno, "operand does not match op!");
                return true;
            }
        }
    } else if (isLogicOP(op)) {
        if (left == NULL) // not
        {
            SemanticType type = right->syn_semantics.semantic_type;
            if (type->kind != BASIC || type->val.basic_val->basic_type != BASIC_INT) {
                printError(7, right->data.lineno, "operand does not match op!");
                return true;
            }
        } else if (strcmp(op->data.specifier, "AND") == 0 || strcmp(op->data.specifier, "OR") == 0)// and / or
        {
            SemanticType left_type = left->syn_semantics.semantic_type;
            SemanticType right_type = right->syn_semantics.semantic_type;
            if (!isSameType(left_type, right_type) || left_type->kind != BASIC ||
                left_type->val.basic_val->basic_type != BASIC_INT) {
                printError(7, right->data.lineno, "operand does not match op!");
                return true;
            }
        } else // relop
        {
            SemanticType left_type = left->syn_semantics.semantic_type;
            SemanticType right_type = right->syn_semantics.semantic_type;
            if (!isSameType(left_type, right_type) || left_type->kind != BASIC) {
                printError(7, right->data.lineno, "operand does not match op!");
                return true;
            }
        }
    } else if (isArithmeticOP(op)) {
        SemanticType left_type = left->syn_semantics.semantic_type;
        SemanticType right_type = right->syn_semantics.semantic_type;
        if (left_type->kind != BASIC || !isSameType(left_type, right_type)) {
            printError(7, right->data.lineno, "operand does not match op!");
            return true;
        }
    }
    return false;
}

// Stmt → RETURN Exp SEMI
// node is exp
bool returnTypeNotMatchDefinition(Node *node, SemanticType return_type) {
    SemanticType type = node->syn_semantics.semantic_type;
    if (!isSameType(type, return_type)) {
        printError(8, node->data.lineno, "return type not match definition!");
        return true;
    }
    return false;
}

// Exp → ID LP Args RP
// the node is the function ID, and args is handled by handleArgs
bool argListNotMatchDefinition(Node *node, ArgList args) {
    SemanticType type = node->syn_semantics.semantic_type;
    if (type->kind == ERROR) {
        return true;
    }
    ArgList params = type->val.function->next;
    while (params != NULL && args != NULL) {
        if (!isSameType(params->type, args->type)) {
            printError(9, node->data.lineno, "argList not match definition!");
            return true;
        }
        params = params->next;
        args = args->next;
    }
    if (params == NULL && args == NULL) {
        return false;
    }
    printError(9, node->data.lineno, "argList not match definition!");
    return true;
}

// [...] for non-array variable
// Exp → Exp LB Exp RB
// node is exp before LB 
bool nonArrayVariableUsingArrayAccess(Node *node) {
    if (node->syn_semantics.semantic_type->kind != ARRAY) {
        printError(10, node->data.lineno, "using [] for non-array variable!");
        return true;
    }
    return false;
}

// Exp → ID LP Args RP | ID LP RP
// () for non-function varible
// node is ID
bool nonFuncVariableUsingFuncCall(Node *node) {
    if (node->syn_semantics.semantic_type->kind != FUNC) {
        printError(11, node->data.lineno, "using () for non-function variable!");
        return true;
    }
    return false;
}

// Exp → Exp LB Exp RB
// node is exp after LB
bool nonIntInArrayAccess(Node *node) {
    SemanticType type = node->syn_semantics.semantic_type;
    if (!(type->kind == BASIC && type->val.basic_val->basic_type == BASIC_INT)) {
        printError(12, node->data.lineno, "non-INT variable in []!");
        return true;
    }
    return false;
}

// exp.ID
// node is exp
bool nonStructVariableUsingDot(Node *node) {
    if (node->syn_semantics.semantic_type->kind != STRUCTURE) {
        printError(13, node->data.lineno, "non-STRUCT variable using \'.\'!");
        return true;
    }
    return false;
}

// node is ID
bool usingNonDefinitionFiled(Node *exp, Node *id) {
    SemanticType type = exp->syn_semantics.semantic_type;
    assert(type->val.structure != NULL);
    FieldList fields = type->val.structure->type->val.structure;
    while (fields != NULL) {
        if (strcmp(id->data.value.string_type, fields->name) == 0) {
            return false;
        }
        fields = fields->next;
    }
    printError(14, id->data.lineno, "using undefined field!");
    return true;
}


// the inner ID of struct field definition
bool doubleDefinitionOfStructField(Node *node, FieldList fields) {
    while (fields != NULL) {
        if (fields->type->kind != NONE && strcmp(fields->name, node->data.value.string_type) == 0) {
            printError(15, node->data.lineno, "double definition of struct field!");
            return true;
        }
        fields = fields->next;
    }
    return false;
}

// the node is dec
bool initializeFiledWhileDefinition(Node *node) {
    if (node->child_count == 3) {
        printError(15, node->data.lineno, "initialize struct filed in definition!");
        return true;
    }
    return false;
}

// StructSpecifier → STRUCT OptTag LC DefList RC
// OptTag → ID
// the node is ID
bool structDoubleDefinition(char *name, int lineno) {
    if (TableContains(name) != -1) {
        printError(16, lineno, "double definition of struct!");
        return true;
    }
    return false;
}

// StructSpecifier → STRUCT OptTag LC DefList RC | STRUCT Tag
// Tag → ID
// the node is ID
// just judge the second production
bool variableDefinitionUsingUndefinedStruct(int lineno, char *name) {
    int index = TableContains(name);
    if (index == -1) // not find ID definition
    {
        printError(17, lineno, "using undefined struct to define variable!");
        return true;
    } else if (TableGetByIndex(index)->type->kind != STRUCTURE) // ID is struct
    {
        printError(17, lineno, "using undefined struct to define variable!");
        return true;
    }
    return false;
}


// handle program
void handleProgram(Node *node) {
    handleExtDefList(node->children[0]);
}

void handleExtDefList(Node *node) {
    if (node != NULL) {
        handleExtDef(node->children[0]);
        handleExtDefList(node->children[1]);
    }
}

void handleExtDef(Node *node) {
    SemanticType type = handleSpecifier(node->children[0]);
    if (strcmp(node->children[1]->data.specifier, "ExtDecList") == 0) {
        copySemanticType(type, node->children[1]->inh_semantics.specifier_type);
        handleExtDecList(node->children[1]);
    } else if (strcmp(node->children[1]->data.specifier, "FunDec") == 0) {
        node->children[1]->inh_semantics.specifier_type = createSemanticType(FUNC);
        node->children[2]->inh_semantics.specifier_type = createSemanticType(FUNC);
        copySemanticType(type, node->children[1]->inh_semantics.specifier_type->val.function->type);
        copySemanticType(type, node->children[2]->inh_semantics.specifier_type->val.function->type);
        handleFunDec(node->children[1]);
        handleCompSt(node->children[2]);
    }
}

void handleExtDecList(Node *node) {
    SemanticType specifier = node->inh_semantics.specifier_type;
    copySemanticType(specifier, node->children[0]->inh_semantics.specifier_type);
    handleVarDec(node->children[0]);
    if (node->child_count == 3) {
        copySemanticType(specifier, node->children[2]->inh_semantics.specifier_type);
        handleExtDecList(node->children[2]);
    }
}


// handle specifier
SemanticType handleSpecifier(Node *node) {
    if (strcmp(node->children[0]->data.specifier, "TYPE") == 0) {
        SemanticType type = createSemanticType(BASIC);
        if (strcmp(node->children[0]->data.value.string_type, "int") == 0) {
            type->val.basic_val->basic_type = BASIC_INT;
        } else {
            type->val.basic_val->basic_type = BASIC_FLOAT;
        }
        return type;
    } else {
        return handleStructSpecifier(node->children[0]);
    }
}

SemanticType handleStructSpecifier(Node *node) {
    SemanticType type = createSemanticType(STRUCTURE);
    if (node->child_count == 2) // handle StructSpecifier → STRUCT Tag
    {
        char *struct_name = handleTag(node->children[1]);
        if (!variableDefinitionUsingUndefinedStruct(node->children[1]->data.lineno, struct_name)) {
            copySemanticType(TableGet(struct_name)->type, type);
        } else {
            type->kind = ERROR; // using undefined struct variable
        }
        return type;
    } else // handle StructSpecifier → STRUCT OptTag LC DefList RC
        // struct definition
    {
        // construct field list
        Node *def_list = node->children[3];
        copySemanticType(type, def_list->inh_semantics.specifier_type);
        type->val.structure->type = createSemanticType(STRUCTURE);
        // type->val.structure->type->val.structure is an empty list with the head node's type.kind = NULL
        handleDefListInStruct(def_list, type->val.structure->type->val.structure);
        type->val.structure->type->val.structure = type->val.structure->type->val.structure->next;
        // OptTag == NULL not record in symbol table
        if (node->children[1] == NULL) {}
            // record in symbol table
        else {
            char *name = handleOptTag(node->children[1]);
            strcpy(type->val.structure->name, name);
            if (structDoubleDefinition(name, node->data.lineno)) {
                type->kind = ERROR;
            } else {
                addSymbolPair(name, type);
            }
        }
        return type;
    }
}

char *handleOptTag(Node *node) {
    if (node == NULL) {
        return NULL;
    }
    char *result = (char *) malloc(strlen(node->children[0]->data.value.string_type) + 1);
    strcpy(result, node->children[0]->data.value.string_type);
    return result;
}

char *handleTag(Node *node) {
    char *result = (char *) malloc(strlen(node->children[0]->data.value.string_type) + 1);
    strcpy(result, node->children[0]->data.value.string_type);
    return result;
}

// handle declaration
// return pair.name is NULL, if it meets error
void handleVarDec(Node *node) {
    // VarDec -> ID
    if (strcmp(node->children[0]->data.specifier, "ID") == 0) {
        SemanticType specifier = node->inh_semantics.specifier_type;
        if (variableDoubleDefinition(node->children[0])) {
            node->syn_semantics.semantic_type = createSemanticType(ERROR);
        } else {
            copySemanticType(specifier, node->children[0]->inh_semantics.specifier_type);
            copySemanticType(specifier, node->children[0]->syn_semantics.semantic_type);
            node->children[0]->syn_semantics.canBeLeftVal = true;
            node->syn_semantics.canBeLeftVal = true;
            copySemanticType(specifier, node->syn_semantics.semantic_type);
            char *name = (char *) malloc(strlen(node->children[0]->data.value.string_type) + 1);
            strcpy(name, node->children[0]->data.value.string_type);
            addSymbolPair(name, node->children[0]->syn_semantics.semantic_type);
            int index = addVar(name);
            Operand *operand = createOperand(OPERAND_VARIABLE);
            if (specifier->kind == ARRAY) {
                operand->is_address = true;
                // DEC size for array
                int size = countSize(specifier);
                Operand *array_size = createOperand(OPERAND_SIZE);
                array_size->val.imm_value = size;
                operand->next = array_size;
            }
            strcpy(operand->val.string, name);
            addOPVar(operand, index);
            if (specifier->kind == ARRAY) {
                // gen DEC array size
                addInterCode(operand, DEC, ASSIGN_NONE);
            }
        }
    }
        // array definition
    else {
        node->children[0]->inh_semantics.specifier_type = createSemanticType(ARRAY);
        SemanticType specifier = node->children[0]->inh_semantics.specifier_type;
        specifier->val.array->size = node->children[2]->data.value.int_type;
        copySemanticType(node->inh_semantics.specifier_type, specifier->val.array->elem);
        handleVarDec(node->children[0]);
        copySemanticType(node->children[0]->syn_semantics.semantic_type, node->syn_semantics.semantic_type);
        node->syn_semantics.canBeLeftVal = node->children[0]->syn_semantics.canBeLeftVal;
    }
}

// node->inh_semantics.specifier_type is return type
SemanticType handleFunDec(Node *node) {
    if (functionDoubleDefinition(node->children[0])) {
        node->inh_semantics.specifier_type->kind = ERROR;
        node->syn_semantics.semantic_type->kind = ERROR;
        if (node->child_count == 4) {
            handleVarList(node->children[2]);
        }
        return node->syn_semantics.semantic_type;
    }
    char *name = createCharName();
    strcpy(name, node->children[0]->data.value.string_type);
    strcpy(node->inh_semantics.specifier_type->val.function->name, name);
    copySemanticType(node->inh_semantics.specifier_type, node->syn_semantics.semantic_type);
    if (node->child_count == 4) {
        node->syn_semantics.semantic_type->val.function->next = handleVarList(node->children[2]);
    }
    addSymbolPair(name, node->syn_semantics.semantic_type);

    // add rename function and generate inter code
    int index = addFunc(name);
    Operand *operand = createOperand(OPERAND_FUNC);
    strcpy(operand->val.string, name);
    addOPFunc(operand, index);
    addInterCode(operand, IR_FUNC, ASSIGN_NONE);
    if (node->child_count == 4) {
        ArgList args = node->syn_semantics.semantic_type->val.function->next;
        while (args != NULL) {
            int index = containsVar(args->name);
            assert(index != -1);
            Operand *arg = getOPVar(index);
            addInterCode(arg, PARAM, ASSIGN_NONE);
        }
    }
    return node->syn_semantics.semantic_type;
}

ArgList handleVarList(Node *node) {
    ArgList result;
    result = handleParamDec(node->children[0]);
    if (node->child_count == 3) {
        result->next = handleVarList(node->children[2]);
    }
    return result;
}

ArgList handleParamDec(Node *node) {
    SemanticType type = handleSpecifier(node->children[0]);
    ArgList result = createArgList();
    copySemanticType(type, node->children[1]->inh_semantics.specifier_type);
    handleVarDec(node->children[1]);
    SemanticType result_type = node->children[1]->syn_semantics.semantic_type;
    strcpy(result->name, getVarDecIDName(node->children[1]));
    copySemanticType(result_type, result->type);
    return result;
}


// handle statements
void handleCompSt(Node *node) {
    SemanticType specifier = node->inh_semantics.specifier_type;
    if (node->children[2] != NULL) {
        copySemanticType(specifier, node->children[2]->inh_semantics.specifier_type);
    }
    handleDefListInFunction(node->children[1]);
    handleStmtList(node->children[2]);
}

void handleStmtList(Node *node) {
    if (node != NULL) {
        copySemanticType(node->inh_semantics.specifier_type, node->children[0]->inh_semantics.specifier_type);
        if (node->children[1] != NULL) {
            copySemanticType(node->inh_semantics.specifier_type, node->children[1]->inh_semantics.specifier_type);
        }
        handleStmt(node->children[0]);
        handleStmtList(node->children[1]);
    }
}

void handleStmt(Node *node) {
    if (strcmp(node->children[0]->data.specifier, "Exp") == 0) {
        copySemanticType(node->inh_semantics.specifier_type, node->children[0]->inh_semantics.specifier_type);
        handleExp(node->children[0]);
    } else if (strcmp(node->children[0]->data.specifier, "CompSt") == 0) {
        copySemanticType(node->inh_semantics.specifier_type, node->children[0]->inh_semantics.specifier_type);
        handleCompSt(node->children[0]);
    } else if (strcmp(node->children[0]->data.specifier, "RETURN") == 0) {
        copySemanticType(node->inh_semantics.specifier_type, node->children[1]->inh_semantics.specifier_type);
        handleExp(node->children[1]);
        returnTypeNotMatchDefinition(node->children[1], node->inh_semantics.specifier_type->val.function->type);
    } else if (node->child_count == 5) {
        copySemanticType(node->inh_semantics.specifier_type, node->children[2]->inh_semantics.specifier_type);
        copySemanticType(node->inh_semantics.specifier_type, node->children[4]->inh_semantics.specifier_type);
        handleExp(node->children[2]);
        handleStmt(node->children[4]);
    } else {
        copySemanticType(node->inh_semantics.specifier_type, node->children[2]->inh_semantics.specifier_type);
        copySemanticType(node->inh_semantics.specifier_type, node->children[4]->inh_semantics.specifier_type);
        copySemanticType(node->inh_semantics.specifier_type, node->children[6]->inh_semantics.specifier_type);
        handleExp(node->children[2]);
        handleStmt(node->children[4]);
        handleStmt(node->children[6]);
    }
}


// handle local definition
void handleDefListInFunction(Node *node) {
    if (node != NULL) {
        handleDefInFunction(node->children[0]);
        handleDefListInFunction(node->children[1]);
    }
}

void handleDefInFunction(Node *node) {
    SemanticType type = handleSpecifier(node->children[0]);
    copySemanticType(type, node->children[1]->inh_semantics.specifier_type);
    handleDecListInFunction(node->children[1]);
}

void handleDecListInFunction(Node *node) {
    copySemanticType(node->inh_semantics.specifier_type, node->children[0]->inh_semantics.specifier_type);
    handleDecInFunction(node->children[0]);
    if (node->child_count == 3) {
        copySemanticType(node->inh_semantics.specifier_type, node->children[2]->inh_semantics.specifier_type);
        handleDecListInFunction(node->children[2]);
    }
}


char *getVarDecIDName(Node *node) {
    if (node->child_count == 1) {
        return node->children[0]->data.value.string_type;
    } else {
        return getVarDecIDName(node->children[0]);
    }
}

void handleDecInFunction(Node *node) {
    SemanticType specifier = node->inh_semantics.specifier_type;
    copySemanticType(specifier, node->children[0]->inh_semantics.specifier_type);
    if (node->child_count == 1) {
        handleVarDec(node->children[0]);
    } else {
        SemanticType assign_type = handleExp(node->children[2]);
        if (!isSameType(specifier, assign_type)) {
            printError(5, node->data.lineno, "the types besides assign op not match!");
        }
        handleVarDec(node->children[0]); // the error in right of = is not compact the type of left
    }
}


// add the definition in the tail of the fields
void handleDefListInStruct(Node *node, FieldList fields) {
    if (node != NULL) {
        handleDefInStruct(node->children[0], fields);
        if (node->children[1] != NULL) {
            copySemanticType(node->inh_semantics.specifier_type, node->children[1]->inh_semantics.specifier_type);
        }
        handleDefListInStruct(node->children[1], fields);
    }
}

void handleDefInStruct(Node *node, FieldList fields) {
    SemanticType type = handleSpecifier(node->children[0]);
    copySemanticType(type, node->children[1]->inh_semantics.specifier_type);
    handleDecListInStruct(node->children[1], fields);
}

void handleDecListInStruct(Node *node, FieldList fields) {
    copySemanticType(node->inh_semantics.specifier_type, node->children[0]->inh_semantics.specifier_type);
    handleDecInStruct(node->children[0], fields);
    if (node->child_count == 3) {
        copySemanticType(node->inh_semantics.specifier_type, node->children[2]->inh_semantics.specifier_type);
        handleDecListInStruct(node->children[2], fields);
    }
}

void handleDecInStruct(Node *node, FieldList fields) {
    initializeFiledWhileDefinition(node);
    copySemanticType(node->inh_semantics.specifier_type, node->children[0]->inh_semantics.specifier_type);
    handleVarDecInStruct(node->children[0], fields);
}

void handleVarDecInStruct(Node *node, FieldList fields) {
    // VarDec -> ID
    if (strcmp(node->children[0]->data.specifier, "ID") == 0) {
        SemanticType specifier = node->inh_semantics.specifier_type;
        if (doubleDefinitionOfStructField(node->children[0], fields)) {
            node->syn_semantics.semantic_type = createSemanticType(ERROR);
        } else {
            copySemanticType(specifier, node->children[0]->inh_semantics.specifier_type);
            copySemanticType(specifier, node->children[0]->syn_semantics.semantic_type);
            node->children[0]->syn_semantics.canBeLeftVal = true;
            node->syn_semantics.canBeLeftVal = true;
            copySemanticType(specifier, node->syn_semantics.semantic_type);
            char *name = (char *) malloc(strlen(node->children[0]->data.value.string_type) + 1);
            strcpy(name, node->children[0]->data.value.string_type);
            addSymbolPair(name, node->children[0]->syn_semantics.semantic_type);
            while (fields->next != NULL) {
                fields = fields->next;
            }
            fields->next = createFieldList();
            strcpy(fields->next->name, name);
            copySemanticType(node->children[0]->syn_semantics.semantic_type, fields->next->type);
        }
    }
        // array definition
    else {
        node->children[0]->inh_semantics.specifier_type = createSemanticType(ARRAY);
        SemanticType specifier = node->children[0]->inh_semantics.specifier_type;
        specifier->val.array->size = node->children[2]->data.value.int_type;
        copySemanticType(node->inh_semantics.specifier_type, specifier->val.array->elem);
        handleVarDecInStruct(node->children[0], fields);
        copySemanticType(node->children[0]->syn_semantics.semantic_type, node->syn_semantics.semantic_type);
        node->syn_semantics.canBeLeftVal = node->children[0]->syn_semantics.canBeLeftVal;
    }
}


// handle expression
// setting whether the node can be left value
SemanticType handleExp(Node *node) {
    if(node->syn_semantics.semantic_type->kind != NONE){
        return node->syn_semantics.semantic_type;
    }
    if (node->child_count == 1) // ID INT FLOAT
    {
        if (strcmp(node->children[0]->data.specifier, "ID") == 0) {
            SemanticType type = handleExpID(node->children[0], NONE);// except function
            copySemanticType(type, node->syn_semantics.semantic_type);
            if (type->kind != ERROR) {
                node->syn_semantics.canBeLeftVal = true;
            }
            if (node->is_translated) {
                return type;
            }
            Operand *tem = getTemVar(true);
            int index = containsVar(node->children[0]->data.value.string_type);
            assert(index != -1);
            Operand *var = getOPVar(index);
            tem->next = var;
            addInterCode(tem, IR_ASSIGN, ASSIGN_NONE);
            node->is_translated = true;
            return type;
        } else if (strcmp(node->children[0]->data.specifier, "INT") == 0) {
            SemanticType type = handleExpINT(node->children[0]);
            copySemanticType(type, node->syn_semantics.semantic_type);
            if (node->is_translated) {
                return type;
            }
            Operand *tem = getTemVar(true);
            Operand *imm = createOperand(OPERAND_IMM);
            imm->val.imm_value = type->val.basic_val->val.int_val;
            tem->next = imm;
            addInterCode(tem, IR_ASSIGN, ASSIGN_NONE);
            node->is_translated = true;
            return type;
        } else if (strcmp(node->children[0]->data.specifier, "FLOAT") == 0) {
            SemanticType type = handleExpFLOAT(node->children[0]);
            copySemanticType(type, node->syn_semantics.semantic_type);
            return type;
        }
        SemanticType type = createSemanticType(ERROR);
        copySemanticType(type, node->syn_semantics.semantic_type);
        return type;
    }
        // NOT / MINUS
    else if (node->child_count == 2) {
        if (strcmp(node->children[0]->data.specifier, "NOT") == 0) {
            SemanticType type = handleExpNOT(node->children[1], node->children[0]);
            copySemanticType(type, node->syn_semantics.semantic_type);
            return type;
        } else if (strcmp(node->children[0]->data.specifier, "MINUS") == 0) {
            SemanticType type = handleExpMinus(node->children[1], node->children[0]);
            copySemanticType(type, node->syn_semantics.semantic_type);
            return type;
        }
        return createSemanticType(ERROR);
    } else if (node->child_count == 3) {
        if (strcmp(node->children[1]->data.specifier, "ASSIGNOP") == 0) {
            SemanticType type = handleExpASSIGNOP(node->children[0], node->children[2]);
            if(type->kind != ERROR){
              node->syn_semantics.canBeLeftVal = true;
            }
            copySemanticType(type, node->syn_semantics.semantic_type);
            return type;
        } else if (strcmp(node->children[1]->data.specifier, "AND") == 0) {
            SemanticType type = handleExpAND(node->children[0], node->children[2], node->children[1]);
            copySemanticType(type, node->syn_semantics.semantic_type);
            return type;
        } else if (strcmp(node->children[1]->data.specifier, "OR") == 0) {
            SemanticType type = handleExpOR(node->children[0], node->children[2], node->children[1]);
            copySemanticType(type, node->syn_semantics.semantic_type);
            return type;
        } else if (strcmp(node->children[1]->data.specifier, "RELOP") == 0) {
            SemanticType type = handleExpRELOP(node->children[0], node->children[2], node->children[1]);
            copySemanticType(type, node->syn_semantics.semantic_type);
            return type;
        } else if (strcmp(node->children[1]->data.specifier, "LP") == 0) {
            handleExpFuncCall(node);
            return node->syn_semantics.semantic_type;
        } else if (strcmp(node->children[1]->data.specifier, "Exp") == 0) {
            SemanticType type;
            if(node->children[1]->syn_semantics.semantic_type->kind == NONE){
                handleExp(node->children[1]);
            }
            type = node->children[1]->syn_semantics.semantic_type;
            copySemanticType(type, node->syn_semantics.semantic_type);
            if (type->kind != ERROR) {
                node->syn_semantics.canBeLeftVal = node->children[1]->syn_semantics.canBeLeftVal;
            }
            return type;
        } else if (strcmp(node->children[1]->data.specifier, "DOT") == 0) {
            handleExpStruct(node);
            SemanticType type = node->syn_semantics.semantic_type;
            if (type->kind != ERROR) {
                node->syn_semantics.canBeLeftVal = true;
            }
            return type;
        } else {
            SemanticType type = handleExpMATH(node->children[0], node->children[2], node->children[1]);
            copySemanticType(type, node->syn_semantics.semantic_type);
            return type;
        }
    } else {
        if (strcmp(node->children[0]->data.specifier, "ID") == 0) {
            return handleExpFuncCall(node);
        } else {
            SemanticType type = handleExpArray(node);
            if (type->kind != ERROR) {
                node->syn_semantics.canBeLeftVal = true;
            }
            return type;
        }
    }
}

SemanticType handleExpASSIGNOP(Node *left, Node *right) {
    if(left->syn_semantics.semantic_type->kind != NONE){
        return left->syn_semantics.semantic_type;
    }
    handleExp(left);
    handleExp(right);
    if (typesNotMatchInAssignOP(left, right) || rightValInLeftOfAssignOP(left)) {
        SemanticType type = createSemanticType(ERROR);
        return type;
    }else {
        return left->syn_semantics.semantic_type;
    }
}

SemanticType handleExpAND(Node *left, Node *right, Node *and) {
    if(left->syn_semantics.semantic_type->kind != NONE){
        return left->syn_semantics.semantic_type;
    }
    SemanticType type;
    handleExp(left);
    handleExp(right);
    if (OperandNotMatchOP(left, right, and)) {
        type = createSemanticType(ERROR);
    } else {
        type = createSemanticType(BASIC);
        type->val.basic_val->basic_type = BASIC_INT;
    }
    return type;
}

SemanticType handleExpOR(Node *left, Node *right, Node *or) {
    if(left->syn_semantics.semantic_type->kind != NONE){
        return left->syn_semantics.semantic_type;
    }
    SemanticType type;
    handleExp(left);
    handleExp(right);
    if (OperandNotMatchOP(left, right, or)) {
        type = createSemanticType(ERROR);
    } else {
        type = createSemanticType(BASIC);
        type->val.basic_val->basic_type = BASIC_INT;
    }
    return type;
}

SemanticType handleExpRELOP(Node *left, Node *right, Node *relop) {
    if(left->syn_semantics.semantic_type->kind != NONE){
        return left->syn_semantics.semantic_type;
    }
    SemanticType type;
    handleExp(left);
    handleExp(right);
    if (OperandNotMatchOP(left, right, relop)) {
        type = createSemanticType(ERROR);
    } else {
        type = createSemanticType(BASIC);
        type->val.basic_val->basic_type = BASIC_INT;
    }
    return type;
}

SemanticType handleExpMATH(Node *left, Node *right, Node *op) {
    if(left->syn_semantics.semantic_type->kind != NONE){
        return left->syn_semantics.semantic_type;
    }
    SemanticType type;
    handleExp(left);
    handleExp(right);
    if (OperandNotMatchOP(left, right, op)) {
        type = createSemanticType(ERROR);
    } else {
        type = left->syn_semantics.semantic_type;
    }
    return type;
}


SemanticType handleExpMinus(Node *node, Node *minus) {
    if(node->syn_semantics.semantic_type->kind != NONE){
        return node->syn_semantics.semantic_type;
    }
    SemanticType type;
    handleExp(node);
    if (OperandNotMatchOP(NULL, node, minus)) {
        type = createSemanticType(ERROR);
    } else {
        type = node->syn_semantics.semantic_type;
    }
    return type;
}

SemanticType handleExpNOT(Node *node, Node *not) {
    if(node->syn_semantics.semantic_type->kind != NONE){
        return node->syn_semantics.semantic_type;
    }
    SemanticType type;
    handleExp(node);
    if (OperandNotMatchOP(NULL, node, not)) {
        type = createSemanticType(ERROR);
    } else {
        type = node->syn_semantics.semantic_type;
    }
    return type;
}

SemanticType handleExpFuncCall(Node *node) {
    handleExpID(node->children[0], FUNC);
    if (nonFuncVariableUsingFuncCall(node->children[0])) {
        return createSemanticType(ERROR);
    }
    SemanticType function = node->syn_semantics.semantic_type;
    // copy return var type and return
    copySemanticType(function->val.function->type, node->syn_semantics.semantic_type);
    if (node->child_count == 4) {
        ArgList args = handleArgs(node->children[2]);
        node->syn_semantics.semantic_type->val.function->next = args;
        if (argListNotMatchDefinition(node->children[0], args)) {
            return createSemanticType(ERROR);
        }
    }
    return node->syn_semantics.semantic_type;
}

SemanticType handleExpArray(Node *node) {
    if (nonArrayVariableUsingArrayAccess(node->children[0]) || nonIntInArrayAccess(node->children[2])) {
        SemanticType type = createSemanticType(ERROR);
        copySemanticType(type, node->syn_semantics.semantic_type);
        return type;
    }
    else{
        SemanticType type = handleExp(node->children[0])->val.array->elem;
        copySemanticType(type, node->syn_semantics.semantic_type);
        return type;
    }
}

SemanticType handleExpStruct(Node *node) {
    if (nonStructVariableUsingDot(node->children[0]) || usingNonDefinitionFiled(node->children[0], node->children[2])) {
        SemanticType type = createSemanticType(ERROR);
        copySemanticType(type, node->syn_semantics.semantic_type);
        return type;
    }
    SemanticType structure = handleExp(node->children[0]);
    FieldList head = structure->val.structure->type->val.structure;
    while (head != NULL) {
        if (strcmp(head->name, node->children[2]->data.value.string_type) == 0) {
            copySemanticType(head->type, node->syn_semantics.semantic_type);
            return node->syn_semantics.semantic_type;
        }
        head = head->next;
    }
    SemanticType type = createSemanticType(ERROR);
    copySemanticType(type, node->syn_semantics.semantic_type);
    return type;
}

SemanticType handleExpID(Node *node, enum Kind kind) {
    if(node->syn_semantics.semantic_type->kind != NONE){
        return node->syn_semantics.semantic_type;
    }
    SemanticType type;
    switch (kind) {
        case FUNC:
            if (functionUsageBeforeDefinition(node)) {
                type = createSemanticType(ERROR);
                copySemanticType(type, node->syn_semantics.semantic_type);
                return type;
            }
            type = TableGet(node->data.value.string_type)->type;
            copySemanticType(type, node->syn_semantics.semantic_type);
            return type;

        default:
            if (variableUsageBeforeDefinition(node)) {
                type = createSemanticType(ERROR);
                copySemanticType(type, node->syn_semantics.semantic_type);
                return type;
            }
            type = TableGet(node->data.value.string_type)->type;
            copySemanticType(type, node->syn_semantics.semantic_type);
            return type;
    }
}

SemanticType handleExpINT(Node *node) {
    if(node->syn_semantics.semantic_type->kind != NONE){
        return node->syn_semantics.semantic_type;
    }
    SemanticType type = createSemanticType(BASIC);
    type->val.basic_val->basic_type = BASIC_INT;
    type->val.basic_val->val.int_val = node->data.value.int_type;
    copySemanticType(type, node->syn_semantics.semantic_type);
    return type;
}

SemanticType handleExpFLOAT(Node *node) {
    if(node->syn_semantics.semantic_type->kind != NONE){
        return node->syn_semantics.semantic_type;
    }
    SemanticType type = createSemanticType(BASIC);
    type->val.basic_val->basic_type = BASIC_FLOAT;
    type->val.basic_val->val.float_val = node->data.value.float_type;
    copySemanticType(type, node->syn_semantics.semantic_type);
    return type;
}


ArgList handleArgs(Node *node) {
    ArgList result = createArgList();
    copySemanticType(handleExp(node->children[0]), result->type);
    Operand *temVar = getTemVar(false);
    if (node->child_count == 3) {
        result->next = handleArgs(node->children[2]);
    }
    addInterCode(temVar, ARG, ASSIGN_NONE);
    return result;
}



int countSize(SemanticType type) {
    int size = 0;
    switch (type->kind) {
        case BASIC:
            size = 4;
            break;
        case ARRAY:
            size = type->val.array->size;
            size *= countSize(type->val.array->elem);
            break;
        case STRUCTURE:
            FieldList fields = type->val.structure->type->val.structure;
            while (fields != NULL) {
                size += countSize(fields->type);
                fields = fields->next;
            }
            break;
        default:
            assert(1 == 1); // can not count in other type
    }
    return size;
}



