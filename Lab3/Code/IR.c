#include "IR.h"

#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include <stdbool.h>
#include <assert.h>

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
    interCodes = ArrayListCreate(sizeof(InterCode *), 100);
    temVars = ArrayListCreate(4, 50);
    labels = ArrayListCreate(4, 50);
    op_functions = ArrayListCreate(4, 50);
    op_variables = ArrayListCreate(4, 50);
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


char *handleOperand(Operand *operand) {
    char *result = (char *) malloc(30);
    switch (operand->kind) {
        case OPERAND_VARIABLE:
            sprintf(result, "var%d", containsVar(operand->val.string));
            break;
        case OPERAND_FUNC:
            sprintf(result, "func%d", containsFunc(operand->val.string));
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
            printf("RETURN %s\n", handleOperand(interCode->operands));
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
        case CALL:
            printf("%s := CALL %s\n", handleOperand(interCode->operands), handleOperand(interCode->operands->next));
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


void addOPVar(Operand* var, int pos){
    ArrayListInsert(op_variables, pos, var);
}

void addOPFunc(Operand* func, int pos){
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

Operand *getOPVar(int index){
    return (Operand *) ArrayListGet(op_variables, index);
}

Operand *getOPFunc(int index){
    return (Operand *) ArrayListGet(op_functions, index);
}

Operand *getLatestTemVar() {
    return (Operand *) ArrayListGet(temVars, tem_count - 1);
}

Operand *getLatestLabel() {
    return (Operand *) ArrayListGet(labels, label_count - 1);
}

void addInterCode(Operand *operands, enum IR_OPERATION kind, enum ASSIGN_TYPE type ){
    InterCode *interCode = (InterCode*) malloc(sizeof(InterCode));
    interCode->operands = operands;
    interCode->operation = kind;
    interCode->type = type;
    ArrayListInsert(interCodes, ArrayListSize(interCodes), interCode);
}



Operand *getTemVar(bool is_new) {
    if (is_new) {
        Operand *result = createOperand(OPERAND_TEMP);
        result->val.temp_no = addTemVar(result);
        return result;
    } else {
        return getLatestTemVar();
    }
}

Operand *getLabel(bool is_new) {
    if (is_new) {
        Operand *result = createOperand(OPERAND_LABEL);
        result->val.label_no = addLabel(result);
        return result;
    } else {
        return getLatestLabel();
    }
}