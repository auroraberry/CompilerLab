#ifndef __SEMANTIC__
#define __SEMANTIC__

#include "SymbolTable.h"
#include "SyntaxTree.h"
#include <stdbool.h>

// the node name is contained in node.data.value.string/int/float
// node data also contains lineno

// node is ID
bool variableUsageBeforeDefinition(Node* node);

// ID LP ArgList/empty RP
// node is ID
bool functionUsageBeforeDefinition(Node* node);

// variable and function can not be the same name
// node is ID
bool variableDoubleDefinition(Node* node);

//FunDec → ID LP VarList RP | ID LP RP
//node is ID
bool functionDoubleDefinition(Node* node);

// exp = exp
// node is left and right
bool typesNotMatchInAssignOP(Node* left, Node* right);

// exp should record if it can be left value
bool rightValInLeftOfAssignOP(Node* node);

// if op is not/minus, then left should be NULL
bool OperandNotMatchOP(Node* left, Node* op, Node* right);

// Stmt → RETURN Exp SEMI
// node is exp
bool returnTypeNotMatchDefinition(Node* node, SemanticType return_type);

// Exp → ID LP Args RP
// the node is the function ID, and args is handled by handleArgs
bool argListNotMatchDefinition(Node* node, ArgList args);

// [...] for non-array variable
// Exp → Exp LB Exp RB
// node is exp before LB 
bool nonArrayVariableUsingArrayAccess(Node* node);

// Exp → ID LP Args RP | ID LP RP
// () for non-function varible
// node is ID
bool nonFuncVariableUsingFuncCall(Node* node);

// Exp → Exp LB Exp RB
// node is exp after LB
bool nonIntInArrayAccess(Node* node);

// exp.ID
// node is exp
bool nonStructVariableUsingDot(Node* node);
// node is ID
bool usingNonDefinitionFiled(Node* exp, Node* id);

// the inner ID of struct field definition
// each definition of struct field should call this method
bool doubleDefinitionOfStructField(Node* node);

// the node is dec
// handle dec should record where it is called
bool initializeFiledWhileDefinition(Node* node);

// StructSpecifier → STRUCT OptTag LC DefList RC
// OptTag → ID
// the node is ID
bool structDoubleDefinition(Node* node);

// StructSpecifier → STRUCT OptTag LC DefList RC | STRUCT Tag
// Tag → ID
// the node is ID
// just judge the second production
bool variableDefinitionUsingUndefinedStruct(Node* node);



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