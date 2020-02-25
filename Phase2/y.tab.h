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
extern YYSTYPE yylval;
