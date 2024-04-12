#ifndef __SYMBOLTABLE__
#define __SYMBOLTABLE__
#include "ArrayList.h"

enum Kind {BASIC, ARRAY, STRUCT, FUNC, NONE};

enum BASIC_TYPE {INT, FLOAT};

enum STATUS {NOEXISTS, EXISTS};

typedef struct Type_* SemanticType;
typedef struct BasicVal_* BasicVal;
typedef struct Array_* Array;
typedef struct FieldList_* FieldList;
typedef struct ArgList_* ArgList;

typedef struct SymbolPair_* SymbolPair;

#define SymbolTable ArrayList*

struct Type_
{
    enum Kind kind;
    union
    {
        // basic type
        BasicVal basic_val;
        // array type is a struct containing type of element and array size
        Array array;
        // struct type is a list of filed
        FieldList structure;
        // function type is a list of parameter
        ArgList function;
    } val;
};

struct BasicVal_{
    enum BASIC_TYPE basic_type;
    union
    {
        int int_val;
        float float_val;
    } val;
};


struct Array_
{
    SemanticType elem;
    int size;
};


struct FieldList_
{
    char* name; // filed name
    SemanticType type; // field type
    FieldList next; // next field
};



struct ArgList_
{
    char* name; //function name or parameter name
    SemanticType type; // return type with funtion name 
    ArgList next; // the head of the arglist is return variable
};

struct SymbolPair_{
    char* name;
    SemanticType type;
};


extern SymbolTable symbol_table;

void initTable();

void freeTable();

bool TableContains(SymbolPair symbol_pair);

bool TableContains(char* name, SemanticType type);

//add symbol and its info, if it is already existing, then return false, otherwise return true 
bool addSymbolPair(char* name, SemanticType type);

bool isSameType(SemanticType type1, SemanticType type2);

SymbolPair TableGet(int index);

SymbolPair TableGet(char* name);


#endif