#include <stdio.h>
#include "Tiny.tab.h"
#include <errno.h>

extern int yyparse(void);
extern FILE* yyin;
extern int yylex(void);
extern int yydebug;

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


int main()
{
    //int lexUnit = 0;
    //yydebug = 1;
    yyin = fopen("input.csrc", "rt");
    if (yyin != NULL)
    {
        int result = yyparse();
        switch (result)
        {
        case 0:
            printf("Parse successfull.\n");
            break;

        case 1:
            printf("Invalid input encountered\n");
            break;

        case 2:
            printf("Out of memory\n");
            break;

        default:
            break;
        }
        /*while ((lexUnit = yylex()) != END)
        {
            printf(" -> TOKEN: %s\n", symbols[lexUnit]);
        }*/
        fclose(yyin);
    }
    else
    {
        printf("Fisier inexistent");
    }

}
