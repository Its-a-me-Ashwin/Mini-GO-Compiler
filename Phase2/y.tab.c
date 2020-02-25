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


#line 124 "parser.y"
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
#line 154 "y.tab.c"

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
#define T_PACKAGE 258
#define T_INT 259
#define T_FLOAT 260
#define T_S_BINARY_OPERATOR 261
#define T_F_BINARY_OPERATOR 262
#define T_ASSIGN_OPERATOR 263
#define T_UNARY_OPERATOR 264
#define T_RELATIONAL_OPERATOR 265
#define T_LOGICAL_OPERATOR 266
#define T_COLON 267
#define T_SEMI_COLON 268
#define T_CLOSE_PARAN 269
#define T_OPEN_PARAN 270
#define T_CLOSE_SCOPE 271
#define T_OPEN_SCOPE 272
#define T_IDENTIFIER 273
#define T_WHILE 274
#define T_SWITCH 275
#define T_CASE 276
#define T_DEFAULT 277
#define T_RETURN 278
#define T_BREAK 279
#define T_STRING 280
#define T_CHARACTER 281
#define T_PRINT 282
#define T_MAIN 283
#define T_CONTINUE 284
#define T_TYPE_NAME 285
#define T_ASSIGN_INITIALIZE 286
#define T_PRINT_BODY 287
#define T_COMMA 288
#define T_TINT 289
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    1,    2,    3,    3,    3,    3,    3,    3,    4,
    4,    4,    8,    8,    8,    9,    9,   10,   16,   16,
   18,   20,   19,   19,   19,   19,   19,   21,   22,   17,
    5,    5,   11,   11,   11,   11,   15,   15,   15,   15,
    6,    6,   43,   43,   38,   38,   38,   38,   27,   39,
   39,   14,   14,   40,   40,   40,   40,   41,   41,   36,
   36,   37,   37,    7,    7,   28,   28,   23,   44,   25,
   29,   13,   12,   32,   31,   33,   24,   26,   42,   30,
   34,   35,
};
static const YYINT yylen[] = {                            2,
    3,    1,    7,    1,    1,    1,    1,    1,    1,    2,
    2,    0,    1,    2,    2,    2,    1,    1,    4,    2,
    3,    4,    3,    5,    3,    5,    1,    3,    2,    4,
    3,    3,    3,    1,    3,    5,    1,    2,    1,    3,
    1,    1,    2,    2,    2,    2,    2,    2,    2,    3,
    3,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    7,    5,    3,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,
};
static const YYINT yydefred[] = {                         0,
    0,    0,    0,    0,    1,    2,    0,   70,    0,   71,
    0,   77,    0,   62,   63,   80,   79,   74,   69,    0,
    0,    0,   61,    0,    0,    0,    0,    0,    4,    0,
    6,   42,    7,    0,    8,    0,    0,    5,    0,    9,
   58,   60,    0,   41,    0,    0,    0,    0,    0,    0,
   11,    0,    0,    0,    0,   10,   78,    3,   49,    0,
    0,   13,   18,   20,    0,    0,    0,    0,   48,   47,
   56,   57,   55,   54,   44,   43,   46,   38,   73,   72,
   53,   52,    0,   45,    0,    0,    0,   68,    0,   31,
   76,    0,    0,   32,   14,   15,   17,    0,   81,   82,
   21,    0,    0,   27,    0,    0,   40,   51,   50,   30,
   22,    0,    0,    0,   33,   16,   19,    0,    0,    0,
    0,    0,   75,   29,   65,   67,    0,    0,   23,    0,
   25,    0,   28,    0,    0,   36,    0,    0,   64,   66,
   24,   26,
};
static const YYINT yydgoto[] = {                          2,
    5,    6,   62,   28,   29,   30,   31,   97,   98,   64,
   53,   81,   82,   83,   32,   33,   34,   35,  101,   36,
  102,  103,   89,   13,   37,  104,   38,  127,   11,   39,
  124,   40,   93,  105,  106,   41,   42,   43,   44,   75,
   45,   46,   47,   48,
};
static const YYINT yysindex[] = {                      -243,
 -226,    0, -231, -221,    0,    0, -190,    0, -179,    0,
 -175,    0,  -33,    0,    0,    0,    0,    0,    0, -190,
 -190, -214,    0, -190, -180, -180,  -33, -172,    0, -167,
    0,    0,    0, -120,    0, -175, -214,    0, -178,    0,
    0,    0,  -15,    0,  -15, -180, -214, -250, -214, -214,
    0, -196, -167, -239, -167,    0,    0,    0,    0, -167,
 -167,    0,    0,    0,  -61, -260, -179, -157,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, -214,    0, -179, -179, -179,    0, -173,    0,
    0, -214, -180,    0,    0,    0,    0,  -92,    0,    0,
    0, -120, -120,    0, -214, -159,    0,    0,    0,    0,
    0, -167, -214, -173,    0,    0,    0, -148,  -61,  -92,
  -61, -159,    0,    0,    0,    0, -244, -180,    0,  -92,
    0,  -92,    0, -167, -214,    0, -260, -172,    0,    0,
    0,    0,
};
static const YYINT yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, -158,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, -158,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, -215,    0, -192,    0,    0, -228,    0,    0,
    0,    0,    0, -151,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, -228,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, -150,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,
};
static const YYINT yygindex[] = {                         0,
    0,    0,   76,   92,    0,  -41,    0,  -32,  -34,    0,
  -22,    0,   67,    0,  -18,    0,    0,    0,  -76,    0,
    0,    0,    0,  -24,  125,  -28,  102,    0,  -64,    0,
    8,  -29,  -84,    0,    0,    0,   96,    0,   55,   98,
    0,  -13,    0,  -19,
};
#define YYTABLESIZE 256
static const YYINT yytable[] = {                         58,
   59,   63,  107,   55,  113,   54,   54,   85,   86,   65,
   57,   66,   79,   17,    1,   99,  100,   68,   67,   70,
  110,  111,  112,   90,   10,   94,   77,   68,   78,  128,
   95,   96,   59,   59,   84,   80,   59,   59,   59,   59,
   59,  129,  135,   91,   14,   15,   80,   16,   91,   17,
  114,   37,   37,   37,   84,    8,    3,    4,   19,   59,
  141,    7,  134,  122,  108,  116,   23,  118,  120,  117,
  115,  126,   37,   54,   39,   39,   39,  119,  121,    8,
   14,   15,  125,   87,  130,  116,  132,  116,   27,   10,
   88,  131,   19,  140,   19,   39,   12,  116,   57,  116,
   18,  137,   27,  138,  139,  136,   17,  123,   54,  142,
   14,   15,   12,   16,   91,   17,   34,   35,   56,   18,
   92,    8,   57,   51,   19,   20,   21,   99,  100,  133,
   60,    9,   23,   24,   69,   61,   25,  109,   14,   15,
   26,   16,   76,   17,   49,   50,    0,   18,   52,    8,
    0,   12,   19,   20,   21,    0,    0,    0,   60,    0,
   23,   24,    0,   61,   25,    0,   14,   15,   26,   16,
    0,   17,    0,    0,    0,   18,    0,    8,   57,    0,
   19,   20,   21,    0,    0,    0,   60,    0,   23,   24,
    0,   61,   25,    0,    0,    0,   26,   14,   15,    0,
   16,    0,   17,    0,    0,    0,   18,    0,    8,    0,
    0,   19,   20,   21,    0,    0,    0,   60,    0,   23,
   24,    0,   61,   25,    0,   14,   15,   26,   16,    0,
   17,    0,    0,    0,   18,    0,    8,    0,    0,   19,
   20,   21,    0,    0,   22,   71,   72,   23,   24,   73,
   74,   25,    0,    0,    0,   26,
};
static const YYINT yycheck[] = {                         28,
   30,   34,   67,   26,   89,   25,   26,   49,   50,   34,
  271,   36,  263,  264,  258,  276,  277,   37,   37,   39,
   85,   86,   87,   53,  269,   55,   46,   47,   47,  114,
   60,   61,  261,  262,   48,  286,  265,  266,  267,  268,
  269,  118,  127,  288,  259,  260,  286,  262,  288,  264,
   92,  267,  268,  269,   68,  270,  283,  289,  273,  288,
  137,  283,  127,  105,   83,   98,  281,  102,  103,   98,
   93,  113,  288,   93,  267,  268,  269,  102,  103,  270,
  259,  260,  112,  280,  119,  118,  121,  120,   13,  269,
  287,  120,  273,  135,  273,  288,  272,  130,  271,  132,
  268,  130,   27,  132,  134,  128,  264,  267,  128,  138,
  259,  260,  271,  262,  288,  264,  268,  268,   27,  268,
   54,  270,  271,   22,  273,  274,  275,  276,  277,  122,
  279,    7,  281,  282,   39,  284,  285,   83,  259,  260,
  289,  262,   45,  264,   20,   21,   -1,  268,   24,  270,
   -1,  272,  273,  274,  275,   -1,   -1,   -1,  279,   -1,
  281,  282,   -1,  284,  285,   -1,  259,  260,  289,  262,
   -1,  264,   -1,   -1,   -1,  268,   -1,  270,  271,   -1,
  273,  274,  275,   -1,   -1,   -1,  279,   -1,  281,  282,
   -1,  284,  285,   -1,   -1,   -1,  289,  259,  260,   -1,
  262,   -1,  264,   -1,   -1,   -1,  268,   -1,  270,   -1,
   -1,  273,  274,  275,   -1,   -1,   -1,  279,   -1,  281,
  282,   -1,  284,  285,   -1,  259,  260,  289,  262,   -1,
  264,   -1,   -1,   -1,  268,   -1,  270,   -1,   -1,  273,
  274,  275,   -1,   -1,  278,  261,  262,  281,  282,  265,
  266,  285,   -1,   -1,   -1,  289,
};
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 289
#define YYUNDFTOKEN 336
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"T_IMPORT","T_PACKAGE","T_INT",
"T_FLOAT","T_S_BINARY_OPERATOR","T_F_BINARY_OPERATOR","T_ASSIGN_OPERATOR",
"T_UNARY_OPERATOR","T_RELATIONAL_OPERATOR","T_LOGICAL_OPERATOR","T_COLON",
"T_SEMI_COLON","T_CLOSE_PARAN","T_OPEN_PARAN","T_CLOSE_SCOPE","T_OPEN_SCOPE",
"T_IDENTIFIER","T_WHILE","T_SWITCH","T_CASE","T_DEFAULT","T_RETURN","T_BREAK",
"T_STRING","T_CHARACTER","T_PRINT","T_MAIN","T_CONTINUE","T_TYPE_NAME",
"T_ASSIGN_INITIALIZE","T_PRINT_BODY","T_COMMA","T_TINT",0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : Go",
"Go : T_PACKAGE T_MAIN Import",
"Import : Main",
"Main : T_TINT T_MAIN OpenParan CloseParan OpenScope Scope CloseScope",
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
#line 348 "parser.y"

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
            fprintf(stderr, "failed open");
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
		printf("TRUE\n");
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
#line 834 "y.tab.c"

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
case 1:
#line 193 "parser.y"
	{error_taker = yyval.stt;}
break;
case 2:
#line 197 "parser.y"
	{check(yystack.l_mark[0].stt);checkBrackets();DisplaySymbolTable(yystack.l_mark[0].stt);yyval.stt -> parent = NULL;}
break;
case 3:
#line 200 "parser.y"
	{yyval.stt = createEntry(yylineno, "Main", "none", "none", "int", 1, yystack.l_mark[-1].stt);error_taker = yyval.stt;}
break;
case 4:
#line 204 "parser.y"
	{yyval.stt = yystack.l_mark[0].stt;}
break;
case 5:
#line 205 "parser.y"
	{yyval.stt =  yystack.l_mark[0].stt;}
break;
case 6:
#line 206 "parser.y"
	{yyval.stt = yystack.l_mark[0].stt;}
break;
case 7:
#line 207 "parser.y"
	{yyval.stt = yystack.l_mark[0].stt;}
break;
case 8:
#line 208 "parser.y"
	{yyval.stt = yystack.l_mark[0].stt;}
break;
case 9:
#line 209 "parser.y"
	{yyval.stt = createEntry(yylineno, "Extra_SemiColon", "none", ";", "none",0);error_taker = yyval.stt;}
break;
case 10:
#line 212 "parser.y"
	{yyval.stt = createEntry(yylineno, "Main_Scope", "none", "none", "none", 2, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 11:
#line 213 "parser.y"
	{yyval.stt = createEntry(yylineno, "Main_Scope_Return", "none", yystack.l_mark[-1].str, "none", 1, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 12:
#line 214 "parser.y"
	{yyval.stt = createEntry(yylineno, "Main_Scope_Return", "none", "none", "none", 0);error_taker = yyval.stt;}
break;
case 13:
#line 217 "parser.y"
	{yyval.stt = yystack.l_mark[0].stt;}
break;
case 14:
#line 218 "parser.y"
	{yyval.stt = createEntry(yylineno, "Scope2_Break", "none", "none", "none", 0);error_taker = yyval.stt;}
break;
case 15:
#line 219 "parser.y"
	{yyval.stt = createEntry(yylineno, "Scope2_Continue", "none", "none", "none", 0);error_taker = yyval.stt;}
break;
case 16:
#line 223 "parser.y"
	{yyval.stt = createEntry(yylineno, "Scope3", "none", "none", "none", 2, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 17:
#line 224 "parser.y"
	{yyval.stt = yystack.l_mark[0].stt;}
break;
case 18:
#line 227 "parser.y"
	{yyval.stt = yystack.l_mark[0].stt;}
break;
case 19:
#line 232 "parser.y"
	{yyval.stt = createEntry(yylineno, "While", "none", "none", "none", 4, yystack.l_mark[-3].stt, yystack.l_mark[-2].stt, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 20:
#line 233 "parser.y"
	{yyval.stt = createEntry(yylineno, "While", "none", "none", "none", 2, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 21:
#line 236 "parser.y"
	{yyval.stt = createEntry(yylineno, "Switch", "none", "none", "none", 3, yystack.l_mark[-2].stt, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 22:
#line 239 "parser.y"
	{yyval.stt = createEntry(yylineno, "SwitchHead", "none", "none", "none", 3, yystack.l_mark[-2].stt, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 23:
#line 243 "parser.y"
	{yyval.stt = createEntry(yylineno, "SwitchBody", "none", "none", "none", 3, yystack.l_mark[-2].stt, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 24:
#line 244 "parser.y"
	{yyval.stt = createEntry(yylineno, "SwitchBody", "none", "none", "none", 5, yystack.l_mark[-4].stt, yystack.l_mark[-3].stt, yystack.l_mark[-2].stt, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 25:
#line 245 "parser.y"
	{yyval.stt = createEntry(yylineno, "SwitchBody", "none", "none", "none", 3, yystack.l_mark[-2].stt, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 26:
#line 246 "parser.y"
	{yyval.stt = createEntry(yylineno, "SwitchBody", "none", "none", "none", 5, yystack.l_mark[-4].stt, yystack.l_mark[-3].stt, yystack.l_mark[-2].stt, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 27:
#line 247 "parser.y"
	{yyval.stt = createEntry(yylineno, "SwitchBody", "none", "none", "none", 1, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 28:
#line 251 "parser.y"
	{yyval.stt = createEntry(yylineno, "SwitchBody", "none", "none", "none", 3, yystack.l_mark[-2].stt, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 29:
#line 255 "parser.y"
	{yyval.stt = createEntry(yylineno, "SwitchBody", "none", "none", "none", 2, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 30:
#line 257 "parser.y"
	{yyval.stt = createEntry(yylineno, "WhileHead", "none", "none", "none", 3, yystack.l_mark[-2].stt, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 31:
#line 260 "parser.y"
	{yyval.stt = createEntry(yylineno, "VariableDefine", "none", "0", "none", 2, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 32:
#line 261 "parser.y"
	{yyval.stt = createEntry(yylineno, "VariableDefine", "none", "0", yystack.l_mark[-2].str, 2, yystack.l_mark[-1].stt, yystack.l_mark[0].stt); error_taker = yyval.stt;}
break;
case 33:
#line 263 "parser.y"
	{yyval.stt = createEntry(yylineno, "VariableDefine", yystack.l_mark[-2].str, "none", "none", 2, yystack.l_mark[-1].stt, yystack.l_mark[0].stt); error_taker = yyval.stt;}
break;
case 34:
#line 264 "parser.y"
	{yyval.stt = createEntry(yylineno, "VariableDefine", yystack.l_mark[0].str, "none", "none", 0);error_taker = yyval.stt;}
break;
case 35:
#line 265 "parser.y"
	{yyval.stt = createEntry(yylineno, "VariableDefine", yystack.l_mark[-2].str , "none", "none", 2, yystack.l_mark[-1].stt, yystack.l_mark[0].stt); error_taker = yyval.stt;}
break;
case 36:
#line 266 "parser.y"
	{yyval.stt = createEntry(yylineno, "VariableDefine", yystack.l_mark[-4].str, "none", "none", 4, yystack.l_mark[-3].stt, yystack.l_mark[-2].stt,yystack.l_mark[-1].stt,yystack.l_mark[0].stt); error_taker = yyval.stt; }
break;
case 37:
#line 269 "parser.y"
	{yyval.stt = yystack.l_mark[0].stt;}
break;
case 38:
#line 270 "parser.y"
	{yyval.stt = createEntry(yylineno, "Expression", "none", "none", "none", 2, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 39:
#line 271 "parser.y"
	{yyval.stt = yystack.l_mark[0].stt;}
break;
case 40:
#line 272 "parser.y"
	{yyval.stt = createEntry(yylineno, "Expression", "none", "none", "none", 3, yystack.l_mark[-2].stt, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 43:
#line 280 "parser.y"
	{yyval.stt = createEntry(yylineno, "Expression", "none", "none", "none", 2, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 44:
#line 281 "parser.y"
	{yyval.stt = createEntry(yylineno, "Expression", "none", "none", "none", 2, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 45:
#line 287 "parser.y"
	{yyval.stt = createEntry(yylineno, "Unary", yystack.l_mark[-1].str, "none", "none", 1, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 46:
#line 288 "parser.y"
	{yyval.stt = createEntry(yylineno, "Unary", yystack.l_mark[0].str, "none", "none", 1, yystack.l_mark[-1].stt);error_taker = yyval.stt;}
break;
case 47:
#line 289 "parser.y"
	{yyval.stt = createEntry(yylineno, "Unary", yystack.l_mark[0].str, "none", "none", 1, yystack.l_mark[-1].stt);error_taker = yyval.stt;}
break;
case 48:
#line 290 "parser.y"
	{yyval.stt = createEntry(yylineno, "Unary", "none", "none", "none", 2, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 49:
#line 293 "parser.y"
	{yyval.stt = createEntry(yylineno, "Expression", "none", "none", "none", 2, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 50:
#line 297 "parser.y"
	{yyval.stt = createEntry(yylineno, "Assign", yystack.l_mark[-2].str, "none", "none", 2, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 51:
#line 298 "parser.y"
	{yyval.stt = createEntry(yylineno, "Assign", yystack.l_mark[-2].str, "none", "none", 2, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 52:
#line 301 "parser.y"
	{yyval.stt = yystack.l_mark[0].stt;}
break;
case 53:
#line 302 "parser.y"
	{yyval.stt = yystack.l_mark[0].stt;}
break;
case 54:
#line 304 "parser.y"
	{yyval.stt = createEntry(yylineno, "LogicalOp", "none", "none", yystack.l_mark[0].str, 0);error_taker = yyval.stt;}
break;
case 55:
#line 305 "parser.y"
	{yyval.stt = createEntry(yylineno, "RelationalOp", "none", "none", yystack.l_mark[0].str, 0);error_taker = yyval.stt;}
break;
case 56:
#line 306 "parser.y"
	{yyval.stt = createEntry(yylineno, "BinarySOp", "none", "none", yystack.l_mark[0].str, 0);error_taker = yyval.stt;}
break;
case 57:
#line 307 "parser.y"
	{yyval.stt = createEntry(yylineno, "BinaryFOp", "none", "none", yystack.l_mark[0].str, 0);error_taker = yyval.stt;}
break;
case 58:
#line 309 "parser.y"
	{yyval.stt = yystack.l_mark[0].stt;}
break;
case 59:
#line 310 "parser.y"
	{yyval.stt = createEntry(yylineno, "Operand", yystack.l_mark[0].str, "none", "none", 0);error_taker = yyval.stt;}
break;
case 60:
#line 314 "parser.y"
	{yyval.stt = yystack.l_mark[0].stt;}
break;
case 61:
#line 315 "parser.y"
	{yyval.stt = createEntry(yylineno, "Value", "none", yystack.l_mark[0].str, "char", 0);error_taker = yyval.stt;lastChar = yystack.l_mark[0].str;}
break;
case 62:
#line 318 "parser.y"
	{yyval.stt = createEntry(yylineno, "Value", "none", yystack.l_mark[0].str, "long long int", 0);error_taker = yyval.stt;}
break;
case 63:
#line 319 "parser.y"
	{yyval.stt = createEntry(yylineno, "Value", "none", yystack.l_mark[0].str, "double", 0);error_taker = yyval.stt;}
break;
case 64:
#line 322 "parser.y"
	{yyval.stt = createEntry(yylineno, "printf", "none", "none", "none", 6, yystack.l_mark[-5].stt, yystack.l_mark[-4].stt, yystack.l_mark[-3].stt, yystack.l_mark[-2].stt, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 65:
#line 323 "parser.y"
	{yyval.stt = createEntry(yylineno, "printf", "none", "none", yystack.l_mark[-2].str, 3, yystack.l_mark[-3].stt, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 66:
#line 325 "parser.y"
	{yyval.stt = createEntry(yylineno, "PrintInsider", "none", "none", "none", 3, yystack.l_mark[-2].stt, yystack.l_mark[-1].stt, yystack.l_mark[0].stt);error_taker = yyval.stt;}
break;
case 67:
#line 326 "parser.y"
	{yyval.stt=yystack.l_mark[0].stt;}
break;
case 68:
#line 328 "parser.y"
	{yyval.stt = createEntry(yylineno, "PrintBody", "none", yystack.l_mark[0].str, "none", 0);error_taker = yyval.stt;lastChar = yystack.l_mark[0].str;}
break;
case 69:
#line 329 "parser.y"
	{yyval.str = yystack.l_mark[0].str;lastChar = yystack.l_mark[0].str;}
break;
case 70:
#line 330 "parser.y"
	{yyval.stt = createEntry(yylineno, "Operand", "none", "none", yystack.l_mark[0].str, 0);error_taker = yyval.stt;lastChar = yystack.l_mark[0].str;checkParan('(');}
break;
case 71:
#line 331 "parser.y"
	{yyval.stt = createEntry(yylineno, "CloseParan", "none", "none", yystack.l_mark[0].str, 0);error_taker = yyval.stt;lastChar = yystack.l_mark[0].str;checkParan(')');}
break;
case 72:
#line 332 "parser.y"
	{yyval.stt = createEntry(yylineno, "AssignInOp", "none", "none", yystack.l_mark[0].str, 0);error_taker = yyval.stt;lastChar = yystack.l_mark[0].str;}
break;
case 73:
#line 333 "parser.y"
	{yyval.stt = createEntry(yylineno, "AssignOp", "none", "none", yystack.l_mark[0].str, 0);error_taker = yyval.stt;lastChar = yystack.l_mark[0].str;}
break;
case 74:
#line 334 "parser.y"
	{yyval.stt = createEntry(yylineno, "SemiColon", "none", "none", yystack.l_mark[0].str, 0);error_taker = yyval.stt;lastChar = yystack.l_mark[0].str; checkParan2();}
break;
case 75:
#line 335 "parser.y"
	{yyval.stt = createEntry(yylineno, "Colon", "none", "none", yystack.l_mark[0].str, 0);error_taker = yyval.stt;lastChar = yystack.l_mark[0].str;}
break;
case 76:
#line 336 "parser.y"
	{yyval.stt = createEntry(yylineno, "Comma", "none", "none", yystack.l_mark[0].str, 0);error_taker = yyval.stt;lastChar = yystack.l_mark[0].str;}
break;
case 77:
#line 337 "parser.y"
	{yyval.stt = createEntry(yylineno, "OpenScope", "none", "none", yystack.l_mark[0].str, 0);checkScope('{');scope = max_scope +1;max_scope++;scopeChildren++;error_taker = yyval.stt;lastChar = yystack.l_mark[0].str;checkParan2();}
break;
case 78:
#line 338 "parser.y"
	{yyval.stt = createEntry(yylineno, "CloseScope", "none", "none", yystack.l_mark[0].str, 0);checkScope('}');scope = iscopeStack;scopeChildren--;error_taker = yyval.stt;lastChar = yystack.l_mark[0].str;}
break;
case 79:
#line 339 "parser.y"
	{yyval.stt = createEntry(yylineno, "UnaryOp", "none", "none", yystack.l_mark[0].str, 0);error_taker = yyval.stt;lastChar = yystack.l_mark[0].str;}
break;
case 80:
#line 340 "parser.y"
	{yyval.stt = createEntry(yylineno, "BinaryFOp", "none", "none", yystack.l_mark[0].str, 0);error_taker = yyval.stt;lastChar = yystack.l_mark[0].str;}
break;
case 81:
#line 342 "parser.y"
	{yyval.stt = createEntry(yylineno, "Case", "none", "none", yystack.l_mark[0].str, 0);error_taker = yyval.stt;lastChar = yystack.l_mark[0].str;}
break;
case 82:
#line 344 "parser.y"
	{yyval.stt = createEntry(yylineno, "default", "none", "none", yystack.l_mark[0].str, 0);error_taker = yyval.stt;lastChar = yystack.l_mark[0].str;}
break;
#line 1356 "y.tab.c"
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
