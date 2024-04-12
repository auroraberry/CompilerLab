#ifndef __SEMANTIC__
#define __SEMANTIC__

#include "SymbolTable.h"
#include "SyntaxTree.h"
#include <stdbool.h>

// the node name is contained in node.data.value.string/int/float
// node data also contains lineno

// node is ID
void variableUsageBeforeDefinition(Node* node);

// ID LP ArgList/empty RP
// node is ID
void functionUsageBeforeDefinition(Node* node);

// variable and function can not be the same name
// node is ID
void variableDoubleDefinition(Node* node);

//FunDec → ID LP VarList RP | ID LP RP
//node is ID
void functionDoubleDefinition(Node* node);

// exp = exp
// node is left and right
void typesNotMatchInAssignOP(Node* left, Node* right);

// exp should record if it can be left value
void rightValInLeftOfAssignOP(Node* node);

// if op is not/minus, then left should be NULL
void OperandNotMatchOP(Node* left, Node* op, Node* right);

// Stmt → RETURN Exp SEMI
// node is exp
void returnTypeNotMatchDefinition(Node* node, SemanticType return_type);

// Exp → ID LP Args RP
// the node is the function ID, and args is handled by handleArgs
void argListNotMatchDefinition(Node* node, ArgList args);

// [...] for non-array variable
// Exp → Exp LB Exp RB
// node is exp before LB 
void nonArrayVariableUsingArrayAccess(Node* node);

// Exp → ID LP Args RP | ID LP RP
// () for non-function varible
// node is ID
void nonFuncVariableUsingFuncCall(Node* node);

// Exp → Exp LB Exp RB
// node is exp after LB
void nonIntInArrayAccess(Node* node);

// exp.ID
// node is exp
void nonStructVariableUsingDot(Node* node);
// node is ID
void usingNonDefinitionFiled(Node* exp, Node* id);

// the inner ID of struct field definition
// each definition of struct field should call this method
void doubleDefinitionOfStructField(Node* node);

// the node is dec
// handle dec should record where it is called
void initializeFiledWhileDefinition(Node* node);

// StructSpecifier → STRUCT OptTag LC DefList RC
// OptTag → ID
// the node is ID
void structDoubleDefinition(Node* node);

// StructSpecifier → STRUCT OptTag LC DefList RC | STRUCT Tag
// Tag → ID
// the node is ID
// just judge the second production
void variableDefinitionUsingUndefinedStruct(Node* node);



// handle program
void handleProgram(Node* node);
void handleExtDefList(Node* node);
void handleExtDef(Node* node); // definition -> record in symbol table
void handleExtDecList(Node* node);


// handle specifier
SemanticType handleSpecifier(Node* node);
SemanticType handleStructSpecifier(Node* node);
char* handleOptTag(Node* node);
char* handleTag(Node* node);


// handle declaration
SymbolPair handleVarDec(Node* node);
SymbolPair handleFunDec(Node* node);
ArgList handleVarList(Node* node);
ArgList handleParamDec(Node* node);


// handle statements
void handleCompSt(Node* node);
void handleStmtList(Node* node);
void handleStmt(Node* node);


// handle local definition
void handleDefList(Node* node);
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
SemanticType handleExpID(Node* node);
SemanticType handleExpINT(Node* node);
SemanticType handleExpFLOAT(Node* node);







#endif