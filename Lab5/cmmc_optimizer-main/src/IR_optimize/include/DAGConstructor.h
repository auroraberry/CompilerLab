//
// Created by aurora on 24-6-12.
//

#ifndef LAB5_DAGCONSTRUCTOR_H
#define LAB5_DAGCONSTRUCTOR_H

#include "IR.h"

typedef enum NODE_TYPE {TOP, BOTTOM, OTHER} NODE_TYPE;
typedef enum DAG_NODE_OP {DAG_OP_ADD, DAG_OP_SUB, DAG_OP_MUL, DAG_OP_DIV, DAG_OP_NONE
    } DAG_NODE_OP;

struct DAG_NODE {
    bool isConst;
    int constVal;
    NODE_TYPE nodeType;
    DAG_NODE_OP nodeOp;
    IR_var vars[10]; // points to the var it represents
    int varCount;
    struct DAG_NODE *left, *right;
};

typedef struct DAG_NODE DAG_NODE;

typedef struct DAG_NODE* DAG_NODE_PTR;

DEF_MAP(IR_var, DAG_NODE_PTR)

DEF_MAP(int, DAG_NODE_PTR)

DEF_VECTOR(DAG_NODE_PTR);

typedef struct {
    DAG_NODE *root;
    Map_IR_var_DAG_NODE_PTR irVar2DagNodePtr; // record all ir var to DAG NODE
    Map_int_DAG_NODE_PTR imm2DagNodePtr;
    Vec_DAG_NODE_PTR allNodes;
} DAG;




extern IR_program *new_ir_program_global;

void initDAG(DAG* dag);

void partialOptimize(IR_function_ptr functionPtr);

void translateDAG2IRStmt(DAG* dag, IR_function* function);

#endif //LAB5_DAGCONSTRUCTOR_H
