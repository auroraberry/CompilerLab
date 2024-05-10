#include "semantic.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>
#include <assert.h>
#include "SymbolTable.h"
#include "SyntaxTree.h"
#include "IR.h"
#include "stdarg.h"

bool has_ir_error = false;
static void printfErrorInfo(char* info){
    //printf("%s", info);
    exit(0);
}

static void handleProgram(Node *node);

static void handleExtDefList(Node *node);

static void handleExtDef(Node *node); // definition -> record in symbol table
static void handleExtDecList(Node *node);

static void handleSpecifier(Node *node);

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
static void handleExpArray(Node *node, Operand *place);

static void handleArgs(Node *node, Args *args, ArgList params);

static void handleCond(Node *exp, Operand *label_true, Operand *label_false);

static char *handleOptTag(Node *node);

static char *handleTag(Node *node);

static char *getVarDecIDName(Node *node);

char *filename;
FILE *file;

void generateIR(Node *root, char *name) {
    filename = (char *) malloc(strlen(name) + 1);
    strcpy(filename, name);
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

static void copyOperands(Operand *src, Operand *dest) {
    switch (src->kind) {
        case OPERAND_IMM:
            dest->val.imm_value = src->val.imm_value;
            break;
        case OPERAND_TEMP:
            dest->val.temp_no = src->val.temp_no;
            break;
        case OPERAND_LABEL:
            dest->val.label_no = src->val.label_no;
            break;
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
            if (strcmp(operand->val.string, "main") == 0) {
                sprintf(result, "main");
            } else {
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
            fprintf(file, "LABEL %s :\n", handleOperand(interCode->operands[0]));
            break;
        case IR_FUNC:
            fprintf(file, "FUNCTION %s :\n", handleOperand(interCode->operands[0]));
            break;
        case IR_ASSIGN: {
            switch (interCode->type) {
                case GET_ADDR:
                    fprintf(file, "%s := &%s\n", handleOperand(interCode->operands[0]),
                            handleOperand(interCode->operands[1]));
                    break;
                case GET_VAL:
                    fprintf(file, "%s := *%s\n", handleOperand(interCode->operands[0]),
                            handleOperand(interCode->operands[1]));
                    break;
                case SET_VAL:
                    fprintf(file, "*%s := %s\n", handleOperand(interCode->operands[0]),
                            handleOperand(interCode->operands[1]));
                    break;
                case BOTH_POINTER:
                    fprintf(file, "*%s := *%s\n", handleOperand(interCode->operands[0]),
                            handleOperand(interCode->operands[1]));
                    break;
                default:
                    fprintf(file, "%s := %s\n", handleOperand(interCode->operands[0]),
                            handleOperand(interCode->operands[1]));
                    break;
            }
            break;
        }
        case IR_ADD:
            switch (interCode->type) {
                case GET_ADDR:
                    fprintf(file, "%s := &%s + %s\n", handleOperand(interCode->operands[0]),
                            handleOperand(interCode->operands[1]), handleOperand(interCode->operands[2]));
                    break;
                default:
                    fprintf(file, "%s := %s + %s\n", handleOperand(interCode->operands[0]),
                            handleOperand(interCode->operands[1]), handleOperand(interCode->operands[2]));
                    break;
            }
            break;
        case IR_MUL:
            fprintf(file, "%s := %s * %s\n", handleOperand(interCode->operands[0]),
                    handleOperand(interCode->operands[1]),
                    handleOperand(interCode->operands[2]));
            break;
        case IR_SUB:
            fprintf(file, "%s := %s - %s\n", handleOperand(interCode->operands[0]),
                    handleOperand(interCode->operands[1]),
                    handleOperand(interCode->operands[2]));
            break;
        case IR_DIV:
            fprintf(file, "%s := %s / %s\n", handleOperand(interCode->operands[0]),
                    handleOperand(interCode->operands[1]),
                    handleOperand(interCode->operands[2]));
            break;
        case GOTO:
            fprintf(file, "GOTO %s\n", handleOperand(interCode->operands[0]));
            break;
        case IR_IF:
            fprintf(file, "IF %s %s %s ", handleOperand(interCode->operands[0]), handleOperand(interCode->operands[1]),
                    handleOperand(interCode->operands[2]));
            break;
        case IR_RETURN:
            fprintf(file, "RETURN %s\n", handleOperand(interCode->operands[0]));
            break;
        case DEC:
            fprintf(file, "DEC %s %s\n", handleOperand(interCode->operands[0]), handleOperand(interCode->operands[1]));
            break;
        case ARG:
            switch (interCode->type) {
                case GET_ADDR:
                    fprintf(file, "ARG &%s\n", handleOperand(interCode->operands[0]));
                    break;
                default:
                    fprintf(file, "ARG %s\n", handleOperand(interCode->operands[0]));
                    break;
            }
            break;
        case CALL:
            fprintf(file, "%s := CALL %s\n", handleOperand(interCode->operands[0]),
                        handleOperand(interCode->operands[1]));
            break;
        case PARAM:
            fprintf(file, "PARAM %s\n", handleOperand(interCode->operands[0]));
            break;
        case READ:
            fprintf(file, "READ %s\n", handleOperand(interCode->operands[0]));
            break;
        case WRITE:
            fprintf(file, "WRITE %s\n", handleOperand(interCode->operands[0]));
            break;
        default:
            fprintf(file, "ERROR in printInterCode\n");
            break;
    }
}

void printInterCodeToStd(InterCode *interCode) {
    switch (interCode->operation) {
        case IR_LABEL:
            printf("LABEL %s :\n", handleOperand(interCode->operands[0]));
            break;
        case IR_FUNC:
            printf("FUNCTION %s :\n", handleOperand(interCode->operands[0]));
            break;
        case IR_ASSIGN: {
            switch (interCode->type) {
                case GET_ADDR:
                    printf("%s := &%s\n", handleOperand(interCode->operands[0]), handleOperand(interCode->operands[1]));
                    break;
                case GET_VAL:
                    printf("%s := *%s\n", handleOperand(interCode->operands[0]), handleOperand(interCode->operands[1]));
                    break;
                case SET_VAL:
                    printf("*%s := %s\n", handleOperand(interCode->operands[0]), handleOperand(interCode->operands[1]));
                    break;
                case BOTH_POINTER:
                    printf("*%s := *%s\n", handleOperand(interCode->operands[0]),
                           handleOperand(interCode->operands[1]));
                    break;
                default:
                    printf("%s := %s\n", handleOperand(interCode->operands[0]), handleOperand(interCode->operands[1]));
                    break;
            }
            break;
        }
        case IR_ADD:
            switch (interCode->type) {
                case GET_ADDR:
                    printf("%s := &%s + %s\n", handleOperand(interCode->operands[0]),
                           handleOperand(interCode->operands[1]), handleOperand(interCode->operands[2]));
                    break;
                default:
                    printf("%s := %s + %s\n", handleOperand(interCode->operands[0]),
                           handleOperand(interCode->operands[1]), handleOperand(interCode->operands[2]));
                    break;
            }
            break;
        case IR_MUL:
            printf("%s := %s * %s\n", handleOperand(interCode->operands[0]), handleOperand(interCode->operands[1]),
                   handleOperand(interCode->operands[2]));
            break;
        case IR_SUB:
            printf("%s := %s - %s\n", handleOperand(interCode->operands[0]), handleOperand(interCode->operands[1]),
                   handleOperand(interCode->operands[2]));
            break;
        case IR_DIV:
            printf("%s := %s / %s\n", handleOperand(interCode->operands[0]), handleOperand(interCode->operands[1]),
                   handleOperand(interCode->operands[2]));
            break;
        case GOTO:
            printf("GOTO %s\n", handleOperand(interCode->operands[0]));
            break;
        case IR_IF:
            printf("IF %s %s %s ", handleOperand(interCode->operands[0]), handleOperand(interCode->operands[1]),
                   handleOperand(interCode->operands[2]));
            break;
        case IR_RETURN:
            printf("RETURN %s\n\n", handleOperand(interCode->operands[0]));
            break;
        case DEC:
            printf("DEC %s %s\n", handleOperand(interCode->operands[0]), handleOperand(interCode->operands[1]));
            break;
        case ARG:
            switch (interCode->type) {
                case GET_ADDR:
                    printf("ARG &%s\n", handleOperand(interCode->operands[0]));
                    break;
                default:
                    printf("ARG %s\n", handleOperand(interCode->operands[0]));
                    break;
            }
            break;
        case CALL:
            printf("%s := CALL %s\n", handleOperand(interCode->operands[0]), handleOperand(interCode->operands[1]));
            break;
        case PARAM:
            printf("PARAM %s\n", handleOperand(interCode->operands[0]));
            break;
        case READ:
            printf("READ %s\n", handleOperand(interCode->operands[0]));
            break;
        case WRITE:
            printf("WRITE %s\n", handleOperand(interCode->operands[0]));
            break;
        default:
            printf("ERROR in printInterCode\n");
            break;
    }
}

void printInterCodes() {
    file = fopen(filename, "w");
    assert(file != NULL);
    int size = ArrayListSize(interCodes);
    for (int i = 0; i < size; i++) {
        printInterCode((InterCode *) ArrayListGet(interCodes, i));
    }
    fclose(file);
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

void addInterCode(Operand **operands, enum IR_OPERATION kind, enum ASSIGN_TYPE type) {
    assert(operands != NULL);
    InterCode *interCode = (InterCode *) malloc(sizeof(InterCode));
    for (int i = 0; i < 4; i++) {
        interCode->operands[i] = operands[i];
    }
    interCode->operation = kind;
    interCode->type = type;
    ArrayListInsert(interCodes, ArrayListSize(interCodes), interCode);
    //printInterCodeToStd(interCode);
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

static Operand **createOperandArray(int num, ...) {
    Operand **result = (Operand **) malloc(4 * 4);
    memset(result, 0, 16);
    va_list vaList;
    va_start(vaList, num);
    for (int i = 0; i < num; i++) {
        result[i] = va_arg(vaList, Operand*);
    }
    va_end(vaList);
    return result;
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
    handleSpecifier(node->children[0]);
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

static void handleSpecifier(Node *node) {
    if (strcmp(node->children[0]->data.specifier, "StructSpecifier") == 0) {
        has_ir_error = true;
        printfErrorInfo("Cannot translate: Code contains variables of struct type.");
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
            // gen DEC array size
            addInterCode(createOperandArray(2, operand, array_size), DEC, ASSIGN_NONE);
        }
    } else {
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
    addInterCode(createOperandArray(1, operand), IR_FUNC, ASSIGN_NONE);

    if (node->child_count == 4) {
        handleVarList(node->children[2]);
        ArgList args = node->syn_semantics.semantic_type->val.function->next;
        while (args != NULL) {
            int pos = containsVar(args->name);
            assert(pos != -1);
            Operand *arg = getOPVar(pos);
            //generate parameter declaration
            addInterCode(createOperandArray(1, arg), PARAM, ASSIGN_NONE);
            args = args->next;
        }
    }
}

static void handleVarList(Node *node) {
    handleParamDec(node->children[0]);
    if (node->child_count == 3) {
        handleVarList(node->children[2]);
    }
}

static void handleVarDecInParam(Node *node, int count) {
    // VarDec -> ID
    if (count >= 3) {
        has_ir_error = true;
        printfErrorInfo("Cannot translate: Code contains variables of multi-dimensional array type.");
    }
    if (strcmp(node->children[0]->data.specifier, "ID") == 0) {
        SemanticType specifier = node->syn_semantics.semantic_type;
        char *name = node->children[0]->data.value.string_type;
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
    } else {
        handleVarDecInParam(node->children[0], count + 1);
    }
}

static void handleParamDec(Node *node) {
    handleVarDecInParam(node->children[1], 1);
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
        if (node->children[1]->syn_semantics.semantic_type->kind == ARRAY) {
            has_ir_error = true;
            printfErrorInfo("Cannot translate: Code contains return variables of array type.");
        }
        Operand *place = getTemVar(true);
        handleExp(node->children[1], place);
        //generate return inter code
        addInterCode(createOperandArray(1, place), IR_RETURN, ASSIGN_NONE);
    } else if (node->child_count == 5) {
        //IF LP Exp RP Stmt
        if (strcmp(node->children[0]->data.specifier, "IF") == 0) {
            Operand *label1 = getLabel(true);
            Operand *label2 = getLabel(true);
            handleCond(node->children[2], label1, label2);
            // LABEL label1
            addInterCode(createOperandArray(1, label1), IR_LABEL, ASSIGN_NONE);
            handleStmt(node->children[4]);
            // LABEL label2
            addInterCode(createOperandArray(1, label2), IR_LABEL, ASSIGN_NONE);
        }
            //WHILE
        else {
            Operand *label1 = getLabel(true);
            Operand *label2 = getLabel(true);
            Operand *label3 = getLabel(true);
            addInterCode(createOperandArray(1, label1), IR_LABEL, ASSIGN_NONE);
            handleCond(node->children[2], label2, label3);
            addInterCode(createOperandArray(1, label2), IR_LABEL, ASSIGN_NONE);
            handleStmt(node->children[4]);
            addInterCode(createOperandArray(1, label1), GOTO, ASSIGN_NONE);
            addInterCode(createOperandArray(1, label3), IR_LABEL, ASSIGN_NONE);
        }

    }
        // IF LP Exp RP Stmt ELSE Stmt
    else {
        Operand *label1 = getLabel(true);
        Operand *label2 = getLabel(true);
        Operand *label3 = getLabel(true);
        handleCond(node->children[2], label1, label2);
        addInterCode(createOperandArray(1, label1), IR_LABEL, ASSIGN_NONE);
        handleStmt(node->children[4]);
        addInterCode(createOperandArray(1, label3), GOTO, ASSIGN_NONE);
        addInterCode(createOperandArray(1, label2), IR_LABEL, ASSIGN_NONE);
        handleStmt(node->children[6]);
        addInterCode(createOperandArray(1, label3), IR_LABEL, ASSIGN_NONE);
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

static void addAssignInterCode(Operand *left, Operand *right) {
    if (right->is_address && left->is_address) {
        addInterCode(createOperandArray(2, left, right), IR_ASSIGN, ASSIGN_NONE);
    } else if (right->is_address) {
        addInterCode(createOperandArray(2, left, right), IR_ASSIGN, GET_VAL);
    } else if (left->is_address) {
        addInterCode(createOperandArray(2, left, right), IR_ASSIGN, GET_ADDR);
    } else {
        addInterCode(createOperandArray(2, left, right), IR_ASSIGN, ASSIGN_NONE);
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
        addAssignInterCode(var, tem);
    }
}


// handle expression
// setting whether the node can be left value
static void handleExp(Node *node, Operand *place) {
    if (node->child_count == 1) // ID INT FLOAT
    {
        if (strcmp(node->children[0]->data.specifier, "ID") == 0) {
            int index = containsVar(node->children[0]->data.value.string_type);
            assert(index != -1);
            Operand *var = getOPVar(index);
            if(place != NULL)
                addAssignInterCode(place, var);
        } else if (strcmp(node->children[0]->data.specifier, "INT") == 0) {
            Operand *imm = createOperand(OPERAND_IMM);
            imm->val.imm_value = node->children[0]->data.value.int_type;
            if(place != NULL)
                addAssignInterCode(place, imm);
        } else if (strcmp(node->children[0]->data.specifier, "FLOAT") == 0) {
            has_ir_error = true;
            printfErrorInfo("Cannot translate: Code contains variables of float type.");
        }
    }
        // MINUS
    else if (node->child_count == 2) {
        if (strcmp(node->children[0]->data.specifier, "MINUS") == 0) {
            Operand *tem = getTemVar(true);
            handleExp(node->children[1], tem);
            Operand *imm = createOperand(OPERAND_IMM);
            imm->val.imm_value = 0;
            if (place != NULL)
                addInterCode(createOperandArray(3, place, imm, tem), IR_SUB, ASSIGN_NONE);
        } else if (strcmp(node->children[0]->data.specifier, "NOT") == 0) {
            assert(place != NULL);
            Operand *label1 = getLabel(true);
            Operand *label2 = getLabel(true);
            Operand *imm1 = createOperand(OPERAND_IMM);
            imm1->val.imm_value = 0;
            addInterCode(createOperandArray(2, place, imm1), IR_ASSIGN, ASSIGN_NONE);
            handleCond(node, label1, label2);
            addInterCode(createOperandArray(1, label1), IR_LABEL, ASSIGN_NONE);
            Operand *imm2 = createOperand(OPERAND_IMM);
            imm2->val.imm_value = 1;
            addInterCode(createOperandArray(2, place, imm2), IR_ASSIGN, ASSIGN_NONE);
            addInterCode(createOperandArray(1, label2), IR_LABEL, ASSIGN_NONE);
        }
    } else if (node->child_count == 3) {
        if (strcmp(node->children[1]->data.specifier, "ASSIGNOP") == 0) {
            // handle left val is Exp -> ID
            if (node->children[0]->child_count == 1) {
                int index = containsVar(node->children[0]->children[0]->data.value.string_type);
                assert(index != -1);
                Operand *var = getOPVar(index);
                Operand *tem = getTemVar(true);
                handleExp(node->children[2], tem);
                if(var->is_address && tem->is_address){
                    addInterCode(createOperandArray(2, var, tem), IR_ASSIGN, BOTH_POINTER);
                }else{
                    addAssignInterCode(var, tem);
                }
                if(place != NULL){
                    addAssignInterCode(place, tem);
                }
            }
                // TODO: how to handle the left val is i[j][k]
            else {
                Operand *tem1 = getTemVar(true);
                tem1->is_address = true;
                handleExp(node->children[0], tem1);
                Operand *tem2 = getTemVar(true);
                handleExp(node->children[2], tem2);
                addInterCode(createOperandArray(2, tem1, tem2), IR_ASSIGN, SET_VAL);
                if(place != NULL){
                    addAssignInterCode(place, tem2);
                }
            }

        } else if (strcmp(node->children[1]->data.specifier, "AND") == 0
                   || strcmp(node->children[1]->data.specifier, "OR") == 0
                   || strcmp(node->children[1]->data.specifier, "RELOP") == 0) {
            Operand *label1 = getLabel(true);
            Operand *label2 = getLabel(true);
            Operand *imm1 = createOperand(OPERAND_IMM);
            imm1->val.imm_value = 0;
            if(place != NULL)
                addAssignInterCode(place, imm1);
            handleCond(node, label1, label2);
            addInterCode(createOperandArray(1, label1), IR_LABEL, ASSIGN_NONE);
            Operand *imm2 = createOperand(OPERAND_IMM);
            imm2->val.imm_value = 1;
            if(place != NULL)
                addAssignInterCode(place, imm2);
            addInterCode(createOperandArray(1, label2), IR_LABEL, ASSIGN_NONE);
        } else if (strcmp(node->children[1]->data.specifier, "LP") == 0) {
            handleExpFuncCall(node, place);
        } else if (strcmp(node->children[1]->data.specifier, "Exp") == 0) {
            handleExp(node->children[1], place);
        } else if (strcmp(node->children[1]->data.specifier, "DOT") == 0) {
            // ? not handle struct
            has_ir_error = true;
            printfErrorInfo("Cannot translate: Code contains variables of struct type.");
        } else {
            // MATH OPERATOR
            Operand *tem1 = getTemVar(true);
            Operand *tem2 = getTemVar(true);
            handleExp(node->children[0], tem1);
            handleExp(node->children[2], tem2);
            if(place != NULL){
                if (strcmp(node->children[1]->data.specifier, "PLUS") == 0) {
                    addInterCode(createOperandArray(3, place, tem1, tem2), IR_ADD, ASSIGN_NONE);
                } else if (strcmp(node->children[1]->data.specifier, "MINUS") == 0) {
                    addInterCode(createOperandArray(3, place, tem1, tem2), IR_SUB, ASSIGN_NONE);
                } else if (strcmp(node->children[1]->data.specifier, "STAR") == 0) {
                    addInterCode(createOperandArray(3, place, tem1, tem2), IR_MUL, ASSIGN_NONE);
                } else if (strcmp(node->children[1]->data.specifier, "DIV") == 0) {
                    addInterCode(createOperandArray(3, place, tem1, tem2), IR_DIV, ASSIGN_NONE);
                }
            }
        }
    } else {
        if (strcmp(node->children[0]->data.specifier, "ID") == 0) {
            return handleExpFuncCall(node, place);
        } else {
            // TODO: handle array Exp -> Exp LB Exp RB
            // only handle i[p][q]..., not handle i.size[j]
            handleExpArray(node, place);
        }
    }
}


// handle for the array var, and compute the size
static void handleExpArray(Node *node, Operand *place) {
    // Exp -> ID
    Operand *size[10];
    int diamond = 0;
    while (node->child_count != 1) {
        Operand *temp_for_size = getTemVar(true);
        handleExp(node->children[2], temp_for_size);
        size[diamond] = temp_for_size;
        diamond++;
        node = node->children[0];
    }
    int index = containsVar(node->children[0]->data.value.string_type);
    assert(index != -1);
    Operand *array = getOPVar(index);
    SemanticType type = TableGet(node->children[0]->data.value.string_type)->type;
    Operand *size_result = getTemVar(true);
    Operand *tem_0 = createOperand(OPERAND_IMM);
    tem_0->val.imm_value = 0;
    addAssignInterCode(size_result, tem_0);
    Operand *tem_size = getTemVar(true);
    for (int i = 0, j = diamond - 1; i < diamond; i++, j--) {
        type = type->val.array->elem;
        Operand *imm = createOperand(OPERAND_IMM);
        imm->val.imm_value = countSize(type);
        addInterCode(createOperandArray(3, tem_size, size[j], imm), IR_MUL, ASSIGN_NONE);
        addInterCode(createOperandArray(3, size_result, size_result, tem_size), IR_ADD, ASSIGN_NONE);
    }
    Operand *tem = getTemVar(true);
    if (array->is_address) {
        tem->is_address = true;
        addInterCode(createOperandArray(3, tem, array, size_result), IR_ADD, ASSIGN_NONE);
    } else {
        tem->is_address = true;
        addInterCode(createOperandArray(3, tem, array, size_result), IR_ADD, GET_ADDR);
    }
    if(place != NULL){
        addAssignInterCode(place, tem);
    }
}

static void handleExpFuncCall(Node *node, Operand *place) {
    SymbolPair function = TableGet(node->children[0]->data.value.string_type);
    // ID LP RP
    if (node->child_count == 3) {
        if (strcmp(function->name, "read") == 0) {
            addInterCode(createOperandArray(1, place), READ, ASSIGN_NONE);
        } else {
            Operand *func = getOPFunc(containsFunc(function->name));
            Operand *tem = getTemVar(true);
            addInterCode(createOperandArray(2, tem, func), CALL, ASSIGN_NONE);
            if (place != NULL) {
                addAssignInterCode(place, tem);
            }
        }
    }
        // ID LP Args RP
    else {
        Args *args = (Args *) malloc(sizeof(Args));
        memset(args, 0, sizeof(Args));
        handleArgs(node->children[2], args, function->type->val.function->next);
        if (strcmp(function->name, "write") == 0) {
            addInterCode(createOperandArray(1, args->next->arg), WRITE, ASSIGN_NONE);
            if (place != NULL) {
                Operand *imm = createOperand(OPERAND_IMM);
                imm->val.imm_value = 0;
                addInterCode(createOperandArray(2, place, imm), IR_ASSIGN, ASSIGN_NONE);
            }
        } else {
            Operand *func = getOPFunc(containsFunc(function->name));
            ArgList params = function->type->val.function->next;
            int param_count = 0;
            while(params != NULL){
                params = params->next;
                param_count++;
            }
            Args *arg = args->next;
            params = function->type->val.function->next;
            int index = 1;
            int need_step;
            while (arg != NULL) {
                need_step = param_count - index;
                for(int i = 0; i < need_step; i++){
                    params = params->next;
                }
                if(params->type->kind == ARRAY
                        && !arg->arg->is_address
                        ){
                    addInterCode(createOperandArray(1, arg->arg), ARG, GET_ADDR);
                }
                else{
                    addInterCode(createOperandArray(1, arg->arg), ARG, ASSIGN_NONE);
                }
                arg = arg->next;
                params = function->type->val.function->next;
                index++;
            }
            Operand *tem = getTemVar(true);
            addInterCode(createOperandArray(2, tem, func), CALL, ASSIGN_NONE);
            if (place != NULL) {
                addAssignInterCode(place, tem);
            }
        }
    }
}


// for change the head of arg list, args.next points to the args, args is the head node
static void handleArgs(Node *node, Args *args, ArgList params) {
    Args *result = (Args *) malloc(sizeof(Args));
    Operand *temVar = getTemVar(true);
    if(params->type->kind == ARRAY){
        temVar->is_address = true;
    }
    handleExp(node->children[0], temVar);
    result->arg = temVar;
    Args *tem_args = args->next;
    result->next = tem_args;
    args->next = result;
    if (node->child_count == 3) {
        handleArgs(node->children[2], args, params->next);
    }

}

// Exp -> condition production
static void handleCond(Node *exp, Operand *label_true, Operand *label_false) {
    if(exp->child_count == 1){
        Operand *tem1 = getTemVar(true);
        handleExp(exp, tem1);
        Operand *imm1 = createOperand(OPERAND_IMM);
        imm1->val.imm_value = 0;
        Operand *op = createOperand(OPERAND_OPERATOR);
        strcpy(op->val.string, "!=");
        addInterCode(createOperandArray(3, tem1, op, imm1), IR_IF, ASSIGN_NONE);
        addInterCode(createOperandArray(1, label_true), GOTO, ASSIGN_NONE);
        addInterCode(createOperandArray(1, label_false), GOTO, ASSIGN_NONE);
    }
    else if (strcmp(exp->children[1]->data.specifier, "RELOP") == 0) {
        Operand *tem1 = getTemVar(true);
        Operand *tem2 = getTemVar(true);
        handleExp(exp->children[0], tem1);
        handleExp(exp->children[2], tem2);
        Operand *op = createOperand(OPERAND_OPERATOR);
        strcpy(op->val.string, exp->children[1]->data.value.string_type);
        addInterCode(createOperandArray(3, tem1, op, tem2), IR_IF, ASSIGN_NONE);
        addInterCode(createOperandArray(1, label_true), GOTO, ASSIGN_NONE);
        addInterCode(createOperandArray(1, label_false), GOTO, ASSIGN_NONE);
    } else if (strcmp(exp->children[1]->data.specifier, "AND") == 0) {
        Operand *label1 = getLabel(true);
        handleCond(exp->children[0], label1, label_false);
        addInterCode(createOperandArray(1, label1), IR_LABEL, ASSIGN_NONE);
        handleCond(exp->children[2], label_true, label_false);
    } else if (strcmp(exp->children[1]->data.specifier, "OR") == 0) {
        Operand *label1 = getLabel(true);
        handleCond(exp->children[0], label_true, label1);
        addInterCode(createOperandArray(1, label1), IR_LABEL, ASSIGN_NONE);
        handleCond(exp->children[2], label_true, label_false);
    } else if (strcmp(exp->children[0]->data.specifier, "NOT") == 0) {
        handleCond(exp->children[1], label_false, label_true);
    } else {
        Operand *tem1 = getTemVar(true);
        handleExp(exp, tem1);
        Operand *imm = createOperand(OPERAND_IMM);
        imm->val.imm_value = 0;
        Operand *op = createOperand(OPERAND_OPERATOR);
        strcpy(op->val.string, "!=");
        addInterCode(createOperandArray(3, tem1, op, imm), IR_IF, ASSIGN_NONE);
        addInterCode(createOperandArray(1, label_true), GOTO, ASSIGN_NONE);
        addInterCode(createOperandArray(1, label_false), GOTO, ASSIGN_NONE);
    }
}

