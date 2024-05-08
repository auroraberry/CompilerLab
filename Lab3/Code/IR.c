#include "semantic.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>
#include <assert.h>
#include "SymbolTable.h"
#include "SyntaxTree.h"
#include "IR.h"


static void handleProgram(Node *node);
static void handleExtDefList(Node *node);
static void handleExtDef(Node *node); // definition -> record in symbol table
static void handleExtDecList(Node *node);
static void handleVarDec(Node *node);
static void handleVarDecInStruct(Node *node, FieldList fields);
static void handleFunDec(Node *node);
static void handleVarList(Node *node);
static void handleParamDec(Node *node);
static void handleCompSt(Node *node);
static void handleStmtList(Node *node);
static void handleStmt(Node *node);
static void handleDefListInFunction(Node *node);
static void handleDefInFunction(Node *node);
static void handleDecListInFunction(Node *node);
static void handleDecInFunction(Node *node);
static void handleExp(Node *node, Operand *place);
static void handleExpFuncCall(Node *node, Operand *place); // node is father exp
static void handeExpArray(Node* node, Operand* size);
static void handleArgs(Node *node, Operand* args);
static void handleCond(Node *exp, Operand *label_true, Operand *label_false);

static char *handleOptTag(Node *node);
static char *handleTag(Node *node);
static char *getVarDecIDName(Node *node);

void generateIR(Node *root) {
    handleProgram(root);
}

int tem_count = 0;
int label_count = 0;

// record the index of var/func
ArrayList *ir_variables;
ArrayList *ir_functions;
// record the operand of var/func
ArrayList *op_variables;
ArrayList *op_functions;
//record the operand of label/temVar
ArrayList *labels;
ArrayList *temVars;

ArrayList *interCodes;

void initIR() {
    ir_functions = ArrayListCreate(50, 20);
    ir_variables = ArrayListCreate(50, 100);
    interCodes = ArrayListCreate(sizeof(InterCode), 100);
    temVars = ArrayListCreate(sizeof(Operand), 50);
    labels = ArrayListCreate(sizeof(Operand), 50);
    op_functions = ArrayListCreate(sizeof(Operand), 50);
    op_variables = ArrayListCreate(sizeof(Operand), 50);
}

int containsInTable(ArrayList *table, char *name) {
    assert(name != NULL);
    int size = ArrayListSize(table);
    int result = -1;
    for (int i = 0; i < size; i++) {
        char *tem = ArrayListGet(table, i);
        if (strcmp(tem, name) == 0) {
            result = i;
            break;
        }
    }
    return result;
}

int containsVar(char *name) {
    return containsInTable(ir_variables, name);
}

int containsFunc(char *name) {
    return containsInTable(ir_functions, name);
}

static void copyOperands(Operand* src, Operand *dest){
    switch(src->kind){
        case OPERAND_IMM: dest->val.imm_value = src->val.imm_value; break;
        case OPERAND_TEMP: dest->val.temp_no = src->val.temp_no; break;
        case OPERAND_LABEL: dest->val.label_no = src->val.label_no; break;
        default:
            strcpy(dest->val.string, src->val.string);
            break;
    }
}


static char *handleOperand(Operand *operand) {
    char *result = (char *) malloc(30);
    switch (operand->kind) {
        case OPERAND_VARIABLE:
            sprintf(result, "var%d", containsVar(operand->val.string));
            break;
        case OPERAND_FUNC:
            if(strcmp(operand->val.string, "main") == 0){
                sprintf(result, "main");
            }
            else{
               sprintf(result, "func%d", containsFunc(operand->val.string));
            }
            break;
        case OPERAND_TEMP:
            sprintf(result, "tem%d", operand->val.temp_no);
            break;
        case OPERAND_IMM:
            sprintf(result, "#%d", operand->val.imm_value);
            break;
        case OPERAND_LABEL:
            sprintf(result, "label%d", operand->val.label_no);
            break;
        case OPERAND_OPERATOR:
            return operand->val.string;
        case OPERAND_SIZE:
            sprintf(result, "%d", operand->val.imm_value);
            break;
        default:
            assert(1 == 1); // not in here
    }
    return result;
}

void printInterCode(InterCode *interCode) {
    switch (interCode->operation) {
        case IR_LABEL:
            printf("LABEL %s :\n", handleOperand(interCode->operands));
            break;
        case IR_FUNC:
            printf("FUNCTION %s :\n", handleOperand(interCode->operands));
            break;
        case IR_ASSIGN: {
            switch (interCode->type) {
                case GET_ADDR:
                    printf("%s := &%s\n", handleOperand(interCode->operands), handleOperand(interCode->operands->next));
                    break;
                case GET_VAL:
                    printf("%s := *%s\n", handleOperand(interCode->operands), handleOperand(interCode->operands->next));
                    break;
                case SET_VAL:
                    printf("*%s := %s\n", handleOperand(interCode->operands), handleOperand(interCode->operands->next));
                    break;
                case BOTH_POINTER:
                    printf("*%s := *%s\n", handleOperand(interCode->operands),
                           handleOperand(interCode->operands->next));
                    break;
                default:
                    printf("%s := %s\n", handleOperand(interCode->operands), handleOperand(interCode->operands->next));
                    break;
            }
            break;
        }
        case IR_ADD:
            switch (interCode->type) {
                case GET_ADDR:
                    printf("%s := &%s + %s\n", handleOperand(interCode->operands),
                           handleOperand(interCode->operands->next), handleOperand(interCode->operands->next->next));
                    break;
                default:
                    printf("%s := %s + %s\n", handleOperand(interCode->operands),
                           handleOperand(interCode->operands->next), handleOperand(interCode->operands->next->next));
                    break;
            }
            break;
        case IR_MUL:
            printf("%s := %s * %s\n", handleOperand(interCode->operands), handleOperand(interCode->operands->next),
                   handleOperand(interCode->operands->next->next));
            break;
        case IR_SUB:
            printf("%s := %s - %s\n", handleOperand(interCode->operands), handleOperand(interCode->operands->next),
                   handleOperand(interCode->operands->next->next));
            break;
        case IR_DIV:
            printf("%s := %s / %s\n", handleOperand(interCode->operands), handleOperand(interCode->operands->next),
                   handleOperand(interCode->operands->next->next));
            break;
        case GOTO:
            printf("GOTO %s\n", handleOperand(interCode->operands));
            break;
        case IR_IF:
            printf("IF %s %s %s ", handleOperand(interCode->operands), handleOperand(interCode->operands->next),
                   handleOperand(interCode->operands->next->next));
            break;
        case IR_RETURN:
            printf("RETURN %s\n\n", handleOperand(interCode->operands));
            break;
        case DEC:
            printf("DEC %s %s\n", handleOperand(interCode->operands), handleOperand(interCode->operands->next));
            break;
        case ARG:
            switch (interCode->type) {
                case GET_ADDR:
                    printf("ARG &%s\n", handleOperand(interCode->operands));
                    break;
                default:
                    printf("ARG %s\n", handleOperand(interCode->operands));
                    break;
            }
            break;
        case CALL:
            if(interCode->operands->kind == OPERAND_FUNC){
                printf("CALL %s\n", handleOperand(interCode->operands));
            }
            else{
                printf("%s := CALL %s\n", handleOperand(interCode->operands), handleOperand(interCode->operands->next));
            }
            break;
        case PARAM:
            printf("PARAM %s\n", handleOperand(interCode->operands));
            break;
        case READ:
            printf("READ %s\n", handleOperand(interCode->operands));
            break;
        case WRITE:
            printf("WRITE %s\n", handleOperand(interCode->operands));
            break;
        default:
            printf("ERROR in printInterCode\n");
            break;
    }
}

void printInterCodes() {
    int size = ArrayListSize(interCodes);
    for (int i = 0; i < size; i++) {
        printInterCode((InterCode *) ArrayListGet(interCodes, i));
    }
}

Operand *createOperand(enum OPERAND_KIND kind) {
    Operand *result = (Operand *) malloc(sizeof(Operand));
    memset(result, 0, sizeof(Operand));
    if (kind == OPERAND_VARIABLE || kind == OPERAND_FUNC || kind == OPERAND_OPERATOR) {
        result->val.string = (char *) malloc(30);
    }
    result->kind = kind;
    return result;
}

int addVar(char *name) {
    int result = ArrayListSize(ir_variables);
    ArrayListInsert(ir_variables, result, name);
    return result;
}


int addFunc(char *name) {
    int result = ArrayListSize(ir_functions);
    ArrayListInsert(ir_functions, result, name);
    return result;
}


void addOPVar(Operand *var, int pos) {
    ArrayListInsert(op_variables, pos, var);
}

void addOPFunc(Operand *func, int pos) {
    ArrayListInsert(op_functions, pos, func);
}

int addTemVar(Operand *tem) {
    int result = tem_count;
    ArrayListInsert(temVars, result, tem);
    tem_count++;
    return result;
}

int addLabel(Operand *label) {
    int result = label_count;
    ArrayListInsert(labels, result, label);
    label_count++;
    return result;
}

Operand *getOPVar(int index) {
    return (Operand *) ArrayListGet(op_variables, index);
}

Operand *getOPFunc(int index) {
    return (Operand *) ArrayListGet(op_functions, index);
}

Operand *getLatestTemVar() {
    return (Operand *) ArrayListGet(temVars, tem_count - 1);
}

Operand *getLatestLabel() {
    return (Operand *) ArrayListGet(labels, label_count - 1);
}

void addInterCode(Operand *operands, enum IR_OPERATION kind, enum ASSIGN_TYPE type) {
    InterCode *interCode = (InterCode *) malloc(sizeof(InterCode));
    interCode->operands = operands;
    interCode->operation = kind;
    interCode->type = type;
    ArrayListInsert(interCodes, ArrayListSize(interCodes), interCode);
    printInterCode(interCode);
}


Operand *getTemVar(bool is_new) {
    if (is_new) {
        Operand *result = createOperand(OPERAND_TEMP);
        result->val.temp_no = tem_count;
        addTemVar(result);
        return result;
    } else {
        return getLatestTemVar();
    }
}

Operand *getLabel(bool is_new) {
    if (is_new) {
        Operand *result = createOperand(OPERAND_LABEL);
        result->val.label_no = label_count;
        addLabel(result);
        return result;
    } else {
        return getLatestLabel();
    }
}

int countSize(SemanticType type) {
    int size = 0;
    FieldList fields;
    switch (type->kind) {
        case BASIC:
            size = 4;
            break;
        case ARRAY:
            size = type->val.array->size;
            size *= countSize(type->val.array->elem);
            break;
        case STRUCTURE:
            fields = type->val.structure->type->val.structure;
            while (fields != NULL) {
                size += countSize(fields->type);
                fields = fields->next;
            }
            break;
        default:
            break;
    }
    return size;
}


// handle program
static void handleProgram(Node *node) {
    handleExtDefList(node->children[0]);
}

static void handleExtDefList(Node *node) {
    if (node != NULL) {
        handleExtDef(node->children[0]);
        handleExtDefList(node->children[1]);
    }
}

static void handleExtDef(Node *node) {
    if (strcmp(node->children[1]->data.specifier, "ExtDecList") == 0) {
        handleExtDecList(node->children[1]);
    } else if (strcmp(node->children[1]->data.specifier, "FunDec") == 0) {
        handleFunDec(node->children[1]);
        handleCompSt(node->children[2]);
    }
}

static void handleExtDecList(Node *node) {
    handleVarDec(node->children[0]);
    if (node->child_count == 3) {
        handleExtDecList(node->children[2]);
    }
}


static char *handleOptTag(Node *node) {
    if (node == NULL) {
        return NULL;
    }
    char *result = (char *) malloc(strlen(node->children[0]->data.value.string_type) + 1);
    strcpy(result, node->children[0]->data.value.string_type);
    return result;
}

static char *handleTag(Node *node) {
    char *result = (char *) malloc(strlen(node->children[0]->data.value.string_type) + 1);
    strcpy(result, node->children[0]->data.value.string_type);
    return result;
}

// handle declaration
// return pair.name is NULL, if it meets error
static void handleVarDec(Node *node) {
    // VarDec -> ID
    if (strcmp(node->children[0]->data.specifier, "ID") == 0) {
        SemanticType specifier = node->syn_semantics.semantic_type;
        char *name = node->children[0]->data.value.string_type;
        // not the first time meet the var
        if (containsVar(name) != -1) {
            return;
        }
        int index = addVar(name);
        Operand *operand = createOperand(OPERAND_VARIABLE);
        strcpy(operand->val.string, name);
        addOPVar(operand, index);
        // array definition
        if (specifier->kind == ARRAY) {
            // DEC size for array
            int size = countSize(specifier);
            Operand *array_size = createOperand(OPERAND_SIZE);
            array_size->val.imm_value = size;
            operand->next = array_size;
            // gen DEC array size
            addInterCode(operand, DEC, ASSIGN_NONE);
        }
    }
    else{
        handleVarDec(node->children[0]);
    }
}

// node->inh_semantics.specifier_type is return type
static void handleFunDec(Node *node) {
    // add rename function and generate inter code
    char *name = node->syn_semantics.semantic_type->val.function->name;
    int index = addFunc(name);
    Operand *operand = createOperand(OPERAND_FUNC);
    strcpy(operand->val.string, name);
    addOPFunc(operand, index);
    //generate function declaration
    addInterCode(operand, IR_FUNC, ASSIGN_NONE);

    if (node->child_count == 4) {
        handleVarList(node->children[2]);
        ArgList args = node->syn_semantics.semantic_type->val.function->next;
        while (args != NULL) {
            int pos = containsVar(args->name);
            assert(pos != -1);
            Operand *arg = getOPVar(pos);
            //generate parameter declaration
            addInterCode(arg, PARAM, ASSIGN_NONE);
            args = args->next;
        }
    }
}

static void handleVarList(Node *node){
    handleParamDec(node->children[0]);
    if (node->child_count == 3) {
        handleVarList(node->children[2]);
    }
}

static void handleVarDecInParam(Node *node) {
    // VarDec -> ID
    if (strcmp(node->children[0]->data.specifier, "ID") == 0) {
        SemanticType specifier = node->syn_semantics.semantic_type;
        char *name = node->children[0]->data.value.string_type;;
        // not the first time meet the var
        if (containsVar(name) != -1) {
            return;
        }
        int index = addVar(name);
        Operand *operand = createOperand(OPERAND_VARIABLE);
        // array definition
        if (specifier->kind == ARRAY) {
            operand->is_address = true;
        }
        strcpy(operand->val.string, name);
        addOPVar(operand, index);
    }
    else{
        handleVarDecInParam(node->children[0]);
    }
}

static void handleParamDec(Node *node){
    handleVarDecInParam(node->children[1]);
}

// handle statements
static void handleCompSt(Node *node) {
    handleDefListInFunction(node->children[1]);
    handleStmtList(node->children[2]);
}

static void handleStmtList(Node *node) {
    if (node != NULL) {
        handleStmt(node->children[0]);
        handleStmtList(node->children[1]);
    }
}

static void handleStmt(Node *node) {
    if (strcmp(node->children[0]->data.specifier, "Exp") == 0) {
        handleExp(node->children[0], NULL);
    } else if (strcmp(node->children[0]->data.specifier, "CompSt") == 0) {
        handleCompSt(node->children[0]);
    } else if (strcmp(node->children[0]->data.specifier, "RETURN") == 0) {
        Operand *place = getTemVar(true);
        handleExp(node->children[1], place);
        //generate return inter code
        addInterCode(place, IR_RETURN, ASSIGN_NONE);
    } else if (node->child_count == 5) {
        //IF LP Exp RP Stmt
        if (strcmp(node->children[0]->data.specifier, "IF") == 0) {
            Operand *label1 = getLabel(true);
            Operand *label2 = getLabel(true);
            handleCond(node->children[2], label1, label2);
            // LABEL label1
            addInterCode(label1, IR_LABEL, ASSIGN_NONE);
            handleStmt(node->children[4]);
            // LABEL label2
            addInterCode(label2, IR_LABEL, ASSIGN_NONE);
        }
            //WHILE
        else {
            Operand *label1 = getLabel(true);
            Operand *label2 = getLabel(true);
            Operand *label3 = getLabel(true);
            addInterCode(label1, IR_LABEL, ASSIGN_NONE);
            handleCond(node->children[2], label2, label3);
            addInterCode(label2, IR_LABEL, ASSIGN_NONE);
            handleStmt(node->children[4]);
            addInterCode(label3, IR_LABEL, ASSIGN_NONE);
        }

    }
        // IF LP Exp RP Stmt ELSE Stmt
    else {
        Operand *label1 = getLabel(true);
        Operand *label2 = getLabel(true);
        Operand *label3 = getLabel(true);
        handleCond(node->children[2], label1, label2);
        addInterCode(label1, IR_LABEL, ASSIGN_NONE);
        handleStmt(node->children[4]);
        addInterCode(label2, IR_LABEL, ASSIGN_NONE);
        handleStmt(node->children[6]);
        addInterCode(label3, IR_LABEL, ASSIGN_NONE);
    }
}


// handle local definition
static void handleDefListInFunction(Node *node) {
    if (node != NULL) {
        handleDefInFunction(node->children[0]);
        handleDefListInFunction(node->children[1]);
    }
}

static void handleDefInFunction(Node *node) {
    handleDecListInFunction(node->children[1]);
}

static void handleDecListInFunction(Node *node) {
    handleDecInFunction(node->children[0]);
    if (node->child_count == 3) {
        handleDecListInFunction(node->children[2]);
    }
}


static char *getVarDecIDName(Node *node) {
    if (node->child_count == 1) {
        return node->children[0]->data.value.string_type;
    } else {
        return getVarDecIDName(node->children[0]);
    }
}

static void addAssignInterCode(Operand* left, Operand* right){
    if(right->is_address && left->is_address){
        addInterCode(left, IR_ASSIGN, ASSIGN_NONE);
    } else if(right->is_address){
        addInterCode(left, IR_ASSIGN, GET_VAL);
    }
    else if(left->is_address){
        addInterCode(left, IR_ASSIGN, GET_ADDR);
    }
    else{
        addInterCode(left, IR_ASSIGN, ASSIGN_NONE);
    }
}

static void handleDecInFunction(Node *node) {
    handleVarDec(node->children[0]);
    if (node->child_count != 1) {
        // int i = 1
        Operand *tem = getTemVar(true);
        handleExp(node->children[2], tem);
        char *name = getVarDecIDName(node->children[0]);
        int index = containsVar(name);
        assert(index != -1);
        Operand *var = getOPVar(index);
        var->next = tem;
        addAssignInterCode(var, tem);
    }
}




// handle expression
// setting whether the node can be left value
static void handleExp(Node *node, Operand *place) {
    if(place == NULL){
        place = getTemVar(true);
    }
    if (node->child_count == 1) // ID INT FLOAT
    {
        if (strcmp(node->children[0]->data.specifier, "ID") == 0) {
            int index = containsVar(node->children[0]->data.value.string_type);
            assert(index != -1);
            Operand *var = getOPVar(index);
            place->next = var;
            addAssignInterCode(place, var);
        } else if (strcmp(node->children[0]->data.specifier, "INT") == 0) {
            Operand *imm = createOperand(OPERAND_IMM);
            imm->val.imm_value = node->children[0]->data.value.int_type;
            place->next = imm;
            addInterCode(place, IR_ASSIGN, ASSIGN_NONE);
        } else if (strcmp(node->children[0]->data.specifier, "FLOAT") == 0) {

        }
    }
    // MINUS
    else if(node->child_count == 2){
        if (strcmp(node->children[0]->data.specifier, "MINUS") == 0) {
            Operand *tem = getTemVar(true);
            handleExp(node->children[1], tem);
            Operand *imm = createOperand(OPERAND_IMM);
            imm->val.imm_value = 0;
            imm->next = tem;
            place->next = imm;
            addInterCode(place, IR_SUB, ASSIGN_NONE);
        } else if(strcmp(node->children[0]->data.specifier, "NOT") == 0){
            Operand *label1 = getLabel(true);
            Operand *label2 = getLabel(true);
            Operand *imm1 = createOperand(OPERAND_IMM);
            imm1->val.imm_value = 0;
            place->next = imm1;
            addInterCode(place, IR_ASSIGN, ASSIGN_NONE);
            handleCond(node, label1, label2);
            addInterCode(label1, IR_LABEL, ASSIGN_NONE);
            Operand *imm2 = createOperand(OPERAND_IMM);
            imm2->val.imm_value = 0;
            place->next = imm2;
            addInterCode(place, IR_ASSIGN, ASSIGN_NONE);
            addInterCode(label2, IR_LABEL, ASSIGN_NONE);
        }
    } else if (node->child_count == 3) {
        if (strcmp(node->children[1]->data.specifier, "ASSIGNOP") == 0) {
            // handle left val is Exp -> ID
            if(node->children[0]->child_count == 1){
                int index = containsVar(node->children[0]->children[0]->data.value.string_type);
                assert(index != -1);
                Operand *var = getOPVar(index);
                Operand *tem = getTemVar(true);
                handleExp(node->children[2], tem);
                var->next = tem;
                addAssignInterCode(var, tem);
                place->next = var;
                var->next = NULL;
                addAssignInterCode(place, var);
            }
            // TODO: how to handle the left val is i[j][k]
            else{
                Operand *tem1 = getTemVar(true);
                handleExp(node->children[0], tem1);
                Operand *tem2 = getTemVar(true);
                handleExp(node->children[2], tem2);
                tem1->next = tem2;
                addInterCode(tem1, IR_ASSIGN, SET_VAL);
                tem1->next = NULL;
                place->next = tem1;
                addInterCode(place, IR_ASSIGN, GET_VAL);
            }

        } else if (strcmp(node->children[1]->data.specifier, "AND") == 0
                    || strcmp(node->children[1]->data.specifier, "OR") == 0
                    || strcmp(node->children[1]->data.specifier, "RELOP") == 0) {
            Operand *label1 = getLabel(true);
            Operand *label2 = getLabel(true);
            Operand *imm1 = createOperand(OPERAND_IMM);
            imm1->val.imm_value = 0;
            place->next = imm1;
            addInterCode(place, IR_ASSIGN, ASSIGN_NONE);
            handleCond(node, label1, label2);
            addInterCode(label1, IR_LABEL, ASSIGN_NONE);
            Operand *imm2 = createOperand(OPERAND_IMM);
            imm2->val.imm_value = 0;
            place->next = imm2;
            addInterCode(place, IR_ASSIGN, ASSIGN_NONE);
            addInterCode(label2, IR_LABEL, ASSIGN_NONE);
        } else if (strcmp(node->children[1]->data.specifier, "LP") == 0) {
            handleExpFuncCall(node, place);
        } else if (strcmp(node->children[1]->data.specifier, "Exp") == 0) {
            handleExp(node->children[1], place);
        } else if (strcmp(node->children[1]->data.specifier, "DOT") == 0) {
            // ? not handle struct
        } else {
            // MATH OPERATOR
            Operand *tem1 = getTemVar(true);
            Operand *tem2 = getTemVar(true);
            handleExp(node->children[0], tem1);
            handleExp(node->children[2], tem2);
            place->next = tem1;
            tem1->next = tem2;
            if(strcmp(node->children[1]->data.specifier, "PLUS") == 0){
                addInterCode(place, IR_ADD, ASSIGN_NONE);
            }
            else if(strcmp(node->children[1]->data.specifier, "MINUS") == 0){
                addInterCode(place, IR_SUB, ASSIGN_NONE);
            }
            else if(strcmp(node->children[1]->data.specifier, "STAR") == 0){
                addInterCode(place, IR_MUL, ASSIGN_NONE);
            }
            else if(strcmp(node->children[1]->data.specifier, "DIV") == 0){
                addInterCode(place, IR_DIV, ASSIGN_NONE);
            }
        }
    } else {
        if (strcmp(node->children[0]->data.specifier, "ID") == 0) {
            return handleExpFuncCall(node, place);
        } else {
            // TODO: handle array Exp -> Exp LB Exp RB

        }
    }
}

static void handeExpArray(Node* node, Operand* size){
    


}

static void handleExpFuncCall(Node *node, Operand* place) {
    assert(place != NULL);
    SymbolPair function = TableGet(node->children[0]->data.value.string_type);
    // ID LP RP
    if(node->child_count == 3){
        if(strcmp(function->name, "read") == 0){
            addInterCode(place, READ, ASSIGN_NONE);
        }
        else{
            Operand * func = getOPFunc(containsFunc(function->name));
            place->next = func;
            addInterCode(place, CALL, ASSIGN_NONE);

        }
    }
    // ID LP Args RP
    else{
        Operand* args = createOperand(OPERAND_TEMP);
        handleArgs(node->children[2], args);
        if(strcmp(function->name, "write") == 0){
            addInterCode(args->next, WRITE, ASSIGN_NONE);
            Operand *imm = createOperand(OPERAND_IMM);
            imm->val.imm_value = 0;
            assert(place != NULL);
            place->next = imm;
            addInterCode(place, IR_ASSIGN, ASSIGN_NONE);
        }
        else{
            Operand * func = getOPFunc(containsFunc(function->name));
            Operand *arg = args->next;
            while (arg != NULL){
                addInterCode(arg, ARG, ASSIGN_NONE);
                arg = arg->next;
            }
            place->next = func;
            addInterCode(place, CALL, ASSIGN_NONE);
        }
    }
}



// for change the head of arg list, args.next points to the args, args is the head node
static void handleArgs(Node *node, Operand* args) {

    Operand *temVar = getTemVar(true);
    handleExp(node->children[0], temVar);

    Operand *tem_args = args->next;
    temVar->next = tem_args;
    args->next = temVar;
    if (node->child_count == 3) {
        handleArgs(node->children[2], args);
    }

}

// Exp -> condition production
static void handleCond(Node *exp, Operand *label_true, Operand *label_false){
    if(strcmp(exp->children[1]->data.specifier, "RELOP") == 0){
        Operand *tem1 = getTemVar(true);
        Operand *tem2 = getTemVar(true);
        handleExp(exp->children[0], tem1);
        handleExp(exp->children[2], tem2);
        Operand *op = createOperand(OPERAND_OPERATOR);
        strcpy(op->val.string, exp->children[1]->data.value.string_type);
        op->next = tem2;
        tem1->next = op;
        addInterCode(tem1, IR_IF, ASSIGN_NONE);
        addInterCode(label_true, GOTO, ASSIGN_NONE);
        addInterCode(label_false, GOTO, ASSIGN_NONE);
    }
    else if(strcmp(exp->children[1]->data.specifier, "AND") == 0){
        Operand *label1 = getLabel(true);
        handleCond(exp->children[0], label1, label_false);
        addInterCode(label1, IR_LABEL, ASSIGN_NONE);
        handleCond(exp->children[2], label_true, label_false);
    }
    else if(strcmp(exp->children[1]->data.specifier, "OR") == 0){
        Operand *label1 = getLabel(true);
        handleCond(exp->children[0], label_true, label1);
        addInterCode(label1, IR_LABEL, ASSIGN_NONE);
        handleCond(exp->children[2], label_true, label_false);
    }
    else if(strcmp(exp->children[0]->data.specifier, "NOT") == 0){
        handleCond(exp->children[1], label_false, label_true);
    }
    else{
        Operand *tem1 = getTemVar(true);
        handleExp(exp, tem1);
        Operand *imm = createOperand(OPERAND_IMM);
        imm->val.imm_value = 0;
        Operand *op = createOperand(OPERAND_OPERATOR);
        strcpy(op->val.string, "!=");
        op->next = imm;
        tem1->next = op;
        addInterCode(tem1, IR_IF, ASSIGN_NONE);
        addInterCode(label_true, GOTO, ASSIGN_NONE);
        addInterCode(label_false, GOTO, ASSIGN_NONE);
    }
}

