%{
#include <stdlib.h>
#include "y.tab.h"
void yyerror(char *);
%}
%%
[a-z] {
yylval.iValue = *yytext - 'a';
return VARIABLE;
}

[1-9][0-9]* {
yylval.sIndex = atoi(yytext);
return INTEGER;
}
[-()<>+*/;{}.] {
return *yytext;
}
">=" return GE;
"<=" return LE;
= return EQ;
"!=" return NE;
"while" return WHILE;
"if" return IF;
"else" return ELSE;
":=" return ASSIGN;
[ \t\n]+ ; /* ignore whitespace */
. yyerror("Unknown character");
%%
int yywrap(void) {
return 1;
}   