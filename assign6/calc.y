%{
	#include<stdio.h>
%}
%token NUMBER
%left '+' '-'  
%left '*' '/'
%left '%' '(' ')'
%precedence NEG 
%%
line: stmt '\n'{
	printf("\nResult=%d\n",$$);
         return 0;
        };
stmt:NUMBER {$$=$1;}
	|stmt'+'stmt {$$=$1+$3;}
	|stmt'-'stmt {$$=$1-$3;}
	|stmt'*'stmt {$$=$1*$3;}
	|stmt'/'stmt {$$=$1/$3;}
	|stmt'%'stmt {$$=$1%$3;}
	| '-' stmt %prec NEG { $$ = -$2;}
	|'('stmt')' {$$=$2;}
	
	
;
%%
int main(){
   yyparse();
}
void yyerror(){
	printf("\nWrong input\n");
}
