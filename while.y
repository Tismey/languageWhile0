%{
#include <stdio.h>
#include <stdlib.h>
#include "master.h"
nodeType *result = NULL;
%}



%union {
    int iValue; /* integer value */
    int sIndex; /* symbol table index */
    nodeType *nPtr; /* node pointer */
};

%token <iValue> INTEGER
%token <sIndex> VARIABLE
%token WHILE IF PRINT ELSE
%left IF ELSE THEN
%left ASSIGN
%left GE LE EQ NE '>' '<' ';'
%left '+' '-'
%left '*' '/'
%nonassoc '.'


%type <nPtr> statement expr stmt_list var program


%{
void yyerror(char *);
int yylex(void);
int booleanValue = 1;
int sym[26];
%}



%%
program:
stmt_list'.'{ result = $1; printf("================COMPILED==================\n\n"); YYACCEPT;}
;
statement:
IF '(' expr ')' THEN '{' stmt_list '}' ELSE '{' stmt_list '}'{$$ = opr(IF,3,$3,$7,$11);}
|IF '(' expr ')' THEN '{' stmt_list '}'{$$ = opr(IF,2,$3,$7);}
|expr { $$ = $1; }
| WHILE '(' expr ')' THEN '{' stmt_list '}' {$$ = opr(WHILE,2,$3,$7);}
;

stmt_list:
statement{ $$ = $1; }
| stmt_list ';' statement{ $$ = opr(';', 2, $1, $3); }
;

var:
VARIABLE { $$ = id($1); }
;

expr:
INTEGER { $$ = con($1); }
| var { $$ = $1; }
| var ASSIGN expr { $$ = opr(ASSIGN,2,$1,$3); }
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
if(yyparse() == 0) {
    ex(result);
}
return 0;
}