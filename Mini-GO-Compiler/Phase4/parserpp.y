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

#include "sttree"

#include "qicg"
using namespace std;

extern "C" {

    int yyparse();
    int yylex(void);
    void yyerror(const char *s);
    int yywrap(void);
}
//extern void yyerror(const char *); 
extern FILE *yyin;
extern FILE *yyout;
extern int yylineno;
extern int line_number;
int scope = 0;
int valid = 1;
int max_scope = 0;
string tab="  ";
string indent = "";
FILE *file;
int scope_nn = 0;
char scopeStack[1000];
char paranStack[1000];
int iparanStack = 0;
int iscopeStack = 0;
int fromLex = 1;
char lexChar[1000];
int isExpError = 0;


string none = "none";


void incIndent(){
    indent = indent + tab;
}
void decIndent(){
    indent.pop_back();
    indent.pop_back();
}

int scopeChildren = 0;




map<string, SymbolTableTree> mapper;
map<string, int> mm;
void DisplaySymbolTable(struct SymbolTableTree* node){

    if(node !=NULL){
        int nu = mm[node->nodeType]++;
        cout<<(node->nodeType+"("+to_string(nu)+")")<<"\n";
        if(node->nodeType == "Identifier"){
            cout<<("Identifier("+to_string(nu)+")`")<<(node->name + "(" + to_string(mm[node->name]++)+")")<<"\n";
        }
        else if(node->Nchildren == 0 && node->nodeType != "Empty"){
            cout<<(node->nodeType+"("+to_string(nu)+")`")<<(node->value + "(" + to_string(mm[node->value]++)+")")<<"\n";
        }
        
        else{
            if (node->Nchildren > 0){
                int i;
                
                for (i=0;i<node->Nchildren;i++){
                    cout<<(node->nodeType+"("+to_string(nu)+")`");
                    DisplaySymbolTable(node->child[i]);
                    // if(i != node->Nchildren - 1){
                    //     cout<<",";
                    // }
                }
            }
            
        }
    }
}




void PrintSymbolTable(struct SymbolTableTree* node){
    if(node!=NULL && (node->name!=none) || (node->value!=none))cout<<node->lineNo<<","<<node->nodeType<<","<<
        node->name<<","<<
        node->value<<","<< 
        node->dataType<<","<<
        node->scope<<"\n";
    int i;
    if (node->Nchildren > 0){
        for (i=0;i<node->Nchildren;i++){
            PrintSymbolTable(node->child[i]);
        }
    }
}



// void printST(map<int, map<string, SymbolTableTree>> m)
// {
//     for(auto i : m){
//         for(auto j : i.second){
//             cout<<j.second.lineNo<<","<<j.second.nodeType<<","<<
//             j.first<<","<<
//             j.second.value<<","<< 
//             j.second.dataType<<","<<
//             i.first<<"\n";
//         }
//     }
// }


void PrintSymbolT(struct SymbolTableTree* node){
    printf("lineNo,nodeType,name,value,dataType,scope\n");
    PrintSymbolTable(node);
    //printST(mapper);
}



void assignString(char *a, char *b){
    a = (char *)malloc(sizeof(b));
    strcpy(a,b);
}



struct SymbolTableTree * createEntry(int lineNo , string nodeType, string name, string value, string dataType, int Nchildren, ...){
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


struct SymbolTableTree *makeOpNode(string a, string b, int lineNo){
    return createEntry(lineNo, a, none, b, none, 0);
}
struct SymbolTableTree *makeOpNodeType(string a, string b, int lineNo){
    return createEntry(lineNo, a, none, none, b, 0);
}

struct SymbolTableTree* error_taker;
string lastChar;


int getParentScope(struct SymbolTableTree *node, int scp);
void trimLeading(char * str);
void trimLeading2(char * str);
void check3(string name, struct SymbolTableTree *node, int *flag, string& dataType);
void check2(struct SymbolTableTree*node);
void checkParan(char ttt);
void checkScope(char ttt);
void checkBrackets();
void checkParan2();
void checkScope2();
void checkSemiColon();
void check(struct SymbolTableTree*node);
void typeCheck(struct SymbolTableTree*node);
void typeCheck2(struct SymbolTableTree*node);
void check_icg(struct SymbolTableTree*node);
void printST();

%}

%union {
    char* str;
    struct SymbolTableTree * stt;
}
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
%token <str> T_DEF;


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
%right LOL;


%type<stt> CPro Main BasicScope Scope VariableDefine Expression IOStatement Scope2 Scope3 LoopScope2 Ids AssignOp AssignInOp Assign2 Expression4 error
%type<stt> While WhileHead Switch SwitchBody SwitchHead CaseHead DefaultHead OpenScope OpenParan CloseScope Expression3 PrintInsider Operation
%type<stt> CloseParan BinaryFOp Colon SemiColon Comma Case default Value Number Unary Assign Operand UnaryOp Id Scope4



%start CPro

%%




CPro:						Main {check($1);typeCheck($1);DisplaySymbolTable($1);$$=$1;$$ -> parent = NULL;check_icg($1);printST();}
                        |   {yyerror("main function missing");}


Main:						T_DEF T_MAIN OpenParan CloseParan OpenScope Scope CloseScope {$$ = createEntry(yylineno, "Main", none, none, "int", 1, $6);error_taker = $$;}



BasicScope:					VariableDefine {$$ = $1;}
						|	Expression3 {$$ =  $1;}
						|	IOStatement {$$ = $1;}
                        |   While {$$ = $1;}
                        |   Switch {$$ = $1;}
						|	SemiColon {$$ = createEntry(yylineno, "Extra_SemiColon", none, ";", none,0);error_taker = $$;}
                        


Scope:						BasicScope Scope {$$ = createEntry(yylineno, "Main_Scope", none, none, none, 2, $1, $2);error_taker = $$;}
						|	T_RETURN Expression3 {$$ = createEntry(yylineno, "Main_Scope_Return", none, $1, none, 2, makeOpNode("return", "return", yylineno), $2);error_taker = $$;}
                        |   OpenScope Scope CloseScope Scope {$$ = createEntry(yylineno, "ExtraScope", none, none, none, 4, $1, $2, $3, $4);error_taker = $$;}
                        |   {$$ = createEntry(yylineno, "Empty", none, none, none, 0);error_taker = $$;}


Scope2:						BasicScope {$$ = $1;}
						|	T_BREAK SemiColon {$$ = createEntry(yylineno, "Scope2_Break", none, none, none, 1,  makeOpNode("break","break", yylineno));error_taker = $$;}
						|	T_CONTINUE SemiColon {$$ = createEntry(yylineno, "Scope2_Continue", none, none, none, 1, makeOpNode("continue","continue", yylineno));error_taker = $$;}
                        |	T_RETURN Expression3 {$$ = createEntry(yylineno, "Main_Scope_Return", none, $1, none, 2, makeOpNode("return", "return", yylineno), $2);error_taker = $$;}
						


Scope4:						Scope4 Scope2 {$$ = createEntry(yylineno, "Scope4", none, none, none, 2, $1, $2);error_taker = $$;}
						|	Scope2 {$$ = $1;}
                        |   Scope3{$$ = $1;error_taker = $$;}


Scope3:                     OpenScope Scope4 CloseScope {$$ = createEntry(yylineno, "Scope3", none, none, none, 3, $1, $2, $3);error_taker = $$;}


LoopScope2:					Scope2 {$$ = $1;}




While:						WhileHead Scope3 {$$ = createEntry(yylineno, "While", none, none, none, 2, $1, $2);error_taker = $$;}
    					|	WhileHead OpenScope CloseScope {$$ = createEntry(yylineno, "While", none, none, none, 3, $1, $2, $3);error_taker = $$;}
						|	WhileHead LoopScope2 {$$ = createEntry(yylineno, "While", none, none, none, 2, $1, $2);error_taker = $$;}


Switch:						SwitchHead OpenScope SwitchBody {$$ = createEntry(yylineno, "Switch", none, none, none, 3, $1, $2, $3);error_taker = $$;}


SwitchHead:					T_SWITCH OpenParan Expression CloseParan {$$ = createEntry(yylineno, "SwitchHead", none, none, none, 4, makeOpNode("SwitchKey", "switch", yylineno), $2, $3, $4);error_taker = $$;}


//SwitchHead:					T_SWITCH Expression {$$ = createEntry(yylineno, "SwitchHead", none, none, none, 2, makeOpNode("SwitchKey", "switch", yylineno), $2);error_taker = $$;}




SwitchBody:					CaseHead Scope4 SwitchBody {$$ = createEntry(yylineno, "SwitchBody", none, none, none, 3, $1, $2, $3);error_taker = $$;}
						|	DefaultHead Scope4 CloseScope {$$ = createEntry(yylineno, "SwitchBody", none, none, none, 3, $1, $2, $3);error_taker = $$;}
						|	CloseScope {$$ = createEntry(yylineno, "SwitchBody", none, none, none, 1, $1);error_taker = $$;}
					


CaseHead:					Case Expression Colon {$$ = createEntry(yylineno, "SwitchBody", none, none, none, 3, $1, $2, $3);error_taker = $$;}
	


DefaultHead:				default Colon {$$ = createEntry(yylineno, "SwitchBody", none, none, none, 2, $1, $2);error_taker = $$;}

WhileHead:					T_WHILE OpenParan Expression CloseParan {$$ = createEntry(yylineno, "WhileHead", none, none, none, 4, makeOpNode("WhileKey", "while",yylineno), $2, $3, $4);error_taker = $$;}


VariableDefine:				T_TYPE_NAME Ids SemiColon {$$ = createEntry(yylineno, "VariableDefine", none, "0", $1, 3,makeOpNodeType("TypeName", $1, yylineno), $2, $3);error_taker = $$;}
						|	T_TINT Ids SemiColon {$$ = createEntry(yylineno, "VariableDefine", none, "0", $1, 3, makeOpNodeType("TypeName", $1, yylineno), $2, $3); error_taker = $$;}
                        

Ids:                        Id Comma Ids {$$ = createEntry(yylineno, "VariableDefine", none, none, none, 3, $1, $2, $3); error_taker = $$;}
                        |   Id {$$ = $1;error_taker = $$;}
                        |   Id AssignInOp Expression {$$ = createEntry(yylineno, "VariableDefine", none, none, none, 3, $1, $2, $3); error_taker = $$;}
                        |   Id AssignInOp Expression Comma Ids {$$ = createEntry(yylineno, "VariableDefine", none, none, none, 5, $1, $2, $3,$4,$5); error_taker = $$;}


Expression4:				Unary {$$ = $1;}
						|	Operation {$$ = $1;}
						|	Operand {$$ = $1;}
                        |   OpenParan Expression4 CloseParan {$$ = createEntry(yylineno, "Expression", none, none, none, 3, $1, $2, $3);error_taker = $$;}
                        |   error SemiColon {isExpError = 1;$$ = createEntry(yylineno, "error", none, none, none, 2, makeOpNode("Error", "error", yylineno), $2);error_taker = $$;}


Expression:                 Assign {$$=$1;}
                        |   Expression4 {$$=$1;}



Operation:					Expression4 T_LOGICAL_OPERATOR Expression4  {$$ = createEntry(yylineno, "LogicalOp", none, none, none, 3, $1, makeOpNode("LogicalOp",$2, yylineno), $3);error_taker = $$;}
                        |	Expression4 T_RELATIONAL_OPERATOR Expression4  {$$ = createEntry(yylineno, "RelationalOp", none, none, none, 3, $1, makeOpNode("RelationalOp",$2, yylineno), $3);error_taker = $$;} 
                        |	Expression4 T_S_BINARY_OPERATOR Expression4  {$$ = createEntry(yylineno, "BinarySOp", none, none, none, 3, $1, makeOpNode("BinarySOp",$2, yylineno), $3);error_taker = $$;}
                        |	Expression4 T_F_BINARY_OPERATOR Expression4  {$$ = createEntry(yylineno, "BinaryFOp", none, none, none, 3, $1, makeOpNode("BinaryFOp",$2, yylineno), $3);error_taker = $$;}



Unary:						Id UnaryOp {$$ = createEntry(yylineno, "Unary", none, none, none, 2, $1, $2);error_taker = $$;}
						|	UnaryOp Id {$$ = createEntry(yylineno, "Unary", none, none, none, 2, $1, $2);error_taker = $$;}
						|	BinaryFOp Id {$$ = createEntry(yylineno, "Unary", none, none, none, 2, $1, $2);error_taker = $$;}
						|	BinaryFOp Number {$$ = createEntry(yylineno, "Unary", none, none, none, 2, $1, $2);error_taker = $$;}


Expression3:                Expression SemiColon {$$ = createEntry(yylineno, "Expression", none, none, none, 2, $1, $2);error_taker = $$;}



Assign:						Id Assign2 Assign {$$ = createEntry(yylineno, "Assign", none, none, none, 3, $1, $2, $3);error_taker = $$;}
                        |   Id Assign2 Expression4 {$$ = createEntry(yylineno, "Assign", none, none, none, 3, $1, $2, $3);error_taker = $$;if(($3->value!= none)){$$->value = $3->value;}}


Assign2:                    AssignInOp {$$ = $1;}
                        |   AssignOp {$$ = $1;}


Operand:					Value {$$ = $1;}
						|	Id {$$ = $1;error_taker = $$;}



Value:						Number {$$ = $1;}
						|	T_CHARACTER {$$ = createEntry(yylineno, "Value", none, $1, "char", 0);error_taker = $$;lastChar = $1;}



Number:						T_INT {$$ = createEntry(yylineno, "Value", none, $1, "long", 0);error_taker = $$;}
						|	T_FLOAT {$$ = createEntry(yylineno, "Value", none, $1, "double", 0);error_taker = $$;}


IOStatement:				T_PRINT OpenParan T_STRING Comma PrintInsider CloseParan SemiColon {$$ = createEntry(yylineno, "Print", none, $3, none, 6, makeOpNode("PrintKey", "printf", yylineno), $2, $4, $5, $6, $7);error_taker = $$;}
                        |   T_PRINT OpenParan T_STRING CloseParan SemiColon {$$ = createEntry(yylineno, "Print", none, $3, none, 4, makeOpNode("PrintKey", "printf", yylineno), $2, $4, $5);error_taker = $$;}

PrintInsider:               PrintInsider Comma Expression {$$ = createEntry(yylineno, "PrintInsider", none, none, none, 3, $1, $2, $3);error_taker = $$;}
                        |   Expression {$$=$1;}


Id:							T_IDENTIFIER {$$ = createEntry(yylineno, "Identifier", $1, "0", none, 0);lastChar = $1;error_taker = $$;}
OpenParan:                  T_OPEN_PARAN {$$ = createEntry(yylineno, "OpenParan", none, $1, none, 0);error_taker = $$;lastChar = $1;checkParan('(');}
CloseParan:                 T_CLOSE_PARAN {$$ = createEntry(yylineno, "CloseParan", none, $1, none, 0);error_taker = $$;lastChar = $1;checkParan(')');}
AssignInOp:                 T_ASSIGN_INITIALIZE {$$ = createEntry(yylineno, "AssignInOp", none, $1, none, 0);error_taker = $$;lastChar = $1;}
AssignOp:                   T_ASSIGN_OPERATOR {$$ = createEntry(yylineno, "AssignOp", none, $1, none, 0);error_taker = $$;lastChar = $1;}
SemiColon:                  T_SEMI_COLON {$$ = createEntry(yylineno, "SemiColon", none, $1, none, 0);error_taker = $$;lastChar = $1; checkParan2();}
Colon:                      T_COLON {$$ = createEntry(yylineno, "Colon", none, $1, none, 0);error_taker = $$;lastChar = $1;}
Comma:                      T_COMMA {$$ = createEntry(yylineno, "Comma", none, $1, none, 0);error_taker = $$;lastChar = $1;}
OpenScope:                  T_OPEN_SCOPE {$$ = createEntry(yylineno, "OpenScope", none, $1, none, 0);checkScope('{');scope = max_scope +1;max_scope++;scopeChildren++;error_taker = $$;lastChar = $1;checkParan2();}
CloseScope:                 T_CLOSE_SCOPE {$$ = createEntry(yylineno, "CloseScope", none, $1, none, 0);checkScope('}');scope = iscopeStack;scopeChildren--;error_taker = $$;lastChar = $1;}
UnaryOp:					T_UNARY_OPERATOR {$$ = createEntry(yylineno, "UnaryOp", none, $1, none, 0);error_taker = $$;lastChar = $1;}
BinaryFOp:                  T_F_BINARY_OPERATOR {$$ = createEntry(yylineno, "BinaryFOp", none, $1, none, 0);error_taker = $$;lastChar = $1;}


Case:						T_CASE {$$ = createEntry(yylineno, "Case", none, none, $1, 0);error_taker = $$;lastChar = $1;}

default:					T_DEFAULT {$$ = createEntry(yylineno, "default", none, none, $1, 0);error_taker = $$;lastChar = $1;}


%%

//char ****c;
int *cindex;

//PrintBody:					T_PRINT_BODY {$$ = createEntry(yylineno, "PrintBody", none, $1, none, 0);error_taker = $$;lastChar = $1; std::cerr<<"--------------------- "<<($1)<<"--------------------\n";}
vector<vector<pair<string,string>>> c;



void typeCheck(struct SymbolTableTree*node){
    if(node != NULL){
        if(node->nodeType == "Assign" || (node->nodeType == "VariableDefine" && node->Nchildren >2 && (node->child[1]->nodeType == "AssignInOp" || node->child[1]->nodeType == "AssignOp"))){
            typeCheck2(node);
        }
        for (int i=0;i<node->Nchildren;i++){
            typeCheck(node->child[i]);
        }
    }

}


void typeCheck2(struct SymbolTableTree*node){

    list<SymbolTableTree*> q;
    set<string> a;
    string b = node->child[0]->dataType;
    //cerr<<node->child[0]->name<<"\n";
    //cerr<<mapper[node->child[0]->name].dataType<<"\n";
    q.push_back(node->child[2]);
    while(!q.empty()){
        SymbolTableTree* x = q.front();
        if(x->dataType!="none") a.insert(x->dataType);
        q.pop_front();
        for(int i = 0; i<x->Nchildren; ++i){
            q.push_back(x->child[i]);

        }
    }
    //cerr<<b<<"\n";
    auto x = a.find(b);
    if(x == a.end()){
        bool flag = false;
        if(b=="int"){

            for(auto t:a){
                    if(t.find("float")!=string::npos || t.find("double")!=string::npos){
                        flag = true;
                    }
            }
        }
        else if(b=="char"){
                for(auto t:a){
                    if(t.find("float")!=string::npos || t.find("int")!=string::npos || t.find("double")!=string::npos){
                        flag = true;
                    }
                }
        }
        if(flag){
            char dis[2000];
            int temp = 0;
            temp = node->lineNo;
            //if(isExpError)temp = yylineno;
            rewind(file);
            while(temp--) fgets(dis, 2000, file);
            trimLeading(dis);
            fprintf(stderr, "lineNo: %d|\t%s \n Warning missmatch data type for assignment \n\n", node->lineNo, dis);
        }
    }
    else{
        a.erase(x);
        if(a.size()>0){
            if(b == "int"){
                for(auto t:a){
                    if(t.find("float")!=string::npos || t.find("double")!=string::npos){
                        char dis[2000];
                        int temp = 0;
                        temp = node->lineNo;
                        //if(isExpError)temp = yylineno;
                        rewind(file);
                        while(temp--) fgets(dis, 2000, file);
                        trimLeading(dis);
                        fprintf(stderr, "lineNo: %d|\t%s \n Warning missmatch data type for assignment \n\n", node->lineNo, dis);
                        break;
                    }
                }
            }
            else if(b=="char"){
                for(auto t:a){
                    if(t.find("float")!=string::npos || t.find("int")!=string::npos || t.find("double")!=string::npos){
                        char dis[2000];
                        int temp = 0;
                        temp = node->lineNo;
                        //if(isExpError)temp = yylineno;
                        rewind(file);
                        while(temp--) fgets(dis, 2000, file);
                        trimLeading(dis);
                        fprintf(stderr, "lineNo: %d|\t%s \n Warning missmatch data type for assignment \n\n", node->lineNo, dis);
                        break;
                    }
                }
            }
        }
    }
    
}



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


// int check3(string  name, struct SymbolTableTree *node, int *flag, string &dataType){
//     for(int i = 0; i<c[node->scope].size(); ++i){
//         if((name== c[node->scope][i].first)){
//             *flag=0;
//             dataType = c[node->scope][i].second;
//         }
//     }
//     if(*flag && node->parent!=NULL) return check3(name, node->parent, flag, dataType);
//     return -> node 
// }

void check2(struct SymbolTableTree*node){
    int flag = 1;
    //printf("lol6\n");
    if(node->nodeType == "VariableDefine" && node->Nchildren >0 && node->child[0]->name != none){
        //printf("lol7\n");
        while(c.size() < node->scope+1){
            vector<pair<string, string>> temp;
            c.push_back(temp);
        }
        node->child[0]->name = node->child[0]->name +"#"+ string(to_string(node->scope));

            if(mapper.find(node->child[0]->name)!=mapper.end()){
                //printf("In Line %d \n", node->lineNo);
                line_number = node->lineNo;
                error_taker = NULL;
                lastChar = node->child[0] -> name;
                yyerror("Redecleration of variable");
                return;
            }
        if(node != NULL && node->Nchildren>1 && node->child[1]->nodeType == "AssignInOp" &&  node->child[2]->nodeType == "Value"){
            node->child[0]->value = node->child[2]->value;
        }
        //printf("lol3\n");
        struct SymbolTableTree *temp = node;
        while(temp!=NULL && temp->nodeType == "VariableDefine" && temp->child[0]->dataType == none) temp = temp->parent;
        //pair<string, string> temper;
        //printf("lol4\n");
        //cerr<<"lol ======= "<<temp->dataType<<"\n";
        node->child[0]->dataType = temp->dataType;
        // temper.first = node->name;
        // temper.second = node->dataType;
        mapper[node->child[0]->name] = *node->child[0];
        //c[node->scope].push_back(temper);
        
        //printf("lol5\n");
    }
    
    else if((node->nodeType == "Assign" || node->nodeType== "Operand") && node->Nchildren >0 && node->child[0]->name != none){
        int scopp = -1;
        if(mapper.find(node->child[0]->name + "#" + string(to_string(node->scope)))!=mapper.end()){
            flag=0;
            //node->dataType = c[node->scope][i].second;
            node->child[0]->name = node->child[0]->name + "#" + string(to_string(node->scope));
            scope = node ->scope;
        }
        
        if(flag){ 
            SymbolTableTree * temp = node;
            while(temp !=NULL && mapper.find(node->child[0]->name + "#" + string(to_string(temp->scope))) == mapper.end()) temp = temp ->parent;
            if(temp!=NULL){
                flag = 0;
                node->child[0]->name = node->child[0]->name + "#" + string(to_string(temp->scope));
                //mapper[node->child[0]->name] = *node;
            }
        }
        if(flag){
            line_number = node->lineNo;
            error_taker = NULL;
            lastChar = node ->child[0]-> name;
            yyerror("Variable not declared");
            return;
        }
        //cerr<<"Hey There "<<mapper[node->child[0]->name].dataType<<" \n";;
        node->child[0]->dataType = mapper[node->child[0]->name].dataType;
        if(node!=NULL && node->Nchildren>2 && node->child[1]->nodeType == "AssignInOp" &&  node->child[2]->nodeType == "Value"){
            node->child[0]->value = node->child[2]->value;
            mapper[node->child[0]->name].value  = node->child[0]->value;
        }
    }
    else if(node->nodeType == "Identifier" && find(node->name.begin(), node->name.end(), '#') == node->name.end()){
        if(node->parent!=NULL && node->parent->nodeType == "VariableDefine"){
            if(mapper.find(node->name + "#" + string(to_string(node->scope)))!=mapper.end()){
                node->name = node->name + "#" + string(to_string(node->scope));
                //cerr<<"------------------------------ "<<(node->name)<<" ---------------------------\n";
                mapper[node->name].value  = node->value;
                mapper[node->name].lineNo  = node->lineNo;
                auto tmpn = node->parent;
                while(tmpn -> nodeType == "VariableDefine" && tmpn->dataType==none) tmpn = tmpn -> parent;
                mapper[node->name].dataType = tmpn->dataType;
                node->dataType = mapper[node->name].dataType;
                flag = 0;
            }
            else{
                auto tmpn = node->parent;
                node->name = node->name + "#" + string(to_string(node->scope));
                while(tmpn -> nodeType == "VariableDefine" && tmpn->dataType==none) tmpn = tmpn -> parent;
                node->dataType = tmpn->dataType;
                mapper[node->name] = *node;
            }
        }
        else{
            //cerr<<"Hey There "<<(node->name)<<" \n";
            if(mapper.find(node->name + "#" + string(to_string(node->scope)))!=mapper.end()){
                flag=0;
                //node->dataType = c[node->scope][i].second;
                node->name = node->name + "#" + string(to_string(node->scope));
                node->dataType = mapper[node->name].dataType;
                scope = node ->scope;
            }
            if(flag){ 
                SymbolTableTree * temp = node;
                while(temp !=NULL && mapper.find(node->name + "#" + string(to_string(temp->scope))) == mapper.end()) temp = temp ->parent;

                if(temp!=NULL){
                    flag = 0;
                    node->name = node->name + "#" + string(to_string(temp->scope));
                    node->dataType = mapper[node->name].dataType;
                    //mapper[node->child[0]->name] = *node;
                }
            }
            if(flag){
                line_number = node->lineNo;
                error_taker = NULL;
                lastChar = node -> name;
                yyerror("Variable not declared");
                return;
            }
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
	fflush(stdout);
	fflush(stderr);
	if (iparanStack)
	{}
}

void checkParan2(){
    
    if(iparanStack){
        fflush(stdout);
        string ttt;
        char dis[2000];
        int temp = 0;
        if(error_taker){
            temp = error_taker -> lineNo;
            ttt = error_taker -> name;
        }
        else
            temp = yylineno;
        //if(isExpError)temp = yylineno;
        rewind(file);
        while(temp--) fgets(dis, 2000, file);
        trimLeading(dis);
        fprintf(stderr, "line %d : %s\nError :  MissMatch of open `(` and close `)` paran after ", yylineno, dis);cout<<lastChar<<"\n";
    }
}

void checkScope2(){
    
    if(iscopeStack){
        fflush(stdout);
        string ttt;
        char dis[2000];
        int temp = 0;
        if(error_taker){
            temp = error_taker -> lineNo;
            ttt = error_taker -> name;
        }
        else
            temp = yylineno;
        //if(isExpError)temp = yylineno;
        rewind(file);
        while(temp--) fgets(dis, 2000, file);
        trimLeading(dis);
        fprintf(stderr, "line %d : %s\nError :  MissMatch of open `{` and close `}` scope after ", yylineno, dis);cout<<lastChar<<"\n";
    }
}

void checkSemiColon(){
    
    if(iscopeStack){
        fflush(stdout);
        string ttt;
        char dis[2000];
        int temp = 0;
        if(error_taker){
            temp = error_taker -> lineNo;
            ttt = error_taker -> name;
        }
        else
            temp = yylineno;
        //if(isExpError)temp = yylineno;
        rewind(file);
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
        else if(lastChar[0] == '{' || (lastChar=="case") || ("Case"==error_taker->nodeType)){
            if((error_taker->nodeType== "Value")){fprintf(stderr, "line %d : %s\nError :  Missing ':' after ", yylineno, dis);cout<<error_taker -> value<<"\n";}
            else if (("Case"==error_taker->nodeType)) fprintf(stderr, "line %d : %s\nError :  Missing ':'\n", yylineno, dis);
            else {fprintf(stderr, "line %d : %s\nError :  Missing ':' after ", yylineno, dis);cout<<error_taker -> name<<"\n";}
        }
        else if((none!=error_taker->value)){fprintf(stderr, "line %d : %s\nError :  \';\' missing after ", yylineno, dis);cout<<lastChar<<"\n";}
        else {fprintf(stderr, "line %d : %s\nError :  \';\' missing after ", yylineno, dis);cout<<lastChar<<"\n";}
    }
}


void check(struct SymbolTableTree*node){
    //printf("lol1\n");
    check2(node);
    //printf("lol2\n");
}


void check_icg(struct SymbolTableTree*node){
    std::vector<Quadruple> &icg = get_icg(node, mapper);
	cerr<<"Oper\t|"<<"Arg1"<<"\t|Arg2"<<"\t|Result\t|"<<endl;
    for(auto t : icg){
        cerr<<(t.op)<<"\t|"<<(t.arg1)<<"\t|"<<(t.arg2)<<"\t|"<<(t.result)<<"\t|\n";
    }
}

void printST(){
    cerr<<"\n\n\n"<<("name")<<":\t"<<("nodeType")<<"\t"<<("dataType")<<"\t"<<("value")<<"\n";
    for(auto t : mapper){
        if(true)
            cerr<<(t.first)<<":\t"<<(t.second.nodeType)<<"\t"<<(t.second.dataType)<<"\t\t"<<(t.second.value)<<"\n";
        else
            cerr<<(t.first)<<":\t"<<(t.second.nodeType)<<"\t"<<(t.second.dataType)<<"\t"<<(t.second.value)<<"\n";
    }
}


extern "C" {

void yyerror(const char *s)
{
    if(iparanStack && lastChar.length()>0 && (lastChar[0] == ';' || lastChar[0] == '\'' || isalpha(lastChar[0])) && error_taker && fromLex) checkParan2();
    else if(iscopeStack && lastChar.length()>0 && lastChar[0] == ';' && error_taker && fromLex) checkScope2();
    else if(iscopeStack && lastChar.length()>0 && lastChar[0] != ';' && error_taker && fromLex) checkSemiColon();
    else if(s){
        fflush(stdout);
        string ttt;
        char dis[2000];
        int temp = 0;
        if(error_taker){
            temp = error_taker -> lineNo;
            ttt = error_taker -> name;
        }
        else
            temp = line_number;
        //if(isExpError)temp = yylineno;
        if(lastChar.length() && ((lastChar=="{") || (lastChar==";"))) {temp++; yylineno++;}
        rewind(file);
        while(temp--) fgets(dis, 2000, file);
        trimLeading(dis);
        if(lastChar.length()){
            if(strcmp(s,"ERROR: Ivalid Identifier ")==0){
                char tempstr[1000];
                strcpy(tempstr,lexChar);
                trimLeading2(tempstr);
                fprintf(stderr, "line %d : %s\n%s %s , did you mean %s\n", line_number, dis, s, lexChar, tempstr);
            }
            else if(strcmp(s,"ERROR: `none` super word")==0) fprintf(stderr, "line %d : %s\n%s\n", line_number, dis, s);
            else {fprintf(stderr, "line %d : %s\nError :  %s  ", line_number, dis, s);cout<<lastChar<<"\n";}
            valid = 0;
        }
        else{
            if(strcmp(s,"ERROR: Ivalid Identifier ")==0){
                char tempstr[1000];
                strcpy(tempstr,lexChar);
                trimLeading2(tempstr);
                fprintf(stderr, "line %d : %s\n%s %s , did you mean %s\n", line_number, dis, s, lexChar, tempstr);
            }
            else if(strcmp(s,"ERROR: `none` super word")==0) fprintf(stderr, "line %d : %s\n%s\n", line_number, dis, s);
            else if(lastChar.length()>0) {fprintf(stderr, "line %d : %s\nError :  %s -- ", line_number, dis, s); cout<<lastChar<<"\n\n";}
            else fprintf(stderr, "line %d : %s\nError :  %s\n", line_number, dis, s);
            valid = 0;
        }
    }else{
    printf("Invalid syntax at line 1\n");
    }
    
}

}
int main(int argc,char **argv)
{
    if (argc > 1)
    {
        
        file = fopen(argv[1], "r");
        if (!file)
        {
            fprintf(stderr, "No file nibba");
            exit(1);
        }
        yyin=fopen(argv[1], "r");;
    }
    else
    {
        printf("no input file\n");
        exit(1);
    }
	yyparse();
	if(valid)
	{
		;
	}
}

