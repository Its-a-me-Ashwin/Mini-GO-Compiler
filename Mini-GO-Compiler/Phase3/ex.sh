bison -d -v -b y parserpp.y 
flex lexer.l
g++ y.tab.c lex.yy.c 
rm lex.yy.c
rm y.tab.h
rm y.tab.c
rm y.output
name=$1
if [[ -n "$name" ]]; then
    ./a.out "Test/$name" > out.txt
    python lol.py
    eog "OutputTree/tree.png" &
    # rm out.txt
    rm a.out
    # sleep 10 
    # rm "OutputTree/tree.png"
else
    echo "argument error"
fi