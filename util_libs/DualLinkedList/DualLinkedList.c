//thisfile:DualLinkedList.c
#include <stdlib.h>
#include <stdio.h>
#include "DualLinkedList.h"

DLL_RET_CD RC_DUALLINKEDLIST = RC_DLL_SUCCESS;

typedef struct _DLL_ST_Node_13s13_163COM  DLL_ST_Node;

struct _DLL_ST_Node_13s13_163COM {
    void * data;
    DLL_ST_Node *prior;
    DLL_ST_Node *next;
};

struct _DLL_ST_List_13s13_163COM {
    DLL_ST_Node *head;
    DLL_ST_Node *current;
    long length;
};

//new
DualLinkedList * DuLkLst_getInstance(DLL_RET_CD *rc);

static DLL_RET_CD DuLkLst_Destory(DualLinkedList *thiz, DLL_RET_CD *rc);
static DLL_RET_CD DuLkLst_Append(DualLinkedList *thiz, DLL_RET_CD *rc, void *data);
static DLL_RET_CD DuLkLst_Insert(DualLinkedList *thiz, DLL_RET_CD *rc, long index, void *data);
static DLL_RET_CD DuLkLst_Remove(DualLinkedList *thiz, DLL_RET_CD *rc, long index);
static DLL_RET_CD DuLkLst_Update(DualLinkedList *thiz, DLL_RET_CD *rc, long index, void *data);
static DLL_RET_CD DuLkLst_UpdateC(DualLinkedList *thiz, DLL_RET_CD *rc, void *data);
static void * DuLkLst_Get(DualLinkedList * thiz, DLL_RET_CD *rc,long index);
static void * DuLkLst_getCurrent(DualLinkedList * thiz, DLL_RET_CD *rc);
static DLL_RET_CD DuLkLst_Foreach(DualLinkedList * thiz, DLL_RET_CD *rc, DLL_RET_CD (*action)(void *,void *), void* ctx);
static long DuLkLst_getLength(DualLinkedList * thiz, DLL_RET_CD *rc);
static DLL_RET_CD DuLkLst_toFirst(DualLinkedList * thiz, DLL_RET_CD *rc);
static DLL_RET_CD DuLkLst_toNext(DualLinkedList * thiz, DLL_RET_CD *rc);
static DLL_RET_CD DuLkLst_toPrior(DualLinkedList * thiz, DLL_RET_CD *rc);

static int DuLkLst_isInit(DualLinkedList * thiz);



/******************************************************
  funcName : DuLkLst_getInstance
  funcDesc : init a new list
  pamrList : NULL
  retnValu : DualLinkedList *
*/
DualLinkedList * DuLkLst_getInstance(DLL_RET_CD *rc){
    *rc = RC_DLL_SUCCESS; RC_DUALLINKEDLIST = *rc;
    DualLinkedList *lst;
    DLL_ST_Node *node;

    lst = NULL;
    lst = (DualLinkedList *)malloc(sizeof(DualLinkedList));
    if (NULL == lst){
        *rc = RC_DLL_MEMORY_ALLOC_ERROR; RC_DUALLINKEDLIST = *rc;
//        fprintf(stderr,"[ERROR]:fail to alloc memory when list init\n");
        return NULL;
    }

    lst->data = (DualLinkedListST*)malloc(sizeof(DualLinkedListST));
    if (NULL == lst->data){
        *rc = RC_DLL_MEMORY_ALLOC_ERROR; RC_DUALLINKEDLIST = *rc;
//        fprintf(stderr,"[ERROR]:fail to alloc memory when list init\n");
        free(lst);
        return NULL;
    }

    node = NULL;
    node = (DLL_ST_Node*)malloc(sizeof(DLL_ST_Node));
    if (NULL == node){
        *rc = RC_DLL_MEMORY_ALLOC_ERROR; RC_DUALLINKEDLIST = *rc;
//        fprintf(stderr,"[ERROR]:fail to alloc memory when list init\n");
        free(lst->data);
        free(lst);
        lst->data = NULL;
        lst=NULL;
        return NULL;
    }
    node->data = NULL; node->next = NULL; node->prior = NULL;
    lst->data->length=0;
    lst->data->head = node; lst->data->current = node;

    lst->destory = DuLkLst_Destory;
    lst->append = DuLkLst_Append;
    lst->insert = DuLkLst_Insert;
    lst->remove = DuLkLst_Remove;
    lst->update = DuLkLst_Update;
    lst->updateC = DuLkLst_UpdateC;
    lst->get = DuLkLst_Get;
    lst->getC = DuLkLst_getCurrent;
    lst->for_each = DuLkLst_Foreach;
    lst->getLen = DuLkLst_getLength;
    lst->toFirst = DuLkLst_toFirst;
    lst->toNext = DuLkLst_toNext;
    lst->toPrior = DuLkLst_toPrior;

    return lst;
}

/************************************************************************************
  funcName : DuLkLst_Destory
  funcDesc : destory the specified DualLinkedList  
  pamrList : DualLinkedList *,specified DualLinkedList ;
  retnValu : DLL_RET_CD, specified in "DualLinkedList _Message.h"
*************************************************************************************/
static DLL_RET_CD DuLkLst_Destory(DualLinkedList * thiz, DLL_RET_CD *rc){
    *rc = RC_DLL_SUCCESS;
    DualLinkedListST *lstdt;

    if(DuLkLst_isInit(thiz) == 0){
        *rc = RC_DLL_LIST_NOT_INIT_ERROR; RC_DUALLINKEDLIST = *rc;
//        fprintf(stderr,"[ERROR]list is not init");
        return *rc;
    }

    lstdt = thiz->data;

    lstdt->current = lstdt->head;

    while(NULL != lstdt->current->next){
        lstdt->current = lstdt->current->next;
    }
    while(lstdt->length != 0){
        lstdt->current = lstdt->current->prior;
        free(lstdt->current->next);
        lstdt->current->next = NULL;
        lstdt->length--;
    }
    free(lstdt);
    lstdt = NULL;
    free(thiz);
    thiz = NULL;

    return *rc;
}


/******************************************************************************************
  funcName : DuLkLst_Append 
  funcDesc : append a node as the end of list
  pamrList : DualLinkedList *,specified DualLinkedList ;void*,the data;
  retnValu : DLL_RET_CD, specified in "DualLinkedList _Message.h"
*******************************************************************************************/
static DLL_RET_CD DuLkLst_Append(DualLinkedList * thiz, DLL_RET_CD *rc, void* data){
    *rc = RC_DLL_SUCCESS; RC_DUALLINKEDLIST = *rc;
    DLL_ST_Node *node;
    DualLinkedListST *lstdt;

    if(DuLkLst_isInit(thiz) == 0){
        *rc = RC_DLL_LIST_NOT_INIT_ERROR; RC_DUALLINKEDLIST = *rc;
//        fprintf(stderr,"list is not init\n");
        return *rc;
    }

    lstdt = thiz->data;

    /* allocate memory for a new node */
    node = NULL;
    node = (DLL_ST_Node*)malloc(sizeof(DLL_ST_Node));
    if(NULL == node){
        *rc = RC_DLL_MEMORY_ALLOC_ERROR; RC_DUALLINKEDLIST = *rc;
//        fprintf(stderr,"[ERROR]:fail to alloc memory when append data\n");
        return *rc;
    }
    node->data = data;

    while(NULL != lstdt->current->next){
        lstdt->current = lstdt->current->next;
    }

    lstdt->current->next = node;
    node->prior = lstdt->current;
    node->next = NULL;
    lstdt->current = node;
    lstdt->length ++;

    return *rc;
} 

/*****************************************************
  funcName : DuLkLst_Insert
  funcDesc : add a element in the middle of specified DualLinkedList 
  pamrList : DualLinkedList *,specified DualLinkedList ;long,the position,from 1 to n;void*,the data;
  retnValu : DLL_RET_CD, specified in "DualLinkedList _Message.h"
***************************************************************************/
static DLL_RET_CD DuLkLst_Insert(DualLinkedList * thiz, DLL_RET_CD *rc, long index, void* data){
    *rc = RC_DLL_SUCCESS; RC_DUALLINKEDLIST = *rc;
    DLL_ST_Node* node;
    int i;
    DualLinkedListST *lstdt;

    if(DuLkLst_isInit(thiz) == 0){
        *rc = RC_DLL_LIST_NOT_INIT_ERROR; RC_DUALLINKEDLIST = *rc;
//        fprintf(stderr,"[ERROR]list is not init");
        return *rc;
    }

    lstdt = thiz->data;

    if((lstdt->length < index) || (index<1)){
        *rc = RC_DLL_OUT_OF_RANG; RC_DUALLINKEDLIST = *rc;
//        fprintf(stderr,"[ERROR]:index out of range when insert data\n");
        return *rc;
    }

    /* allocate memory for a new node */
    node = NULL;
    node = (DLL_ST_Node*)malloc(sizeof(DLL_ST_Node));
    if(NULL == node){
        *rc = RC_DLL_MEMORY_ALLOC_ERROR; RC_DUALLINKEDLIST = *rc;
//        fprintf(stderr,"[ERROR]:fail to alloc memory when insert data\n");
        return *rc;
    }
    node->data = data;

    lstdt->current = lstdt->head;
    for(i=0;i<index;i++){
        lstdt->current = lstdt->current->next;
    }

    node->next = lstdt->current;
    node->prior = lstdt->current->prior;
    lstdt->current->prior->next = node;
    lstdt->current->prior = node;
    lstdt->current = node;
    lstdt->length ++;

    return *rc;
}

/*****************************************************
  funcName : DuLkLst_Remove
  funcDesc : remove a node by index from specified DualLinkedList 
  pamrList : DualLinkedList *,specified DualLinkedList ;long,the position,from 1 to n;
  retnValu : DLL_RET_CD, specified in "DualLinkedList _Message.h"
*/
static DLL_RET_CD DuLkLst_Remove(DualLinkedList * thiz, DLL_RET_CD *rc, long index){
    *rc = RC_DLL_SUCCESS; RC_DUALLINKEDLIST = *rc;
    int i;
    DualLinkedListST *lstdt;
    DLL_ST_Node *tmpNode;

    if(DuLkLst_isInit(thiz) == 0){
        *rc = RC_DLL_LIST_NOT_INIT_ERROR; RC_DUALLINKEDLIST = *rc;
//        fprintf(stderr,"list is not init");
        return *rc;
    }
    lstdt = thiz->data;

    if((lstdt->length < index) || (index<1)){
        *rc = RC_DLL_OUT_OF_RANG; RC_DUALLINKEDLIST = *rc;
//        fprintf(stderr,"[ERROR]:index out of range when remove data\n");
        return *rc;
    }

    lstdt->current = lstdt->head;
    for(i=0;i<index;i++){
        lstdt->current = lstdt->current->next;
    }

    tmpNode = lstdt->current;
    lstdt->current = lstdt->current->prior;

    if(NULL != tmpNode->next){
        tmpNode->next->prior = tmpNode->prior;
        lstdt->current->next = tmpNode->next;
    }
    else {
        lstdt->current->next = NULL;
    }
    free(tmpNode);
    tmpNode = NULL;
    lstdt->length--;

    return *rc;
} 

/*****************************************************
  funcName : DuLkLst_UpdateC
  funcDesc : update the data by current node of DualLinkedList 
  pamrList : DualLinkedList *,specified DualLinkedList ;void*,the data;
  retnValu : DLL_RET_CD, specified in "DualLinkedList _Message.h"
*/
static DLL_RET_CD DuLkLst_UpdateC(DualLinkedList *thiz, DLL_RET_CD *rc, void *data){
    *rc = RC_DLL_SUCCESS; RC_DUALLINKEDLIST = *rc;
    DualLinkedListST *lstdt;

    if(DuLkLst_isInit(thiz) == 0){
        *rc = RC_DLL_LIST_NOT_INIT_ERROR; RC_DUALLINKEDLIST = *rc;
//        fprintf(stderr,"list is not init");
        return *rc;
    }

    lstdt = thiz->data;

    if(thiz->getLen(thiz,rc) == 0 || lstdt->current == NULL){
        *rc = RC_DLL_EMPTY_LIST; RC_DUALLINKEDLIST = *rc;
        return *rc;
    }

    lstdt->current->data = data;

    return *rc;
}

/*****************************************************
  funcName : DuLkLst_Update
  funcDesc : update the data by index in specified DualLinkedList 
  pamrList : DualLinkedList *,specified DualLinkedList ;long,the position,from 1 to n;void*,the data;
  retnValu : DLL_RET_CD, specified in "DualLinkedList _Message.h"
*/
static DLL_RET_CD DuLkLst_Update(DualLinkedList * thiz, DLL_RET_CD *rc, long index, void* data){
    *rc = RC_DLL_SUCCESS; RC_DUALLINKEDLIST = *rc;
    int i;
    DualLinkedListST *lstdt;

    if(DuLkLst_isInit(thiz) == 0){
        *rc = RC_DLL_LIST_NOT_INIT_ERROR; RC_DUALLINKEDLIST = *rc;
//        fprintf(stderr,"list is not init");
        return *rc;
    }

    lstdt = thiz->data;

    if((lstdt->length < index) || (index<1)){
        *rc = RC_DLL_OUT_OF_RANG; RC_DUALLINKEDLIST = *rc;
//        fprintf(stderr,"[ERROR]:index out of range when update data\n");
        return *rc;
    }

    lstdt->current = lstdt->head;
    for(i=0;i<index;i++){
        lstdt->current = lstdt->current->next;
    }

    DuLkLst_UpdateC(thiz, rc, data);

    return *rc;
} 

/*****************************************************
  funcName : DuLkLst_Get
  funcDesc : get the data at position from specified DualLinkedList 
  pamrList : DualLinkedList *,specified DualLinkedList ;long,the position,from 1 to n;
  retnValu : void*,the data;
*/
static void* DuLkLst_Get(DualLinkedList * thiz, DLL_RET_CD *rc, long index){
    *rc = RC_DLL_SUCCESS; RC_DUALLINKEDLIST = *rc;
    int i;
    DualLinkedListST *lstdt;

    if(DuLkLst_isInit(thiz) == 0){
        *rc = RC_DLL_LIST_NOT_INIT_ERROR; RC_DUALLINKEDLIST = *rc;
//        fprintf(stderr,"[ERROR]list is not init");
        return NULL;
    }

    lstdt = thiz->data;

    if((lstdt->length < index) || (index<1)){
        *rc = RC_DLL_OUT_OF_RANG; RC_DUALLINKEDLIST = *rc;
//        fprintf(stderr,"[ERROR]list out of range!");
        return NULL;
    }

    lstdt->current = lstdt->head;
    for(i=0;i<index;i++){
        lstdt->current = lstdt->current->next;
    }

    return lstdt->current->data;
}

/*****************************************************
  funcName : DuLkLst_getCurrent
  funcDesc : return the current value
  pamrList : 
  retnValu : void * 
*/
static void * DuLkLst_getCurrent(DualLinkedList * thiz, DLL_RET_CD *rc){
    *rc = RC_DLL_SUCCESS; RC_DUALLINKEDLIST = *rc;
    if(DuLkLst_isInit(thiz) == 0){
        *rc = RC_DLL_LIST_NOT_INIT_ERROR; RC_DUALLINKEDLIST = *rc;
//        fprintf(stderr,"list is not init");
        return NULL;
    }

    if(0 == thiz->data->length){
        *rc = RC_DLL_EMPTY_LIST; RC_DUALLINKEDLIST = *rc;
        return NULL;
    }

    return thiz->data->current->data;

}


/*****************************************************
  funcName : DuLkLst_Foreach
  funcDesc : 
  pamrList : 
  retnValu : void
*/
static DLL_RET_CD DuLkLst_Foreach(DualLinkedList * thiz, DLL_RET_CD *rc, DLL_RET_CD (*action)(void *,void *), void* ctx){
    *rc = RC_DLL_SUCCESS; RC_DUALLINKEDLIST = *rc;
    DualLinkedListST *lstdt;

    if(DuLkLst_isInit(thiz) == 0){
        *rc = RC_DLL_LIST_NOT_INIT_ERROR; RC_DUALLINKEDLIST = *rc;
//        fprintf(stderr,"[error]:list is not init");
        return *rc;
    }

    lstdt = thiz->data;

    lstdt->current = lstdt->head;

    while(NULL!=thiz->data->current->next){
        lstdt->current = lstdt->current->next;
        action(lstdt->current->data, ctx);
    }
    return *rc;
}

/*****************************************************
  funcName : DuLkLst_isInit
  funcDesc : judge the specified DualLinkedList  is inited ot not
  pamrList : DualLinkedList *,specified DualLinkedList ;
  retnValu : int 
*/
static int DuLkLst_isInit(DualLinkedList * thiz){

    if(thiz == NULL){
        return 0;
    }
    if(NULL == thiz->data){
        return 0;
    }

    return 1;
}

/*****************************************************
  funcName : DuLkLst_getLength
  funcDesc : return the length of DualLinkedList
  pamrList : DualLinkedList *,specified DualLinkedList ;
  retnValu : long
*/
static long DuLkLst_getLength(DualLinkedList * thiz, DLL_RET_CD *rc){
    *rc = RC_DLL_SUCCESS; RC_DUALLINKEDLIST = *rc;

    if(DuLkLst_isInit(thiz) == 0){
        *rc = RC_DLL_LIST_NOT_INIT_ERROR; RC_DUALLINKEDLIST = *rc;
//        fprintf(stderr,"list is not init");
        return *rc;
    }

    return thiz->data->length;
}

/*****************************************************
  funcName : DuLkLst_toFirst
  funcDesc : set the current node to the first
  pamrList : DualLinkedList *,specified DualLinkedList ;
  retnValu : DLL_RET_CD
*/
static DLL_RET_CD DuLkLst_toFirst(DualLinkedList * thiz, DLL_RET_CD *rc){
    *rc = RC_DLL_SUCCESS; RC_DUALLINKEDLIST = *rc;

    if(DuLkLst_isInit(thiz) == 0){
        *rc = RC_DLL_LIST_NOT_INIT_ERROR; RC_DUALLINKEDLIST = *rc;
//        fprintf(stderr,"list is not init");
        return *rc;
    }

    if(NULL == thiz->data->head->next){
        thiz->data->current = thiz->data->head;
    }
    else {
        thiz->data->current = thiz->data->head->next;
    }

    return *rc;

}

/*****************************************************
  funcName : DuLkLst_toNext
  funcDesc : set the current node to the next
  pamrList : DualLinkedList *,specified DualLinkedList ;
  retnValu : DLL_RET_CD
*/
static DLL_RET_CD DuLkLst_toNext(DualLinkedList * thiz, DLL_RET_CD *rc){
    *rc = RC_DLL_SUCCESS; RC_DUALLINKEDLIST = *rc;

    if(DuLkLst_isInit(thiz) == 0){
        *rc = RC_DLL_LIST_NOT_INIT_ERROR; RC_DUALLINKEDLIST = *rc;
//        fprintf(stderr,"[ERROR]list is not init\n");
        return *rc;
    }

    if(NULL == thiz->data->current->next){
        *rc = RC_DLL_END_OF_LIST; RC_DUALLINKEDLIST = *rc;
//        fprintf(stderr,"[ERROR]to the end of list\n");
        return *rc;
    }
    else {
        thiz->data->current = thiz->data->current->next;
    }

    return *rc;
}

/*****************************************************
  funcName : DuLkLst_toPrior
  funcDesc : set the current node to the prior
  pamrList : DualLinkedList *,specified DualLinkedList ;
  retnValu : DLL_RET_CD
*/
static DLL_RET_CD DuLkLst_toPrior(DualLinkedList * thiz, DLL_RET_CD *rc){
    *rc = RC_DLL_SUCCESS; RC_DUALLINKEDLIST = *rc;

    if(DuLkLst_isInit(thiz) == 0){
        *rc = RC_DLL_LIST_NOT_INIT_ERROR; RC_DUALLINKEDLIST = *rc;
//        fprintf(stderr,"[error]list is not init\n");
        return *rc;
    }

    if(thiz->data->head == thiz->data->current->prior){
        *rc = RC_DLL_HEAD_OF_LIST; RC_DUALLINKEDLIST = *rc;
//        fprintf(stderr,"[error]to the head of list\n");
        return *rc;
    }
    else {
        thiz->data->current = thiz->data->current->prior;
    }

    return *rc;
}
