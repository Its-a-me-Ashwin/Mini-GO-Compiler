%{

#include "y.tab.h"
extern YYSTYPE yylval;
extern int yyerror(char *);
int line_number = 0;
extern int scope_nn;
extern int fromLex;
extern char lexChar[1000];
#include<string.h>	
	struct symbolTable {
			int lineNo;
			char symbol[50];
			void *value;
			char type[50];
			int scope;	
		};
	struct lexeme {
			char key[50];
			char value[50];
		};
	int lineNUmber = 0;
	int tokenNo = 0;
	int lexemeNo = 0;
	unsigned int depth = 0;
	struct symbolTable Table[1000];
	struct lexeme Lexeme[1000];
	void addLexeme(char key[],char value[])
	{
		strcpy(Lexeme[lexemeNo].key,key);
		strcpy(Lexeme[lexemeNo].value,value);		
		lexemeNo++;
	}
	void addSymbolTable (int lineNo,
			char symbol[50],
			void *value,
			char type[50],
			int scope)
	{
		Table[tokenNo].lineNo = lineNo;
		Table[tokenNo].scope =scope;
		Table[tokenNo].value = value;
		strcpy(Table[tokenNo].symbol,symbol);
		strcpy(Table[tokenNo].type,type);
		tokenNo++;
	}
	int findSymbolTable (int scope, char *symbol)
	{
		for (int i =0;i < tokenNo; ++i)
		{
			if(!strcmp(Table[i].symbol,symbol) && Table[i].scope == scope) return Table[i].lineNo;
		}
		return -1;
	}
	void printSymbolTable ()
	{
		printf("_________________________________________________\n");		
		printf("|LineNo |   Symbol   |   Value    | Type  | Scope\n");
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");			
		for (int i =0;i < tokenNo; ++i)
		{
			printf("| %5d | %10s | %10p | %5s | %5d \n",Table[i].lineNo,Table[i].symbol,Table[i].value,Table[i].type,Table[i].scope);
		}
	}
	void printLexeme()
	{
		for (int i =0;i < lexemeNo; ++i)
		{
			printf("< %s , %s >\n",Lexeme[i].key,Lexeme[i].value);
		}
	}
%}
%option yylineno

printBody “%d”|“%ld”|“%lld”|“%f”|“%lf”|“%s”|“%c”|“%u”|“%lu”|“%llu”


%%

\n {line_number++;}
"//".*\n {;}

[/][*][^*]*[*]+([^*/][^*]*[*]+)*[/] {}

\"[^\"{printBody}]*\" {yylval.str = strdup(yytext) ;return T_STRING;}
\"[^\"]*\" {yylval.str = strdup(yytext) ;return T_PRINT_BODY;}

\'(.|\\n)\' {yylval.str = strdup(yytext) ;return T_CHARACTER;}



"int"	{yylval.str = strdup(yytext) ;return T_TINT;}
"double"|"long"|"long long"|"float"|"char"|"long int"|"long long int"|"long float" {yylval.str = strdup(yytext) ;return T_TYPE_NAME;}
func {yylval.str = strdup(yytext) ;return T_FUNC;}
package {yylval.str = strdup(yytext) ;return T_PACKAGE;}
for	{yylval.str = strdup(yytext) ;return T_WHILE;}
switch	{yylval.str = strdup(yytext) ;return T_SWITCH;}
case	{yylval.str = strdup(yytext) ;return T_CASE;}
default	{yylval.str = strdup(yytext) ;return T_DEFAULT;}
"return" {yylval.str = strdup(yytext) ;return T_RETURN;}
break {yylval.str = strdup(yytext) ;return T_BREAK;}
fmt\.[P|p]rint {yylval.str = strdup(yytext) ;return T_PRINT;}
fmt\.[P|p]rintln {yylval.str = strdup(yytext) ;return T_PRINT;}
continue {yylval.str = strdup(yytext) ;return T_CONTINUE;}
import {yylval.str = strdup(yytext) ;return T_IMPORT;}


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

":="	{yylval.str = strdup(yytext) ;return T_ASSIGN_INITIALIZE;}
"+="|"-="|"*="|"/="|"%=" {yylval.str = strdup(yytext) ;return T_ASSIGN_OPERATOR;}

"+"|"-" {yylval.str = strdup(yytext) ;return T_F_BINARY_OPERATOR;}
"/"|"*"|"%" {yylval.str = strdup(yytext) ;return  T_S_BINARY_OPERATOR;}


[0-9]+\.[0-9]+ {yylval.str = strdup(yytext) ;return T_FLOAT;}

[0-9]+	{yylval.str = strdup(yytext) ;return T_INT;}

"," {yylval.str = strdup(yytext) ;return T_COMMA;}

\t|" "	{}



. {fromLex=0;yyerror("Invalid Syntax Panic BOis;\n");}
%%

int yywrap()
{
	return 1;
}
