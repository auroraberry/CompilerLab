#include <stdlib.h>
#include <stdio.h>
#include "syntax.tab.h"
#include "SyntaxTree.h"
#include "SyntaxTreePrinter.h"
#include "semantic.h"

extern int yyparse();
extern void yyrestart(FILE*); /* yyrestart(f)函数是Flex提供的库函数，它可以让Flex将其输入文件的文件指针yyin设置为f
                               * （当然也可以像前面一样手动设置令yyin = f）并重新初始化该文件指针，令其指向输入文件的开头。
                               * */
extern void yylex();
extern FILE* yyin;
extern Node* root;
extern bool lexical_error;
extern bool syntax_error;

int main(int argc, char **argv) {
    if (argc <= 1) return 1;
    FILE *f = fopen(argv[1], "r");
    if (!f) {
        perror(argv[1]);
        return 1;
    }
    yyrestart(f);
    yyparse();
    if(!lexical_error && !syntax_error){
        //printSyntaxTree(root, 0);
        #ifdef __SEMANTIC__
        initTable();
        handleProgram(root);
        #endif
    }

    return 0;
}

/*int main(int argc, char** argv) {
    if (argc > 1) {
        if (!(yyin = fopen(argv[1], "r"))) {
            perror(argv[1]);
            return 1;
        }
    }
    while (yylex() != 0);
    return 0;
}*/

