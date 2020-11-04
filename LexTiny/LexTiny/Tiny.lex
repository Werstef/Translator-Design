D		[0-9]
L		[a-zA-Z_]
H		[a-fA-F0-9]
E		[Ee][+-]?{D}+
FS		(f|F|l|L)
IS		(u|U|l|L)*

%{
#include <stdio.h>
#include "Tiny.tab.h"

void count();
%}

%%
"//"		{comment(); }

"int"			{count(); return(INT); }
"char"			{count(); return(CHAR); }
"if"			{count(); return(IF); }
"else"			{count(); return(ELSE); }
"return"		{count(); return(RETURN); }
"write"			{count(); return(WRITE); }
"read"			{count(); return(READ); }
"length"		{count(); return(LENGTH); }
"while"			{count(); return(WHILE); }




{L}({L}|{D})*		{ count(); return(NAME); }
{D}*			{ count(); return(NUMBER); }
('.')			{ count(); return(QCHAR); }
0{D}+{IS}?		    { count(); return(CONSTANT); }
{D}+{IS}?		    { count(); return(CONSTANT); }
{D}+{E}{FS}?		{ count(); return(CONSTANT); }
{D}*"."{D}+({E})?{FS}?	{ count(); return(CONSTANT); }
{D}+"."{D}*({E})?{FS}?	{ count(); return(CONSTANT); }

L?\"(\\.|[^\\"])*\"		{ count(); return(STRING_LITERAL); }




"("			{ count(); return(LPAR); }
")"			{ count(); return(RPAR); }
"{"			{ count(); return(LBRACE); }
"}"			{ count(); return(RBRACE); }
"["			{ count(); return(LBRACK); }
"]"			{ count(); return(RBRACK); }
"="			{ count(); return(ASSIGN); }
";"			{ count(); return(SEMICOLON); }
","			{ count(); return(COMMA); }
"+"			{ count(); return(PLUS); }
"-"			{ count(); return(MINUS); }
"*"			{ count(); return(TIMES); }
"/"			{ count(); return(DIVIDE); }
"=="		{ count(); return(EQUAL); }
">"			{ count(); return(GREATER); }
"<"			{ count(); return(LESS); }
"!="		{ count(); return(NEQUAL); }





[ \t\v\n\f]		{ count();}

%%

yywrap()
{
	return(1);
}

print_error(){
	printf("Bad character: %s\n", yytext);
}


comment()
{
	char c, c1;

loop:
	while ((c = input()) != '*' && c != 0)
		putchar(c);

	if ((c1 = input()) != '/' && c != 0)
	{
		unput(c1);
		goto loop;
	}

	if (c != 0)
		putchar(c1);
}


int column = 0;

void count()
{
	int i;

	for (i = 0; yytext[i] != '\0'; i++)
		if (yytext[i] == '\n')
			column = 0;
		else if (yytext[i] == '\t')
			column += 8 - (column % 8);
		else
			column++;

	ECHO;
}




