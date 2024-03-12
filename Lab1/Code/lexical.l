%option yylineno
%option noyywrap
/* locations */
%{

    #include <stdio.h>
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
PLUS +
MINUS -
STAR \*
DIV /
AND &&
OR ||
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


BLANK [\t\n]




%%


{INT} { printf("INT\n"); }
{FLOAT} { printf("FLOAT\n"); }
{ID} { printf("ID\n"); }
{SEMI} { printf("SEMI\n"); }
{COMMA} { printf("COMMA\n"); }
{RELOP} { printf("RELOP\n"); }
{PLUS} { printf("PLUS\n"); }
{MINUS} { printf("MINUS\n"); }
{STAR} { printf("STAR\n"); }
{DIV} { printf("DIV\n"); }
{AND} { printf("AND\n"); }
{OR} { printf("OR\n"); }
{DOT} { printf("DOT\n"); }
{NOT} { printf("NOT\n"); }
{TYPE} { printf("TYPE\n"); }
{LP} { printf("LP\n"); }
{RP} { printf("RP\n"); }
{LB} { printf("LB\n"); }
{RB} { printf("RB\n"); }
{LC} { printf("LC\n"); }
{RC} { printf("RC\n"); }
{STRUCT} { printf("STRUCT\n"); }
{RETURN} { printf("RETURN\n"); }
{IF} { printf("IF\n"); }
{ELSE} { printf("ELSE\n"); }
{WHILE} { printf("WHILE\n"); }

/*
"//" {
    char c = input();
    while (c != '\n'  &&  c)
        c = input();
}*/


\n { yycolumn = 1; }





/* Handle error type of input */
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