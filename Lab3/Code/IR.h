#ifndef __IR__
#define __IR__

#include "ArrayList.h"
#include "SyntaxTree.h"

typedef struct Operand Operand;
typedef struct InterCode InterCode;
typedef struct Args Args;

// record the index of var/func
extern ArrayList *ir_variables;
extern ArrayList *ir_functions;
// record the operand of var/func
extern ArrayList *op_variables;
extern ArrayList *op_functions;
//record the operand of label/temVar
extern ArrayList *labels;
extern ArrayList *temVars;

extern ArrayList *interCodes;

extern int tem_count;
extern int label_count;


enum IR_OPERATION {
    IR_LABEL, IR_FUNC, IR_ASSIGN, IR_ADD, IR_SUB, IR_MUL, IR_DIV, GOTO, IR_IF, IR_RETURN, DEC, ARG, CALL, PARAM, READ, WRITE
};

enum ASSIGN_TYPE {
    GET_ADDR, GET_VAL, SET_VAL, BOTH_POINTER, ASSIGN_NONE
};

enum OPERAND_KIND {
    OPERAND_VARIABLE, OPERAND_TEMP, OPERAND_IMM, OPERAND_FUNC, OPERAND_LABEL, OPERAND_OPERATOR, OPERAND_SIZE
};


struct InterCode {
    enum IR_OPERATION operation;
    enum ASSIGN_TYPE type;
    Operand *operands[4];
};


struct Operand {
    enum OPERAND_KIND kind;
    bool is_address;
    union {
        char *string; // variable name, function name, then can get definition by serching in tables
        // or the type of operator
        int temp_no;
        int label_no;
        int imm_value;
    } val;
};

struct Args {
    Operand* arg;
    Args* next;
};

void initIR();

int containsVar(char *name);
int containsFunc(char *name);

// return the index where it inserts
int addVar(char *name);
int addFunc(char *name);
void addOPVar(Operand* var, int pos);
void addOPFunc(Operand* func, int pos);
int addTemVar(Operand *tem);
int addLabel(Operand *label);

Operand *getOPVar(int index);
Operand *getOPFunc(int index);
Operand *getLatestTemVar();
Operand *getLatestLabel();
Operand* getTemVar(bool is_new);
Operand* getLabel(bool is_new);

void addInterCode(Operand **operands, enum IR_OPERATION kind, enum ASSIGN_TYPE type);

void printInterCodes();

Operand *createOperand(enum OPERAND_KIND kind);

void generateIR(Node* root, char* name);

int countSize(SemanticType type);


#endif


