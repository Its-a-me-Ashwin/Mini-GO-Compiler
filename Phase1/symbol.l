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



%%
\/\/(.*) {}; // Single line comments				
\/\*(.*\n)*.*\*\/  {} // multi line comments
\n {lineNUmber++;}
"." { 
	addLexeme("DOT",yytext);
    }
":" { 
	addLexeme("COLON",yytext);
    }
";" { 
	addLexeme("SEMI-COLON",yytext);
    }
"(" {  
	addLexeme("OPN_PAR",yytext);
    }	
")" {  
	addLexeme("COL_PAR",yytext);
    }	
"{" {  
	addLexeme("OPN_BRA",yytext); depth++;
    }	
"}" {  
	addLexeme("COL_BRA",yytext); depth--;
    }
":=" {  
	addLexeme("ASSG",yytext);
     }


break     {  addLexeme("KEY_WRD",yytext); }
default   {  addLexeme("KEY_WRD",yytext); }
func      {  addLexeme("KEY_WRD",yytext); }
interface {  addLexeme("KEY_WRD",yytext); } 
select    {  addLexeme("KEY_WRD",yytext); }
case      {  addLexeme("KEY_WRD",yytext); }
defer     {  addLexeme("KEY_WRD",yytext); }   
go        {  addLexeme("KEY_WRD",yytext); }
map       {  addLexeme("KEY_WRD",yytext); } 
struct    {  addLexeme("KEY_WRD",yytext); }
chan      {  addLexeme("KEY_WRD",yytext); }
else      {  addLexeme("KEY_WRD",yytext); }   
goto      {  addLexeme("KEY_WRD",yytext); }
package   {  addLexeme("KEY_WRD",yytext); } 
switch    {  addLexeme("KEY_WRD",yytext); }
const     {  addLexeme("KEY_WRD",yytext); }
fallthrough  {  addLexeme("KEY_WRD",yytext); }
if        {  addLexeme("KEY_WRD",yytext); }
range     {  addLexeme("KEY_WRD",yytext); }
type      {  addLexeme("KEY_WRD",yytext); }
continue  {  addLexeme("KEY_WRD",yytext); }
for       {  addLexeme("KEY_WRD",yytext); }   
import    {  addLexeme("KEY_WRD",yytext); }
return    {  addLexeme("KEY_WRD",yytext); } 
var       {  addLexeme("KEY_WRD",yytext); }
int       {  addLexeme("KEY_WRD",yytext); }
float     {  addLexeme("KEY_WRD",yytext); }
string    {  addLexeme("KEY_WRD",yytext); }
main      {  addLexeme("KEY_WRD",yytext); }



"&&"|"||"|"!" { addLexeme("LOG_OP",yytext);}
"&"|"|"|"~" { addLexeme("BIT_OP",yytext);}
"<="|">="|"=="|"!=" { addLexeme("REL_OP",yytext); } 
"<"|">" { addLexeme("REL_OP",yytext); } 
\".*\" {addLexeme("STR",yytext);}
[a-zA-Z_][A-Za-z_0-9]* { 
				addLexeme("ID",yytext); 
				if (-1 == findSymbolTable (depth,yytext))
					addSymbolTable (lineNUmber,yytext,NULL,"ID",depth);
		       }
[0-9]+.[0-9]+ { addLexeme("FLT",yytext); }
[0-9]+ { addLexeme("INT",yytext);}
"<END>" { printLexeme(); printSymbolTable();}
%%

int yywrap()
{
	return 1;
}

int main ()
{
	yyin=fopen("input.go","r");
	yyout=fopen("output.go","w");
	/*call the yylex function.*/
	yylex();
	return 0;
}
