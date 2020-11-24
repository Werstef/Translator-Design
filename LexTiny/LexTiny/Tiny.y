%{
#include <stdio.h>
#include "ast.h"

Node* astRoot = NULL;
int yyerror(char * s);
extern int yylex(void);

%}

%union{
	Node	*node;
	char* strings;
	int intVal;
}

%token INT
%token CHAR
%token IF
%token ELSE
%token RETURN
%token WRITE
%token READ
%token LENGTH
%token WHILE
%token <strings> NAME
%token <intVal> NUMBER
%token <strings> QCHAR
%token <intVal> CONSTANT
%token STRING_LITERAL
%token LPAR
%token RPAR
%token LBRACE
%token RBRACE
%token LBRACK
%token RBRACK
%token ASSIGN
%token SEMICOLON
%token COMMA
%left PLUS
%left MINUS
%left TIMES
%left DIVIDE
%left EQUAL
%left GREATER
%left LESS
%left NEQUAL

%expect 19

%type <node> program
%type <node> declaration
%type <node> fun_declaration
%type <node> var_declaration
%type <node> var_declaration_list
%type <node> statements_list
%type <node> type
%type <node> formal_pars
%type <node> formal_par
%type <node> block
%type <node> param_list
%type <node> statements
%type <node> statement
%type <node> exp
%type <node> lexp
%type <node> binop
%type <node> unop
%type <node> pars
%type <node> par
%type <node> var

%start program
%%
program
	: declaration { $$ = createProgramNode($1); astRoot = $$;}
	| program declaration {							 
								  $$ = $1; 
								  addLinkToList($$, $2);
								}
	;

declaration 
	: fun_declaration { $$ = createDeclarationNode($1);}
	| var_declaration { $$ = createDeclarationNode($1);}
	;

type
	: INT {$$ = createType("INT");}
	| CHAR {$$ = createType("CHAR");}
	;

fun_declaration 
	: type NAME LPAR formal_pars RPAR block { $$ = createFunctionDeclarationNode($1, $2, $4, $6);  }
	;

formal_pars
	: param_list { $$ = createListNode("ParamList", $1); }
	| {$$ = NULL;}
	;

param_list 
	: param_list COMMA formal_par  {
									$$ = $1;
									addLinkToList($$, $3);
									}
	| formal_par { $$ = createListNode("Parameter", $1); }
	;

formal_par
	: type NAME { $$ = createVarDeclaration($1, $2, 0);}
	;

block
	: LBRACE var_declaration_list statements_list RBRACE {$$ = createBlock($2, $3);}
	;

var_declaration_list
	: var_declaration { $$ = createListNode("LocalDeclarations", $1); }
	| var_declaration_list var_declaration {
					$$ = $1;
					addLinkToList($$, $2);
						}
	|	{$$ = NULL;}
	;

var_declaration
	: type NAME SEMICOLON { $$ = createVarDeclaration($1, $2, 0);}
	| type NAME ASSIGN NUMBER SEMICOLON { $$ = createVarDeclaration($1, $2, $4);}
	| type NAME LBRACK exp RBRACK SEMICOLON {$$ = createArrayDeclaration($1, $2, $4 );}
	;

statements_list
	: statements { $$ = createListNode("StatementsList", $1); }
	| {$$ = NULL;}
	;

statements 
	: statements  statement {
							$$ = $1;
							addLinkToList($$, $2);
							}
	| statement SEMICOLON   { $$ = createListNode("Statement", $1); }
	; 

statement
	: IF LPAR exp RPAR statement { $$ = createIfStatement($3, $5, NULL);}
	| IF LPAR exp RPAR statement ELSE statement { $$ = createIfStatement($3, $5, $7);}
	| WHILE LPAR exp RPAR statement { $$ = createWhileStatement($3, $5);} // x
	| lexp ASSIGN exp { $$ = createAssignStatement($1, $3);} // x
	| RETURN exp { $$ = createReturnStatement($2);} // x
	| NAME LPAR pars RPAR { $$ = createFunctionCall($1, $3);} // x
	| block { $$ = createListNode("Block", $1); } // x
	| WRITE exp { $$ = createWriteNode($2); } // x
	| READ lexp { $$ = createReadNode($2); } // x
	;

lexp
	: var { $$ = createVarNode($1); }
	| lexp LBRACK exp RBRACK { $$ = createExpArray($1, $3); }
	;

exp : lexp { $$ = createLExp($1); }
	| exp binop exp { $$ = createBinopExp($1, $2, $3); }
	| unop exp	{ $$ = createUnopExp($1, $2); }
	| LPAR exp RPAR { $$ = createParameterExp($2); }
	| NUMBER { $$ = createNumberNode($1); }
	| NAME LPAR pars RPAR { $$ = createFunctionCall($1, $3);}
	| QCHAR { $$ = createQChrNode($1); }
	| LENGTH lexp { $$ = createSizeArray($2); }
	;

binop
	: MINUS {$$ = MINUS;}
	| PLUS {$$ = PLUS;}
	| TIMES {$$ = TIMES;} 
	| DIVIDE {$$ = DIVIDE;} 
	| EQUAL {$$ = EQUAL;} 
	| NEQUAL {$$ = NEQUAL;} 
	| GREATER {$$ = GREATER;} 
	| LESS {$$ = LESS;} 
	;

unop
	: MINUS {$$ = MINUS;} // to be modified
	| NEQUAL {$$ = EQUAL;}
	;

pars 
	: par { $$ = createParameter($1); }
	|  {$$ = NULL;}
	;

par 
	: par COMMA exp {
						$$ = $1;
						addLinkToList($$, $3);
						}
	| exp { $$ = createExp($1); }
	;

var
	: NAME { $$ = createVarNameNode($1); }
	;

%%

int yyerror(char * s) 
/* yacc error handler */
{    
	printf ( "%s\n", s); 
	return 0;
}  