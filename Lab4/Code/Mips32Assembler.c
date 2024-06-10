#include "Mips32Assembler.h"
#include "ArrayList.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>
#include <assert.h>

int *varOff; // the var offset of the fp
int *temOff; // the tem offset of the fp
int *frameSize; // the frame size needs to be allocated for a func, the index is func in ir_functions
int need_stored; // whether the result needs to be stored
// just use t0 t1 t2 to record the data, and result stored in t0
// -1 -> not need store, else the var offset of the fp
// not used now
int var_count;
static FILE *file;

static void prepareFuncCall();
static void endFuncCall();

static void printPreCodes() {
    assert(file != NULL);
    fprintf(file, ".data\n_prompt: .asciiz \"Enter an integer:\"\n");
    fprintf(file, "_ret: .asciiz \"\\n\"\n.globl main\n.text\n");

    fprintf(file, "read:\n");
    fprintf(file, " li $v0, 4\n");
    fprintf(file, " la $a0, _prompt\n");
    fprintf(file, " syscall\n");
    fprintf(file, " li $v0, 5\n");
    fprintf(file, " syscall\n");
    fprintf(file, " jr $ra\n\n");

    fprintf(file, "write:\n");
    fprintf(file, " li $v0, 1\n");
    fprintf(file, " syscall\n");
    fprintf(file, " li $v0, 4\n");
    fprintf(file, " la $a0, _ret\n");
    fprintf(file, " syscall\n");
    fprintf(file, " move $v0, $0\n");
    fprintf(file, " jr $ra\n");
}

static int getOffset(int no, bool is_var) {
    if (!is_var) {
        return temOff[no];
    } else {
        return varOff[no];
    }
}

static void setOffset(int no, bool is_var, int offset) {
    if (is_var) {
        varOff[no] = offset;
    } else {
        temOff[no] = offset;
    }
}

static void calculateOffset(Operand *operand, int *curr) {
    if (operand->kind == OPERAND_VARIABLE) {
        int varIndex = containsVar(operand->val.string);
        assert(varIndex != -1);
        if (getOffset(varIndex, true) == -1) {
            setOffset(varIndex, true, -(*curr));
            *curr = *curr + 4;
        }
    }
    if (operand->kind == OPERAND_TEMP) {
        if (getOffset(operand->val.temp_no, false) == -1) {
            setOffset(operand->val.temp_no, false, -(*curr));
            *curr = *curr + 4;
        }
    }
}

// only use t1/t2 to load operands, the offset is the var away from fp
static void loadOperands(int reg, Operand* operand){
    assert(reg == 1 || reg == 2 || reg == 0);
    switch (operand->kind) {
        case OPERAND_VARIABLE: {
            fprintf(file, " lw $t%d, %d($fp)\n", reg,
                    getOffset(containsVar(operand->val.string), true));
            break;
        }
        case OPERAND_TEMP: {
            fprintf(file, " lw $t%d, %d($fp)\n", reg,
                    getOffset(operand->val.temp_no, false));
            break;
        }
        case OPERAND_IMM: {
            fprintf(file, " li $t%d, %d\n", reg, operand->val.imm_value);
            break;
        }
        default:{
            printf("error type of operand!\n");
            exit(-1);
        }
    }
}

static void storeOperands(int reg, Operand* operand){
    assert(reg == 1 || reg == 2 || reg == 0);
    switch (operand->kind) {
        case OPERAND_VARIABLE: {
            fprintf(file, " sw $t%d, %d($fp)\n", reg,
                    getOffset(containsVar(operand->val.string), true));
            break;
        }
        case OPERAND_TEMP: {
            fprintf(file, " sw $t%d, %d($fp)\n", reg,
                    getOffset(operand->val.temp_no, false));
            break;
        }
        default:{
            printf("error type of operand!\n");
            exit(-1);
        }
    }
}

// this function will be called when we into a new func
// only handle variables in this func
// the param is the index of the beginning of the func(the first ir after Func main:)
// return the size of all the variables
static int initVariableIntraProcedure(int irIndex) {
    int result = 4;
    InterCode *irCode = (InterCode *) ArrayListGet(interCodes, irIndex);
    int irSize = ArrayListSize(interCodes);
    while (irCode->operation != IR_FUNC) {
        switch (irCode->operation) {
            // judge three operands
            case IR_ASSIGN:{
                calculateOffset(irCode->operands[0], &result);
                calculateOffset(irCode->operands[1], &result);
                break;
            }
            case IR_DIV:
            case IR_MUL:
            case IR_SUB:
            case IR_ADD: {
                calculateOffset(irCode->operands[0], &result);
                calculateOffset(irCode->operands[1], &result);
                calculateOffset(irCode->operands[2], &result);
                break;
            }
                // judge two operands
            case IR_IF: {
                calculateOffset(irCode->operands[0], &result);
                calculateOffset(irCode->operands[2], &result);
                break;
                break;
            }
                // judge one operand
            case DEC: {
                // needs to handle size
                Operand *operand = irCode->operands[0];
                result += irCode->operands[1]->val.imm_value - 4;// add the DEC size
                calculateOffset(operand, &result);
                break;
            }
            case ARG:
            case PARAM:
            case CALL:
            case IR_RETURN:
            case READ:
            case WRITE: {
                Operand *operand = irCode->operands[0];
                calculateOffset(operand, &result);
                break;
            }
            // CALL and GOTO and LABEL not need to handle
            default:
                break;
        }
        irIndex++;
        if(irIndex == irSize){
            break;
        }
        irCode = (InterCode *) ArrayListGet(interCodes, irIndex);
    }
    return result - 4;
}


static void prepareFuncCall(){
    fprintf(file, " addi $sp, $sp, -8\n");
    fprintf(file, " sw $ra, 0($sp)\n");
    fprintf(file, " sw $fp, 4($sp)\n");
    fprintf(file, " move $fp, $sp\n");
}

static void endFuncCall(){
    fprintf(file, " move $sp, $fp\n");
    fprintf(file, " lw $fp, 4($sp)\n");
    fprintf(file, " lw $ra, 0($sp)\n");
    fprintf(file, " addi $sp, $sp, 8\n");
}

static void allocateSP(int size){
    fprintf(file, " addi $sp, $sp, -%d\n", size);
}

static void freeSP(int size){
    fprintf(file, " addi $sp, $sp, %d\n", size);
}

void translateIR2Mips(char *filename) {
    file = fopen(filename, "w");
    if (file == NULL) {
        printf("error in open file\n");
        exit(-1);
    }
    printPreCodes(file); // the fixed part of the assembler code
    int irSize = ArrayListSize(interCodes);
    InterCode *interCode;
    for(int irIndex = 0; irIndex < irSize; irIndex++){
        interCode = ArrayListGet(interCodes, irIndex);
        switch (interCode->operation) {
            case IR_LABEL:{
                fprintf(file, "label%d:\n", interCode->operands[0]->val.label_no);
                break;
            }
            case IR_FUNC:{
                if(strcmp(interCode->operands[0]->val.string, "main") == 0){
                    fprintf(file, "\nmain:\n");
                }
                else{
                   fprintf(file, "\nfunc%d:\n", containsFunc(interCode->operands[0]->val.string));
                }
                int var_size = initVariableIntraProcedure(irIndex + 1);
                prepareFuncCall();
                allocateSP(var_size);
                break;
            }
            case IR_ASSIGN:{
                if(interCode->operands[1]->kind == OPERAND_IMM){
                    fprintf(file, " li $t0, %d\n", interCode->operands[1]->val.imm_value);
                    storeOperands(0, interCode->operands[0]);
                }
                else{
                    switch (interCode->type) {
                        case GET_ADDR:{ // record the offset away from fp
                            Operand * operand = interCode->operands[1];
                            assert(operand->kind == OPERAND_TEMP || operand->kind == OPERAND_VARIABLE);
                            int offset;
                            if(operand->kind == OPERAND_TEMP){
                                offset = getOffset(operand->val.temp_no, false);
                            } else{
                                offset = getOffset(containsVar(operand->val.string), true);
                            }
                            fprintf(file, " li $t1, %d\n", offset);
                            fprintf(file, " add $t0, $t1, $fp\n");
                            storeOperands(0, interCode->operands[0]);
                            break;
                        }
                        case GET_VAL:{
                            loadOperands(1, interCode->operands[1]);
                            fprintf(file, " lw $t0, 0($t1)\n");
                            storeOperands(0, interCode->operands[0]);\
                            break;
                        }
                        case SET_VAL:{
                            loadOperands(1, interCode->operands[1]);
                            loadOperands(0, interCode->operands[0]);
                            fprintf(file, " sw $t1, 0($t0)\n");
                            break;
                        }
                        case BOTH_POINTER:{
                            loadOperands(1, interCode->operands[1]);
                            loadOperands(0, interCode->operands[0]);
                            fprintf(file, " lw $t2, 0($t1)\n");
                            fprintf(file, " sw $t2, 0($t0)\n");
                            break;
                        }
                        default:{
                            loadOperands(1, interCode->operands[1]);
                            storeOperands(1, interCode->operands[0]);
                            break;
                        }
                    }
                }
                break;
            }
            case IR_DIV:{
                loadOperands(1, interCode->operands[1]);
                loadOperands(2, interCode->operands[2]);
                fprintf(file, " div $t1, $t2\n");
                fprintf(file, " mflo $t0\n");
                storeOperands(0, interCode->operands[0]);
                break;
            }
            case IR_MUL:{
                loadOperands(1, interCode->operands[1]);
                loadOperands(2, interCode->operands[2]);
                fprintf(file, " mul $t0, $t1, $t2\n");
                storeOperands(0, interCode->operands[0]);
                break;
            }
            case IR_SUB:{
                if(interCode->operands[2]->kind == OPERAND_IMM){
                    loadOperands(1, interCode->operands[1]);
                    fprintf(file, " addi $t0, $t1, -%d\n", interCode->operands[2]->val.imm_value);
                    storeOperands(0, interCode->operands[0]);
                }
                else{
                    loadOperands(1, interCode->operands[1]);
                    loadOperands(2, interCode->operands[2]);
                    fprintf(file, " sub $t0, $t1, $t2\n");
                    storeOperands(0, interCode->operands[0]);
                }
                break;
            }
            case IR_ADD:{
                switch (interCode->type) {
                    case GET_ADDR:{
                        if(interCode->operands[2]->kind == OPERAND_IMM){
                            loadOperands(1, interCode->operands[1]);
                            fprintf(file, " lw $t2, 0($t1)\n");
                            fprintf(file, " addi $t0, $t2, %d\n", interCode->operands[2]->val.imm_value);
                            storeOperands(0, interCode->operands[0]);
                        }
                        else{
                            loadOperands(1, interCode->operands[1]);
                            fprintf(file, " lw $t2, 0($t1)\n");
                            loadOperands(1, interCode->operands[2]);
                            fprintf(file, " add $t0, $t2, $t1\n");
                            storeOperands(0, interCode->operands[0]);
                        }
                        break;
                    }
                    default: {
                        if(interCode->operands[2]->kind == OPERAND_IMM){
                            loadOperands(1, interCode->operands[1]);
                            fprintf(file, " addi $t0, $t1, %d\n", interCode->operands[2]->val.imm_value);
                            storeOperands(0, interCode->operands[0]);
                        }
                        else{
                            loadOperands(1, interCode->operands[1]);
                            loadOperands(2, interCode->operands[2]);
                            fprintf(file, " add $t0, $t1, $t2\n");
                            storeOperands(0, interCode->operands[0]);
                        }
                        break;
                    }
                }
                break;
            }
            case GOTO:{
                fprintf(file, " j label%d\n", interCode->operands[0]->val.label_no);
                break;
            }
            case IR_IF:{
                loadOperands(1, interCode->operands[0]);
                loadOperands(2, interCode->operands[2]);
                char* op = interCode->operands[1]->val.string;
                irIndex++;
                InterCode * IF_GOTO = ArrayListGet(interCodes, irIndex);
                assert(IF_GOTO->operands[0]->kind == OPERAND_LABEL);
                if(strcmp(op, "==") == 0){
                    fprintf(file, " beq $t1, $t2, label%d\n", IF_GOTO->operands[0]->val.label_no);
                } else if(strcmp(op, "!=") == 0){
                    fprintf(file, " bne $t1, $t2, label%d\n", IF_GOTO->operands[0]->val.label_no);
                } else if(strcmp(op, ">") == 0){
                    fprintf(file, " bgt $t1, $t2, label%d\n", IF_GOTO->operands[0]->val.label_no);
                } else if(strcmp(op, "<") == 0){
                    fprintf(file, " blt $t1, $t2, label%d\n", IF_GOTO->operands[0]->val.label_no);
                } else if(strcmp(op, ">=") == 0){
                    fprintf(file, " bge $t1, $t2, label%d\n", IF_GOTO->operands[0]->val.label_no);
                } else{ // <=
                    fprintf(file, " ble $t1, $t2, label%d\n", IF_GOTO->operands[0]->val.label_no);
                }
                break;
            }
            case IR_RETURN:{
                loadOperands(1, interCode->operands[0]);
                fprintf(file, " move $v0, $t1\n");
                endFuncCall();
                fprintf(file, " jr $ra\n");
                break;
            }
            case DEC:{
                break;
            }
            // if current ir is an ARG, then handles all args
            case ARG:{
                while (interCode->operation == ARG){
                    allocateSP(4); // allocate arg space
                    loadOperands(1, interCode->operands[0]);
                    fprintf(file, " sw $t1, 0($sp)\n");
                    irIndex++;
                    interCode = ArrayListGet(interCodes, irIndex);
                }
                irIndex--; // back to the last ARG
                break;
            }
            case CALL:{
                if(strcmp(interCode->operands[1]->val.string, "main") == 0){
                    fprintf(file, " jal main\n");
                }
                else{
                    fprintf(file, " jal func%d\n", containsFunc(interCode->operands[1]->val.string));
                }
                fprintf(file, " move $t1, $v0\n");
                storeOperands(1, interCode->operands[0]);
                break;
            }
            // if current ir is an PARAM, then handles all params
            case PARAM:{
                int offset = 8; // for the last fp and ret address
                while (interCode->operation == PARAM){
                    fprintf(file, " lw $t0, %d($fp)\n", offset);
                    storeOperands(0, interCode->operands[0]);
                    offset += 4;
                    irIndex++;
                    interCode = ArrayListGet(interCodes, irIndex);
                }
                irIndex--; // back to the last PARAM
                break;
            }
            case READ:{
                fprintf(file, " jal read\n");
                fprintf(file, " move $t1, $v0\n");
                storeOperands(1, interCode->operands[0]);
                break;
            }
            case WRITE:{
                loadOperands(1, interCode->operands[0]);
                fprintf(file, " move $a0, $t1\n");
                fprintf(file, " jal write\n");
                break;
            }
            default:{
                printf("error of ir type in line %d\n", irIndex);
                exit(-1);
            }
        }
    }
    fclose(file);
}

void initAssembler() {
    var_count = ArrayListSize(ir_variables);
    varOff = (int *) malloc(sizeof(int) * (var_count));
    temOff = (int *) malloc(sizeof(int) * (tem_count));
    memset(varOff, -1, sizeof(int) * (var_count));
    memset(temOff, -1, sizeof(int) * (tem_count));
    need_stored = -1;
}