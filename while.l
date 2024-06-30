/*
Timothée M'BASSIDJE 12104516
Denis LINDE 12104516
*/

%{
#include <stdlib.h>
#include "master.h"
void yyerror(char *);
%}
%%
$[a-z]* {
char * varname = (char *) malloc(strlen(yytext) + 1);
strcpy(varname, yytext);
yylval.iValue = addTolistWithId(varname);
return VARIABLE;
}

[0-9] {
yylval.sIndex = atoi(yytext);
return INTEGER;
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
"then" return THEN;
"or" return OR;
"and" return AND;
"true" {
    yylval.sIndex = 1;
    return INTEGER;
}
"false" {
    yylval.sIndex = 0;
    return INTEGER;
}
[ \t\n]+ ; /* ignore whitespace */
. printf("Unknown character %s\n", yytext);
%%
int yywrap(void) {
return 1;
}   