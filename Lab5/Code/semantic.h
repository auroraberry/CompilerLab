#ifndef __SEMANTIC__
#define __SEMANTIC__

#include "SymbolTable.h"
#include "SyntaxTree.h"



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
bool variableDefinitionUsingUndefinedStruct(int lineno, char* name);



void semanticAnalysis(Node* root);



int countSize(SemanticType type);







#endif