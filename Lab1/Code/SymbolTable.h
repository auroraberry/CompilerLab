#ifndef __SYMBOLTABLE__
#define __SYMBOLTABLE__
#include "ArrayList.h"

enum Kind {BASIC, ARRAY, STRUCTURE, FUNC, ERROR, NONE};

enum BASIC_TYPE {BASIC_INT, BASIC_FLOAT};

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

// memory management  
SemanticType createSemanticType(enum Kind Kind);
BasicVal createBasicVal();
Array createArray();
FieldList createFieldList();
ArgList createArgList();
SymbolPair createSymbolPair();
char* createCharName();



extern SymbolTable symbol_table;

void initTable();

void freeTable();

int TableContains(char* name);


//add symbol and its info, if it is already existing, then return false, otherwise return true 
bool addSymbolPair(char* name, SemanticType type);

bool isSameType(SemanticType type1, SemanticType type2);

SymbolPair TableGetByIndex(int index);

SymbolPair TableGet(char* name);



// helper function
void copySemanticType(SemanticType src, SemanticType dest);
void copyStructure(FieldList src, FieldList dest);
void copyArray(Array src, Array dest);
void copyFunction(ArgList src, ArgList dest);
void copyBasicVal(BasicVal src, BasicVal dest);

#endif