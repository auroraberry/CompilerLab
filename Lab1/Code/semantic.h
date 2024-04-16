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
bool OperandNotMatchOP(Node* left, Node* right, Node* op);

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
bool doubleDefinitionOfStructField(Node* node, FieldList fields);

// the node is dec
// handle dec should record where it is called
bool initializeFiledWhileDefinition(Node* node);

// StructSpecifier → STRUCT OptTag LC DefList RC
// OptTag → ID
// the node is ID
bool structDoubleDefinition(char* name, int lineno);

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
// return pair.name is NULL, if it meet error
void handleVarDec(Node* node);
void handleVarDecInStruct(Node* node, FieldList fields);
SemanticType handleFunDec(Node* node);
ArgList handleVarList(Node* node);
ArgList handleParamDec(Node* node);


// handle statements
void handleCompSt(Node* node);
void handleStmtList(Node* node);
void handleStmt(Node* node);


// handle local definition
void handleDefListInStruct(Node* node, FieldList fields);
FieldList handleDefInStruct(Node* node, FieldList fields);
FieldList handleDecListInStruct(Node* node, FieldList fields);
FieldList handleDecInStruct(Node* node, FieldList fields);
void handleDefListInFunction(Node* node);
void handleDefInFunction(Node* node);
void handleDecListInFunction(Node* node);
void handleDecInFunction(Node* node);
char *getVarDecIDName(Node *node);

// handle expression
// setting whether the node can be left value
SemanticType handleExp(Node* node);
SemanticType handleExpASSIGNOP(Node* left, Node* right);
SemanticType handleExpAND(Node* left, Node* right, Node* and);
SemanticType handleExpOR(Node* left, Node* right, Node* or);
SemanticType handleExpRELOP(Node* left, Node* right, Node* relop);
SemanticType handleExpMATH(Node* left, Node* right, Node* op);
SemanticType handleExpMinus(Node* node, Node* minus); // node is right exp
SemanticType handleExpNOT(Node* node, Node* not); // node is right exp
SemanticType handleExpFuncCall(Node* node); // node is father exp
SemanticType handleExpArray(Node* node); // node is father exp
SemanticType handleExpStruct(Node* node); // node is father exp
SemanticType handleExpID(Node* node, enum Kind kind); // node is ID
SemanticType handleExpINT(Node* node); // node is INT
SemanticType handleExpFLOAT(Node* node); // node is FLOAT

ArgList handleArgs(Node* node);





#endif