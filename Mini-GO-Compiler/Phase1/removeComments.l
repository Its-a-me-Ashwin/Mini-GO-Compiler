/*Definition Section*/
%{
#include<stdio.h>
%}


/*Rule Section*/

%%
\/\/(.*) {};					
\/\*(.*\n)*.*\*\/  {};			
%%

/*call the yywrap function*/
int yywrap()
{
return 1;
}



/*Auxiliary function*/
/*Driver function*/

int main()
{
yyin=fopen("input.go","r");
yyout=fopen("output.go","w");
/*call the yylex function.*/
yylex();
return 0;
}
