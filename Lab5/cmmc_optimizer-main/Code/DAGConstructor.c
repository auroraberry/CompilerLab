//
// Created by aurora on 24-6-12.
//
#include "DAGConstructor.h"

IR_program *new_ir_program_global;


static DAG_NODE_PTR createDAGNODE(bool is_const, NODE_TYPE type, DAG_NODE_PTR left, DAG_NODE_PTR right){
    DAG_NODE_PTR nodePtr = (DAG_NODE_PTR) malloc(sizeof(DAG_NODE));
    nodePtr->nodeType = type;
    nodePtr->isConst = is_const;
    nodePtr->left = left;
    nodePtr->right = right;
    nodePtr->varCount = 0;
    return nodePtr;
}

void initDAG(DAG* dag){
    dag->root = NULL;
    Map_IR_var_DAG_NODE_PTR_init(&dag->irVar2DagNodePtr);
    Vec_DAG_NODE_PTR_init(&dag->allNodes);
    Map_int_DAG_NODE_PTR_init(&dag->imm2DagNodePtr);
    IR_program_init(new_ir_program_global);
}

void removeDeadCode(DAG* dag){

}

static bool equalDAGNode(DAG_NODE* this, DAG_NODE* other){
    if(this == NULL && other == NULL){
        return true;
    }
    else if(this == NULL || other == NULL){
        return false;
    }
    if(this->nodeOp != other->nodeOp){
        return false;
    }
    for(int i = 0; i < this->varCount; i++){
        for(int j = 0; j < other->varCount; j++){
            if(this->vars[i] == other->vars[j]){
                return true;
            }
        }
    }
    return false;
}

void partialOptimize(IR_function_ptr functionPtr){
    IR_function *new_function = NEW(IR_function, functionPtr->func_name);
    // can not remove DEC
    for_map(IR_var, IR_Dec, it, functionPtr->map_dec){
        VCALL(new_function->map_dec, insert, it->key, it->val);
    }
    // record the params
    for_vec(IR_var, item, functionPtr->params){
        VCALL(new_function->params, push_back, *item);
    }

    for_list(IR_block_ptr, block, functionPtr->blocks){
        // record the label
        if(block->val->label != IR_LABEL_NONE){
            IR_function_push_label(new_function, block->val->label);
        }
        // construct DAG
        int init = false;
        DAG* dag;
        for_list(IR_stmt_ptr, stmt, block->val->stmts){
            if(!init){
               dag = (DAG*)malloc(sizeof(DAG));
               initDAG(dag);
               init = true;
            }
            switch (stmt->val->stmt_type) {
                case IR_OP_STMT:{
                    IR_op_stmt * opStmt = (IR_op_stmt*)stmt->val;
                    DAG_NODE_OP opType;
                    switch (opStmt->op) {
                        case IR_OP_ADD:{
                            opType = DAG_OP_ADD;
                            break;
                        }
                        case IR_OP_DIV:{
                            opType = DAG_OP_DIV;
                            break;
                        }
                        case IR_OP_MUL:{
                            opType = DAG_OP_MUL;
                            break;
                        }
                        case IR_OP_SUB:{
                            opType = DAG_OP_SUB;
                            break;
                        }
                    }
                    bool added = false;
                    // find available expression
                    for_vec(DAG_NODE_PTR, item, dag->allNodes){
                        DAG_NODE_PTR nodePtr = *item;
                        if(nodePtr->nodeOp == opType){

                        }
                    }
                    break;
                }
                case IR_ASSIGN_STMT:{
                    IR_assign_stmt* assignStmt = (IR_assign_stmt*)stmt->val;
                    DAG_NODE_PTR rsNodePtr = NULL;
                    if(assignStmt->rs.is_const){
                        if(VCALL(dag->imm2DagNodePtr, exist, assignStmt->rs.const_val)){
                            rsNodePtr = VCALL(dag->imm2DagNodePtr, get, assignStmt->rs.const_val);
                        }
                        else{
                            rsNodePtr = createDAGNODE(true, DAG_OP_NONE, NULL, NULL);
                            rsNodePtr->nodeType = BOTTOM;
                            rsNodePtr->constVal = assignStmt->rs.const_val;
                            VCALL(dag->imm2DagNodePtr, insert, assignStmt->rs.const_val, rsNodePtr);
                            VCALL(dag->allNodes, push_back, rsNodePtr);
                        }
                    }
                    else{
                        if(VCALL(dag->irVar2DagNodePtr, exist, assignStmt->rs.var)){
                            rsNodePtr = VCALL(dag->irVar2DagNodePtr, get, assignStmt->rs.var);
                        }
                        else{
                            rsNodePtr = createDAGNODE(false, DAG_OP_NONE, NULL, NULL);
                            rsNodePtr->vars[rsNodePtr->varCount] = assignStmt->rs.var;
                            rsNodePtr->varCount++;
                            VCALL(dag->allNodes, push_back, rsNodePtr);
                            VCALL(dag->irVar2DagNodePtr, insert, assignStmt->rs.var, rsNodePtr);
                        }
                        rsNodePtr->nodeType = OTHER;
                    }
                    // the var exists in DAG
                    DAG_NODE_PTR rdNodePtr;
                    if(VCALL(dag->irVar2DagNodePtr, exist, assignStmt->rd)){
                        rdNodePtr = VCALL(dag->irVar2DagNodePtr, get, assignStmt->rd);
                        for(int i = 0; i < rdNodePtr->varCount; i++){
                            if(rdNodePtr->vars[i] == assignStmt->rd){
                                for(int j = i+1; j < rdNodePtr->varCount; j++){
                                    rdNodePtr->vars[j-1] = rdNodePtr->vars[j];
                                }
                                break;
                            }
                        }
                        rdNodePtr->varCount--;
                        VCALL(dag->irVar2DagNodePtr, delete, assignStmt->rd);
                    }
                    rdNodePtr = createDAGNODE(false, DAG_OP_NONE, NULL, NULL);
                    rdNodePtr->vars[rdNodePtr->varCount] = assignStmt->rd;
                    rdNodePtr->varCount++;
                    rdNodePtr->nodeType = TOP;
                    rdNodePtr->left = rsNodePtr;
                    if(rsNodePtr->nodeType == BOTTOM){
                        rdNodePtr->nodeType = BOTTOM;
                        rdNodePtr->constVal = rsNodePtr->constVal;
                    }
                    VCALL(dag->allNodes, push_back, rdNodePtr);
                    VCALL(dag->irVar2DagNodePtr, insert, assignStmt->rd, rdNodePtr);
                    break;
                }
                default:{
                    IR_stmt *new_stmt = NULL;
                    switch (stmt->val->stmt_type){
                        case IR_LOAD_STMT:{
                            new_stmt = (IR_stmt*)NEW(IR_load_stmt, ((IR_load_stmt*)stmt->val)->rd,
                                                     ((IR_load_stmt*)stmt->val)->rs_addr);
                            break;
                        }
                        case IR_STORE_STMT:{
                            new_stmt = (IR_stmt*)NEW(IR_store_stmt, ((IR_store_stmt*)stmt->val)->rd_addr,
                                                     ((IR_store_stmt*)stmt->val)->rs);
                            break;
                        }
                        case IR_IF_STMT:{
                            new_stmt = (IR_stmt*)NEW(IR_if_stmt, ((IR_if_stmt*)stmt->val)->relop,
                                                     ((IR_if_stmt*)stmt->val)->rs1, ((IR_if_stmt*)stmt->val)->rs2,
                                                     ((IR_if_stmt*)stmt->val)->true_label, ((IR_if_stmt*)stmt->val)->false_label);
                            break;
                        }
                        case IR_GOTO_STMT:{
                            new_stmt = (IR_stmt*)NEW(IR_goto_stmt, ((IR_goto_stmt*)stmt->val)->label);
                            break;
                        }
                        case IR_CALL_STMT:{
                            new_stmt = (IR_stmt*)NEW(IR_call_stmt, ((IR_call_stmt*)stmt->val)->rd,
                                                     ((IR_call_stmt*)stmt->val)->func_name,
                                                     ((IR_call_stmt*)stmt->val)->argc,
                                                     ((IR_call_stmt*)stmt->val)->argv);
                            break;
                        }
                        case IR_RETURN_STMT:{
                            new_stmt = (IR_stmt*)NEW(IR_return_stmt, ((IR_return_stmt*)stmt->val)->rs);
                            break;
                        }
                        case IR_READ_STMT:{
                            new_stmt = (IR_stmt*)NEW(IR_read_stmt, ((IR_read_stmt*)stmt->val)->rd);
                            break;
                        }
                        case IR_WRITE_STMT:{
                            new_stmt = (IR_stmt*)NEW(IR_write_stmt, ((IR_write_stmt*)stmt->val)->rs);
                            break;
                        }
                        default:
                            break;
                    }
                    init = false;
                    removeDeadCode(dag);
                    translateDAG2IRStmt(dag, new_function);
                    free(dag);
                    dag = NULL;
                    IR_function_push_stmt(new_function, new_stmt);
                }
            }
        }
    }
    IR_function_closure(new_function);
    VCALL(new_ir_program_global->functions, push_back, new_function);
}


void translateDAG2IRStmt(DAG* dag, IR_function* function){

}

