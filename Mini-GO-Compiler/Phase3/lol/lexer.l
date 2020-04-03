%{
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"
extern "C" {
    int yylex(void);
    void yyerror(const char *s);
    int yywrap(void);
}
int line_number = 0;
extern int scope_nn;
extern int fromLex;
extern char lexChar[1000];
%}
%option yylineno

printBody “%d”|“%ld”|“%lld”|“%f”|“%lf”|“%s”|“%c”|“%u”|“%lu”|“%llu”


%%

\n {line_number++;}
"//".*\n {;}

[/][*][^*]*[*]+([^*/][^*]*[*]+)*[/] {}

\"[^\"{printBody}]*\" {yylval.str = strdup(yytext) ;return T_PRINT_BODY;}
\"[^\"]*\" {yylval.str = strdup(yytext) ;return T_STRING;}

\'(.|\\n)\' {yylval.str = strdup(yytext) ;return T_CHARACTER;}



"int"	{yylval.str = strdup(yytext) ;return T_TINT;}
"double"|"long"|"long long"|"float"|"char"|"long int"|"long long int"|"long float" {yylval.str = strdup(yytext) ;return T_TYPE_NAME;}


while	{yylval.str = strdup(yytext) ;return T_WHILE;}
switch	{yylval.str = strdup(yytext) ;return T_SWITCH;}
case	{yylval.str = strdup(yytext) ;return T_CASE;}
default	{yylval.str = strdup(yytext) ;return T_DEFAULT;}
"return" {yylval.str = strdup(yytext) ;return T_RETURN;}
break {yylval.str = strdup(yytext) ;return T_BREAK;}
"fmt\.Print"+"fmt\.Printf" {yylval.str = strdup(yytext) ;return T_PRINT;}
continue {yylval.str = strdup(yytext) ;return T_CONTINUE;}


main {yylval.str = strdup(yytext) ;return T_MAIN;}


none  {fromLex=0;yyerror("ERROR: `none` super word");}


[0-9][a-zA-Z_]+	{strcpy(lexChar,yytext);fromLex=0;yyerror("ERROR: Ivalid Identifier ");}


[a-zA-Z_][a-zA-Z_0-9]*	{yylval.str = strdup(yytext) ;return T_IDENTIFIER;}

"{"	{yylval.str = strdup(yytext); scope_nn++; return T_OPEN_SCOPE;}

"}"	{yylval.str = strdup(yytext) ;return T_CLOSE_SCOPE;}

"("	{yylval.str = strdup(yytext) ;return T_OPEN_PARAN;}

")"	{yylval.str = strdup(yytext) ;return T_CLOSE_PARAN;}

";"	{yylval.str = strdup(yytext) ;return T_SEMI_COLON;}

":" {yylval.str = strdup(yytext) ;return T_COLON;}

"!"|"&&"|"||" {yylval.str = strdup(yytext) ;return T_LOGICAL_OPERATOR;}

"<"|">"|"=="|"!="|">="|"<=" {yylval.str = strdup(yytext) ;return T_RELATIONAL_OPERATOR;}

"++"|"--" {yylval.str = strdup(yytext) ;return T_UNARY_OPERATOR;}

"="	{yylval.str = strdup(yytext) ;return T_ASSIGN_INITIALIZE;}
"+="|"-="|"*="|"/="|"%=" {yylval.str = strdup(yytext) ;return T_ASSIGN_OPERATOR;}

"+"|"-" {yylval.str = strdup(yytext) ;return T_F_BINARY_OPERATOR;}
"/"|"*"|"%" {yylval.str = strdup(yytext) ;return  T_S_BINARY_OPERATOR;}


[0-9]+\.[0-9]+ {yylval.str = strdup(yytext) ;return T_FLOAT;}

[0-9]+	{yylval.str = strdup(yytext) ;return T_INT;}

"," {yylval.str = strdup(yytext) ;return T_COMMA;}

\t|" "	{}



. {fromLex = 0;yyerror("Invalid Syntax PANIC;\n");}
%%

int yywrap()
{
	return 1;
}
