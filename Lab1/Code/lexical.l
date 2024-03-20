%option yylineno
%option noyywrap

%{
    #define YYSTYPE Node*
    #include <stdio.h>
    #include <stdbool.h>
    #include <stdlib.h>
    #include <string.h>
    #include "SyntaxTree.h"
    #include "syntax.tab.h"

    bool has_error = false;

    int yycolumn = 1;
    #define YY_USER_ACTION \
    yylloc.first_line = yylloc.last_line = yylineno; \
    yylloc.first_column = yycolumn; \
    yylloc.last_column = yycolumn + yyleng - 1; \
    yycolumn += yyleng;
%}





/* some common definitions */
digit [0-9]
letter [_A-Za-z]
sign [+-]?



INT [1-9]{digit}*|0
FLOAT {INT}\.{digit}+|{digit}*\.{digit}*[Ee]{sign}{digit}+
ID {letter}({letter}|{digit})*
SEMI ;
COMMA ,
RELOP >|<|>=|<=|==|!=
ASSIGNOP =
PLUS \+
MINUS \-
STAR \*
DIV \/
AND &&
OR \|\|
DOT \.
NOT !
TYPE int|float
LP \(
RP \)
LB \[
RB \]
LC \{
RC \}
STRUCT struct
RETURN return
IF if
ELSE else
WHILE while


BLANK [ \t\r]




%%

{BLANK} {;}
{SEMI} { //printf("SEMI\n"); 
         Type val;
         val.string_type = (char*)malloc(strlen(yytext)+1);
         strcpy(val.string_type, yytext);
         yylval = createTokenNode(yylineno, val, "SEMI");
         return SEMI; }
{COMMA} {//printf("COMMA\n"); 
         Type val;
         val.string_type = (char*)malloc(strlen(yytext)+1);
         strcpy(val.string_type, yytext);
         yylval = createTokenNode(yylineno, val, "COMMA");
         return COMMA; }
{RELOP} {//printf("RELOP\n"); 
         Type val;
         val.string_type = (char*)malloc(strlen(yytext)+1);
         strcpy(val.string_type, yytext);
         yylval = createTokenNode(yylineno, val, "RELOP");
         return RELOP; }
{ASSIGNOP} { //printf("ASSIGNOP\n"); 
         Type val;
         val.string_type = (char*)malloc(strlen(yytext)+1);
         strcpy(val.string_type, yytext);
         yylval = createTokenNode(yylineno, val, "ASSIGNOP");
         return ASSIGNOP; }
{PLUS} { //printf("PLUS\n"); 
         Type val;
         val.string_type = (char*)malloc(strlen(yytext)+1);
         strcpy(val.string_type, yytext);
         yylval = createTokenNode(yylineno, val, "PLUS");
         return PLUS; }
{MINUS} { //printf("MINUS\n"); 
         Type val;
         val.string_type = (char*)malloc(strlen(yytext)+1);
         strcpy(val.string_type, yytext);
         yylval = createTokenNode(yylineno, val, "MINUS");
         return MINUS; }
{STAR} { //printf("STAR\n"); 
         Type val;
         val.string_type = (char*)malloc(strlen(yytext)+1);
         strcpy(val.string_type, yytext);
         yylval = createTokenNode(yylineno, val, "STAR");
         return STAR; }
{DIV} { //printf("DIV\n"); 
         Type val;
         val.string_type = (char*)malloc(strlen(yytext)+1);
         strcpy(val.string_type, yytext);
         yylval = createTokenNode(yylineno, val, "STAR");
         return STAR; }
{AND} { //printf("AND\n"); 
         Type val;
         val.string_type = (char*)malloc(strlen(yytext)+1);
         strcpy(val.string_type, yytext);
         yylval = createTokenNode(yylineno, val, "AND");
         return AND; }
{OR} { //printf("OR\n"); 
         Type val;
         val.string_type = (char*)malloc(strlen(yytext)+1);
         strcpy(val.string_type, yytext);
         yylval = createTokenNode(yylineno, val, "OR");
         return OR; }
{DOT} { //printf("DOT\n"); 
         Type val;
         val.string_type = (char*)malloc(strlen(yytext)+1);
         strcpy(val.string_type, yytext);
         yylval = createTokenNode(yylineno, val, "DOT");
         return DOT; }
{NOT} { //printf("NOT\n"); 
         Type val;
         val.string_type = (char*)malloc(strlen(yytext)+1);
         strcpy(val.string_type, yytext);
         yylval = createTokenNode(yylineno, val, "NOT");
         return NOT; }
{LP} { //printf("LP\n"); 
         Type val;
         val.string_type = (char*)malloc(strlen(yytext)+1);
         strcpy(val.string_type, yytext);
         yylval = createTokenNode(yylineno, val, "LP");
         return LP; }
{RP} { //printf("RP\n"); 
         Type val;
         val.string_type = (char*)malloc(strlen(yytext)+1);
         strcpy(val.string_type, yytext);
         yylval = createTokenNode(yylineno, val, "RP");
         return RP; }
{LB} { //printf("LB\n"); 
         Type val;
         val.string_type = (char*)malloc(strlen(yytext)+1);
         strcpy(val.string_type, yytext);
         yylval = createTokenNode(yylineno, val, "LB");
         return LB; }
{RB} { //printf("RB\n"); 
         Type val;
         val.string_type = (char*)malloc(strlen(yytext)+1);
         strcpy(val.string_type, yytext);
         yylval = createTokenNode(yylineno, val, "RB");
         return RB; }
{LC} { //printf("LC\n"); 
         Type val;
         val.string_type = (char*)malloc(strlen(yytext)+1);
         strcpy(val.string_type, yytext);
         yylval = createTokenNode(yylineno, val, "LC");
         return LC; }
{RC} { //printf("RC\n"); 
         Type val;
         val.string_type = (char*)malloc(strlen(yytext)+1);
         strcpy(val.string_type, yytext);
         yylval = createTokenNode(yylineno, val, "RC");
         return RC; }
{STRUCT} { //printf("STRUCT\n"); 
         Type val;
         val.string_type = (char*)malloc(strlen(yytext)+1);
         strcpy(val.string_type, yytext);
         yylval = createTokenNode(yylineno, val, "STRUCT");
         return STRUCT; }
{RETURN} { //printf("RETURN\n"); 
         Type val;
         val.string_type = (char*)malloc(strlen(yytext)+1);
         strcpy(val.string_type, yytext);
         yylval = createTokenNode(yylineno, val, "RETURN");
         return RETURN; }
{IF} { //printf("IF\n"); 
         Type val;
         val.string_type = (char*)malloc(strlen(yytext)+1);
         strcpy(val.string_type, yytext);
         yylval = createTokenNode(yylineno, val, "IF");
         return IF; }
{ELSE} { //printf("ELSE\n"); 
         Type val;
         val.string_type = (char*)malloc(strlen(yytext)+1);
         strcpy(val.string_type, yytext);
         yylval = createTokenNode(yylineno, val, "ELSE");
         return ELSE; }
{WHILE} { //printf("WHILE\n"); 
         Type val;
         val.string_type = (char*)malloc(strlen(yytext)+1);
         strcpy(val.string_type, yytext);
         yylval = createTokenNode(yylineno, val, "WHILE");
         return WHILE; }
{TYPE} { //printf("TYPE\n"); 
         Type val;
         val.string_type = (char*)malloc(strlen(yytext)+1);
         strcpy(val.string_type, yytext);
         yylval = createTokenNode(yylineno, val, "TYPE");
         return TYPE; }
{INT} { //printf("INT\n"); 
         Type val;
         val.int_type = atoi(yytext);
         yylval = createTokenNode(yylineno, val, "INT");
         return INT; }
{FLOAT} { //printf("FLOAT\n"); 
         Type val;
         val.float_type = atof(yytext);
         yylval = createTokenNode(yylineno, val, "FLOAT");
         return FLOAT; }
{ID} { //printf("ID\n"); 
         Type val;
         val.string_type = (char*)malloc(strlen(yytext)+1);
         strcpy(val.string_type, yytext);
         yylval = createTokenNode(yylineno, val, "ID");
         return ID; }





\n { yycolumn = 1; }






0+{INT} {
    printf("Error type A at Line %d: Error format of number \'%s\'\n",
        yylineno, yytext);
    has_error = true;
}

{digit}+{ID} {
    printf("Error type A at Line %d: Error format of ID \'%s\'\n",
        yylineno, yytext);
    has_error = true;
}

. {
    printf("Error type A at Line %d: Mysterious characters \'%s\'\n",
        yylineno, yytext);
    has_error = true;
}



%%