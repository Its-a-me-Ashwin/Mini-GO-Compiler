%{
    #include<stdio.h>
%}

start \/\*
end \*\/

%%

    \/\/\ (.)* ;


%%

int main(int k,char **argcv) 
{ 
    yyin=fopen(argcv[1],"r"); 
    yyout=fopen("out.c","w"); 
    yylex(); 
    return 0; 
} 