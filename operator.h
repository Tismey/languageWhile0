#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef enum { typeConst, typeId, typeOpr } nodeEnum;
typedef int conNodeType;
typedef int idNodeType;


typedef struct oprNodeType {
    int oper;
    int nops;
    struct nodeTypeTag **op;
} oprNodeType;



typedef struct nodeTypeTag {
    nodeEnum type;
    union {
        conNodeType con;
        idNodeType id;
        oprNodeType opr;
    };
} nodeType;

typedef struct varList{
    char *name;
    int value;
    struct varList *next;
} varList;

char * oprToString(int oper);

extern varList *varListHead;

int addTolistWithId(char *name);

varList *findInList(int id);

nodeType *opr(int oper, int nops, ...);


nodeType *con(int value);

nodeType *id(int i);

void printList();
void printSyntaxTreeHelper(nodeType *p, int depth);
extern int sym[26];


