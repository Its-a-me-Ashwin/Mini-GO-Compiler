# Mini-GO-Compiler
CD Project Mini GO Compiler (While and Switch statements)


## To Do
* Generate assembly code


## Dpendencies:

* Lex 2.6.4 
* Yacc 1.9 (sudo apt-get install byacc flex)
* python3
* vis.js package

## TO RUN:
### Phase 1
  * cd Mini-GO-compiler/Phase1
  * lex symbol.l
  * gcc lex.yy.c
  * ./a.out output.go
 
### Phase 2
  * cd Mini-GO-compiler/Phase2
  * chmod +x  ex.sh
  * ./ex.sh (if doesnt work  chmod +x  ex.sh)
### Phase 4
  * cd Mini-GO-compiler/Phase4
  * chmod +x  ex.sh
  * ./ex.sh (if doesnt work  chmod +x  ex.sh)
  * outputs has the AST
  * three address code in generated
### Phase 5
  * cd Mini-GO-compiler/Phase5
  * chmod +x  ex.sh
  * ./ex.sh (if doesnt work  chmod +x  ex.sh)
  * AST is found in Output Tree Floder
  * Unptimized and Optimized Three address code are generated 
  * Code Optimization techniques (Constant folding and constant propogation)
### Phase 6
  * cd Mini-GO-compiler/Phase6
  * chmod +x  ex.sh
  * ./ex.sh (if doesnt work  chmod +x  ex.sh)
  * AST is found in Output Tree Floder
  * Unptimized and Optimized Three address code are generated 
  * Code Optimization techniques (Constant folding and constant propogation)
  * Code also displays the assembly code generated (ARM based)
