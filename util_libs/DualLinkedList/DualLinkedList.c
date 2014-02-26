//thisfile:DualLinkedList.c
#include <stdlib.h>
#include <stdio.h>
#include "DualLinkedList.h"
#include<stdarg.h>

//maco======================================================================
//maco for check is inited
#define CHECK_DLL_ISINITED(OBJ_STR, RC_STR, RETURN_STR) \
    if(DuLkLst_isInit(OBJ_STR)==0){ \
        RC_STR = RC_LIST_NOT_INIT; \
        GLRC_DLL_WH_G = RC_STR; \
        return RETURN_STR; \
    }

#define CHECK_DLL_ITR_ISINITED(PITR_STR, RC_STR, RETURN_STR) \
    if(Iter_isInit(PITR_STR)==0){ \
        RC_STR = RC_LIST_NOT_INIT; \
        GLRC_DLL_WH_G = RC_STR; \
        return RETURN_STR; \
    }

//maco for check obj deal error
#define CHECK_DLL_OBJDEAL_ERROR(ORC_STR, RC_STR, RETURN_STR, BEFORE_RETURN) \
    if(ORC_STR != RC_OBJ_SUCCESS){ \
        RC_STR = RC_OBJ_ERROR; \
        GLRC_DLL_WH_G = RC_STR; \
        BEFORE_RETURN; \
        return RETURN_STR; \
    }

//maco for check list deal error
#define CHECK_DLL_LISTDEAL_ERROR(RC_STR, RETURN_STR, BEFORE_RETURN) \
    if(RC_STR != RC_LIST_SUCCESS){ \
        BEFORE_RETURN; \
        return RETURN_STR; \
    }

//data struct==================================================================
typedef struct _DLL_ST_Node_13s13_163COM  DL_Node;

struct _DLL_ST_Node_13s13_163COM {
    Object_WH_G *data;
    DL_Node *prior;
    DL_Node *next;
};

typedef struct _DLL_ST_List_13s13_163COM {
    DL_Node *head;
    DL_Node *tail;
    long length;
} DL_LIST;

//declare======================================================================
//new
List_WH_G *DLL_WH_G_getInst(int *rc);
void DLL_WH_G_Init(List_WH_G *thiz, int *rc);
void DLL_WH_G_OP_Init(List_Op_WH_G *lop, int *rc);

void DLL_WH_G_Itr_Bind(Iter_WH_G *itr, int *rc, void *list, unsigned char soe);
void DLL_WH_G_Itr_Set(Iter_WH_G *itr, int *rc, Iter_WH_G *src);

//extend from obj
static void DuLkLst_Destory(List_WH_G *thiz, int *rc);
static List_WH_G *DuLkLst_Clone(List_WH_G *thiz, int *rc);
static void DuLkLst_Set(List_WH_G *thiz, int *rc, ...);
//implement list
static void DuLkLst_Insert(List_WH_G *thiz, int *rc, long index, Object_WH_G *value);
static void DuLkLst_InsertC(Iter_WH_G *itr, int *rc, Object_WH_G *value);
static void DuLkLst_Append(List_WH_G *thiz, int *rc, Object_WH_G *value);
static void DuLkLst_Update(List_WH_G *thiz, int *rc, long index, Object_WH_G *value);
static void DuLkLst_UpdateC(Iter_WH_G *itr, int *rc, Object_WH_G *value);
static void DuLkLst_Remove(List_WH_G *thiz, int *rc, long index);
static void DuLkLst_RemoveC(Iter_WH_G *itr, int *rc);
static Object_WH_G *DuLkLst_FindByIndex(List_WH_G *thiz, int *rc, long index);
static long DuLkLst_Length(List_WH_G *thiz, int *rc);
//implement iterator
static void DuLkLst_toFisrt(Iter_WH_G *itr, int *rc);
static void DuLkLst_toLast(Iter_WH_G *itr, int *rc);
static void DuLkLst_toNext(Iter_WH_G *itr, int *rc);
static void DuLkLst_toPrior(Iter_WH_G *itr, int *rc);
static void DuLkLst_foreach(
        List_WH_G *list,
        int *rc,
        void (*action)(Object_WH_G *val, int *rc ,void *ctx),
        void *ctx
        );
static Object_WH_G *DuLkLst_Current(Iter_WH_G *itr, int *rc);
static Object_WH_G *DuLkLst_Next(Iter_WH_G *itr, int *rc);
static Object_WH_G *DuLkLst_Prior(Iter_WH_G *itr, int *rc);
static Object_WH_G *DuLkLst_First(Iter_WH_G *itr, int *rc);
static Object_WH_G *DuLkLst_Last(Iter_WH_G *itr, int *rc);
static unsigned char DuLkLst_hasNext(Iter_WH_G *itr, int *rc);
static unsigned char DuLkLst_hasPrior(Iter_WH_G *itr, int *rc);
//tool method
static int DuLkLst_isInit(List_WH_G *thiz);
static int Iter_isInit(Iter_WH_G *iter);
static int DuLkLst_isVaildIndex(List_WH_G *thiz, int *rc, long index);
static void DuLkLst_MoveToIndex(Iter_WH_G *it, int *rc, long index, List_WH_G *list);

//global variable==========================================================
Object_Op_WH_G GLOP_DLL_O_WH_G = {
    DuLkLst_Destory,
    DuLkLst_Clone,
    DuLkLst_Set,
    NULL, //toString,
    NULL, //compare
    NULL, //setter
    NULL, //releaser
};
List_Op_WH_G GLOP_DLL_L_WH_G = {
    DuLkLst_Insert, DuLkLst_Append, DuLkLst_Update, DuLkLst_Remove,
    DuLkLst_FindByIndex, DuLkLst_Length, DuLkLst_foreach,
};
Iter_Op_WH_G GLOP_DLL_I_WH_G = {
    DuLkLst_toFisrt, DuLkLst_toLast, DuLkLst_toNext,
    DuLkLst_toPrior, DuLkLst_Current,
    DuLkLst_Next, DuLkLst_Prior, DuLkLst_First,
    DuLkLst_Last, DuLkLst_hasNext, DuLkLst_hasPrior,
    DuLkLst_InsertC, DuLkLst_UpdateC, DuLkLst_RemoveC
};

RC_LIST_WH_G GLRC_DLL_WH_G = RC_LIST_SUCCESS; //全局状态码

//implements===============================================================
/*doc************************************************
 *funcName : List_WH_G_Init
 *funcDesc : 对已分配内存的list初始化
 *pamrList : List_WH_G *thiz 列表实例;int *rc 状态码
 *retnValu : void
 *comment  : 1,创建、初始化head节点;2,创建、初始化list;3,绑定操作变量;
*/
void DLL_WH_G_Init(List_WH_G *thiz, int *rc){
    *rc = RC_LIST_SUCCESS; GLRC_DLL_WH_G = *rc;
    DL_Node *head = NULL; DL_LIST *list = NULL;
    //空指针判断
    if(NULL == thiz){
        *rc = RC_LIST_NOT_INIT; GLRC_DLL_WH_G = *rc; return;
    }
    //创建队列
    list = (DL_LIST *)malloc(sizeof(DL_LIST));
    if(list == NULL){
        *rc = RC_LIST_MEMORY_ALLOC_FAIL; GLRC_DLL_WH_G = *rc; return;
    }
    //创建头结点
    head = (DL_Node *)malloc(sizeof(DL_Node));
    if(head == NULL){
        *rc = RC_LIST_MEMORY_ALLOC_FAIL; GLRC_DLL_WH_G = *rc;
        free(list); return;
    }

    head->data = NULL; head->next = NULL; head->prior = NULL;//初始化头结点
    list->head = head; list->length = 0; list->tail = head; //初始化队列
    thiz->data = list;//绑定队列

    //绑定操作变量
    thiz->lst_op = &GLOP_DLL_L_WH_G;
    thiz->obj_op = &GLOP_DLL_O_WH_G;
    thiz->obj_op->toString = GLOP_OBJ_WH_G.toString;
    thiz->obj_op->compare = GLOP_OBJ_WH_G.compare;
    thiz->obj_op->setter = GLOP_OBJ_WH_G.setter;
    thiz->obj_op->releaser = GLOP_OBJ_WH_G.releaser;

    return;
}

/*doc************************************************
 *funcName : DLL_WH_G_getInst
 *funcDesc : 获取list实例
 *pamrList : int *rc 状态码
 *retnValu : List_WH_G * 列表实例
 *comment  : 1,list分配内存;2,初始化list;
*/
List_WH_G *DLL_WH_G_getInst(int *rc){
    *rc = RC_LIST_SUCCESS; GLRC_DLL_WH_G = *rc;
    List_WH_G *res = NULL;

    res = (List_WH_G *)malloc(sizeof(List_WH_G));
    if(res == NULL){
        *rc = RC_LIST_MEMORY_ALLOC_FAIL; GLRC_DLL_WH_G = *rc;
        return NULL;
    }

    DLL_WH_G_Init(res, rc);
    CHECK_DLL_LISTDEAL_ERROR(*rc, NULL, free(res));

    return res;
}

/*doc************************************************
 *funcName : DLL_WH_G_OP_Init
 *funcDesc : dll操作实例初始化
 *pamrList : int *rc 状态码
 *retnValu : void
 *comment  : 1,绑定操作函数;
*/
//void DLL_WH_G_OP_Init(List_Op_WH_G *lop, int *rc){
//    *rc = RC_LIST_SUCCESS; GLRC_DLL_WH_G = *rc;

//    if(lop == NULL){
//        *rc = RC_LIST_NOT_INIT; GLRC_DLL_WH_G = *rc; return;
//    }

//    lop->append = GLOP_DLL_WH_G.append;
//    lop->findByIndex = GLOP_DLL_WH_G.findByIndex;
//    lop->insert = GLOP_DLL_WH_G.insert;
//    lop->length = GLOP_DLL_WH_G.length;
//    lop->remove = GLOP_DLL_WH_G.remove;
//    lop->update = GLOP_DLL_WH_G.update;
//    lop->for_each = GLOP_DLL_WH_G.for_each;

//    lop->obj_op.clone = DuLkLst_Clone;
//    lop->obj_op.compare = GLOP_OBJ_WH_G.compare;
//    lop->obj_op.destory = DuLkLst_Destory;
//    lop->obj_op.set = DuLkLst_Set;
//    lop->obj_op.toString = GLOP_OBJ_WH_G.toString;

//    lop->itr_op.toFisrt = GLOP_DLL_WH_G.itr_op.toFisrt;
//    lop->itr_op.toLast = GLOP_DLL_WH_G.itr_op.toLast;
//    lop->itr_op.toNext = GLOP_DLL_WH_G.itr_op.toNext;
//    lop->itr_op.toPrior = GLOP_DLL_WH_G.itr_op.toPrior;
//    lop->itr_op.current = GLOP_DLL_WH_G.itr_op.current;
//    lop->itr_op.next = GLOP_DLL_WH_G.itr_op.next;
//    lop->itr_op.prior = GLOP_DLL_WH_G.itr_op.prior;
//    lop->itr_op.first = GLOP_DLL_WH_G.itr_op.first;
//    lop->itr_op.last = GLOP_DLL_WH_G.itr_op.last;
//    lop->itr_op.hasNext = GLOP_DLL_WH_G.itr_op.hasNext;
//    lop->itr_op.hasPrior = GLOP_DLL_WH_G.itr_op.hasPrior;
//    lop->itr_op.insertC = GLOP_DLL_WH_G.itr_op.insertC;
//    lop->itr_op.updateC = GLOP_DLL_WH_G.itr_op.updateC;
//    lop->itr_op.removeC = GLOP_DLL_WH_G.itr_op.removeC;
//    lop->itr_op.bind =GLOP_DLL_WH_G.itr_op.bind;
//    lop->itr_op.set =GLOP_DLL_WH_G.itr_op.set;

//    return ;
//}

/*doc************************************************
 *funcName : DLL_WH_G_Itr_Bind
 *funcDesc : 迭代器绑定列表的头或尾
 *pamrList : Iter_WH_G *itr 迭代器实例; int *rc 状态码
 *  void *list 列表实例; unsigned char soe 开始(0)或结束(1)位置;
 *retnValu : void
 *comment  : 1,迭代器绑定列表的头或尾;
*/
void DLL_WH_G_Itr_Bind(Iter_WH_G *itr, int *rc, void *list, unsigned char soe){
    *rc = RC_LIST_SUCCESS; GLRC_DLL_WH_G = *rc;

    if(itr == NULL || list == NULL){
        *rc = RC_LIST_NOT_INIT; GLRC_DLL_WH_G = *rc; return;
    }

    CHECK_DLL_ISINITED(list, *rc, );

    itr->list = list; //绑定列表
    itr->itr_op = &GLOP_DLL_I_WH_G; //绑定操作变量
    if(soe == 0){
        itr->itr_op->toFisrt(itr, rc); //首
    }else{
        itr->itr_op->toLast(itr, rc); //尾
    }
    return ;
}

/*doc************************************************
 *funcName : DLL_WH_G_Itr_Set
 *funcDesc : 迭代器赋值方法
 *pamrList : Iter_WH_G *itr 目标迭代器实例;int *rc 状态码;Iter_WH_G *src 源迭代器实例;
 *retnValu : void
 *comment  : 1,迭代器赋值方法;
*/
void DLL_WH_G_Itr_Set(Iter_WH_G *itr, int *rc, Iter_WH_G *src){
    *rc = RC_LIST_SUCCESS; GLRC_DLL_WH_G = *rc;

    if(itr == NULL || src == NULL){
        *rc = RC_LIST_NOT_INIT; GLRC_DLL_WH_G = *rc; return;
    }

    itr->cur = src->cur;
    itr->list = src->list;
    itr->itr_op = src->itr_op;

    return ;
}

/*doc************************************************
 *funcName : DuLkLst_Destory
 *funcDesc : 列表destory方法
 *pamrList : List_WH_G *thiz 列表实例; int *rc 状态码;
 *retnValu : void
 *comment  : 1,依次移除队列中元素;2,释放head节点;3,释放申请的资源;
*/
static void DuLkLst_Destory(List_WH_G *thiz, int *rc){
    *rc = RC_LIST_SUCCESS; GLRC_DLL_WH_G = *rc;
    DL_LIST *l = NULL;
    Iter_WH_G it;

    CHECK_DLL_ISINITED(thiz, *rc, );

    DLL_WH_G_Itr_Bind(&it, rc, thiz, 0);
    CHECK_DLL_LISTDEAL_ERROR(*rc, , );

    if(thiz->obj_op->releaser != NULL){ //自定义释放方法
        thiz->obj_op->releaser(thiz);
    }
    else { //默认释放方法
        while(*rc == RC_LIST_SUCCESS){
            it.itr_op->removeC(&it, rc);
            if(*rc == RC_LIST_OUT_OF_RANG){
                *rc = RC_LIST_SUCCESS; GLRC_DLL_WH_G = *rc;
                break ;
            }
            CHECK_DLL_LISTDEAL_ERROR(*rc, , );
        }

        l = (DL_LIST *)(thiz->data);
        free(l->head); //释放head节点
        free(l);    //释放list
        free(thiz);
    }

    return;
}

/*doc************************************************
 *funcName : DuLkLst_Clone
 *funcDesc : 列表clone方法
 *pamrList : List_WH_G *thiz 列表实例; int *rc 状态码;
 *retnValu : List_WH_G *列表实例
 *comment  : 1,新建队列;2,向列表追加原队列中元素的clone值;
*/
static List_WH_G *DuLkLst_Clone(List_WH_G *thiz, int *rc){
    *rc = RC_LIST_SUCCESS; GLRC_DLL_WH_G = *rc;
    RC_OBJ_WH_G orc = RC_OBJ_SUCCESS;
    Object_WH_G *to = NULL;
    List_WH_G *l = NULL;
    Iter_WH_G it;

    CHECK_DLL_ISINITED(thiz, *rc, NULL);

    DLL_WH_G_Itr_Bind(&it, rc, thiz, 0);
    CHECK_DLL_LISTDEAL_ERROR(*rc, NULL, );

    l = DLL_WH_G_getInst(rc);
    CHECK_DLL_LISTDEAL_ERROR(*rc, NULL, );

    while (*rc == RC_LIST_SUCCESS) {
        to = it.itr_op->current(&it, rc);
        CHECK_DLL_LISTDEAL_ERROR(*rc, NULL, l->obj_op->destory(l, rc));

        to = to->obj_op->clone(to, &orc);
        CHECK_DLL_LISTDEAL_ERROR(*rc, NULL, l->obj_op->destory(l, rc));

        thiz->lst_op->append(l, rc, to);
        CHECK_DLL_LISTDEAL_ERROR(*rc, NULL, l->obj_op->destory(l, rc));

        it.itr_op->toNext(&it, rc);
    }

    return l;
}

/*doc************************************************
 *funcName : DuLkLst_Set
 *funcDesc : 列表批量赋值
 *pamrList :
 *  List_WH_G *thiz 列表实例; int *rc 状态码;
 *  ... int + Object_WH_G *赋值个数 + 实例序列;
 *retnValu : void
 *comment  : 1,清空队列;2,获取赋值个数;3,向列表追加值;
*/
static void DuLkLst_Set(List_WH_G *thiz, int *rc, ...){
    *rc = RC_LIST_SUCCESS; GLRC_DLL_WH_G = *rc;
    va_list ap;
    long n = 0, i=0;
    Iter_WH_G it;

    CHECK_DLL_ISINITED(thiz, *rc, );

    DLL_WH_G_Itr_Bind(&it, rc, thiz, 0);
    CHECK_DLL_LISTDEAL_ERROR(*rc, , );

    //清空列表
    while (*rc==RC_LIST_SUCCESS) {
        it.itr_op->removeC(&it, rc);
        CHECK_DLL_LISTDEAL_ERROR(*rc, , );
    }

    va_start(ap,rc);
    //获取赋值个数
    n = *((int *)ap);
    //依次追加至队列
    for(i = 0; i < n; i++){
        va_arg(ap, Object_WH_G*);
        thiz->lst_op->append(thiz, rc, *((Object_WH_G **)ap));
        CHECK_DLL_LISTDEAL_ERROR(*rc, , );
    }

    va_end(ap);

    return;
}

//implement list============================================================
/*doc************************************************
 *funcName : DuLkLst_Insert
 *funcDesc : 在index位置插入元素value(index范围为1...n)
 *pamrList :
 *  List_WH_G *thiz 列表实例;
 *  int *rc 状态码;
 *  long index 下标;
 *  Object_WH_G *value 追加值实例;
 *retnValu : void
 *comment  :
 *  1,判断下标位置是否超出范围;
 *  2,下标位置指向队尾,追加元素(调用append);
 *  3,itr移动至index,在itr位置插入元素(调用insertC);
*/
static void DuLkLst_Insert(List_WH_G *thiz, int *rc, long index, Object_WH_G *value){
    *rc = RC_LIST_SUCCESS; GLRC_DLL_WH_G = *rc;
    long len;
    Iter_WH_G it;

    CHECK_DLL_ISINITED(thiz, *rc, );

    DLL_WH_G_Itr_Bind(&it, rc, thiz, 0);
    CHECK_DLL_LISTDEAL_ERROR(*rc, , );

    len = thiz->lst_op->length(thiz, rc);
    CHECK_DLL_LISTDEAL_ERROR(*rc, , );
    if(index == len + 1){ //下标位置为列表末尾
        thiz->lst_op->append(thiz, rc, value);
        CHECK_DLL_LISTDEAL_ERROR(rc, , );
    }
    else if(DuLkLst_isVaildIndex(thiz, rc, index) != 1){ //下标超出范围
        return;
    }

    DuLkLst_MoveToIndex(&it, rc, index, thiz);
    CHECK_DLL_LISTDEAL_ERROR(*rc, , );

    it.itr_op->insertC(&it, rc, value);

    return;
}

/*doc************************************************
 *funcName : DuLkLst_InsertC
 *funcDesc : 在iter所在位置插入元素value
 *pamrList : List_WH_G *thiz 列表实例; int *rc 状态码; Object_WH_G *value 追加值实例;
 *retnValu : void
 *comment  : 1,判断队列是否为空,在尾部追加;2,判断iter是否指向head,指向第一个元素;3,新建node;4,插入node;
*/
static void DuLkLst_InsertC(Iter_WH_G *itr, int *rc, Object_WH_G *value){
    *rc = RC_LIST_SUCCESS; GLRC_DLL_WH_G = *rc;
    DL_Node *n = NULL, *c = NULL; DL_LIST *l = NULL;

    CHECK_DLL_ITR_ISINITED(itr, *rc, );
    CHECK_DLL_ITR_ISINITED(itr->list, *rc, );

    l = ((List_WH_G *)(itr->list))->data; c = itr->cur;
    CHECK_DLL_ITR_ISINITED(l, *rc, );

    if(itr->cur == l->head){ //iter指向head
        if(l->head->next == NULL){ //队列空
            DuLkLst_Append(itr->list, rc, value);
            CHECK_DLL_LISTDEAL_ERROR(*rc, , );
        }
        else { //队列不空
            itr->itr_op->toFisrt(itr, rc);
            CHECK_DLL_LISTDEAL_ERROR(*rc, , );
        }
    }

    n = (DL_Node *)malloc(sizeof(DL_Node));
    if(n == NULL){*rc = RC_LIST_MEMORY_ALLOC_FAIL; GLRC_DLL_WH_G = *rc; return;}

    n->data = value;
    n->next = c;
    n->prior = c->prior;
    c->prior->next = n;
    c->prior = n;
    l->length++;
    itr->cur = n;

    return;
}

/*doc************************************************
 *funcName : DuLkLst_Append
 *funcDesc : 队尾追加value
 *pamrList : List_WH_G *thiz 列表实例; int *rc 状态码; Object_WH_G *value 追加值实例;
 *retnValu : List_WH_G * 列表实例
 *comment  : 1,新建node;2,追加node;
*/
static void DuLkLst_Append(List_WH_G *thiz, int *rc, Object_WH_G *value){
    *rc = RC_LIST_SUCCESS; GLRC_DLL_WH_G = *rc;
    DL_LIST *l = NULL; DL_Node *n = NULL;

    CHECK_DLL_ISINITED(thiz, *rc, );

    n = (DL_Node *)malloc(sizeof(DL_Node)); //新建node
    if(n == NULL){*rc = RC_LIST_MEMORY_ALLOC_FAIL; GLRC_DLL_WH_G = *rc; return;}

    l = (DL_LIST *)(thiz->data);

    n->data = value;
    n->next = NULL;
    n->prior = l->tail; //node的前置指向原队尾
    l->tail->next = n;  //原队尾的后置指向新node

    l->length++;

    l->tail = n; //队尾指针指向新node

    return;
}

/*doc************************************************
 *funcName : DuLkLst_Update
 *funcDesc : 在index位置修改元素value(index范围为1...n)
 *pamrList :
 *  List_WH_G *thiz 列表实例;
 *  int *rc 状态码;
 *  long index 下标;
 *  Object_WH_G *value 追加值实例;
 *retnValu : void
 *comment  :
 *  1,判断下标位置是否超出范围; 2,itr移动至index,在itr位置更新元素(调用updateC);
*/
static void DuLkLst_Update(List_WH_G *thiz, int *rc, long index, Object_WH_G *value){
    *rc = RC_LIST_SUCCESS; GLRC_DLL_WH_G = *rc;
    Iter_WH_G it;

    CHECK_DLL_ISINITED(thiz, *rc, );

    if(DuLkLst_isVaildIndex(thiz, rc, index) != 1){return;}//下标超出范围

    DuLkLst_MoveToIndex(&it, rc, index, thiz);
    CHECK_DLL_LISTDEAL_ERROR(*rc, , );

    it.itr_op->updateC(&it, rc, value);

    return;
}

/*doc************************************************
 *funcName : DuLkLst_UpdateC
 *funcDesc : 在iter所在位置更新元素为value
 *pamrList : List_WH_G *thiz 列表实例; int *rc 状态码; Object_WH_G *value 追加值实例;
 *retnValu : void
 *comment  : 1,判断iter是否指向有效的节点;2,释放原节点数据;3,更新节点数据为value;
*/
static void DuLkLst_UpdateC(Iter_WH_G *itr, int *rc, Object_WH_G *value){
    *rc = RC_LIST_SUCCESS; GLRC_DLL_WH_G = *rc;
    RC_OBJ_WH_G orc = RC_OBJ_SUCCESS;
    DL_Node *c = NULL; DL_LIST *l = NULL;

    CHECK_DLL_ITR_ISINITED(itr, *rc, );
    CHECK_DLL_ITR_ISINITED(itr->list, *rc, );
    l = ((List_WH_G *)(itr->list))->data; c = itr->cur;
    CHECK_DLL_ITR_ISINITED(l, *rc, );

    if(c == l->head || c == NULL){ //iter指向范围判断
        *rc = RC_LIST_OUT_OF_RANG; GLRC_DLL_WH_G = *rc; return;
    }

    c->data->obj_op->destory(c->data, &orc);
    CHECK_DLL_OBJDEAL_ERROR(orc, *rc, , );

    c->data = value;

    return;
}

/*doc************************************************
 *funcName : DuLkLst_Remove
 *funcDesc : 在index位置删除元素(index范围为1...n)
 *pamrList : List_WH_G *thiz 列表实例; int *rc 状态码; long index 下标;
 *retnValu : void
 *comment  :
 *  1,判断下标位置是否超出范围;
 *  2,itr移动至index,在itr位置删除元素(调用removeC);
*/
static void DuLkLst_Remove(List_WH_G *thiz, int *rc, long index){
    *rc = RC_LIST_SUCCESS; GLRC_DLL_WH_G = *rc;
    Iter_WH_G it;

    CHECK_DLL_ISINITED(thiz, *rc, );

    if(DuLkLst_isVaildIndex(thiz, rc, index) != 1){return;} //下标超出范围

    DuLkLst_MoveToIndex(&it, rc, index, thiz);
    CHECK_DLL_LISTDEAL_ERROR(*rc, , );

    it.itr_op->removeC(&it, rc);

    return;
}

/*doc************************************************
 *funcName : DuLkLst_RemoveC
 *funcDesc : 移除iter所在位置元素
 *pamrList : List_WH_G *thiz 列表实例; int *rc 状态码; retnValu : void
 *comment  : 1,判断iter是否指向有效的节点;2,释放节点数据;3,断开前后节点;4,释放节点;
*/
static void DuLkLst_RemoveC(Iter_WH_G *itr, int *rc){
    *rc = RC_LIST_SUCCESS; GLRC_DLL_WH_G = *rc;
    RC_OBJ_WH_G orc = RC_OBJ_SUCCESS;
    DL_Node *c = NULL; DL_LIST *l = NULL;

    CHECK_DLL_ITR_ISINITED(itr, *rc, );
    CHECK_DLL_ITR_ISINITED(itr->list, *rc, );
    l = ((List_WH_G *)(itr->list))->data; c = itr->cur;
    CHECK_DLL_ITR_ISINITED(l, *rc, );

    if(c == l->head || c == NULL){ //iter指向范围判断
        *rc = RC_LIST_OUT_OF_RANG; GLRC_DLL_WH_G = *rc; return;
    }

    c->data->obj_op->destory(c->data, &orc); //释放节点数据
    CHECK_DLL_OBJDEAL_ERROR(orc, *rc, , );

    itr->cur = c->prior; //itr前移一位

    c->prior->next = c->next; //断开前后节点
    if(NULL != c->next){c->next->prior = c->prior;}
    free(c); //释放节点
    l->length--;

    c = itr->cur;
    if(c->next != NULL){itr->cur = c->next;} //itr后移一位

    return;
}

/*doc************************************************
 *funcName : DuLkLst_FindByIndex
 *funcDesc : 返回index所在位置元素
 *pamrList : List_WH_G *thiz 列表实例; int *rc 状态码; long index 下标;
 *retnValu : Object_WH_G *列表元素实例
 *comment  : 1,判断index是否在有效范围;2,itr移至index;3,返回节点元素;
*/
static Object_WH_G *DuLkLst_FindByIndex(List_WH_G *thiz, int *rc, long index){
    *rc = RC_LIST_SUCCESS; GLRC_DLL_WH_G = *rc;
    Object_WH_G *o = NULL;
    Iter_WH_G it;

    CHECK_DLL_ISINITED(thiz, *rc, NULL);

    if(DuLkLst_isVaildIndex(thiz, rc, index) != 1){return NULL;}//下标超出范围

    DuLkLst_MoveToIndex(&it, rc, index, thiz); //移至index
    CHECK_DLL_LISTDEAL_ERROR(*rc, NULL, );

    o = it.itr_op->current(&it, rc);
    return o;
}

/*doc************************************************
 *funcName : DuLkLst_Length
 *funcDesc : 返回列表长度
 *pamrList : List_WH_G *thiz 列表实例; int *rc 状态码;
 *retnValu : long 列表长度
 *comment  : 返回列表长度;
*/
static long DuLkLst_Length(List_WH_G *thiz, int *rc){
    *rc = RC_LIST_SUCCESS; GLRC_DLL_WH_G = *rc;

    CHECK_DLL_ISINITED(thiz, *rc, -1);

    return ((DL_LIST *)thiz->data)->length;
}

//implement iterator
/*doc************************************************
 *funcName : DuLkLst_toFisrt
 *funcDesc : iter移动到第一个结点
 *pamrList : List_WH_G *thiz 列表实例; int *rc 状态码;
 *retnValu : void
 *comment  : 1,判断head是否有下一个;2,iter移动到head的下一个;
*/
static void DuLkLst_toFisrt(Iter_WH_G *itr, int *rc){
    *rc = RC_LIST_SUCCESS; GLRC_DLL_WH_G = *rc;
    DL_LIST *l = NULL;

    CHECK_DLL_ITR_ISINITED(itr, *rc, );
    CHECK_DLL_ITR_ISINITED(itr->list, *rc, );
    l = ((List_WH_G *)(itr->list))->data;
    CHECK_DLL_ITR_ISINITED(l, *rc, );

    if(l->head->next == NULL){
        *rc = RC_LIST_EMPTY; GLRC_DLL_WH_G = *rc; return;
    }
    itr->cur = l->head->next;

    return;
}

/*doc************************************************
 *funcName : DuLkLst_toLast
 *funcDesc : iter移动到最后一个结点
 *pamrList : List_WH_G *thiz 列表实例; int *rc 状态码;
 *retnValu : void
 *comment  : 1,判断tail是否等于head;2,iter移动到tail;
*/
static void DuLkLst_toLast(Iter_WH_G *itr, int *rc){
    *rc = RC_LIST_SUCCESS; GLRC_DLL_WH_G = *rc;
    DL_LIST *l = NULL;

    CHECK_DLL_ITR_ISINITED(itr, *rc, );
    CHECK_DLL_ITR_ISINITED(itr->list, *rc, );
    l = ((List_WH_G *)(itr->list))->data;
    CHECK_DLL_ITR_ISINITED(l, *rc, );

    if(l->tail == l->head){
        *rc = RC_LIST_EMPTY; GLRC_DLL_WH_G = *rc; return;
    }
    itr->cur = l->tail;

    return;
}

/*doc************************************************
 *funcName : DuLkLst_toNext
 *funcDesc : iter移动下一个
 *pamrList : List_WH_G *thiz 列表实例; int *rc 状态码;
 *retnValu : void
 *comment  : 1,判断是否有下一个;2,iter移动到下一个;
*/
static void DuLkLst_toNext(Iter_WH_G *itr, int *rc){
    *rc = RC_LIST_SUCCESS; GLRC_DLL_WH_G = *rc;
    DL_Node *c = NULL;

    CHECK_DLL_ITR_ISINITED(itr, *rc, );

    c = itr->cur;
    CHECK_DLL_ITR_ISINITED(c, *rc, );

    if(itr->itr_op->hasNext(itr, rc) > 0){
        itr->cur = c->next;
    }

    return;
}

/*doc************************************************
 *funcName : DuLkLst_toPrior
 *funcDesc : iter移动到前一个
 *pamrList : List_WH_G *thiz 列表实例; int *rc 状态码;
 *retnValu : void
 *comment  : 1,判断是否有前一个;2,iter移动到前一个;
*/
static void DuLkLst_toPrior(Iter_WH_G *itr, int *rc){
    *rc = RC_LIST_SUCCESS; GLRC_DLL_WH_G = *rc;
    DL_Node *c = NULL;

    CHECK_DLL_ITR_ISINITED(itr, *rc, );
    c = itr->cur;
    CHECK_DLL_ITR_ISINITED(c, *rc, );

    if(itr->itr_op->hasPrior(itr, rc) > 0){
        itr->cur = c->prior;
    }

    return;
}

/*doc************************************************
 *funcName : DuLkLst_foreach
 *funcDesc : 遍历列表
 *pamrList :
 *  List_WH_G *list 列表实例;
 *  int *rc 状态码;
 *  void (*action) 元素值处理回调方法
 *  void *ctx 元素值处理回调上下文
 *retnValu : void
 *comment  : 1,遍历列表所有元素; 2,调用回调函数处理列表元素
*/
static void DuLkLst_foreach(
        List_WH_G *list,
        int *rc,
        void (*action)(Object_WH_G *val, int *rc ,void *ctx),
        void *ctx
        )
{
    *rc = RC_LIST_SUCCESS; GLRC_DLL_WH_G = *rc;
    Object_WH_G *o = NULL;
    Iter_WH_G it;

    CHECK_DLL_ISINITED(list, *rc, );

    DLL_WH_G_Itr_Bind(&it, rc, list, 0);
    CHECK_DLL_LISTDEAL_ERROR(*rc, ,);

    while(*rc == RC_LIST_SUCCESS){
        o = it.itr_op->current(&it, rc);
        CHECK_DLL_LISTDEAL_ERROR(*rc, ,);

        action(o, rc, ctx);
        CHECK_DLL_LISTDEAL_ERROR(*rc, ,);

        it.itr_op->toNext(&it, rc);
    }

    return;
}

/*doc************************************************
 *funcName : DuLkLst_Current
 *funcDesc : 返回当前结点的data值
 *pamrList : List_WH_G *list 列表实例; int *rc 状态码;
 *retnValu : Object_WH_G *当前结点的data值
 *comment  : 1,判断iter是否指向head, 若是指向第一个;返回值
*/
static Object_WH_G *DuLkLst_Current(Iter_WH_G *itr, int *rc){
    *rc = RC_LIST_SUCCESS; GLRC_DLL_WH_G = *rc;
    DL_Node *c = NULL; DL_LIST *l = NULL;

    CHECK_DLL_ITR_ISINITED(itr, *rc, NULL);
    CHECK_DLL_ITR_ISINITED(itr->list, *rc, NULL);
    l = ((List_WH_G *)(itr->list))->data;
    CHECK_DLL_ITR_ISINITED(l, *rc, NULL);
    c = itr->cur;
    CHECK_DLL_ITR_ISINITED(c, *rc, NULL);

    if(c == l->head){
        itr->itr_op->toFisrt(itr, rc);
        CHECK_DLL_LISTDEAL_ERROR(*rc, NULL, );
    }

    c = itr->cur;
    return c->data;
}

/*doc************************************************
 *funcName : DuLkLst_Next
 *funcDesc : 返回当前结点的下一个data值
 *pamrList : List_WH_G *list 列表实例; int *rc 状态码;
 *retnValu : Object_WH_G *下一结点的data值
 *comment  : 1,判断iter是否有下一个;2,返回值
*/
static Object_WH_G *DuLkLst_Next(Iter_WH_G *itr, int *rc){
    *rc = RC_LIST_SUCCESS; GLRC_DLL_WH_G = *rc;
    DL_Node *c = NULL;

    CHECK_DLL_ITR_ISINITED(itr, *rc, NULL);

    if(itr->itr_op->hasNext(itr, rc) > 0){
        c = itr->cur;
        return c->next->data;
    }

    return NULL;
}

/*doc************************************************
 *funcName : DuLkLst_Prior
 *funcDesc : 返回当前结点的前一个data值
 *pamrList : List_WH_G *list 列表实例; int *rc 状态码;
 *retnValu : Object_WH_G *前一结点的data值
 *comment  : 1,判断iter是否有前一个;2,返回值
*/
static Object_WH_G *DuLkLst_Prior(Iter_WH_G *itr, int *rc){
    *rc = RC_LIST_SUCCESS; GLRC_DLL_WH_G = *rc;
    DL_Node *c = NULL;

    CHECK_DLL_ITR_ISINITED(itr, *rc, NULL);
    c = itr->cur;
    CHECK_DLL_ITR_ISINITED(c, *rc, NULL);

    if(itr->itr_op->hasPrior(itr, rc) > 0){
        c = itr->cur;
        return c->prior->data;
    }

    return NULL;
}

/*doc************************************************
 *funcName : DuLkLst_First
 *funcDesc : 返回第一个data值
 *pamrList : List_WH_G *list 列表实例; int *rc 状态码;
 *retnValu : Object_WH_G *第一个结点的data值
 *comment  : 1,判断列表是否空;2,返回值
*/
static Object_WH_G *DuLkLst_First(Iter_WH_G *itr, int *rc){
    *rc = RC_LIST_SUCCESS; GLRC_DLL_WH_G = *rc;
    DL_LIST *l = NULL;

    CHECK_DLL_ITR_ISINITED(itr, *rc, NULL);
    CHECK_DLL_ISINITED(itr->list, *rc, NULL);

    l = ((List_WH_G *)(itr->list))->data;
    CHECK_DLL_ISINITED(l, *rc, NULL);

    if(l->head->next == NULL){
        *rc = RC_LIST_EMPTY; GLRC_DLL_WH_G = *rc; return NULL;
    }

    return l->head->next->data;
}

/*doc************************************************
 *funcName : DuLkLst_Last
 *funcDesc : 返回最后一个data值
 *pamrList : List_WH_G *list 列表实例; int *rc 状态码;
 *retnValu : Object_WH_G * 最后一个结点的data值
 *comment  : 1,判断列表是否空;2,返回值
*/
static Object_WH_G *DuLkLst_Last(Iter_WH_G *itr, int *rc){
    *rc = RC_LIST_SUCCESS; GLRC_DLL_WH_G = *rc;
    DL_LIST *l = NULL;

    CHECK_DLL_ITR_ISINITED(itr, *rc, NULL);
    CHECK_DLL_ISINITED(itr->list, *rc, NULL);

    l = ((List_WH_G *)(itr->list))->data;
    CHECK_DLL_ISINITED(l, *rc, NULL);

    if(l->tail == l->head){
        *rc = RC_LIST_EMPTY; GLRC_DLL_WH_G = *rc; return NULL;
    }

    return l->tail->data;
}

/*doc************************************************
 *funcName : DuLkLst_hasNext
 *funcDesc : 判断iter是否有下一个
 *pamrList : List_WH_G *thiz 列表实例; int *rc 状态码;
 *retnValu : unsigned char 是否有下一个(1:有;0:无)
 *comment  : 1,判断是否有下一个;
*/
static unsigned char DuLkLst_hasNext(Iter_WH_G *itr, int *rc){
    *rc = RC_LIST_SUCCESS; GLRC_DLL_WH_G = *rc;
    DL_Node *c = NULL;

    CHECK_DLL_ITR_ISINITED(itr, *rc, 0);
    c = itr->cur;
    CHECK_DLL_ITR_ISINITED(c, *rc, 0);

    if(c->next == NULL){
        *rc = RC_ITER_END_OF_LIST; GLRC_DLL_WH_G = *rc; return 0;
    }

    return 1;
}

/*doc************************************************
 *funcName : DuLkLst_hasPrior
 *funcDesc : 判断iter是否有前一个
 *pamrList : List_WH_G *thiz 列表实例; int *rc 状态码;
 *retnValu : unsigned char 是否有下一个(1:有;0:无)
 *comment  : 1,判断是否有前一个;
*/
static unsigned char DuLkLst_hasPrior(Iter_WH_G *itr, int *rc){
    *rc = RC_LIST_SUCCESS; GLRC_DLL_WH_G = *rc;
    DL_Node *c = NULL; DL_LIST *l = NULL;

    CHECK_DLL_ITR_ISINITED(itr, *rc, 0);
    CHECK_DLL_ISINITED(itr->list, *rc, 0);

    l = ((List_WH_G *)(itr->list))->data;
    CHECK_DLL_ITR_ISINITED(l, *rc, 0);
    c = itr->cur;
    CHECK_DLL_ITR_ISINITED(c, *rc, 0);

    if(c->prior == l->head){
        *rc = RC_ITER_HEAD_OF_LIST; GLRC_DLL_WH_G = *rc; return 0;
    }
    return 1;
}

//下标范围有效判断
static int DuLkLst_isVaildIndex(List_WH_G *thiz, int *rc, long index){
    *rc = RC_LIST_SUCCESS; GLRC_DLL_WH_G = *rc;
    long len;

    CHECK_DLL_ISINITED(thiz, *rc, 0);

    len = thiz->lst_op->length(thiz, rc);
    CHECK_DLL_LISTDEAL_ERROR(*rc, 0, );
    if(index <= 0 || index > len){ //下标超出范围
        *rc = RC_LIST_OUT_OF_RANG; GLRC_DLL_WH_G = *rc; return 0;
    }
    return 1;
}

//移至第n个元素
static void DuLkLst_MoveToIndex(Iter_WH_G *itr, int *rc, long index, List_WH_G *list){
    *rc = RC_LIST_SUCCESS; GLRC_DLL_WH_G = *rc;
    long i;

    CHECK_DLL_ITR_ISINITED(itr, *rc, );
    CHECK_DLL_ISINITED(list, *rc, );

    DLL_WH_G_Itr_Bind(itr, rc, list, 0);
    CHECK_DLL_LISTDEAL_ERROR(*rc, , );

    for(i = 0; i < index - 1; i++){
        itr->itr_op->toNext(itr, rc);
        CHECK_DLL_LISTDEAL_ERROR(*rc, , );
    }
    return;
}

//工具方法 itr是否初始化
static int Iter_isInit(Iter_WH_G *itr){
    if(itr == NULL)return 0;
    return 1;
}

//工具方法 list isInit
static int DuLkLst_isInit(List_WH_G *thiz){
    if(thiz == NULL)return 0;
    if(thiz->data == NULL) return 0;
    if(((DL_LIST *)(thiz->data))->head == NULL) return 0;
    return 1;
}
