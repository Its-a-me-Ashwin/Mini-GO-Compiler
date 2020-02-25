yacc -d -v parser.y
lex lexer.l
gcc y.tab.c lex.yy.c -o go
./go test.go
