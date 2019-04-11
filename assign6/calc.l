/*
6. Write a program to implement calculator using LEX and YACC.
*/

%{
#include<stdio.h>
#include "y.tab.h"
%}
%%
[0-9]* {yylval=atoi(yytext);return NUMBER;}
" " 
. {return *yytext;}
[\n] return 0;
%%


