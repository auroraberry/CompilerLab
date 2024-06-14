//
// Created by hby on 22-12-2.
//

#include <IR_optimize.h>
#include <live_variable_analysis.h>
#include <constant_propagation.h>
#include <available_expressions_analysis.h>
#include <copy_propagation.h>
#include <DAGConstructor.h>

void remove_dead_block(IR_function *func) {
    // remove
    for(ListNode_IR_block_ptr *i = func->blocks.head; i;) {
        IR_block *blk = i->val;
        if(blk->dead) { // remove dead block
            RDELETE(IR_block, blk); // IR_block_teardown(blk); free(blk);
            i = VCALL(func->blocks, delete, i);
        } else i = i->nxt;
    }
}

void remove_dead_stmt(IR_block *blk) {
    for(ListNode_IR_stmt_ptr *j = blk->stmts.head; j;) {
        IR_stmt *stmt = j->val;
        if(stmt->dead) { // remove dead stmt
            RDELETE(IR_stmt, stmt); // IR_stmt_teardown(stmt); free(stmt);
            j = VCALL(blk->stmts, delete, j);
            continue;
        } else j = j->nxt;
    }
}


void IR_optimize() {
    ConstantPropagation *constantPropagation;
    AvailableExpressionsAnalysis *availableExpressionsAnalysis;
    CopyPropagation *copyPropagation;
    LiveVariableAnalysis *liveVariableAnalysis;
    for_vec(IR_function_ptr, i, ir_program_global->functions) {
        IR_function *func = *i;

        //// 局部优化
        //partialOptimize(func);

    }
}
