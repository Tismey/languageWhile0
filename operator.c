#include "y.tab.h"
#include <string.h>

varList *varListHead = NULL;

nodeType *opr(int oper, int nops, ...) {
    printf("building op %s with %d operands\n",oprToString(oper), nops);
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
    for (i = 0; i < nops; i++){
        nodeType * tmp = (nodeType *) va_arg(ap, nodeType *);
        p->opr.op[i] = tmp;
    }
    va_end(ap);
    return p;
}

nodeType *con(int value) {
    printf("building con with %d as value\n",value);
    nodeType *p;

    if (!(p = (nodeType *)malloc(sizeof(nodeType))))
        perror("out of memory");
    p->type = typeConst;
    p->con = value;
    return p;
}

nodeType *id(int i) {
    printf("building variable with %d as id\n",i);
    nodeType *p;

    if (!(p = (nodeType *)malloc(sizeof(nodeType))))
        perror("out of memory");
    p->type = typeId;
    p->id = i;
    return p;
}

char * oprToString(int oper){
    switch(oper){
        case WHILE:
            return "WHILE";
            break;
        case IF:
            return "IF";
            break;
        case PRINT:
            return "PRINT";
            break;
        case ';':
            return ";";
            break;
        case ASSIGN:
            return "ASSIGN";
            break;
        case '+':
            return "+";
            break;
        case '-':
            return "-";
            break;
        case '*':
            return "*";
            break;
        case '/':
            return "/";
            break;
        case '<':
            return "<";
            break;
        case '>':
            return ">";
            break;
        case GE:
            return "GE";
            break;
        case LE:
            return "LE";
            break;
        case EQ:
            return "EQ";
            break;
        case NE:
            return "NE";
            break;
        default:
            return "UNKNOWN";
            break;
    }
}

 int addTolistWithId(char *name){
        int id = 0;
        varList *tmp = varListHead;
        if(tmp == NULL){
            printf("adding %s at %d\n",name,id);
            varListHead = (varList *)malloc(sizeof(varList));
            varListHead->name = name;
            varListHead->value = 0;
            varListHead->next = NULL;
            return id;
        }
        printf("searching for %s\n",name);
        while(tmp->next != NULL){
            printf("cur var is %s\n",tmp->name);
            if(strcmp(tmp->name,name) == 0){
                printf("found %s at %d\n",name,id);
                return id;
            }
            id++;
            tmp = tmp->next;
        }
        printf("cur var is %s\n",tmp->name);
        if(strcmp(tmp->name,name) == 0){
             printf("found %s at %d\n",name,id);
            return id;
        }
        printf("adding %s at %d\n",name,id);
        varList *new = (varList *)malloc(sizeof(varList));
        new->name = name;
        new->value = 0;
        new->next = NULL;
        tmp->next = new;
        return ++id;
    }

    varList *findInList(int id){
        int i  = id;
        varList *tmp = varListHead;
        while(tmp != NULL){
            if(id == 0){
                return tmp;
            }
            id--;
            tmp = tmp->next;
        }
        printf("could not find id %d\n",i);
        return NULL;
    }

    void printList(){
        varList *tmp = varListHead;
        printf("-------------------------------------------variable table-------------------------------------------\n\n");
        while(tmp != NULL){
            printf("| %s | %d |\n",tmp->name,tmp->value);
            tmp = tmp->next;
        }
        printf("\n------------------------------------end of variable table-------------------------------------------\n");
    }


