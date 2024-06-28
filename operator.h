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


nodeType *opr(int oper, int nops, ...);


nodeType *con(int value);

nodeType *id(int i);

extern int sym[26];


