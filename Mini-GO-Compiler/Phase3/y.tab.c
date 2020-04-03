/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parserpp.y" /* yacc.c:339  */

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
#include <bits/stdc++.h>

using namespace std;

#define STR(VAR) (#VAR)
#define release 1
#define MAXCHILD 10
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


struct SymbolTableTree{
	struct SymbolTableTree *child[MAXCHILD];
    string nodeType;
    string name;
    string value;
    string dataType;
    int lineNo;
    int Nchildren;
    int scope;
    int scopeChildren;
    struct SymbolTableTree *parent;
};
struct ast{
    int Nchildren;
    string str;
    ast *child[MAXCHILD];
};

map<string, SymbolTableTree> mapper;
map<string, int> mm;
// void DisplaySymbolTable(struct SymbolTableTree* node){
//     printf("%s<Tree lineNo=\"%d\" nodeType=\"%s\" name=\"%s\" value=\"%s\" dataType=\"%s\" scope=\"%d\">\n", 
//         indent,
//         node->lineNo,
//         node->nodeType.c_str(),
//         node->name.c_str(),
//         node->value.c_str(), 
//         node->dataType.c_str(),
//         node->scope);
//     int i;
//     if (node->Nchildren > 0){
//         printf("%s<Child>\n", indent);
//         incIndent();
//         for (i=0;i<node->Nchildren;i++){
//             DisplaySymbolTable(node->child[i]);
//         }
//         decIndent();
//         printf("%s</Child>\n", indent);
//     }
//     printf("%s</Tree>\n", indent);
// }

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


#line 298 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    T_INT = 258,
    T_FLOAT = 259,
    T_S_BINARY_OPERATOR = 260,
    T_F_BINARY_OPERATOR = 261,
    T_ASSIGN_OPERATOR = 262,
    T_UNARY_OPERATOR = 263,
    T_RELATIONAL_OPERATOR = 264,
    T_LOGICAL_OPERATOR = 265,
    T_COLON = 266,
    T_SEMI_COLON = 267,
    T_CLOSE_PARAN = 268,
    T_OPEN_PARAN = 269,
    T_CLOSE_SCOPE = 270,
    T_OPEN_SCOPE = 271,
    T_IDENTIFIER = 272,
    T_WHILE = 273,
    T_SWITCH = 274,
    T_CASE = 275,
    T_DEFAULT = 276,
    T_RETURN = 277,
    T_BREAK = 278,
    T_STRING = 279,
    T_CHARACTER = 280,
    T_PRINT = 281,
    T_MAIN = 282,
    T_DEF = 283,
    T_CONTINUE = 284,
    T_TYPE_NAME = 285,
    T_ASSIGN_INITIALIZE = 286,
    T_PRINT_BODY = 287,
    T_COMMA = 288,
    T_TINT = 289,
    LOL = 290
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 233 "parserpp.y" /* yacc.c:355  */

    char* str;
    struct SymbolTableTree * stt;

#line 379 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 396 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   278

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  45
/* YYNRULES -- Number of rules.  */
#define YYNRULES  85
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  146

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   290

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   298,   298,   299,   302,   306,   307,   308,   309,   310,
     311,   315,   316,   317,   318,   321,   322,   323,   324,   328,
     329,   330,   333,   336,   341,   342,   343,   346,   349,   353,
     354,   355,   359,   363,   365,   368,   369,   372,   373,   374,
     375,   378,   379,   380,   381,   382,   385,   386,   390,   391,
     392,   393,   397,   398,   399,   400,   403,   407,   408,   411,
     412,   415,   416,   420,   421,   425,   426,   429,   430,   432,
     433,   435,   436,   437,   438,   439,   440,   441,   442,   443,
     444,   445,   446,   447,   450,   452
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_INT", "T_FLOAT",
  "T_S_BINARY_OPERATOR", "T_F_BINARY_OPERATOR", "T_ASSIGN_OPERATOR",
  "T_UNARY_OPERATOR", "T_RELATIONAL_OPERATOR", "T_LOGICAL_OPERATOR",
  "T_COLON", "T_SEMI_COLON", "T_CLOSE_PARAN", "T_OPEN_PARAN",
  "T_CLOSE_SCOPE", "T_OPEN_SCOPE", "T_IDENTIFIER", "T_WHILE", "T_SWITCH",
  "T_CASE", "T_DEFAULT", "T_RETURN", "T_BREAK", "T_STRING", "T_CHARACTER",
  "T_PRINT", "T_MAIN", "T_DEF", "T_CONTINUE", "T_TYPE_NAME",
  "T_ASSIGN_INITIALIZE", "T_PRINT_BODY", "T_COMMA", "T_TINT", "LOL",
  "$accept", "CPro", "Main", "BasicScope", "Scope", "Scope2", "Scope4",
  "Scope3", "LoopScope2", "While", "Switch", "SwitchHead", "SwitchBody",
  "CaseHead", "DefaultHead", "WhileHead", "VariableDefine", "Ids",
  "Expression4", "Expression", "Operation", "Unary", "Expression3",
  "Assign", "Assign2", "Operand", "Value", "Number", "IOStatement",
  "PrintInsider", "PrintBody", "Id", "OpenParan", "CloseParan",
  "AssignInOp", "AssignOp", "SemiColon", "Colon", "Comma", "OpenScope",
  "CloseScope", "UnaryOp", "BinaryFOp", "Case", "default", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290
};
# endif

#define YYPACT_NINF -84

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-84)))

#define YYTABLE_NINF -15

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       0,    32,    61,   -84,    51,   -84,   -84,    64,   -84,    58,
     -84,   244,    75,   -84,   -84,   -84,   -84,   -84,   -84,    51,
      51,    72,   -84,    51,    77,    77,   244,    78,   -84,   -84,
      58,   180,   -84,   138,    75,   -84,   -84,   -84,   -84,   -84,
     -84,   -84,   -84,     6,    72,   -84,   244,    77,    53,   -84,
      72,    72,   -84,    30,    75,    12,    75,   -84,   -84,   -84,
      48,    72,    75,    75,   -84,   -84,   -84,   -84,   148,    72,
      72,    72,    72,   -84,   -84,   -84,    72,   -84,   -84,   -84,
     262,    90,    78,   -84,   -84,   -84,    64,    64,    64,   -84,
      71,   -84,   -84,    72,    77,   -84,   -84,   -84,   -84,   180,
     180,   -84,    72,    97,   -84,   -84,   -84,   -84,   212,   -84,
     180,   -84,   104,   104,     4,    76,   138,   -84,   -84,   244,
     -84,   -84,    75,    72,    71,   -84,   116,   212,    97,   -84,
     -84,   -84,   -84,   -84,   -84,   -84,     5,    77,   -84,   -84,
     -84,    75,    72,   -84,   -84,   -84
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     2,     0,     1,    73,     0,    74,     0,
      80,     0,     0,    65,    66,    83,    82,    77,    72,     0,
       0,     0,    64,     0,     0,     0,     0,     0,     8,     9,
       0,     0,     5,    47,     0,    42,    41,     6,    46,    43,
      61,    63,     7,    62,     0,    10,     0,     0,     0,    45,
       0,     0,    12,     0,     0,    38,     0,    11,    81,     4,
       0,     0,     0,     0,    15,    23,    24,    26,     0,     0,
       0,     0,     0,    56,    76,    75,     0,    59,    60,    52,
       0,    62,     0,    53,    55,    54,     0,     0,     0,    71,
       0,    35,    79,     0,     0,    36,    84,    85,    27,     0,
       0,    31,     0,     0,    18,    16,    17,    20,     0,    21,
       0,    25,    50,    51,    49,    48,    58,    57,    44,     0,
      34,    28,     0,     0,    39,    37,     0,     0,     0,    78,
      33,    19,    22,    13,    68,    70,     0,     0,    29,    30,
      32,     0,     0,    40,    67,    69
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -84,   -84,   -84,    -7,   -14,   -25,    -9,    82,   -84,   -84,
     -84,   -84,   -10,   -84,   -84,   -84,   -84,   -22,   -36,   -35,
     -84,   -84,    -1,    42,   -84,   -84,   -84,    73,   -84,   -84,
     -84,   -23,    80,   -57,    68,   -84,   -12,    -3,   -83,    -4,
     -16,   -26,   -84,   -84,   -84
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    64,    27,   107,   108,   109,    67,    28,
      29,    30,    98,    99,   100,    31,    32,    54,    33,    34,
      35,    36,    37,    38,    76,    39,    40,    41,    42,   136,
      90,    43,    44,     9,    77,    78,    45,   130,    94,    46,
     101,    47,    48,   102,   103
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      49,    55,    55,    56,    26,    11,    65,   123,    80,    69,
      70,    59,    57,    74,    16,    86,    87,    79,     8,    26,
      52,    81,    73,   118,    83,    85,    60,    68,     1,   120,
     121,   122,    82,   112,   113,   114,   115,    75,    92,    26,
     116,   137,    91,    75,    95,    92,    81,    81,    81,    81,
     105,   106,   111,   142,    88,    79,    13,    14,   124,     4,
     104,     5,    89,    58,   110,     6,   119,   128,    96,    97,
      18,    55,   125,    12,    10,    13,    14,     8,    15,   141,
      16,    69,    70,   131,     7,    71,     6,    17,   135,    18,
     126,   127,   132,    58,    18,   110,   110,    22,    16,    50,
      51,   131,   131,    53,    92,   133,   110,   145,   129,    69,
     134,   139,    26,    66,    55,   143,   138,    12,   117,    13,
      14,    84,    15,    93,    16,   140,     0,     0,    17,   144,
       6,    58,     0,    18,    19,    20,    96,    97,    61,    62,
       0,    22,    23,    69,    70,    63,    24,    71,    72,    12,
      25,    13,    14,     0,    15,     0,    16,     0,     0,     0,
      17,     0,     6,    58,    10,    18,    19,    20,     0,     0,
      61,    62,     0,    22,    23,     0,     0,    63,    24,     0,
       0,    12,    25,    13,    14,     0,    15,     0,    16,     0,
       0,     0,    17,     0,     6,     0,    10,    18,    19,    20,
       0,     0,    61,    62,     0,    22,    23,     0,     0,    63,
      24,     0,     0,    12,    25,    13,    14,     0,    15,     0,
      16,     0,     0,     0,    17,     0,     6,    58,     0,    18,
      19,    20,     0,     0,    61,    62,     0,    22,    23,     0,
       0,    63,    24,     0,     0,    12,    25,    13,    14,     0,
      15,     0,    16,     0,     0,     0,    17,     0,     6,   -14,
      10,    18,    19,    20,     0,     0,    21,    69,    70,    22,
      23,    71,    72,     0,    24,     8,     0,     0,    25
};

static const yytype_int16 yycheck[] =
{
      12,    24,    25,    25,    11,     9,    31,    90,    44,     5,
       6,    27,    26,     7,     8,    50,    51,    43,    13,    26,
      21,    44,    34,    80,    47,    48,    30,    31,    28,    86,
      87,    88,    46,    69,    70,    71,    72,    31,    33,    46,
      76,   124,    54,    31,    56,    33,    69,    70,    71,    72,
      62,    63,    68,   136,    24,    81,     3,     4,    93,    27,
      61,     0,    32,    15,    68,    14,    82,   102,    20,    21,
      17,    94,    94,     1,    16,     3,     4,    13,     6,   136,
       8,     5,     6,   108,     4,     9,    14,    12,   123,    17,
      99,   100,   108,    15,    17,    99,   100,    25,     8,    19,
      20,   126,   127,    23,    33,   119,   110,   142,    11,     5,
     122,   127,   119,    31,   137,   137,   126,     1,    76,     3,
       4,    48,     6,    55,     8,   128,    -1,    -1,    12,   141,
      14,    15,    -1,    17,    18,    19,    20,    21,    22,    23,
      -1,    25,    26,     5,     6,    29,    30,     9,    10,     1,
      34,     3,     4,    -1,     6,    -1,     8,    -1,    -1,    -1,
      12,    -1,    14,    15,    16,    17,    18,    19,    -1,    -1,
      22,    23,    -1,    25,    26,    -1,    -1,    29,    30,    -1,
      -1,     1,    34,     3,     4,    -1,     6,    -1,     8,    -1,
      -1,    -1,    12,    -1,    14,    -1,    16,    17,    18,    19,
      -1,    -1,    22,    23,    -1,    25,    26,    -1,    -1,    29,
      30,    -1,    -1,     1,    34,     3,     4,    -1,     6,    -1,
       8,    -1,    -1,    -1,    12,    -1,    14,    15,    -1,    17,
      18,    19,    -1,    -1,    22,    23,    -1,    25,    26,    -1,
      -1,    29,    30,    -1,    -1,     1,    34,     3,     4,    -1,
       6,    -1,     8,    -1,    -1,    -1,    12,    -1,    14,    15,
      16,    17,    18,    19,    -1,    -1,    22,     5,     6,    25,
      26,     9,    10,    -1,    30,    13,    -1,    -1,    34
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    28,    37,    38,    27,     0,    14,    68,    13,    69,
      16,    75,     1,     3,     4,     6,     8,    12,    17,    18,
      19,    22,    25,    26,    30,    34,    39,    40,    45,    46,
      47,    51,    52,    54,    55,    56,    57,    58,    59,    61,
      62,    63,    64,    67,    68,    72,    75,    77,    78,    72,
      68,    68,    58,    68,    53,    67,    53,    40,    15,    76,
      75,    22,    23,    29,    39,    41,    43,    44,    75,     5,
       6,     9,    10,    72,     7,    31,    60,    70,    71,    77,
      54,    67,    40,    67,    63,    67,    55,    55,    24,    32,
      66,    72,    33,    70,    74,    72,    20,    21,    48,    49,
      50,    76,    79,    80,    58,    72,    72,    41,    42,    43,
      75,    76,    54,    54,    54,    54,    54,    59,    69,    76,
      69,    69,    69,    74,    55,    53,    42,    42,    55,    11,
      73,    41,    76,    40,    72,    55,    65,    74,    48,    76,
      73,    69,    74,    53,    72,    55
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    36,    37,    37,    38,    39,    39,    39,    39,    39,
      39,    40,    40,    40,    40,    41,    41,    41,    41,    42,
      42,    42,    43,    44,    45,    45,    45,    46,    47,    48,
      48,    48,    49,    50,    51,    52,    52,    53,    53,    53,
      53,    54,    54,    54,    54,    54,    55,    55,    56,    56,
      56,    56,    57,    57,    57,    57,    58,    59,    59,    60,
      60,    61,    61,    62,    62,    63,    63,    64,    64,    65,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     7,     1,     1,     1,     1,     1,
       1,     2,     2,     4,     0,     1,     2,     2,     2,     2,
       1,     1,     3,     1,     2,     3,     2,     3,     4,     3,
       3,     1,     3,     2,     4,     3,     3,     3,     1,     3,
       5,     1,     1,     1,     3,     2,     1,     1,     3,     3,
       3,     3,     2,     2,     2,     2,     2,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     7,     5,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 298 "parserpp.y" /* yacc.c:1646  */
    {check((yyvsp[0].stt));typeCheck((yyvsp[0].stt));DisplaySymbolTable((yyvsp[0].stt));(yyval.stt)=(yyvsp[0].stt);(yyval.stt) -> parent = NULL;}
#line 1610 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 299 "parserpp.y" /* yacc.c:1646  */
    {yyerror("main function missing");}
#line 1616 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 302 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "Main", none, none, "int", 1, (yyvsp[-1].stt));error_taker = (yyval.stt);}
#line 1622 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 306 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = (yyvsp[0].stt);}
#line 1628 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 307 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) =  (yyvsp[0].stt);}
#line 1634 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 308 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = (yyvsp[0].stt);}
#line 1640 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 309 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = (yyvsp[0].stt);}
#line 1646 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 310 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = (yyvsp[0].stt);}
#line 1652 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 311 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "Extra_SemiColon", none, ";", none,0);error_taker = (yyval.stt);}
#line 1658 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 315 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "Main_Scope", none, none, none, 2, (yyvsp[-1].stt), (yyvsp[0].stt));error_taker = (yyval.stt);}
#line 1664 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 316 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "Main_Scope_Return", none, (yyvsp[-1].str), none, 2, makeOpNode("return", "return", yylineno), (yyvsp[0].stt));error_taker = (yyval.stt);}
#line 1670 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 317 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "ExtraScope", none, none, none, 4, (yyvsp[-3].stt), (yyvsp[-2].stt), (yyvsp[-1].stt), (yyvsp[0].stt));error_taker = (yyval.stt);}
#line 1676 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 318 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "Empty", none, none, none, 0);error_taker = (yyval.stt);}
#line 1682 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 321 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = (yyvsp[0].stt);}
#line 1688 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 322 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "Scope2_Break", none, none, none, 1,  makeOpNode("break","break", yylineno));error_taker = (yyval.stt);}
#line 1694 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 323 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "Scope2_Continue", none, none, none, 1, makeOpNode("continue","continue", yylineno));error_taker = (yyval.stt);}
#line 1700 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 324 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "Main_Scope_Return", none, (yyvsp[-1].str), none, 2, makeOpNode("return", "return", yylineno), (yyvsp[0].stt));error_taker = (yyval.stt);}
#line 1706 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 328 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "Scope4", none, none, none, 2, (yyvsp[-1].stt), (yyvsp[0].stt));error_taker = (yyval.stt);}
#line 1712 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 329 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = (yyvsp[0].stt);}
#line 1718 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 330 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = (yyvsp[0].stt);error_taker = (yyval.stt);}
#line 1724 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 333 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "Scope3", none, none, none, 3, (yyvsp[-2].stt), (yyvsp[-1].stt), (yyvsp[0].stt));error_taker = (yyval.stt);}
#line 1730 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 336 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = (yyvsp[0].stt);}
#line 1736 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 341 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "While", none, none, none, 2, (yyvsp[-1].stt), (yyvsp[0].stt));error_taker = (yyval.stt);}
#line 1742 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 342 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "While", none, none, none, 3, (yyvsp[-2].stt), (yyvsp[-1].stt), (yyvsp[0].stt));error_taker = (yyval.stt);}
#line 1748 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 343 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "While", none, none, none, 2, (yyvsp[-1].stt), (yyvsp[0].stt));error_taker = (yyval.stt);}
#line 1754 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 346 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "Switch", none, none, none, 3, (yyvsp[-2].stt), (yyvsp[-1].stt), (yyvsp[0].stt));error_taker = (yyval.stt);}
#line 1760 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 349 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "SwitchHead", none, none, none, 4, makeOpNode("SwitchKey", "switch", yylineno), (yyvsp[-2].stt), (yyvsp[-1].stt), (yyvsp[0].stt));error_taker = (yyval.stt);}
#line 1766 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 353 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "SwitchBody", none, none, none, 3, (yyvsp[-2].stt), (yyvsp[-1].stt), (yyvsp[0].stt));error_taker = (yyval.stt);}
#line 1772 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 354 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "SwitchBody", none, none, none, 3, (yyvsp[-2].stt), (yyvsp[-1].stt), (yyvsp[0].stt));error_taker = (yyval.stt);}
#line 1778 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 355 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "SwitchBody", none, none, none, 1, (yyvsp[0].stt));error_taker = (yyval.stt);}
#line 1784 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 359 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "SwitchBody", none, none, none, 3, (yyvsp[-2].stt), (yyvsp[-1].stt), (yyvsp[0].stt));error_taker = (yyval.stt);}
#line 1790 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 363 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "SwitchBody", none, none, none, 2, (yyvsp[-1].stt), (yyvsp[0].stt));error_taker = (yyval.stt);}
#line 1796 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 365 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "WhileHead", none, none, none, 4, makeOpNode("WhileKey", "while",yylineno), (yyvsp[-2].stt), (yyvsp[-1].stt), (yyvsp[0].stt));error_taker = (yyval.stt);}
#line 1802 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 368 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "VariableDefine", none, "0", (yyvsp[-2].str), 3,makeOpNodeType("TypeName", (yyvsp[-2].str), yylineno), (yyvsp[-1].stt), (yyvsp[0].stt));error_taker = (yyval.stt);}
#line 1808 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 369 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "VariableDefine", none, "0", (yyvsp[-2].str), 3, makeOpNodeType("TypeName", (yyvsp[-2].str), yylineno), (yyvsp[-1].stt), (yyvsp[0].stt)); error_taker = (yyval.stt);}
#line 1814 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 372 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "VariableDefine", none, none, none, 3, (yyvsp[-2].stt), (yyvsp[-1].stt), (yyvsp[0].stt)); error_taker = (yyval.stt);}
#line 1820 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 373 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = (yyvsp[0].stt);error_taker = (yyval.stt);}
#line 1826 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 374 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "VariableDefine", none, none, none, 3, (yyvsp[-2].stt), (yyvsp[-1].stt), (yyvsp[0].stt)); error_taker = (yyval.stt);}
#line 1832 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 375 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "VariableDefine", none, none, none, 5, (yyvsp[-4].stt), (yyvsp[-3].stt), (yyvsp[-2].stt),(yyvsp[-1].stt),(yyvsp[0].stt)); error_taker = (yyval.stt); }
#line 1838 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 378 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = (yyvsp[0].stt);}
#line 1844 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 379 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = (yyvsp[0].stt);}
#line 1850 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 380 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = (yyvsp[0].stt);}
#line 1856 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 381 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "Expression", none, none, none, 3, (yyvsp[-2].stt), (yyvsp[-1].stt), (yyvsp[0].stt));error_taker = (yyval.stt);}
#line 1862 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 382 "parserpp.y" /* yacc.c:1646  */
    {isExpError = 1;(yyval.stt) = createEntry(yylineno, "error", none, none, none, 2, makeOpNode("Error", "error", yylineno), (yyvsp[0].stt));error_taker = (yyval.stt);}
#line 1868 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 385 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt)=(yyvsp[0].stt);}
#line 1874 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 386 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt)=(yyvsp[0].stt);}
#line 1880 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 390 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "LogicalOp", none, none, none, 3, (yyvsp[-2].stt), makeOpNode("LogicalOp",(yyvsp[-1].str), yylineno), (yyvsp[0].stt));error_taker = (yyval.stt);}
#line 1886 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 391 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "RelationalOp", none, none, none, 3, (yyvsp[-2].stt), makeOpNode("RelationalOp",(yyvsp[-1].str), yylineno), (yyvsp[0].stt));error_taker = (yyval.stt);}
#line 1892 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 392 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "BinarySOp", none, none, none, 3, (yyvsp[-2].stt), makeOpNode("BinarySOp",(yyvsp[-1].str), yylineno), (yyvsp[0].stt));error_taker = (yyval.stt);}
#line 1898 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 393 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "BinaryFOp", none, none, none, 3, (yyvsp[-2].stt), makeOpNode("BinaryFOp",(yyvsp[-1].str), yylineno), (yyvsp[0].stt));error_taker = (yyval.stt);}
#line 1904 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 397 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "Unary", none, none, none, 2, (yyvsp[-1].stt), (yyvsp[0].stt));error_taker = (yyval.stt);}
#line 1910 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 398 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "Unary", none, none, none, 2, (yyvsp[-1].stt), (yyvsp[0].stt));error_taker = (yyval.stt);}
#line 1916 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 399 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "Unary", none, none, none, 2, (yyvsp[-1].stt), (yyvsp[0].stt));error_taker = (yyval.stt);}
#line 1922 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 400 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "Unary", none, none, none, 2, (yyvsp[-1].stt), (yyvsp[0].stt));error_taker = (yyval.stt);}
#line 1928 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 403 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "Expression", none, none, none, 2, (yyvsp[-1].stt), (yyvsp[0].stt));error_taker = (yyval.stt);}
#line 1934 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 407 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "Assign", none, none, none, 3, (yyvsp[-2].stt), (yyvsp[-1].stt), (yyvsp[0].stt));error_taker = (yyval.stt);}
#line 1940 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 408 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "Assign", none, none, none, 3, (yyvsp[-2].stt), (yyvsp[-1].stt), (yyvsp[0].stt));error_taker = (yyval.stt);if(((yyvsp[0].stt)->value!= none)){(yyval.stt)->value = (yyvsp[0].stt)->value;}}
#line 1946 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 411 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = (yyvsp[0].stt);}
#line 1952 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 412 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = (yyvsp[0].stt);}
#line 1958 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 415 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = (yyvsp[0].stt);}
#line 1964 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 416 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = (yyvsp[0].stt);error_taker = (yyval.stt);}
#line 1970 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 420 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = (yyvsp[0].stt);}
#line 1976 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 421 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "Value", none, (yyvsp[0].str), "char", 0);error_taker = (yyval.stt);lastChar = (yyvsp[0].str);}
#line 1982 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 425 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "Value", none, (yyvsp[0].str), "long long int", 0);error_taker = (yyval.stt);}
#line 1988 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 426 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "Value", none, (yyvsp[0].str), "double", 0);error_taker = (yyval.stt);}
#line 1994 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 429 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "Print", none, none, none, 7, makeOpNode("PrintKey", "printf", yylineno), (yyvsp[-5].stt), (yyvsp[-4].stt), (yyvsp[-3].stt), (yyvsp[-2].stt), (yyvsp[-1].stt), (yyvsp[0].stt));error_taker = (yyval.stt);}
#line 2000 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 430 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "Print", none, none, (yyvsp[-2].str), 4, makeOpNode("PrintKey", "printf", yylineno), (yyvsp[-3].stt), (yyvsp[-1].stt), (yyvsp[0].stt));error_taker = (yyval.stt);}
#line 2006 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 432 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "PrintInsider", none, none, none, 3, (yyvsp[-2].stt), (yyvsp[-1].stt), (yyvsp[0].stt));error_taker = (yyval.stt);}
#line 2012 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 433 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt)=(yyvsp[0].stt);}
#line 2018 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 435 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "PrintBody", none, (yyvsp[0].str), none, 0);error_taker = (yyval.stt);lastChar = (yyvsp[0].str);}
#line 2024 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 436 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "Identifier", (yyvsp[0].str), "0", none, 0);lastChar = (yyvsp[0].str);error_taker = (yyval.stt);}
#line 2030 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 437 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "OpenParan", none, (yyvsp[0].str), none, 0);error_taker = (yyval.stt);lastChar = (yyvsp[0].str);checkParan('(');}
#line 2036 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 438 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "CloseParan", none, (yyvsp[0].str), none, 0);error_taker = (yyval.stt);lastChar = (yyvsp[0].str);checkParan(')');}
#line 2042 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 439 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "AssignInOp", none, (yyvsp[0].str), none, 0);error_taker = (yyval.stt);lastChar = (yyvsp[0].str);}
#line 2048 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 440 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "AssignOp", none, (yyvsp[0].str), none, 0);error_taker = (yyval.stt);lastChar = (yyvsp[0].str);}
#line 2054 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 441 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "SemiColon", none, (yyvsp[0].str), none, 0);error_taker = (yyval.stt);lastChar = (yyvsp[0].str); checkParan2();}
#line 2060 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 442 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "Colon", none, (yyvsp[0].str), none, 0);error_taker = (yyval.stt);lastChar = (yyvsp[0].str);}
#line 2066 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 443 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "Comma", none, (yyvsp[0].str), none, 0);error_taker = (yyval.stt);lastChar = (yyvsp[0].str);}
#line 2072 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 444 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "OpenScope", none, (yyvsp[0].str), none, 0);checkScope('{');scope = max_scope +1;max_scope++;scopeChildren++;error_taker = (yyval.stt);lastChar = (yyvsp[0].str);checkParan2();}
#line 2078 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 445 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "CloseScope", none, (yyvsp[0].str), none, 0);checkScope('}');scope = iscopeStack;scopeChildren--;error_taker = (yyval.stt);lastChar = (yyvsp[0].str);}
#line 2084 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 446 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "UnaryOp", none, (yyvsp[0].str), none, 0);error_taker = (yyval.stt);lastChar = (yyvsp[0].str);}
#line 2090 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 447 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "BinaryFOp", none, (yyvsp[0].str), none, 0);error_taker = (yyval.stt);lastChar = (yyvsp[0].str);}
#line 2096 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 450 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "Case", none, none, (yyvsp[0].str), 0);error_taker = (yyval.stt);lastChar = (yyvsp[0].str);}
#line 2102 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 452 "parserpp.y" /* yacc.c:1646  */
    {(yyval.stt) = createEntry(yylineno, "default", none, none, (yyvsp[0].str), 0);error_taker = (yyval.stt);lastChar = (yyvsp[0].str);}
#line 2108 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2112 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 455 "parserpp.y" /* yacc.c:1906  */


//char ****c;
int *cindex;


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
            
            node->name = node->name + "#" + string(to_string(node->scope));
            mapper[node->name].value  = node->value;
            node->dataType = mapper[node->name].dataType;
            flag = 0;
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
		//printf("TRUE\n");
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
