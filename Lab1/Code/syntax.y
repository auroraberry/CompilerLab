%{
#include <stdio.h>
%}

/* declared types */
%union {
int type_int;
float type_float;
double type_double;
}

/* declared tokens */
%token <type_int> INT
%token <type_float> FLOAT
%token ADD SUB MUL DIV

/* declared non-terminals */
%type <type_double> Exp Factor Term



/* declared associativity */
%right ASSIGN
%left ADD SUB
%left MUL DIV
%left LB RB
%left LP RP
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE








%%

Stmt : IF LP Exp RP Stmt %prec LOWER_THAN_ELSE
    | IF LP Exp RP Stmt ELSE Stmt







%%