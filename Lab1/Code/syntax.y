%{
    #define YYSTYPE Node*
    #include <stdio.h>
    #include "SyntaxTree.h"
    #include "lex.yy.c"

    Node* root = NULL;
    bool syntax_error = false;
    bool needHandling(int lineno); 
    
    void handleError(int lineno, char* msg) {
        if(needHandling(lineno)){
            syntax_error = true;
            printf("Error type B at Line %d: Syntax Error. %s", yylineno, msg); 
        }
    }

    void yyerror(char* msg){}

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
| Specifier error SEMI {
    //$$ = NULL;
    handleError(@1.first_line, "Error in global definition.\n");
}
| Specifier SEMI {
    Type val;
    val.string_type = NULL;
    Node** kids = (Node**)malloc(sizeof(Node*)*2);
    kids[0] = $1;
    kids[1] = $2;
    $$ = createVariableNode(@$.first_line, val, "ExtDef", 2, kids);
}
| error SEMI {
    //$$ = NULL;
    handleError(@2.first_line, "Error in global definition.\n");
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
| STRUCT OptTag LC error RC {
    //$$ = NULL;
    handleError(@3.first_line, "Error in Struct definition.\n");
}
| STRUCT error LC DefList RC {
    //$$ = NULL;
    handleError(@1.first_line, "Error in Struct definition.\n");
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
| error LB INT RB {
    //$$ = NULL;
    handleError(@2.first_line, "Error in var declaration.\n");
}
| VarDec LB error RB {
    //$$ = NULL;
    handleError(@2.first_line, "Error in var declaration.\n");
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
| error LP VarList RP {
    //$$ = NULL;
    handleError(@2.first_line, "Error in func declaration.\n");
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
| ID LP error RP {
    //$$ = NULL;
    handleError(@2.first_line, "Error in func declaration.\n");
}
| error LP RP {
    //$$ = NULL;
    handleError(@2.first_line, "Error in func declaration.\n");
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
| LC DefList error RC {
    //$$ = NULL;
    handleError(@2.first_line, "Error in CompSt.\n");
}
| LC error StmtList RC {
    //$$ = NULL;
    handleError(@2.first_line, "Error in definition.\n");
}
;

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
| Exp error SEMI {
    //$$ = NULL;
    handleError(@1.first_line, "Invalid statement.\n");
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
| RETURN error SEMI {
    //$$ = NULL;
    handleError(@1.first_line, "Invalid statement.\n");
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
| IF LP error RP Stmt %prec LOWER_THAN_ELSE {
    //$$ = NULL;
    handleError(@2.first_line, "Invalid statement.\n");
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
| IF LP error RP Stmt ELSE Stmt {
    //$$ = NULL;
    handleError(@2.first_line, "Invalid statement.\n");
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
| WHILE LP error RP Stmt {
    //$$ = NULL;
    handleError(@2.first_line, "Invalid statement.\n");
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
} 
| Specifier error SEMI {
    //$$ = NULL;
    handleError(@1.first_line, "Error in definition.\n");
}
| error SEMI {
    //$$ = NULL;
    handleError(@1.first_line, "Error in definition.\n");
}
;

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
| error ASSIGNOP Exp {
    handleError(@2.first_line, "Error in declaration.\n");
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
| error ASSIGNOP Exp {
    //$$ = NULL;
    handleError(@1.first_line, "Error in exp.\n");
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
| Exp STAR error Exp {
    //$$ = NULL;
    handleError(@1.first_line, "Error in exp.\n");
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
| LP error RP {
    //$$ = NULL;
    handleError(@1.first_line, "Error in exp.\n");
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
| Exp LB error RB {
    //$$ = NULL;
    handleError(@1.first_line, "Error in exp.\n");
}
| error LB Exp RB {
    //$$ = NULL;
    handleError(@1.first_line, "Error in exp.\n");
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