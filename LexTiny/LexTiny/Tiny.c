#include <stdio.h>
#include "Tiny.tab.h"
#include <errno.h>

extern FILE* yyin;
extern int yylex(void);

char* symbols[] = {
    "END",
 "CHAR",
 "IF",
 "ELSE",
 "RETURN",
 "WRITE",
 "READ",
 "LENGTH",
 "WHILE",
 "CONSTANT",
 "STRING_LITERAL",
 "QCHAR",
 "NUMBER",
 "LPAR",
 "RPAR",
 "LBRANCE",
 "RBRANCE",
 "LBRACK",
 "RBRACK",
 "ASSIGN",
 "SEMICOLON",
 "COMMA",
 "PLUS",
 "MINUS",
 "TIMES",
 "DIVIDE",
 "EQUAL",
 "GREATER",
 "LESS",
 "NAME",
 "INT",
 "NEQUAL"
};


int main() {
    int lexUnit = 0;
    yyin = fopen( "input.csrc", "rt" );
    if (yyin != NULL) {
        while ((lexUnit = yylex()) != YYEOF)
        {
            printf(" -> TOKEN %s\n", symbols[lexUnit]);
        }
        fclose(yyin);
    }
    else {
        printf("Erorr: %d", errno);
    }
}
