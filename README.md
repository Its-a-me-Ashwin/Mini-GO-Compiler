# Mini-GO-Compiler
CD Project


## To Do
* Add sumbol Table
* Make syntax tree more redable
* Change the grammar

## Dpendencies:

Lex 2.6.4 ,Yacc 1.9 (sudo apt-get install byacc flex)

## TO RUN:
* Phase 1
  * cd Mini-GO-compiler/Phase1
  * lex symbol.l
  * gcc lex.yy.c
  * ./a.out output.go
* Phase 2
  * cd Mini-GO-compiler/Phase2
  * chmod +x  ex.sh
  * ./ex.sh (if doesnt work  chmod +x  ex.sh)
* Phase 4
  * cd Mini-GO-compiler/Phase4
  * chmod +x  ex.sh
  * ./ex.sh (if doesnt work  chmod +x  ex.sh)
  * outputs has the AST
  * three address code in generated
