%{
    #define YYSTYPE Node*
    #include <stdio.h>
    #include "SyntaxTree.h"
    #include "lex.yy.c"

    Node* root = NULL;

    void yyerror(char* msg) {
        fprintf(stdout, "error: %s\n", msg);
    }

%}

%locations


/* declared tokens */
%token INT
%token FLOAT
%token ID 
%token TYPE
%token SEMI COMMA
%token RELOP ASSIGNOP
%token PLUS MINUS STAR DIV
%token AND OR DOT NOT
%token LP RP LB RB LC RC
%token STRUCT RETURN IF ELSE WHILE




/* declared associativity */
%right ASSIGNOP
%left OR
%left AND
%left RELOP
%left PLUS MINUS
%left STAR DIV
%right NOT
%left LB RB LP RP DOT

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE






%%
Program : ExtDefList {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*1);
    kids[0] = $1;
    $$ = createVariableNode(@$.first_line, val, "Program", 1, kids);
    root = $$;
} ;

ExtDefList : ExtDef ExtDefList {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*2);
    kids[0] = $1;
    kids[1] = $2;
    $$ = createVariableNode(@$.first_line, val, "ExtDefList", 2, kids);
}
| { $$ = NULL; }
;

ExtDef : Specifier ExtDecList SEMI {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*3);
    kids[0] = $1;
    kids[1] = $2;
    kids[2] = $3;
    $$ = createVariableNode(@$.first_line, val, "ExtDef", 3, kids);
}
| Specifier SEMI {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*2);
    kids[0] = $1;
    kids[1] = $2;
    $$ = createVariableNode(@$.first_line, val, "ExtDef", 2, kids);
}
| Specifier FunDec CompSt {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*3);
    kids[0] = $1;
    kids[1] = $2;
    kids[2] = $3;
    $$ = createVariableNode(@$.first_line, val, "ExtDef", 3, kids);
}
;  

ExtDecList : VarDec {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*));
    kids[0] = $1;
    $$ = createVariableNode(@$.first_line, val, "ExtDecList", 1, kids);
}
| VarDec COMMA ExtDecList {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*3);
    kids[0] = $1;
    kids[1] = $2;
    kids[2] = $3;
    $$ = createVariableNode(@$.first_line, val, "ExtDecList", 3, kids);
}
;





Specifier : TYPE {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*));
    kids[0] = $1;
    $$ = createVariableNode(@$.first_line, val, "Specifier", 1, kids);
}
| StructSpecifier {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*));
    kids[0] = $1;
    $$ = createVariableNode(@$.first_line, val, "Specifier", 1, kids);
}
;

StructSpecifier : STRUCT OptTag LC DefList RC {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*5);
    kids[0] = $1;
    kids[1] = $2;
    kids[2] = $3;
    kids[3] = $4;
    kids[4] = $5;
    $$ = createVariableNode(@$.first_line, val, "StructSpecifier", 5, kids);
}
| STRUCT Tag {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*2);
    kids[0] = $1;
    kids[1] = $2;
    $$ = createVariableNode(@$.first_line, val, "StructSpecifier", 2, kids);
}
;

OptTag : ID {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*));
    kids[0] = $1;
    $$ = createVariableNode(@$.first_line, val, "OptTag", 1, kids);
}
| { $$ = NULL; }
;

Tag : ID {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*));
    kids[0] = $1;
    $$ = createVariableNode(@$.first_line, val, "Tag", 1, kids);
} ;





VarDec : ID {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*));
    kids[0] = $1;
    $$ = createVariableNode(@$.first_line, val, "VarDec", 1, kids);
} 
| VarDec LB INT RB {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*4);
    kids[0] = $1;
    kids[1] = $2;
    kids[2] = $3;
    kids[3] = $4;
    $$ = createVariableNode(@$.first_line, val, "VarDec", 4, kids);
}
;

FunDec : ID LP VarList RP {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*4);
    kids[0] = $1;
    kids[1] = $2;
    kids[2] = $3;
    kids[3] = $4;
    $$ = createVariableNode(@$.first_line, val, "FunDec", 4, kids);
}
| ID LP RP {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*3);
    kids[0] = $1;
    kids[1] = $2;
    kids[2] = $3;
    $$ = createVariableNode(@$.first_line, val, "FunDec", 3, kids);
}
;

VarList : ParamDec COMMA VarList {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*3);
    kids[0] = $1;
    kids[1] = $2;
    kids[2] = $3;
    $$ = createVariableNode(@$.first_line, val, "VarList", 3, kids);
}
| ParamDec {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*));
    kids[0] = $1;
    $$ = createVariableNode(@$.first_line, val, "VarList", 1, kids);
}
;

ParamDec : Specifier VarDec {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*2);
    kids[0] = $1;
    kids[1] = $2;
    $$ = createVariableNode(@$.first_line, val, "ParamDec", 2, kids);
} ;





CompSt : LC DefList StmtList RC {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*4);
    kids[0] = $1;
    kids[1] = $2;
    kids[2] = $3;
    kids[3] = $4;
    $$ = createVariableNode(@$.first_line, val, "CompSt", 4, kids);
}

StmtList : Stmt StmtList {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*2);
    kids[0] = $1;
    kids[1] = $2;
    $$ = createVariableNode(@$.first_line, val, "StmtList", 2, kids);
}
| { $$ = NULL; }
;

Stmt : Exp SEMI {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*2);
    kids[0] = $1;
    kids[1] = $2;
    $$ = createVariableNode(@$.first_line, val, "Stmt", 2, kids);
}
| CompSt {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*));
    kids[0] = $1;
    $$ = createVariableNode(@$.first_line, val, "Stmt", 1, kids);
}
| RETURN Exp SEMI {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*3);
    kids[0] = $1;
    kids[1] = $2;
    kids[2] = $3;
    $$ = createVariableNode(@$.first_line, val, "Stmt", 3, kids);
}
| IF LP Exp RP Stmt %prec LOWER_THAN_ELSE {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*5);
    kids[0] = $1;
    kids[1] = $2;
    kids[2] = $3;
    kids[3] = $4;
    kids[4] = $5;
    $$ = createVariableNode(@$.first_line, val, "Stmt", 5, kids);
}
| IF LP Exp RP Stmt ELSE Stmt {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*7);
    kids[0] = $1;
    kids[1] = $2;
    kids[2] = $3;
    kids[3] = $4;
    kids[4] = $5;
    kids[5] = $6;
    kids[6] = $7;
    $$ = createVariableNode(@$.first_line, val, "Stmt", 7, kids);
}
| WHILE LP Exp RP Stmt {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*5);
    kids[0] = $1;
    kids[1] = $2;
    kids[2] = $3;
    kids[3] = $4;
    kids[4] = $5;
    $$ = createVariableNode(@$.first_line, val, "Stmt", 5, kids);
}
;





DefList : Def DefList {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*2);
    kids[0] = $1;
    kids[1] = $2;
    $$ = createVariableNode(@$.first_line, val, "DefList", 2, kids);
}
| { $$ = NULL; }
;

Def : Specifier DecList SEMI {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*3);
    kids[0] = $1;
    kids[1] = $2;
    kids[2] = $3;
    $$ = createVariableNode(@$.first_line, val, "Def", 3, kids);
} ;

DecList : Dec {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*));
    kids[0] = $1;
    $$ = createVariableNode(@$.first_line, val, "DecList", 1, kids);
}
| Dec COMMA DecList {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*3);
    kids[0] = $1;
    kids[1] = $2;
    kids[2] = $3;
    $$ = createVariableNode(@$.first_line, val, "DecList", 3, kids);
}
;

Dec : VarDec {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*));
    kids[0] = $1;
    $$ = createVariableNode(@$.first_line, val, "Dec", 1, kids);
}
| VarDec ASSIGNOP Exp {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*3);
    kids[0] = $1;
    kids[1] = $2;
    kids[2] = $3;
    $$ = createVariableNode(@$.first_line, val, "Dec", 3, kids);
}
;





Exp : Exp ASSIGNOP Exp {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*3);
    kids[0] = $1;
    kids[1] = $2;
    kids[2] = $3;
    $$ = createVariableNode(@$.first_line, val, "Exp", 3, kids);
}
| Exp AND Exp {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*3);
    kids[0] = $1;
    kids[1] = $2;
    kids[2] = $3;
    $$ = createVariableNode(@$.first_line, val, "Exp", 3, kids);
}
| Exp OR Exp {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*3);
    kids[0] = $1;
    kids[1] = $2;
    kids[2] = $3;
    $$ = createVariableNode(@$.first_line, val, "Exp", 3, kids);
}
| Exp RELOP Exp {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*3);
    kids[0] = $1;
    kids[1] = $2;
    kids[2] = $3;
    $$ = createVariableNode(@$.first_line, val, "Exp", 3, kids);
}
| Exp PLUS Exp {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*3);
    kids[0] = $1;
    kids[1] = $2;
    kids[2] = $3;
    $$ = createVariableNode(@$.first_line, val, "Exp", 3, kids);
}
| Exp MINUS Exp {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*3);
    kids[0] = $1;
    kids[1] = $2;
    kids[2] = $3;
    $$ = createVariableNode(@$.first_line, val, "Exp", 3, kids);
}
| Exp STAR Exp {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*3);
    kids[0] = $1;
    kids[1] = $2;
    kids[2] = $3;
    $$ = createVariableNode(@$.first_line, val, "Exp", 3, kids);
}
| Exp DIV Exp {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*3);
    kids[0] = $1;
    kids[1] = $2;
    kids[2] = $3;
    $$ = createVariableNode(@$.first_line, val, "Exp", 3, kids);
}
| LP Exp RP {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*3);
    kids[0] = $1;
    kids[1] = $2;
    kids[2] = $3;
    $$ = createVariableNode(@$.first_line, val, "Exp", 3, kids);
}
| MINUS Exp {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*2);
    kids[0] = $1;
    kids[1] = $2;
    $$ = createVariableNode(@$.first_line, val, "Exp", 2, kids);
}
| NOT Exp {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*2);
    kids[0] = $1;
    kids[1] = $2;
    $$ = createVariableNode(@$.first_line, val, "Exp", 2, kids);
}
| ID LP Args RP {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*4);
    kids[0] = $1;
    kids[1] = $2;
    kids[2] = $3;
    kids[3] = $4;
    $$ = createVariableNode(@$.first_line, val, "Exp", 4, kids);
}
| ID LP RP {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*3);
    kids[0] = $1;
    kids[1] = $2;
    kids[2] = $3;
    $$ = createVariableNode(@$.first_line, val, "Exp", 3, kids);
}
| Exp LB Exp RB {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*4);
    kids[0] = $1;
    kids[1] = $2;
    kids[2] = $3;
    kids[3] = $4;
    $$ = createVariableNode(@$.first_line, val, "Exp", 4, kids);
}
| Exp DOT ID {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*3);
    kids[0] = $1;
    kids[1] = $2;
    kids[2] = $3;
    $$ = createVariableNode(@$.first_line, val, "Exp", 3, kids);
}
| ID {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*));
    kids[0] = $1;
    $$ = createVariableNode(@$.first_line, val, "Exp", 1, kids);
}
| INT {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*));
    kids[0] = $1;
    $$ = createVariableNode(@$.first_line, val, "Exp", 1, kids);
}
| FLOAT {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*));
    kids[0] = $1;
    $$ = createVariableNode(@$.first_line, val, "Exp", 1, kids);
}
;

Args : Exp COMMA Args {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*3);
    kids[0] = $1;
    kids[1] = $2;
    kids[2] = $3;
    $$ = createVariableNode(@$.first_line, val, "Args", 3, kids);
}
| Exp {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*));
    kids[0] = $1;
    $$ = createVariableNode(@$.first_line, val, "Args", 1, kids);
}
;




%%