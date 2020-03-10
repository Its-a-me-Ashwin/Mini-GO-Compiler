yacc -d -v parser.y
lex lexer.l
gcc y.tab.c lex.yy.c -o go
./go ./testCase/test1.go
./go ./testCase/test2.go
./go ./testCase/test3.go
./go ./testCase/test4.go
./go ./testCase/test5.go
./go ./testCase/test6.go

