%{
#include <stdio.h>
#include <stdlib.h>
#include "master.h"
%}

%union {
    int iValue; /* integer value */
    int sIndex; /* symbol table index */
    nodeType *nPtr; /* node pointer */
};

%token <iValue> INTEGER
%token <sIndex> VARIABLE
%token WHILE IF PRINT ELSE
%left IF ELSE
%left GE LE EQ NE '>' '<' ';'
%left '+' '-'
%left '*' '/'
%left ASSIGN

%type <nPtr> statement expr stmt_list


%{
void yyerror(char *);
int yylex(void);
int booleanValue = 1;
int sym[26];
%}
%%
program:
program statement '.' {ex($2); printf("program terminer"); }
|
;
statement:
expr { $$ = $1; }
| statement ';' statement {$$  = $1; $$ = $3;}
| IF '(' expr ')' statement ELSE statement {$$ = opr(IF,3,$3,$5,$7);}
|'{' stmt_list '}' { $$ = $2; }
;

stmt_list:
statement { $$ = $1; }
| stmt_list statement { $$ = opr(';', 2, $1, $2); }
;

expr:
INTEGER { $$ = con($1); }
| VARIABLE { $$ = id($1); printf("variable %c ::=  %d\n",'a' + $1, sym[$1]);}
| VARIABLE ASSIGN expr { $$ = opr(ASSIGN,2,$1,$3); }
| expr '+' expr { $$ = opr('+',2,$1,$3); }
| expr '-' expr { $$ = opr('-',2,$1,$3); }
| expr '*' expr { $$ = opr('*',2,$1,$3); }
| expr '/' expr { $$ = opr('/',2,$1,$3); }
| '(' expr ')' { $$ = $2; }
| expr '>' expr {$$ = opr('>',2,$1,$3); }
| expr '<' expr { $$ = opr('<',2,$1,$3); }
| expr GE expr { $$ = opr(GE,2,$1,$3); }
| expr LE expr { $$ = opr(LE,2,$1,$3); }
| expr EQ expr { $$ = opr(EQ,2,$1,$3); }
| expr NE expr { $$ = opr(NE,2,$1,$3); }
;
%%
void yyerror(char *s) {
fprintf(stderr, "%s\n", s);
}

int main(void) {
return yyparse();

}