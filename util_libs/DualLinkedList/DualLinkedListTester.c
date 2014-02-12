//thisfile:DualLinkedListTester.c
#include <stdio.h>

//#include "DualLinkedList.h"
//#include"Object_WH_G.h"
#include"List_WH_G.h"

void PrintForeachAction(void *val, RC_Iterator_WH_G *rc ,Object_WH_G * ctx);

//main test
//int main(int argc, char* argv[], char* env[]){
int main(void){
    RC_OBJ_WH_G orc = RC_OBJ_SUCCESS;
    RC_LIST_WH_G lrc = RC_LIST_SUCCESS;
    RC_Iterator_WH_G irc = RC_ITER_SUCCESS;

    List_WH_G *l = NULL;

    Object_WH_G *tobj;

    //create list
    printf("create a list...\n");
    l = List_WH_G_getInst(&lrc);
    if(lrc==RC_LIST_SUCCESS)
        printf("create a list success!\n");
    else
        printf("create a list fail!\n");

    //apend a elem
    printf("append a elem...\n");
    tobj = Object_WH_G_getInst(&orc);
    if(orc!=RC_OBJ_SUCCESS){printf("fail!\n");return 1;}
    tobj->op->set(tobj, &orc, (void *)100);
    if(orc!=RC_OBJ_SUCCESS){printf("fail!\n");return 1;}
    l->lop->append(l, &lrc, tobj);
    tobj = NULL;
    if(lrc!=RC_LIST_SUCCESS){printf("fail!\n");return 1;}
    printf("append a elem 100\n");

    printf("append a elem...\n");
    tobj = Object_WH_G_getInst(&orc);
    if(orc!=RC_OBJ_SUCCESS){printf("fail!\n");return 1;}
    tobj->op->set(tobj, &orc, (void *)101);
    if(orc!=RC_OBJ_SUCCESS){printf("fail!\n");return 1;}
    l->lop->append(l, &lrc, tobj);
    tobj = NULL;
    if(lrc!=RC_LIST_SUCCESS){printf("fail!\n");return 1;}
    printf("append a elem 101\n");

    printf("append a elem...\n");
    tobj = Object_WH_G_getInst(&orc);
    if(orc!=RC_OBJ_SUCCESS){printf("fail!\n");return 1;}
    tobj->op->set(tobj, &orc, (void *)102);
    if(orc!=RC_OBJ_SUCCESS){printf("fail!\n");return 1;}
    l->lop->append(l, &lrc, tobj);
    tobj = NULL;
    if(lrc!=RC_LIST_SUCCESS){printf("fail!\n");return 1;}
    printf("append a elem 102\n");

    //for_each
    printf("print all elem...\n");
    l->itr->iop->for_each(l, &irc, PrintForeachAction, NULL);
    if(irc==RC_ITER_END_OF_LIST)printf("end of list!\n");
    else if(irc!=RC_ITER_SUCCESS){printf("fail!\n");return 1;}

    //反向遍历
    printf("print all elem desc...\n");
    irc = RC_ITER_SUCCESS;
    while(irc == RC_ITER_SUCCESS){
        tobj = l->itr->iop->current(l, &irc);
        if(irc != RC_ITER_SUCCESS){printf("fail!\n");return 1;}
        PrintForeachAction(tobj, &irc, NULL);
        if(irc != RC_ITER_SUCCESS){printf("fail!\n");return 1;}
        l->itr->iop->toPrior(l, &irc);
    }
    if(irc==RC_ITER_HEAD_OF_LIST)printf("head of list!\n");
    else if(irc!=RC_ITER_SUCCESS){printf("fail!\n");return 1;}

    //insert
    printf("insert elem at index 2...\n");
    tobj = Object_WH_G_getInst(&orc);
    if(orc!=RC_OBJ_SUCCESS){printf("fail!\n");return 1;}
    tobj->op->set(tobj, &orc, (void *)106);
    if(orc!=RC_OBJ_SUCCESS){printf("fail!\n");return 1;}
    l->lop->insert(l, &lrc, 2, tobj);
    tobj = NULL;
    if(lrc!=RC_LIST_SUCCESS){printf("fail!\n");return 1;}
    printf("insert a elem 106 at index 2\n");
    //for_each
    printf("print all elem...\n");
    l->itr->iop->for_each(l, &irc, PrintForeachAction, NULL);
    if(irc==RC_ITER_END_OF_LIST)printf("end of list!\n");
    else if(irc!=RC_ITER_SUCCESS){printf("fail!\n");return 1;}

    //update
    printf("update elem at index 3...\n");
    tobj = Object_WH_G_getInst(&orc);
    if(orc!=RC_OBJ_SUCCESS){printf("fail!\n");return 1;}
    tobj->op->set(tobj, &orc, (void *)108);
    if(orc!=RC_OBJ_SUCCESS){printf("fail!\n");return 1;}
    l->lop->update(l, &lrc, 3, tobj);
    tobj = NULL;
    if(lrc!=RC_LIST_SUCCESS){printf("fail!\n");return 1;}
    printf("update elem to 108 at index 3\n");
    //for_each
    printf("print all elem...\n");
    l->itr->iop->for_each(l, &irc, PrintForeachAction, NULL);
    if(irc==RC_ITER_END_OF_LIST)printf("end of list!\n");
    else if(irc!=RC_ITER_SUCCESS){printf("fail!\n");return 1;}

    //remove
    printf("remove elem at index 1...\n");
    l->lop->remove(l, &lrc, 1);
    tobj = NULL;
    if(lrc!=RC_LIST_SUCCESS){printf("fail!\n");return 1;}
    printf("remove elem at index 1\n");
    //for_each
    printf("print all elem...\n");
    l->itr->iop->for_each(l, &irc, PrintForeachAction, NULL);
    if(irc==RC_ITER_END_OF_LIST)printf("end of list!\n");
    else if(irc!=RC_ITER_SUCCESS){printf("fail!\n");return 1;}

    l->obj.op->destory(l, &orc);

    return 0;
}

void PrintForeachAction(void *val, RC_Iterator_WH_G *rc ,Object_WH_G * ctx){
    *rc = RC_ITER_SUCCESS;
    Object_WH_G *v = val;

    printf("%d ", v->val);

    return;
}
