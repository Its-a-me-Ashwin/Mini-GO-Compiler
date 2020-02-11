%{
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
	void printLExeme()
	{
		for (int i =0;i < lexemeNo; ++i)
		{
			printf("< %s , %s >\n",Lexeme[i].key,Lexeme[i].value);
		}
	}
%}

%%

"break" {  addLexeme("KEY_WRD",yytext);}
"while"	{  addLexeme("KEY_WRD",yytext);}
"switch" { addLexeme("KEY_WRD",yytext);}
"case"	{  addLexeme("KEY_WRD",yytext);}
"default" {  addLexeme("KEY_WRD",yytext);}
"return" {  addLexeme("KEY_WRD",yytext);}
"printf" {  addLexeme("KEY_WRD",yytext);}
"continue" { addLexeme("KEY_WRD",yytext);}
"&&"|"||"|"!" { addLexeme("LOG_OP",yytext);}
"&"|"|"|"~" { addLexeme("BIT_OP",yytext);}
"<="|">="|"=="|"!=" { addLexeme("REL_OP",yytext); } 
"<"|">" { addLexeme("REL_OP",yytext); } 
[a-zA-Z_][A-Za-z_0-9]* { addLexeme("ID",yytext);}
"<END>" { printLExeme(); }
%%

int yywrap()
{
	return 	1;
}

int main ()
{
	yylex();
}
