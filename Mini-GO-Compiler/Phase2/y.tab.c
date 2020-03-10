/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20140715

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "parser.y"
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


#line 125 "parser.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
    char* str;
    struct SymbolTableTree * stt;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 155 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define T_IMPORT 257
#define T_FUNC 258
#define T_PACKAGE 259
#define T_INT 260
#define T_FLOAT 261
#define T_S_BINARY_OPERATOR 262
#define T_F_BINARY_OPERATOR 263
#define T_ASSIGN_OPERATOR 264
#define T_UNARY_OPERATOR 265
#define T_RELATIONAL_OPERATOR 266
#define T_LOGICAL_OPERATOR 267
#define T_COLON 268
#define T_SEMI_COLON 269
#define T_CLOSE_PARAN 270
#define T_OPEN_PARAN 271
#define T_CLOSE_SCOPE 272
#define T_OPEN_SCOPE 273
#define T_IDENTIFIER 274
#define T_WHILE 275
#define T_SWITCH 276
#define T_CASE 277
#define T_DEFAULT 278
#define T_RETURN 279
#define T_BREAK 280
#define T_STRING 281
#define T_CHARACTER 282
#define T_PRINT 283
#define T_MAIN 284
#define T_CONTINUE 285
#define T_TYPE_NAME 286
#define T_ASSIGN_INITIALIZE 287
#define T_PRINT_BODY 288
#define T_COMMA 289
#define T_TINT 290
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    1,    2,    3,    4,    4,    4,    4,    4,    4,
    5,    5,    5,    9,    9,    9,   10,   10,   11,   17,
   17,   19,   21,   20,   20,   20,   20,   20,   22,   23,
   18,    6,    6,   12,   12,   12,   12,   16,   16,   16,
   16,    7,    7,   44,   44,   39,   39,   39,   39,   28,
   40,   40,   15,   15,   41,   41,   41,   41,   42,   42,
   37,   37,   38,   38,    8,    8,   29,   29,   24,   45,
   26,   30,   14,   13,   33,   32,   34,   25,   27,   43,
   31,   35,   36,
};
static const YYINT yylen[] = {                            2,
    1,    3,    1,    7,    1,    1,    1,    1,    1,    1,
    2,    2,    0,    1,    2,    2,    2,    1,    1,    4,
    2,    3,    4,    3,    5,    3,    5,    1,    3,    2,
    4,    3,    3,    3,    1,    3,    5,    1,    2,    1,
    3,    1,    1,    2,    2,    2,    2,    2,    2,    2,
    3,    3,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    7,    5,    3,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,
};
static const YYINT yydefred[] = {                         0,
    0,    0,    1,    0,    0,    2,    3,    0,   71,    0,
   72,    0,   78,    0,   63,   64,   81,   80,   75,   70,
    0,    0,    0,   62,    0,    0,    0,    0,    0,    5,
    0,    7,   43,    8,    0,    9,    0,    0,    6,    0,
   10,   59,   61,    0,   42,    0,    0,    0,    0,    0,
    0,   12,    0,    0,    0,    0,   11,   79,    4,   50,
    0,    0,   14,   19,   21,    0,    0,    0,    0,   49,
   48,   57,   58,   56,   55,   45,   44,   47,   39,   74,
   73,   54,   53,    0,   46,    0,    0,    0,   69,    0,
   32,   77,    0,    0,   33,   15,   16,   18,    0,   82,
   83,   22,    0,    0,   28,    0,    0,   41,   52,   51,
   31,   23,    0,    0,    0,   34,   17,   20,    0,    0,
    0,    0,    0,   76,   30,   66,   68,    0,    0,   24,
    0,   26,    0,   29,    0,    0,   37,    0,    0,   65,
   67,   25,   27,
};
static const YYINT yydgoto[] = {                          2,
    3,    6,    7,   63,   29,   30,   31,   32,   98,   99,
   65,   54,   82,   83,   84,   33,   34,   35,   36,  102,
   37,  103,  104,   90,   14,   38,  105,   39,  128,   12,
   40,  125,   41,   94,  106,  107,   42,   43,   44,   45,
   76,   46,   47,   48,   49,
};
static const YYINT yysindex[] = {                      -244,
 -227,    0,    0, -200, -222,    0,    0, -191,    0, -180,
    0, -176,    0,  -34,    0,    0,    0,    0,    0,    0,
 -191, -191, -215,    0, -191, -181, -181,  -34, -173,    0,
 -168,    0,    0,    0, -121,    0, -176, -215,    0, -179,
    0,    0,    0,  -16,    0,  -16, -181, -215, -251, -215,
 -215,    0, -197, -168, -240, -168,    0,    0,    0,    0,
 -168, -168,    0,    0,    0,  -62, -261, -180, -158,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, -215,    0, -180, -180, -180,    0, -174,
    0,    0, -215, -181,    0,    0,    0,    0,  -93,    0,
    0,    0, -121, -121,    0, -215, -160,    0,    0,    0,
    0,    0, -168, -215, -174,    0,    0,    0, -149,  -62,
  -93,  -62, -160,    0,    0,    0,    0, -245, -181,    0,
  -93,    0,  -93,    0, -168, -215,    0, -261, -173,    0,
    0,    0,    0,
};
static const YYINT yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, -159,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, -159,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, -216,    0, -193,    0,    0, -229,    0,
    0,    0,    0,    0, -152,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, -229,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, -151,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,
};
static const YYINT yygindex[] = {                         0,
    0,    0,    0,   75,   91,    0,  -42,    0,  -33,  -35,
    0,  -23,    0,   66,    0,  -19,    0,    0,    0,  -77,
    0,    0,    0,    0,  -25,  124,  -29,  101,    0,  -65,
    0,    7,  -30,  -85,    0,    0,    0,   95,    0,   54,
   97,    0,  -14,    0,  -20,
};
#define YYTABLESIZE 256
static const YYINT yytable[] = {                         59,
   60,   64,  108,   56,  114,   55,   55,   86,   87,   66,
   58,   67,   80,   18,    1,  100,  101,   69,   68,   71,
  111,  112,  113,   91,   11,   95,   78,   69,   79,  129,
   96,   97,   60,   60,   85,   81,   60,   60,   60,   60,
   60,  130,  136,   92,   15,   16,   81,   17,   92,   18,
  115,   38,   38,   38,   85,    9,    4,    5,   20,   60,
  142,    8,  135,  123,  109,  117,   24,  119,  121,  118,
  116,  127,   38,   55,   40,   40,   40,  120,  122,    9,
   15,   16,  126,   88,  131,  117,  133,  117,   28,   11,
   89,  132,   20,  141,   20,   40,   13,  117,   58,  117,
   19,  138,   28,  139,  140,  137,   18,  124,   55,  143,
   15,   16,   13,   17,   92,   18,   35,   36,   57,   19,
   93,    9,   58,   52,   20,   21,   22,  100,  101,  134,
   61,   10,   24,   25,   70,   62,   26,  110,   15,   16,
   27,   17,   77,   18,   50,   51,    0,   19,   53,    9,
    0,   13,   20,   21,   22,    0,    0,    0,   61,    0,
   24,   25,    0,   62,   26,    0,   15,   16,   27,   17,
    0,   18,    0,    0,    0,   19,    0,    9,   58,    0,
   20,   21,   22,    0,    0,    0,   61,    0,   24,   25,
    0,   62,   26,    0,    0,    0,   27,   15,   16,    0,
   17,    0,   18,    0,    0,    0,   19,    0,    9,    0,
    0,   20,   21,   22,    0,    0,    0,   61,    0,   24,
   25,    0,   62,   26,    0,   15,   16,   27,   17,    0,
   18,    0,    0,    0,   19,    0,    9,    0,    0,   20,
   21,   22,    0,    0,   23,   72,   73,   24,   25,   74,
   75,   26,    0,    0,    0,   27,
};
static const YYINT yycheck[] = {                         29,
   31,   35,   68,   27,   90,   26,   27,   50,   51,   35,
  272,   37,  264,  265,  259,  277,  278,   38,   38,   40,
   86,   87,   88,   54,  270,   56,   47,   48,   48,  115,
   61,   62,  262,  263,   49,  287,  266,  267,  268,  269,
  270,  119,  128,  289,  260,  261,  287,  263,  289,  265,
   93,  268,  269,  270,   69,  271,  284,  258,  274,  289,
  138,  284,  128,  106,   84,   99,  282,  103,  104,   99,
   94,  114,  289,   94,  268,  269,  270,  103,  104,  271,
  260,  261,  113,  281,  120,  119,  122,  121,   14,  270,
  288,  121,  274,  136,  274,  289,  273,  131,  272,  133,
  269,  131,   28,  133,  135,  129,  265,  268,  129,  139,
  260,  261,  272,  263,  289,  265,  269,  269,   28,  269,
   55,  271,  272,   23,  274,  275,  276,  277,  278,  123,
  280,    8,  282,  283,   40,  285,  286,   84,  260,  261,
  290,  263,   46,  265,   21,   22,   -1,  269,   25,  271,
   -1,  273,  274,  275,  276,   -1,   -1,   -1,  280,   -1,
  282,  283,   -1,  285,  286,   -1,  260,  261,  290,  263,
   -1,  265,   -1,   -1,   -1,  269,   -1,  271,  272,   -1,
  274,  275,  276,   -1,   -1,   -1,  280,   -1,  282,  283,
   -1,  285,  286,   -1,   -1,   -1,  290,  260,  261,   -1,
  263,   -1,  265,   -1,   -1,   -1,  269,   -1,  271,   -1,
   -1,  274,  275,  276,   -1,   -1,   -1,  280,   -1,  282,
  283,   -1,  285,  286,   -1,  260,  261,  290,  263,   -1,
  265,   -1,   -1,   -1,  269,   -1,  271,   -1,   -1,  274,
  275,  276,   -1,   -1,  279,  262,  263,  282,  283,  266,
  267,  286,   -1,   -1,   -1,  290,
};
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 290
#define YYUNDFTOKEN 338
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"T_IMPORT","T_FUNC","T_PACKAGE",
"T_INT","T_FLOAT","T_S_BINARY_OPERATOR","T_F_BINARY_OPERATOR",
"T_ASSIGN_OPERATOR","T_UNARY_OPERATOR","T_RELATIONAL_OPERATOR",
"T_LOGICAL_OPERATOR","T_COLON","T_SEMI_COLON","T_CLOSE_PARAN","T_OPEN_PARAN",
"T_CLOSE_SCOPE","T_OPEN_SCOPE","T_IDENTIFIER","T_WHILE","T_SWITCH","T_CASE",
"T_DEFAULT","T_RETURN","T_BREAK","T_STRING","T_CHARACTER","T_PRINT","T_MAIN",
"T_CONTINUE","T_TYPE_NAME","T_ASSIGN_INITIALIZE","T_PRINT_BODY","T_COMMA",
"T_TINT",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : GoStart",
"GoStart : Go",
"Go : T_PACKAGE T_MAIN Import",
"Import : Main",
"Main : T_FUNC T_MAIN OpenParan CloseParan OpenScope Scope CloseScope",
"BasicScope : VariableDefine",
"BasicScope : Expression3",
"BasicScope : IOStatement",
"BasicScope : While",
"BasicScope : Switch",
"BasicScope : SemiColon",
"Scope : BasicScope Scope",
"Scope : T_RETURN Expression3",
"Scope :",
"Scope2 : BasicScope",
"Scope2 : T_BREAK SemiColon",
"Scope2 : T_CONTINUE SemiColon",
"Scope3 : Scope3 Scope2",
"Scope3 : Scope2",
"LoopScope2 : Scope2",
"While : WhileHead OpenScope Scope3 CloseScope",
"While : WhileHead LoopScope2",
"Switch : SwitchHead OpenScope SwitchBody",
"SwitchHead : T_SWITCH OpenParan Expression CloseParan",
"SwitchBody : CaseHead Scope3 SwitchBody",
"SwitchBody : CaseHead OpenScope Scope3 CloseScope SwitchBody",
"SwitchBody : DefaultHead Scope3 CloseScope",
"SwitchBody : DefaultHead OpenScope Scope3 CloseScope CloseScope",
"SwitchBody : CloseScope",
"CaseHead : Case Expression Colon",
"DefaultHead : default Colon",
"WhileHead : T_WHILE OpenParan Expression CloseParan",
"VariableDefine : T_TYPE_NAME Ids SemiColon",
"VariableDefine : T_TINT Ids SemiColon",
"Ids : Id Comma Ids",
"Ids : Id",
"Ids : Id AssignInOp Expression",
"Ids : Id AssignInOp Expression Comma Ids",
"Expression4 : Unary",
"Expression4 : Expression2 Expression4",
"Expression4 : Operand",
"Expression4 : OpenParan Expression4 CloseParan",
"Expression : Assign",
"Expression : Expression4",
"Expression2 : Operand Operator",
"Expression2 : Unary Operator",
"Unary : Id UnaryOp",
"Unary : UnaryOp Id",
"Unary : BinaryFOp Id",
"Unary : BinaryFOp Number",
"Expression3 : Expression SemiColon",
"Assign : Id Assign2 Assign",
"Assign : Id Assign2 Expression4",
"Assign2 : AssignInOp",
"Assign2 : AssignOp",
"Operator : T_LOGICAL_OPERATOR",
"Operator : T_RELATIONAL_OPERATOR",
"Operator : T_S_BINARY_OPERATOR",
"Operator : T_F_BINARY_OPERATOR",
"Operand : Value",
"Operand : Id",
"Value : Number",
"Value : T_CHARACTER",
"Number : T_INT",
"Number : T_FLOAT",
"IOStatement : T_PRINT OpenParan PrintBody Comma PrintInsider CloseParan SemiColon",
"IOStatement : T_PRINT OpenParan T_STRING CloseParan SemiColon",
"PrintInsider : PrintInsider Comma Expression",
"PrintInsider : Expression",
"PrintBody : T_PRINT_BODY",
"Id : T_IDENTIFIER",
"OpenParan : T_OPEN_PARAN",
"CloseParan : T_CLOSE_PARAN",
"AssignInOp : T_ASSIGN_INITIALIZE",
"AssignOp : T_ASSIGN_OPERATOR",
"SemiColon : T_SEMI_COLON",
"Colon : T_COLON",
"Comma : T_COMMA",
"OpenScope : T_OPEN_SCOPE",
"CloseScope : T_CLOSE_SCOPE",
"UnaryOp : T_UNARY_OPERATOR",
"BinaryFOp : T_F_BINARY_OPERATOR",
"Case : T_CASE",
"default : T_DEFAULT",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 352 "parser.y"

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
#line 837 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    YYERROR_CALL("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 3:
#line 201 "parser.y"
	{check(yystack.l_mark[0].stt);checkBrackets();DisplaySymbolTable(yystack.l_mark[0].stt);yyval.stt -> parent = NULL;}
break;
case 4:
#line 204 "parser.y"
	{yyval.stt = createEntry(yylineno, "Main", "none", "none", "int", 1, yystack.l_mark[-1].stt);error_taker = yyval.stt;}
break;
case 5:
#line 208 "parser.y"
	{yyval.stt = yystack.l_mark[0].stt;}
break;
case 6:
#line 209 "parser.y"
	{yyval.stt =  yystack.l_mark[0].stt;}
break;
case 7:
#line 210 "parser.y"
	{yyval.stt = yystack.l_mark[0].stt;}
break;
case 8:
#line 211 "parser.y"
	{yyval.stt = yystack.l_mark[0].stt;}
break;
case 9:
#line 212 "parser.y"
	{yyval.stt = yystack.l_mark[0].stt;}
break;
case 10:
#line 213 "parser.y"
	{yyval.stt = createEntry(yylineno, "Extra_SemiColon", "none", ";", "none",0);error_taker = yyval.stt;}
break;
case 11:
#line 216 "parser.y"
	{yyval.stt = createEntry(yylineno, "Main_Scope", "none", "none", "none", 2, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 12:
#line 217 "parser.y"
	{yyval.stt = createEntry(yylineno, "Main_Scope_Return", "none", yystack.l_mark[-1].str, "none", 1, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 13:
#line 218 "parser.y"
	{yyval.stt = createEntry(yylineno, "Main_Scope_Return", "none", "none", "none", 0);error_taker = yyval.stt;}
break;
case 14:
#line 221 "parser.y"
	{yyval.stt = yystack.l_mark[0].stt;}
break;
case 15:
#line 222 "parser.y"
	{yyval.stt = createEntry(yylineno, "Scope2_Break", "none", "none", "none", 0);error_taker = yyval.stt;}
break;
case 16:
#line 223 "parser.y"
	{yyval.stt = createEntry(yylineno, "Scope2_Continue", "none", "none", "none", 0);error_taker = yyval.stt;}
break;
case 17:
#line 227 "parser.y"
	{yyval.stt = createEntry(yylineno, "Scope3", "none", "none", "none", 2, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 18:
#line 228 "parser.y"
	{yyval.stt = yystack.l_mark[0].stt;}
break;
case 19:
#line 231 "parser.y"
	{yyval.stt = yystack.l_mark[0].stt;}
break;
case 20:
#line 236 "parser.y"
	{yyval.stt = createEntry(yylineno, "While", "none", "none", "none", 4, yystack.l_mark[-3].stt, yystack.l_mark[-2].stt, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 21:
#line 237 "parser.y"
	{yyval.stt = createEntry(yylineno, "While", "none", "none", "none", 2, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 22:
#line 240 "parser.y"
	{yyval.stt = createEntry(yylineno, "Switch", "none", "none", "none", 3, yystack.l_mark[-2].stt, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 23:
#line 243 "parser.y"
	{yyval.stt = createEntry(yylineno, "SwitchHead", "none", "none", "none", 3, yystack.l_mark[-2].stt, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 24:
#line 247 "parser.y"
	{yyval.stt = createEntry(yylineno, "SwitchBody", "none", "none", "none", 3, yystack.l_mark[-2].stt, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 25:
#line 248 "parser.y"
	{yyval.stt = createEntry(yylineno, "SwitchBody", "none", "none", "none", 5, yystack.l_mark[-4].stt, yystack.l_mark[-3].stt, yystack.l_mark[-2].stt, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 26:
#line 249 "parser.y"
	{yyval.stt = createEntry(yylineno, "SwitchBody", "none", "none", "none", 3, yystack.l_mark[-2].stt, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 27:
#line 250 "parser.y"
	{yyval.stt = createEntry(yylineno, "SwitchBody", "none", "none", "none", 5, yystack.l_mark[-4].stt, yystack.l_mark[-3].stt, yystack.l_mark[-2].stt, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 28:
#line 251 "parser.y"
	{yyval.stt = createEntry(yylineno, "SwitchBody", "none", "none", "none", 1, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 29:
#line 255 "parser.y"
	{yyval.stt = createEntry(yylineno, "SwitchBody", "none", "none", "none", 3, yystack.l_mark[-2].stt, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 30:
#line 259 "parser.y"
	{yyval.stt = createEntry(yylineno, "SwitchBody", "none", "none", "none", 2, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 31:
#line 261 "parser.y"
	{yyval.stt = createEntry(yylineno, "WhileHead", "none", "none", "none", 3, yystack.l_mark[-2].stt, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 32:
#line 264 "parser.y"
	{yyval.stt = createEntry(yylineno, "VariableDefine", "none", "0", "none", 2, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 33:
#line 265 "parser.y"
	{yyval.stt = createEntry(yylineno, "VariableDefine", "none", "0", yystack.l_mark[-2].str, 2, yystack.l_mark[-1].stt, yystack.l_mark[0].stt); error_taker = yyval.stt;}
break;
case 34:
#line 267 "parser.y"
	{yyval.stt = createEntry(yylineno, "VariableDefine", yystack.l_mark[-2].str, "none", "none", 2, yystack.l_mark[-1].stt, yystack.l_mark[0].stt); error_taker = yyval.stt;}
break;
case 35:
#line 268 "parser.y"
	{yyval.stt = createEntry(yylineno, "VariableDefine", yystack.l_mark[0].str, "none", "none", 0);error_taker = yyval.stt;}
break;
case 36:
#line 269 "parser.y"
	{yyval.stt = createEntry(yylineno, "VariableDefine", yystack.l_mark[-2].str , "none", "none", 2, yystack.l_mark[-1].stt, yystack.l_mark[0].stt); error_taker = yyval.stt;}
break;
case 37:
#line 270 "parser.y"
	{yyval.stt = createEntry(yylineno, "VariableDefine", yystack.l_mark[-4].str, "none", "none", 4, yystack.l_mark[-3].stt, yystack.l_mark[-2].stt,yystack.l_mark[-1].stt,yystack.l_mark[0].stt); error_taker = yyval.stt; }
break;
case 38:
#line 273 "parser.y"
	{yyval.stt = yystack.l_mark[0].stt;}
break;
case 39:
#line 274 "parser.y"
	{yyval.stt = createEntry(yylineno, "Expression", "none", "none", "none", 2, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 40:
#line 275 "parser.y"
	{yyval.stt = yystack.l_mark[0].stt;}
break;
case 41:
#line 276 "parser.y"
	{yyval.stt = createEntry(yylineno, "Expression", "none", "none", "none", 3, yystack.l_mark[-2].stt, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 44:
#line 284 "parser.y"
	{yyval.stt = createEntry(yylineno, "Expression", "none", "none", "none", 2, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 45:
#line 285 "parser.y"
	{yyval.stt = createEntry(yylineno, "Expression", "none", "none", "none", 2, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 46:
#line 291 "parser.y"
	{yyval.stt = createEntry(yylineno, "Unary", yystack.l_mark[-1].str, "none", "none", 1, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 47:
#line 292 "parser.y"
	{yyval.stt = createEntry(yylineno, "Unary", yystack.l_mark[0].str, "none", "none", 1, yystack.l_mark[-1].stt);error_taker = yyval.stt;}
break;
case 48:
#line 293 "parser.y"
	{yyval.stt = createEntry(yylineno, "Unary", yystack.l_mark[0].str, "none", "none", 1, yystack.l_mark[-1].stt);error_taker = yyval.stt;}
break;
case 49:
#line 294 "parser.y"
	{yyval.stt = createEntry(yylineno, "Unary", "none", "none", "none", 2, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 50:
#line 297 "parser.y"
	{yyval.stt = createEntry(yylineno, "Expression", "none", "none", "none", 2, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 51:
#line 301 "parser.y"
	{yyval.stt = createEntry(yylineno, "Assign", yystack.l_mark[-2].str, "none", "none", 2, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 52:
#line 302 "parser.y"
	{yyval.stt = createEntry(yylineno, "Assign", yystack.l_mark[-2].str, "none", "none", 2, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 53:
#line 305 "parser.y"
	{yyval.stt = yystack.l_mark[0].stt;}
break;
case 54:
#line 306 "parser.y"
	{yyval.stt = yystack.l_mark[0].stt;}
break;
case 55:
#line 308 "parser.y"
	{yyval.stt = createEntry(yylineno, "LogicalOp", "none", "none", yystack.l_mark[0].str, 0);error_taker = yyval.stt;}
break;
case 56:
#line 309 "parser.y"
	{yyval.stt = createEntry(yylineno, "RelationalOp", "none", "none", yystack.l_mark[0].str, 0);error_taker = yyval.stt;}
break;
case 57:
#line 310 "parser.y"
	{yyval.stt = createEntry(yylineno, "BinarySOp", "none", "none", yystack.l_mark[0].str, 0);error_taker = yyval.stt;}
break;
case 58:
#line 311 "parser.y"
	{yyval.stt = createEntry(yylineno, "BinaryFOp", "none", "none", yystack.l_mark[0].str, 0);error_taker = yyval.stt;}
break;
case 59:
#line 313 "parser.y"
	{yyval.stt = yystack.l_mark[0].stt;}
break;
case 60:
#line 314 "parser.y"
	{yyval.stt = createEntry(yylineno, "Operand", yystack.l_mark[0].str, "none", "none", 0);error_taker = yyval.stt;}
break;
case 61:
#line 318 "parser.y"
	{yyval.stt = yystack.l_mark[0].stt;}
break;
case 62:
#line 319 "parser.y"
	{yyval.stt = createEntry(yylineno, "Value", "none", yystack.l_mark[0].str, "char", 0);error_taker = yyval.stt;lastChar = yystack.l_mark[0].str;}
break;
case 63:
#line 322 "parser.y"
	{yyval.stt = createEntry(yylineno, "Value", "none", yystack.l_mark[0].str, "long long int", 0);error_taker = yyval.stt;}
break;
case 64:
#line 323 "parser.y"
	{yyval.stt = createEntry(yylineno, "Value", "none", yystack.l_mark[0].str, "double", 0);error_taker = yyval.stt;}
break;
case 65:
#line 326 "parser.y"
	{yyval.stt = createEntry(yylineno, "printf", "none", "none", "none", 6, yystack.l_mark[-5].stt, yystack.l_mark[-4].stt, yystack.l_mark[-3].stt, yystack.l_mark[-2].stt, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 66:
#line 327 "parser.y"
	{yyval.stt = createEntry(yylineno, "printf", "none", "none", yystack.l_mark[-2].str, 3, yystack.l_mark[-3].stt, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 67:
#line 329 "parser.y"
	{yyval.stt = createEntry(yylineno, "PrintInsider", "none", "none", "none", 3, yystack.l_mark[-2].stt, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 68:
#line 330 "parser.y"
	{yyval.stt=yystack.l_mark[0].stt;}
break;
case 69:
#line 332 "parser.y"
	{yyval.stt = createEntry(yylineno, "PrintBody", "none", yystack.l_mark[0].str, "none", 0);error_taker = yyval.stt;lastChar = yystack.l_mark[0].str;}
break;
case 70:
#line 333 "parser.y"
	{yyval.str = yystack.l_mark[0].str;lastChar = yystack.l_mark[0].str;}
break;
case 71:
#line 334 "parser.y"
	{yyval.stt = createEntry(yylineno, "Operand", "none", "none", yystack.l_mark[0].str, 0);error_taker = yyval.stt;lastChar = yystack.l_mark[0].str;checkParan('(');}
break;
case 72:
#line 335 "parser.y"
	{yyval.stt = createEntry(yylineno, "CloseParan", "none", "none", yystack.l_mark[0].str, 0);error_taker = yyval.stt;lastChar = yystack.l_mark[0].str;checkParan(')');}
break;
case 73:
#line 336 "parser.y"
	{yyval.stt = createEntry(yylineno, "AssignInOp", "none", "none", yystack.l_mark[0].str, 0);error_taker = yyval.stt;lastChar = yystack.l_mark[0].str;}
break;
case 74:
#line 337 "parser.y"
	{yyval.stt = createEntry(yylineno, "AssignOp", "none", "none", yystack.l_mark[0].str, 0);error_taker = yyval.stt;lastChar = yystack.l_mark[0].str;}
break;
case 75:
#line 338 "parser.y"
	{yyval.stt = createEntry(yylineno, "SemiColon", "none", "none", yystack.l_mark[0].str, 0);error_taker = yyval.stt;lastChar = yystack.l_mark[0].str; checkParan2();}
break;
case 76:
#line 339 "parser.y"
	{yyval.stt = createEntry(yylineno, "Colon", "none", "none", yystack.l_mark[0].str, 0);error_taker = yyval.stt;lastChar = yystack.l_mark[0].str;}
break;
case 77:
#line 340 "parser.y"
	{yyval.stt = createEntry(yylineno, "Comma", "none", "none", yystack.l_mark[0].str, 0);error_taker = yyval.stt;lastChar = yystack.l_mark[0].str;}
break;
case 78:
#line 341 "parser.y"
	{yyval.stt = createEntry(yylineno, "OpenScope", "none", "none", yystack.l_mark[0].str, 0);checkScope('{');scope = max_scope +1;max_scope++;scopeChildren++;error_taker = yyval.stt;lastChar = yystack.l_mark[0].str;checkParan2();}
break;
case 79:
#line 342 "parser.y"
	{yyval.stt = createEntry(yylineno, "CloseScope", "none", "none", yystack.l_mark[0].str, 0);checkScope('}');scope = iscopeStack;scopeChildren--;error_taker = yyval.stt;lastChar = yystack.l_mark[0].str;}
break;
case 80:
#line 343 "parser.y"
	{yyval.stt = createEntry(yylineno, "UnaryOp", "none", "none", yystack.l_mark[0].str, 0);error_taker = yyval.stt;lastChar = yystack.l_mark[0].str;}
break;
case 81:
#line 344 "parser.y"
	{yyval.stt = createEntry(yylineno, "BinaryFOp", "none", "none", yystack.l_mark[0].str, 0);error_taker = yyval.stt;lastChar = yystack.l_mark[0].str;}
break;
case 82:
#line 346 "parser.y"
	{yyval.stt = createEntry(yylineno, "Case", "none", "none", yystack.l_mark[0].str, 0);error_taker = yyval.stt;lastChar = yystack.l_mark[0].str;}
break;
case 83:
#line 348 "parser.y"
	{yyval.stt = createEntry(yylineno, "default", "none", "none", yystack.l_mark[0].str, 0);error_taker = yyval.stt;lastChar = yystack.l_mark[0].str;}
break;
#line 1355 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                yys = yyname[YYTRANSLATE(yychar)];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
