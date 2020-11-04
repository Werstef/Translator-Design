%{
#include <stdio.h>
int yyerror(char * s);
extern int yylex(void);
%}

%token INT
%token CHAR
%token IF
%token ELSE
%token RETURN
%token WRITE
%token READ
%token LENGTH
%token WHILE
%token NAME
%token NUMBER
%token QCHAR
%token CONSTANT
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


%start program
%%
program
	: declaration
	| program declaration
	;

declaration 
	: fun_declaration
	| var_declaration
	;

type
	: INT
	| CHAR
	| type LBRACK exp RBRACK
	;

fun_declaration 
	: type NAME LPAR formal_pars RPAR block
	;

formal_pars
	: param_list
	|
	;

param_list 
	: param_list COMMA formal_par 
	| formal_par
	;

formal_par
	: type NAME
	;

block
	: LBRACE var_declaration_list statements_list RBRACE
	;

var_declaration_list
	: var_declaration
	| var_declaration_list var_declaration
	|
	;

var_declaration
	: type NAME SEMICOLON
	| type NAME ASSIGN NUMBER SEMICOLON
	;

statements_list
	: statements
	|
	;

statements 
	: statements SEMICOLON statement
	| statement
	;

statement
	: IF LPAR exp RPAR statement
	| IF LPAR exp RPAR statement ELSE statement
	| WHILE LPAR exp RPAR statement
	| lexp ASSIGN exp
	| RETURN exp
	| NAME LPAR pars RPAR 
	| block
	| WRITE exp
	| READ lexp
	;

lexp
	: var
	| lexp LBRACK exp RBRACK
	;

exp : lexp
	| exp binop exp
	| unop exp	
	| LPAR exp RPAR
	| NUMBER
	| NAME LPAR pars RPAR // function call
	| QCHAR
	| LENGTH lexp // size of an array
	;

binop
	: MINUS
	| PLUS
	| TIMES
	| DIVIDE
	| EQUAL
	| NEQUAL
	| GREATER
	| LESS
	;

unop
	: MINUS
	| NEQUAL
	;

pars 
	: par
	|
	;

par 
	: par COMMA exp
	| exp
	;

var
	: NAME
	;

%%

int yyerror(char * s) 
/* yacc error handler */
{    
	printf ( "%s\n", s); 
	return 0;
}  