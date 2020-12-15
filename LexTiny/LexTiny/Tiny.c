#include "ast.h"
#include "Tiny.tab.h"
#include "SemanticAnalyzer.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>

extern int yyparse(void);
extern FILE* yyin;
extern int yylex(void);
extern int yydebug;
extern Node* astRoot;



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
        printAst(astRoot, 0);

        SymTableNode* root = NULL;

        createSymbolList(astRoot, 0, &root);
        printSymbolList(root);

        fclose(yyin);
    }
    else
    {
        printf("Fisier inexistent");
    }

}
