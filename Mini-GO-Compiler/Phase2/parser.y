%{
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <sys/resource.h>
#include <errno.h>
#include <math.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <ctype.h>
#include <stdarg.h>


#define STR(VAR) (#VAR)
#define release 1
#define MAXCHILD 10

extern void yyerror(const char *); 
extern int yylex(void);
extern FILE *yyin;
extern FILE *yyout;
extern int yylineno;
extern int line_number;
int scope = 0;
int valid = 1;
int max_scope = 0;
char* tab="  ";
char indent[100]="";
FILE *file;
int scope_nn = 0;
char scopeStack[1000];
char paranStack[1000];
int iparanStack = 0;
int iscopeStack = 0;
int fromLex = 1;
char lexChar[1000];

void incIndent(){
    strcat(indent, tab);
}
void decIndent(){
    int len = strlen(indent);
    indent[len-2]='\0';
}

int scopeChildren = 0;


struct SymbolTableTree{
	struct SymbolTableTree *child[MAXCHILD];
    char* nodeType;
    char* name;
    char* value;
    char* dataType;
    int lineNo;
    int Nchildren;
    int scope;
    int scopeChildren;
    struct SymbolTableTree *parent;
};


void DisplaySymbolTable(struct SymbolTableTree* node)
{
    printf("%s<Tree lineNo=\"%d\" nodeType=\"%s\" name=\"%s\" value=\"%s\" dataType=\"%s\" scope=\"%d\">\n", 
        indent,
        node->lineNo,
        node->nodeType,
        node->name,
        node->value, 
        node->dataType,
        node->scope);
    int i;
    if (node->Nchildren > 0){
        printf("%s<Child>\n", indent);
        incIndent();
        for (i=0;i<node->Nchildren;i++){
            DisplaySymbolTable(node->child[i]);
        }
        decIndent();
        printf("%s</Child>\n", indent);
    }
    printf("%s</Tree>\n", indent);
}


void assignString(char *a, char *b){
    a = (char *)malloc(sizeof(b));
    strcpy(a,b);
}



struct SymbolTableTree * createEntry(int lineNo , char* nodeType, char* name, char* value, char* dataType, int Nchildren, ...){
    struct SymbolTableTree * node = (struct SymbolTableTree*) malloc(sizeof(struct SymbolTableTree));
    ( node->nodeType = nodeType);
    ( node->name = name);
    ( node->value = value);
    ( node->dataType = dataType);
    node->lineNo = lineNo;
    node->Nchildren = Nchildren;
    node->scope = scope;
    node->scopeChildren = scopeChildren;
    va_list ap;
    int i;
    va_start(ap, Nchildren);
    for (i=0;i<Nchildren;i++){
        node->child[i]=va_arg(ap, struct SymbolTableTree *);
        node->child[i]->parent = node;
    }
    va_end(ap);
    return node;
}


struct SymbolTableTree* error_taker;
char *lastChar;


%}

%union {
    char* str;
    struct SymbolTableTree * stt;
}
%token <str> T_IMPORT;
%token <str> T_FUNC;
%token <str> T_PACKAGE
%token <str> T_INT;
%token <str> T_FLOAT;
%token <str> T_S_BINARY_OPERATOR;
%token <str> T_F_BINARY_OPERATOR;
%token <str> T_ASSIGN_OPERATOR;
%token <str> T_UNARY_OPERATOR;
%token <str> T_RELATIONAL_OPERATOR;
%token <str> T_LOGICAL_OPERATOR;
%token <str> T_COLON;
%token <str> T_SEMI_COLON;
%token <str> T_CLOSE_PARAN;
%token <str> T_OPEN_PARAN;
%token <str> T_CLOSE_SCOPE;
%token <str> T_OPEN_SCOPE;
%token <str> T_IDENTIFIER;
%token <str> T_WHILE;
%token <str> T_SWITCH;
%token <str> T_CASE;
%token <str> T_DEFAULT;
%token <str> T_RETURN;
%token <str> T_BREAK;
%token <str> T_STRING;
%token <str> T_CHARACTER;
%token <str> T_PRINT;
%token <str> T_MAIN;
%token <str> T_CONTINUE;
%token <str> T_TYPE_NAME;
%token <str> T_ASSIGN_INITIALIZE;
%token <str> T_PRINT_BODY;
%token <str> T_COMMA
%token <str> T_TINT;


%left T_CLOSE_PARAN;
%left T_SEMI_COLON;
%left T_COLON;
%left T_COMMA;
%left T_ASSIGN_OPERATOR;
%left T_ASSIGN_INITIALIZE;
%left T_LOGICAL_OPERATOR;
%left T_RELATIONAL_OPERATOR;
%left T_F_BINARY_OPERATOR;
%left T_S_BINARY_OPERATOR;
%left T_UNARY_OPERATOR;


%type<stt> GoStart Go Import Main BasicScope Scope VariableDefine Expression IOStatement Scope2 Scope3 LoopScope2 Ids AssignOp AssignInOp Assign2 Expression4
%type<stt> While WhileHead Switch SwitchBody SwitchHead CaseHead DefaultHead PrintBody OpenScope OpenParan CloseScope Expression3 PrintInsider
%type<stt> CloseParan BinaryFOp Colon SemiColon Comma Case default Value Number Unary Assign Operator Operand UnaryOp Expression2




%type<str>   T_INT T_FLOAT T_S_BINARY_OPERATOR T_F_BINARY_OPERATOR T_ASSIGN_OPERATOR T_UNARY_OPERATOR T_RELATIONAL_OPERATOR T_LOGICAL_OPERATOR T_COLON T_SEMI_COLON T_CLOSE_PARAN T_OPEN_PARAN T_CLOSE_SCOPE T_IDENTIFIER T_WHILE T_SWITCH T_CASE T_DEFAULT T_RETURN T_BREAK T_STRING T_CHARACTER T_PRINT T_MAIN T_CONTINUE T_TYPE_NAME T_ASSIGN_INITIALIZE T_PRINT_BODY T_COMMA T_TINT Id


%start GoStart

%%
 

GoStart:					Go



Go:						T_PACKAGE T_MAIN Import



Import:						Main {check($1);checkBrackets();DisplaySymbolTable($1);$$ -> parent = NULL;}


Main:						T_FUNC T_MAIN OpenParan CloseParan OpenScope Scope CloseScope {$$ = createEntry(yylineno, "Main", "none", "none", "int", 1, $6);error_taker = $$;}



BasicScope:					VariableDefine {$$ = $1;}
						|	Expression3 {$$ =  $1;}
						|	IOStatement {$$ = $1;}
                        |   While {$$ = $1;}
                        |   Switch {$$ = $1;}
						|	SemiColon {$$ = createEntry(yylineno, "Extra_SemiColon", "none", ";", "none",0);error_taker = $$;}


Scope:						BasicScope Scope {$$ = createEntry(yylineno, "Main_Scope", "none", "none", "none", 2, $1, $2);error_taker = $$;}
						|	T_RETURN Expression3 {$$ = createEntry(yylineno, "Main_Scope_Return", "none", $1, "none", 1, $2);error_taker = $$;}
                        |   ; {$$ = createEntry(yylineno, "Main_Scope_Return", "none", "none", "none", 0);error_taker = $$;}


Scope2:						BasicScope {$$ = $1;}
						|	T_BREAK SemiColon {$$ = createEntry(yylineno, "Scope2_Break", "none", "none", "none", 0);error_taker = $$;}
						|	T_CONTINUE SemiColon {$$ = createEntry(yylineno, "Scope2_Continue", "none", "none", "none", 0);error_taker = $$;}
						


Scope3:						Scope3 Scope2 {$$ = createEntry(yylineno, "Scope3", "none", "none", "none", 2, $1, $2);error_taker = $$;}
						|	Scope2 {$$ = $1;}


LoopScope2:					Scope2 {$$ = $1;}




While:						WhileHead OpenScope Scope3 CloseScope {$$ = createEntry(yylineno, "While", "none", "none", "none", 4, $1, $2, $3, $4);error_taker = $$;}
						|	WhileHead LoopScope2 {$$ = createEntry(yylineno, "While", "none", "none", "none", 2, $1, $2);error_taker = $$;}


Switch:						SwitchHead OpenScope SwitchBody {$$ = createEntry(yylineno, "Switch", "none", "none", "none", 3, $1, $2, $3);error_taker = $$;}


SwitchHead:					T_SWITCH OpenParan Expression CloseParan {$$ = createEntry(yylineno, "SwitchHead", "none", "none", "none", 3, $2, $3, $4);error_taker = $$;}



SwitchBody:					CaseHead Scope3 SwitchBody {$$ = createEntry(yylineno, "SwitchBody", "none", "none", "none", 3, $1, $2, $3);error_taker = $$;}
						|	CaseHead OpenScope Scope3 CloseScope SwitchBody {$$ = createEntry(yylineno, "SwitchBody", "none", "none", "none", 5, $1, $2, $3, $4, $5);error_taker = $$;}
						|	DefaultHead Scope3 CloseScope {$$ = createEntry(yylineno, "SwitchBody", "none", "none", "none", 3, $1, $2, $3);error_taker = $$;}
						|	DefaultHead OpenScope Scope3 CloseScope CloseScope {$$ = createEntry(yylineno, "SwitchBody", "none", "none", "none", 5, $1, $2, $3, $4, $5);error_taker = $$;}
						|	CloseScope {$$ = createEntry(yylineno, "SwitchBody", "none", "none", "none", 1, $1);error_taker = $$;}
					


CaseHead:					Case Expression Colon {$$ = createEntry(yylineno, "SwitchBody", "none", "none", "none", 3, $1, $2, $3);error_taker = $$;}
	


DefaultHead:				default Colon {$$ = createEntry(yylineno, "SwitchBody", "none", "none", "none", 2, $1, $2);error_taker = $$;}

WhileHead:					T_WHILE OpenParan Expression CloseParan {$$ = createEntry(yylineno, "WhileHead", "none", "none", "none", 3, $2, $3, $4);error_taker = $$;}


VariableDefine:				T_TYPE_NAME Ids SemiColon {$$ = createEntry(yylineno, "VariableDefine", "none", "0", "none", 2, $2, $3);error_taker = $$;}
						|	T_TINT Ids SemiColon {$$ = createEntry(yylineno, "VariableDefine", "none", "0", $1, 2, $2, $3); error_taker = $$;}

Ids:                        Id Comma Ids {$$ = createEntry(yylineno, "VariableDefine", $1, "none", "none", 2, $2, $3); error_taker = $$;}
                        |   Id {$$ = createEntry(yylineno, "VariableDefine", $1, "none", "none", 0);error_taker = $$;}
                        |   Id AssignInOp Expression {$$ = createEntry(yylineno, "VariableDefine", $1 , "none", "none", 2, $2, $3); error_taker = $$;}
                        |   Id AssignInOp Expression Comma Ids {$$ = createEntry(yylineno, "VariableDefine", $1, "none", "none", 4, $2, $3,$4,$5); error_taker = $$; }


Expression4:				Unary {$$ = $1;}
						|	Expression2 Expression4 {$$ = createEntry(yylineno, "Expression", "none", "none", "none", 2, $1, $2);error_taker = $$;}
						|	Operand {$$ = $1;}
                        |   OpenParan Expression4 CloseParan {$$ = createEntry(yylineno, "Expression", "none", "none", "none", 3, $1, $2, $3);error_taker = $$;}


Expression:                 Assign
                        |   Expression4



Expression2:                Operand Operator {$$ = createEntry(yylineno, "Expression", "none", "none", "none", 2, $1, $2);error_taker = $$;}
                        |   Unary Operator {$$ = createEntry(yylineno, "Expression", "none", "none", "none", 2, $1, $2);error_taker = $$;}





Unary:						Id UnaryOp {$$ = createEntry(yylineno, "Unary", $1, "none", "none", 1, $2);error_taker = $$;}
						|	UnaryOp Id {$$ = createEntry(yylineno, "Unary", $2, "none", "none", 1, $1);error_taker = $$;}
						|	BinaryFOp Id {$$ = createEntry(yylineno, "Unary", $2, "none", "none", 1, $1);error_taker = $$;}
						|	BinaryFOp Number {$$ = createEntry(yylineno, "Unary", "none", "none", "none", 2, $1, $2);error_taker = $$;}


Expression3:                Expression SemiColon {$$ = createEntry(yylineno, "Expression", "none", "none", "none", 2, $1, $2);error_taker = $$;}



Assign:						Id Assign2 Assign {$$ = createEntry(yylineno, "Assign", $1, "none", "none", 2, $2, $3);error_taker = $$;}
                        |   Id Assign2 Expression4 {$$ = createEntry(yylineno, "Assign", $1, "none", "none", 2, $2, $3);error_taker = $$;}


Assign2:                    AssignInOp {$$ = $1;}
                        |   AssignOp {$$ = $1;}

Operator:					T_LOGICAL_OPERATOR {$$ = createEntry(yylineno, "LogicalOp", "none", "none", $1, 0);error_taker = $$;}
						|	T_RELATIONAL_OPERATOR {$$ = createEntry(yylineno, "RelationalOp", "none", "none", $1, 0);error_taker = $$;}
						|	T_S_BINARY_OPERATOR {$$ = createEntry(yylineno, "BinarySOp", "none", "none", $1, 0);error_taker = $$;}
						|	T_F_BINARY_OPERATOR {$$ = createEntry(yylineno, "BinaryFOp", "none", "none", $1, 0);error_taker = $$;}

Operand:					Value {$$ = $1;}
						|	Id {$$ = createEntry(yylineno, "Operand", $1, "none", "none", 0);error_taker = $$;}



Value:						Number {$$ = $1;}
						|	T_CHARACTER {$$ = createEntry(yylineno, "Value", "none", $1, "char", 0);error_taker = $$;lastChar = $1;}


Number:						T_INT {$$ = createEntry(yylineno, "Value", "none", $1, "long long int", 0);error_taker = $$;}
						|	T_FLOAT {$$ = createEntry(yylineno, "Value", "none", $1, "double", 0);error_taker = $$;}


IOStatement:				T_PRINT OpenParan PrintBody Comma PrintInsider CloseParan SemiColon {$$ = createEntry(yylineno, "printf", "none", "none", "none", 6, $2, $3, $4, $5, $6, $7);error_taker = $$;}
                        |   T_PRINT OpenParan T_STRING CloseParan SemiColon {$$ = createEntry(yylineno, "printf", "none", "none", $3, 3, $2, $4, $5);error_taker = $$;}

PrintInsider:               PrintInsider Comma Expression {$$ = createEntry(yylineno, "PrintInsider", "none", "none", "none", 3, $1, $2, $3);error_taker = $$;}
                        |   Expression {$$=$1;}

PrintBody:					T_PRINT_BODY {$$ = createEntry(yylineno, "PrintBody", "none", $1, "none", 0);error_taker = $$;lastChar = $1;}
Id:							T_IDENTIFIER {$$ = $1;lastChar = $1;}
OpenParan:                  T_OPEN_PARAN {$$ = createEntry(yylineno, "Operand", "none", "none", $1, 0);error_taker = $$;lastChar = $1;checkParan('(');}
CloseParan:                 T_CLOSE_PARAN {$$ = createEntry(yylineno, "CloseParan", "none", "none", $1, 0);error_taker = $$;lastChar = $1;checkParan(')');}
AssignInOp:                 T_ASSIGN_INITIALIZE {$$ = createEntry(yylineno, "AssignInOp", "none", "none", $1, 0);error_taker = $$;lastChar = $1;}
AssignOp:                   T_ASSIGN_OPERATOR {$$ = createEntry(yylineno, "AssignOp", "none", "none", $1, 0);error_taker = $$;lastChar = $1;}
SemiColon:                  T_SEMI_COLON {$$ = createEntry(yylineno, "SemiColon", "none", "none", $1, 0);error_taker = $$;lastChar = $1; checkParan2();}
Colon:                      T_COLON {$$ = createEntry(yylineno, "Colon", "none", "none", $1, 0);error_taker = $$;lastChar = $1;}
Comma:                      T_COMMA {$$ = createEntry(yylineno, "Comma", "none", "none", $1, 0);error_taker = $$;lastChar = $1;}
OpenScope:                  T_OPEN_SCOPE {$$ = createEntry(yylineno, "OpenScope", "none", "none", $1, 0);checkScope('{');scope = max_scope +1;max_scope++;scopeChildren++;error_taker = $$;lastChar = $1;checkParan2();}
CloseScope:                 T_CLOSE_SCOPE {$$ = createEntry(yylineno, "CloseScope", "none", "none", $1, 0);checkScope('}');scope = iscopeStack;scopeChildren--;error_taker = $$;lastChar = $1;}
UnaryOp:					T_UNARY_OPERATOR {$$ = createEntry(yylineno, "UnaryOp", "none", "none", $1, 0);error_taker = $$;lastChar = $1;}
BinaryFOp:                  T_F_BINARY_OPERATOR {$$ = createEntry(yylineno, "BinaryFOp", "none", "none", $1, 0);error_taker = $$;lastChar = $1;}

Case:						T_CASE {$$ = createEntry(yylineno, "Case", "none", "none", $1, 0);error_taker = $$;lastChar = $1;}

default:					T_DEFAULT {$$ = createEntry(yylineno, "default", "none", "none", $1, 0);error_taker = $$;lastChar = $1;}


%%

char ***c;
int *cindex;


int getParentScope(struct SymbolTableTree *node, int scp){
    if(node->parent) return node->parent ->scope+1;
    return 1;
}


void trimLeading(char * str)
{
    int index, i, j;

    index = 0;
    while(str[index] == ' ' || str[index] == '\t' || str[index] == '\n')
    {
        index++;
    }

    int n = strlen(str)-1;
    while(n>0 && str[n] == ' '){
        str[n] = '\0';
        n--;
    }
    if(index != 0)
    {
        i = 0;
        while(str[i + index] != '\0')
        {
            str[i] = str[i + index];
            i++;
        }
        str[i] = '\0';
    }
}


void trimLeading2(char * str)
{
    int index, i, j;

    index = 0;
    while(isdigit(str[index]))
    {
        index++;
    }

    int n = strlen(str)-1;
    while(n>0 && str[n] == ' '){
        str[n] = '\0';
        n--;
    }
    if(index != 0)
    {
        i = 0;
        while(str[i + index] != '\0')
        {
            str[i] = str[i + index];
            i++;
        }
        str[i] = '\0';
    }
}


void check3(char * name, struct SymbolTableTree *node, int *flag){
    for(int i = 0; i<cindex[node->scope]; ++i){
        if(strcmp(name, c[node->scope][i])==0){
            *flag=0;
        }
    }
    if(*flag && node->parent) check3(name, node->parent, flag); 
}

void check2(struct SymbolTableTree*node){
    int flag = 1;
    if(strcmp(node->nodeType, "VariableDefine")==0 && strcmp(node->name, "none")){
        for(int i = 0; i<cindex[node->scope]; ++i){
            if(strcmp(node->name, c[node->scope][i])==0){
                //printf("In Line %d \n", node->lineNo);
                line_number = node->lineNo;
                error_taker = NULL;
                lastChar = node -> name;
                yyerror("Redecleration of variable");
            }
        }
        c[node->scope][cindex[node->scope]] = node->name;
        cindex[node->scope]++;
    }
    
    else if((strcmp(node->nodeType, "Assign")==0 || strcmp(node->nodeType, "Operand")==0) && strcmp(node->name, "none")){
            check3(node->name, node -> parent, &flag);
            for(int i = 0; i<cindex[node->scope]; ++i){
                if(strcmp(node->name, c[node->scope][i])==0){
                    flag=0;
                }
            }
        if(flag){
            line_number = node->lineNo;
            error_taker = NULL;
            lastChar = node -> name;
            yyerror("Variable not declared");
        }
    }
    for(int i = 0; i<node->Nchildren; ++i){
        check2(node->child[i]);
    }
}



void checkParan(char ttt){
    if(ttt == '('){
        paranStack[iparanStack] = ttt;
        iparanStack++;
    }
    else{
        if(iparanStack && paranStack[iparanStack-1]=='('){
            iparanStack--;
        }
        else{
            yyerror("Paran MissMatch");
        }
    }
}


void checkScope(char ttt){
    if(ttt == '{'){
        scopeStack[iscopeStack] = ttt;
        iscopeStack++;
    }
    else{
        if(iscopeStack && scopeStack[iscopeStack-1]=='{'){
            iscopeStack--;
        }
        else{
            yyerror("Scope closing MissMatch");
        }
    }
}


void checkBrackets(){

}

void checkParan2(){
    
    if(iparanStack){
        fflush(stdout);
        char *ttt;
        char dis[2000];
        int temp = 0;
        if(error_taker){
            temp = error_taker -> lineNo;
            ttt = error_taker -> name;
        }
        else
            temp = yylineno;
        while(temp--) fgets(dis, 2000, file);
        trimLeading(dis);
        fprintf(stderr, "line %d : %s\nError :  MissMatch of open `(` and close `)` paran after %s\n", yylineno, dis, lastChar);
        exit(1);
    }
}

void checkScope2(){
    
    if(iscopeStack){
        fflush(stdout);
        char *ttt;
        char dis[2000];
        int temp = 0;
        if(error_taker){
            temp = error_taker -> lineNo;
            ttt = error_taker -> name;
        }
        else
            temp = yylineno;
        while(temp--) fgets(dis, 2000, file);
        trimLeading(dis);
        fprintf(stderr, "line %d : %s\nError :  MissMatch of open `{` and close `}` scope after %s\n", yylineno, dis, lastChar);
        exit(1);
    }
}

void checkSemiColon(){
    
    if(iscopeStack){
        fflush(stdout);
        char *ttt;
        char dis[2000];
        int temp = 0;
        if(error_taker){
            temp = error_taker -> lineNo;
            ttt = error_taker -> name;
        }
        else
            temp = yylineno;
        
        while(temp--) fgets(dis, 2000, file);
        trimLeading(dis);
        int itr = 0;
        int pos = 0;
        while(dis[itr] != '\0'){
            if(dis[itr] == ' ') pos = itr;
            itr++;
        }
        char lt[1000] = { '\0' };
        strcpy(lt,dis+pos);
        if(lastChar[0] == '}') fprintf(stderr, "line %d : %s\nError :  MissMatch of open `{` and close `}` scope\n", yylineno, dis);
        else if(lastChar[0] == '{' || strcmp(lastChar,"case")==0 || strcmp("Case",error_taker->nodeType)==0){
            if(strcmp(error_taker->nodeType, "Value")==0)fprintf(stderr, "line %d : %s\nError :  Missing ':' after %s\n", yylineno, dis,error_taker -> value);
            else if (strcmp("Case",error_taker->nodeType)==0) fprintf(stderr, "line %d : %s\nError :  Missing ':'\n", yylineno, dis);
            else fprintf(stderr, "line %d : %s\nError :  Missing ':' after %s\n", yylineno, dis,error_taker -> name);
        }
        else if(strcmp("none",error_taker->value))fprintf(stderr, "line %d : %s\nError :  \';\' missing after %s\n", yylineno, dis, error_taker->value);
        else fprintf(stderr, "line %d : %s\nError :  \';\' missing after %s\n", yylineno, dis, lastChar);
        exit(1);
    }
}


void check(struct SymbolTableTree*node){
    c = (char***)malloc(sizeof(char **)*(max_scope+1));
    cindex = (int *)malloc(sizeof(int)*(max_scope+1));
    for(int i = 0; i < max_scope+1; ++i) {c[i] =  (char **)malloc(sizeof(char *)*1000);cindex[i]=0;}
    check2(node);
}



void yyerror(const char *s)
{
    if(iparanStack && strlen(lastChar)>0 && (lastChar[0] == ';' || lastChar[0] == '\'' || isalpha(lastChar[0])) && error_taker && fromLex) checkParan2();
    else if(iscopeStack && strlen(lastChar)>0 && lastChar[0] == ';' && error_taker && fromLex) checkScope2();
    else if(iscopeStack && strlen(lastChar)>0 && lastChar[0] != ';' && error_taker && fromLex) checkSemiColon();
	fflush(stdout);
    char *ttt;
    char dis[2000];
    int temp = 0;
    if(error_taker){
        temp = error_taker -> lineNo;
        ttt = error_taker -> name;
    }
    else
        temp = line_number;
    if(strcmp(lastChar,"{")==0 || strcmp(lastChar,";")==0) {temp++; yylineno++;}
    
    while(temp--) fgets(dis, 2000, file);
    trimLeading(dis);
    if(strcmp(s,"ERROR: Ivalid Identifier ")==0){
        char tempstr[1000];
        strcpy(tempstr,lexChar);
        trimLeading2(tempstr);
        fprintf(stderr, "line %d : %s\n%s %s , did you mean %s\n", line_number, dis, s, lexChar, tempstr);
    }
    else if(strcmp(s,"ERROR: `none` super word")==0) fprintf(stderr, "line %d : %s\n%s\n", line_number, dis, s);
	else fprintf(stderr, "line %d : %s\nError :  %s  %s\n", line_number, dis, s, lastChar);
	valid = 0;
    exit(1);
}


int main(argc, argv)
    int argc;
    char** argv;
    {
    if (argc > 1)
    {
        
        file = fopen(argv[1], "r");
        if (!file)
        {
            fprintf(stderr, "File not present / curupted");
            exit(1);
        }
        yyin=fopen(argv[1], "r");;
        //printf("success open %s\n", argv[1]);
    }
    else
    {
        printf("no input file\n");
        exit(1);
    }
	yyparse();
	if(valid)
	{
		printf("Successufully Parsed\n");
	}
}


/*
void DisplaySymbolTable(struct SymbolTableTree* node){
    printf("%s<Tree lineNo=\"%d\" nodeType=\"%s\" name=\"%s\" value=\"%s\" dataType=\"%s\" scope=\"%d\">\n", 
        indent,
        node->lineNo,
        node->nodeType,
        node->name,
        node->value, 
        node->dataType,
        node->scope);
    int i;
    if (node->Nchildren > 0){
        printf("%s<Child>\n", indent);
        incIndent();
        for (i=0;i<node->Nchildren;i++){
            DisplaySymbolTable(node->child[i]);
        }
        decIndent();
        printf("%s</Child>\n", indent);
    }
    printf("%s</Tree>\n", indent);
}

*/
