//thisfile:DualLinkedListTester.c
#include <stdio.h>

#include "DualLinkedList.h"

DLL_RET_CD PrintForeach(void *ctx, void *data); 

//main test
//int main(int argc, char* argv[], char* env[]){
int main(void){

    DLL_RET_CD rc = RC_DLL_SUCCESS;

    printf("test in\n=============================\n");
    DualLinkedList *lst;
    printf("test:lst init\n");
    lst = DuLkLst_getInstance(&rc);
    if(rc==RC_DLL_SUCCESS){
        printf("init list success!\n");
        printf("test:lst=%p\n",lst);
    }


    printf("test:append a element to lst\n");
    lst->append(lst, &rc, (void *)'a');
    printf("test:lst->data=%c\n",(char*)lst->get(lst, &rc, 1));
    lst->append(lst, &rc, (void *)'f');
    printf("test:lst->data=%c\n",(char*)lst->get(lst, &rc, 1));
    printf("test:lst->data=%c\n",(char*)lst->get(lst, &rc, 2));
    printf("test:lst->getLength=%d\n",lst->getLen(lst, &rc));
    printf("test:insert 0...\n");
    lst->insert(lst, &rc, 1, (void *)'0');
    if(rc==RC_DLL_SUCCESS)
        printf("test:insert 0 success!\n");
    else
        printf("test:insert 0 fail!\n");
    //	lst->append(lst, (void *)'x');
    printf("test:insert e...\n");
    lst->insert(lst, &rc ,3, (void *)'e');
    if(rc==RC_DLL_SUCCESS)
        printf("test:insert 0 success!\n");
    else
        printf("test:insert 0 fail!\n");
    printf("test:lst->getLength=%d\n",lst->getLen(lst, &rc));
    printf("test:lst elem 1=%c\n",lst->get(lst, &rc, 1));
    printf("test:lst elem 2=%c\n",lst->get(lst, &rc, 2));
    printf("test:lst elem 3=%c\n",lst->get(lst, &rc, 3));
    printf("test:lst elem 4=%c\n",lst->get(lst, &rc, 4));


    printf("test:print all element of DualLinkedList.lst \n");
    lst->for_each(lst, &rc, PrintForeach, (void*)"test");
    //	lst->append(lst, (void *)'x');

    printf("test:main:insert t\n");
    lst->insert(lst, &rc,6, (void *)'t');
    printf("test:lst->getLength=%d\n",lst->getLen(lst, &rc));
    //	if(rc==RC_DLL_OUT_OF_RANG)printf("out of range\n");
    printf("test:main:print all element of DualLinkedList.lst \n");
    lst->for_each(lst, &rc, PrintForeach, (void*)"test");

    printf("test:main:append x\n");
    lst->append(lst, &rc, (void *)'x');

    printf("test:print all element of DualLinkedList.lst \n");
    lst->for_each(lst, &rc, PrintForeach, (void*)"test");

    printf("test:main:remove a element of DualLinkedList.lst \n");
    lst->remove(lst, &rc, 5);
    printf("test:main:remove a element of DualLinkedList.lst \n");
    lst->remove(lst, &rc, 3);
    printf("test:main:remove a element of DualLinkedList.lst \n");
    lst->remove(lst, &rc, 5);

    printf("test:print all element of DualLinkedList.lst \n");
    lst->for_each(lst, &rc, PrintForeach, (void*)"test");

    printf("test:print all element of DualLinkedList.lst \n");
    lst->toFirst(lst, &rc);
    while(1){
        printf("test:next = %c\n",lst->getC(lst, &rc));
        lst->toNext(lst, &rc);
        if(RC_DUALLINKEDLIST==RC_DLL_END_OF_LIST){
            printf("test:the end of the list!\n");
            break;
        }
    }

    while(1){
        printf("test:prior = %c\n",lst->getC(lst, &rc));
        lst->toPrior(lst, &rc);
        if(RC_DUALLINKEDLIST == RC_DLL_HEAD_OF_LIST){
            printf("test:the head of the list!\n");
            break;
        }
    }

    printf("test:destory lst");
    lst->destory(lst, &rc);

    //printf("lst:%p\n",lst);
    //printf("ret:%d\n",ret);
    printf("=======================\ntest OUT\n");

    return 0;

}

DLL_RET_CD PrintForeach(void *data, void *ctx){
    //printf("DualLinkedList:test:start to print a element\n");
    printf("data=%c\n",(char *)data);
    //printf("DualLinkedList:test:end of print a element\n");
    return RC_DLL_SUCCESS;
} 
