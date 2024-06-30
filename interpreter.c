/*
Timothée M'BASSIDJE 12104516
Denis LINDE 12104516
*/

#include "master.h"


int ex(nodeType *p){
    if(!p) return 0;
    switch(p->type){
        case typeConst:
            return p->con;
            break;
        case typeId:
            return findInList(p->id)->value;
            break;
        case typeOpr:
        switch(p->opr.oper){
            case WHILE:
            printList();
                while(ex(p->opr.op[0]))
                    ex(p->opr.op[1]);
                return 0;
                break;
            case IF:
                printList();
                if(ex(p->opr.op[0]))
                    return ex(p->opr.op[1]);
                else if(p->opr.nops > 2)
                   return ex(p->opr.op[2]);
                else
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
                printf("ASSIGN\n");
                printf("ASSIGN var id %d value %d to -> ?\n", p->opr.op[0]->id ,findInList(p->opr.op[0]->id)->value);
                findInList(p->opr.op[0]->id)->value = ex(p->opr.op[1]);
                printf("is now %d\n", findInList(p->opr.op[0]->id)->value);
                printList();
                return findInList(p->opr.op[0]->id)->value;
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
            case OR:
                return (ex(p->opr.op[0]) || ex(p->opr.op[1]));
            break;
            case AND:
                return (ex(p->opr.op[0]) && ex(p->opr.op[1]));
            break;
        }
    }
}