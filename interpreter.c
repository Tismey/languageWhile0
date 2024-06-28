#include "master.h"


int ex(nodeType *p){
    if(!p) return 0;
    printf("p = %d\n", p->type);
    switch(p->type){
        case typeConst:
            printf("%d", p->con);
            return p->con;
            break;
        case typeId:
            printf("%d", sym[p->id]);
            return sym[p->id];
            break;
        case typeOpr:
        switch(p->opr.oper){
            case WHILE:
                while(ex(p->opr.op[0]))
                    ex(p->opr.op[1]);
                return 0;
                break;
            case IF:
                if(ex(p->opr.op[0]))
                    ex(p->opr.op[1]);
                else if(p->opr.nops > 2)
                    ex(p->opr.op[2]);
                return 0;
                break;
            case PRINT:
                printf("%d\n", ex(p->opr.op[0]));
                return 0;
                break;
            case ';':
                ex(p->opr.op[0]);
                return ex(p->opr.op[1]);
                break;
            case ASSIGN:
                printf("ASSIGN letter %c value %d to -> %d\n", p->opr.op[0]->id + 'a',0, 0);
                return sym[p->opr.op[0]->id] = ex(p->opr.op[1]);
                break;
            case '+':
                return ex(p->opr.op[0]) + ex(p->opr.op[1]);
                break;
            case '-':
                return ex(p->opr.op[0]) - ex(p->opr.op[1]);
                break;
            case '*':
                return ex(p->opr.op[0]) * ex(p->opr.op[1]);
                break;
            case '/':
                return ex(p->opr.op[0]) / ex(p->opr.op[1]);
                break;
            case '<':
                return ex(p->opr.op[0]) < ex(p->opr.op[1]);
                break;
            case '>':
                return ex(p->opr.op[0]) > ex(p->opr.op[1]);
                break;
            case GE:
                return ex(p->opr.op[0]) >= ex(p->opr.op[1]);
                break;
            case LE:
                return ex(p->opr.op[0]) <= ex(p->opr.op[1]);
                break;
            case NE:
                return ex(p->opr.op[0]) != ex(p->opr.op[1]);
                break;
            case EQ:
                return ex(p->opr.op[0]) == ex(p->opr.op[1]);
                break;
        }
    }
}