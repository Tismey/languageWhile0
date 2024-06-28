#include "operator.h"

nodeType *opr(int oper, int nops, ...) {
    va_list ap;
    nodeType *p;
    int i;

    if (!(p = (nodeType *)malloc(sizeof(nodeType))))
        perror("out of memory");
    if(!(p->opr.op = (nodeType **)malloc(nops * sizeof(nodeType *))))
        perror("out of memory");
    p->type = typeOpr;
    p->opr.oper = oper;
    p->opr.nops = nops;
    va_start(ap, nops);
    for (i = 0; i < nops; i++)
        p->opr.op[i] = va_arg(ap, nodeType *);
    va_end(ap);
    return p;
}

nodeType *con(int value) {
    nodeType *p;

    if (!(p = (nodeType *)malloc(sizeof(nodeType))))
        perror("out of memory");
    p->type = typeConst;
    p->con = value;
    return p;
}

nodeType *id(int i) {
    nodeType *p;

    if (!(p = (nodeType *)malloc(sizeof(nodeType))))
        perror("out of memory");
    p->type = typeId;
    p->id = i;
    return p;
}


