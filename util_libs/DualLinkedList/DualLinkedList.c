//thisfile:DualLinkedList.c
#include <stdlib.h>
#include <stdio.h>
#include "List_WH_G.h"
#include<stdarg.h>

//maco======================================================================
//maco for check is inited
#define CHECK_DLL_ISINITED(OBJ_STR, RC_STR, RETURN_STR)     \
    if(DuLkLst_isInit(OBJ_STR)==0){                         \
        RC_STR = RC_LIST_NOT_INIT;                          \
        RC_LIST_WH_G_GL = RC_STR;                           \
        return RETURN_STR;                                  \
    }

//maco for check obj deal error
#define CHECK_DLL_OBJDEAL_ERROR(ORC_STR, RC_STR, RETURN_STR, BEFORE_RETURN)        \
    if(ORC_STR != RC_OBJ_SUCCESS){                                  \
        RC_STR = RC_OBJ_ERROR;                                      \
        RC_LIST_WH_G_GL = RC_STR;                                   \
        BEFORE_RETURN;                                              \
        return RETURN_STR;                                          \
    }

//maco for check list deal error
#define CHECK_DLL_LISTDEAL_ERROR(RC_STR, RETURN_STR, BEFORE_RETURN)        \
    if(RC_STR != RC_LIST_SUCCESS){                                  \
        BEFORE_RETURN;                                              \
        return RETURN_STR;                                          \
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
List_WH_G *List_WH_G_getInst(RC_LIST_WH_G *rc);
void List_WH_G_Init(List_WH_G *thiz, RC_LIST_WH_G *rc);
//extend from obj
static void DuLkLst_Destory(List_WH_G *thiz, RC_LIST_WH_G *rc);
static List_WH_G *DuLkLst_Clone(List_WH_G *thiz, RC_LIST_WH_G *rc);
static void DuLkLst_Set(List_WH_G *thiz, RC_LIST_WH_G *rc, ...);
//implement list
static void DuLkLst_Insert(List_WH_G *thiz, RC_LIST_WH_G *rc, long index, Object_WH_G *value);
static void DuLkLst_InsertC(List_WH_G *thiz, RC_LIST_WH_G *rc, Object_WH_G *value);
static void DuLkLst_Append(List_WH_G *thiz, RC_LIST_WH_G *rc, Object_WH_G *value);
static void DuLkLst_Update(List_WH_G *thiz, RC_LIST_WH_G *rc, long index, Object_WH_G *value);
static void DuLkLst_UpdateC(List_WH_G *thiz, RC_LIST_WH_G *rc, Object_WH_G *value);
static void DuLkLst_Remove(List_WH_G *thiz, RC_LIST_WH_G *rc, long index);
static void DuLkLst_RemoveC(List_WH_G *thiz, RC_LIST_WH_G *rc);
static Object_WH_G *DuLkLst_FindByIndex(List_WH_G *thiz, RC_LIST_WH_G *rc, long index);
static long DuLkLst_Length(List_WH_G *thiz, RC_LIST_WH_G *rc);
//implement iterator
static void DuLkLst_toFisrt(List_WH_G *list, RC_Iterator_WH_G *rc);
static void DuLkLst_toLast(List_WH_G *list, RC_Iterator_WH_G *rc);
static void DuLkLst_toNext(List_WH_G *list, RC_Iterator_WH_G *rc);
static void DuLkLst_toPrior(List_WH_G *list, RC_Iterator_WH_G *rc);
static void DuLkLst_foreach(
        List_WH_G *list,
        RC_Iterator_WH_G *rc,
        void (*action)(Object_WH_G *val, RC_Iterator_WH_G *rc ,Object_WH_G * ctx),
        Object_WH_G *ctx
        );
static Object_WH_G *DuLkLst_Current(List_WH_G *list, RC_Iterator_WH_G *rc);
static Object_WH_G *DuLkLst_Next(List_WH_G *list, RC_Iterator_WH_G *rc);
static Object_WH_G *DuLkLst_Prior(List_WH_G *list, RC_Iterator_WH_G *rc);
static Object_WH_G *DuLkLst_First(List_WH_G *list, RC_Iterator_WH_G *rc);
static Object_WH_G *DuLkLst_Last(List_WH_G *list, RC_Iterator_WH_G *rc);
static unsigned char DuLkLst_hasNext(List_WH_G *list, RC_Iterator_WH_G *rc);
static unsigned char DuLkLst_hasPrior(List_WH_G *list, RC_Iterator_WH_G *rc);
//tool method
static int DuLkLst_isInit(List_WH_G *thiz);
static int DuLkLst_isVaildIndex(List_WH_G *thiz, RC_LIST_WH_G *rc, long index);
static void DuLkLst_MoveToIndex(List_WH_G *thiz, RC_LIST_WH_G *rc, long index);

//global variable==========================================================
static List_Op_WH_G LIST_OP_GL = {
    DuLkLst_Insert, DuLkLst_InsertC, DuLkLst_Append,
    DuLkLst_Update, DuLkLst_UpdateC, DuLkLst_Remove,
    DuLkLst_RemoveC, DuLkLst_FindByIndex, DuLkLst_Length
};

static Iter_Op_WH_G ITER_OP_GL = {
    DuLkLst_toFisrt, DuLkLst_toLast, DuLkLst_toNext,
    DuLkLst_toPrior, DuLkLst_foreach, DuLkLst_Current,
    DuLkLst_Next, DuLkLst_Prior, DuLkLst_First,
    DuLkLst_Last, DuLkLst_hasNext, DuLkLst_hasPrior
};

RC_LIST_WH_G RC_LIST_WH_G_GL = RC_LIST_SUCCESS; //全局状态码

//implements===============================================================
/*doc************************************************
 *funcName : List_WH_G_Init
 *funcDesc : 对已分配内存的list初始化
 *pamrList : List_WH_G *thiz 列表实例;RC_LIST_WH_G *rc 状态码
 *retnValu : void
 *comment  : 1,初始换obj;2,初始化lop;3,itr;4,创建队列;5,插入头结点;6,绑定扩展方法;
*/
void List_WH_G_Init(List_WH_G *thiz, RC_LIST_WH_G *rc){
    *rc = RC_LIST_SUCCESS; RC_LIST_WH_G_GL = *rc;
    RC_OBJ_WH_G orc = RC_OBJ_SUCCESS;
    Object_WH_G *obj = NULL;
    DL_Node *head = NULL; DL_LIST *list = NULL;

    if(NULL == thiz){ //空指针判断
        *rc = RC_LIST_NOT_INIT; RC_LIST_WH_G_GL = *rc; return;
    }

    Object_WH_G_Init(&(thiz->obj), &orc); //初始化obj
    CHECK_DLL_OBJDEAL_ERROR(orc, *rc, ,);

    //创建队列
    list = (DL_LIST *)malloc(sizeof(DL_LIST));
    if(list == NULL){
        *rc = RC_LIST_MEMORY_ALLOC_ERROR; RC_LIST_WH_G_GL = *rc;
        return;
    }
    //创建头结点
    head = (DL_Node *)malloc(sizeof(DL_Node));
    if(head == NULL){
        *rc = RC_LIST_MEMORY_ALLOC_ERROR; RC_LIST_WH_G_GL = *rc;
        free(list); return;
    }

    head->data = Object_WH_G_getInst(&orc); //初始化头结点
    CHECK_DLL_OBJDEAL_ERROR(orc, *rc, , free(list);free(head));
    head->data = NULL; head->next = NULL; head->prior = NULL;
    //初始化队列
    list->head = head; list->length = 0; list->tail = head;

    thiz->obj.op->set(&(thiz->obj), &orc, list); //绑定队列
    CHECK_DLL_OBJDEAL_ERROR(orc, *rc, , free(list);free(head->data);free(head));

    thiz->lop = &LIST_OP_GL; //初始化lop

    //初始化itr
    thiz->itr = NULL;
    thiz->itr = (Iter_WH_G *)malloc(sizeof(Iter_WH_G));
    if(thiz->itr == NULL){
        *rc = RC_OBJ_MEMORY_ALLOC_ERROR; RC_LIST_WH_G_GL = *rc;
        free(list); free(head->data); free(head); free(thiz->itr); return;
    }
    thiz->itr->iop = &ITER_OP_GL;
    thiz->itr->cur = list->head;

    //绑定扩展方法
    thiz->obj.op->destory = DuLkLst_Destory;
    thiz->obj.op->clone = DuLkLst_Clone;
    thiz->obj.op->set = DuLkLst_Set;

    return;
}

/*doc************************************************
 *funcName : List_WH_G_getInst
 *funcDesc : 获取list实例
 *pamrList : RC_LIST_WH_G *rc 状态码
 *retnValu : List_WH_G * 列表实例
 *comment  : 1,list分配内存;2,初始化list;
*/
List_WH_G *List_WH_G_getInst(RC_LIST_WH_G *rc){
    *rc = RC_LIST_SUCCESS; RC_LIST_WH_G_GL = *rc;
    List_WH_G *res = NULL;
    res = (List_WH_G*)malloc(sizeof(List_WH_G));
    if(res == NULL){
        *rc = RC_LIST_MEMORY_ALLOC_ERROR; RC_LIST_WH_G_GL = *rc;
        return NULL;
    }

    List_WH_G_Init(res, rc);
    CHECK_DLL_LISTDEAL_ERROR(*rc, NULL, );

    return res;
}

/*doc************************************************
 *funcName : DuLkLst_Destory
 *funcDesc : 列表destory方法
 *pamrList : List_WH_G *thiz 列表实例; RC_LIST_WH_G *rc 状态码;
 *retnValu : void
 *comment  : 1,依次移除队列中元素;2,释放head节点;3,释放申请的资源;
*/
static void DuLkLst_Destory(List_WH_G *thiz, RC_LIST_WH_G *rc){
    *rc = RC_LIST_SUCCESS; RC_LIST_WH_G_GL = *rc;
    DL_LIST *l = NULL;
    CHECK_DLL_ISINITED(thiz, *rc, );

    thiz->itr->iop->toFisrt(thiz, rc);
    CHECK_DLL_LISTDEAL_ERROR(*rc, , );
    while(*rc == RC_LIST_SUCCESS){
        thiz->lop->removeC(thiz, rc);
        CHECK_DLL_LISTDEAL_ERROR(*rc, , );
    }

    l = (DL_LIST *)(thiz->obj.val);
    free(l->head); //释放head节点
    free(l);    //释放list
    free(thiz->itr);
    free(thiz);

    return;
}

/*doc************************************************
 *funcName : DuLkLst_Clone
 *funcDesc : 列表clone方法
 *pamrList : List_WH_G *thiz 列表实例; RC_LIST_WH_G *rc 状态码;
 *retnValu : List_WH_G *列表实例
 *comment  : 1,新建队列;2,向列表追加原队列中元素的clone值;
*/
static List_WH_G *DuLkLst_Clone(List_WH_G *thiz, RC_LIST_WH_G *rc){
    *rc = RC_LIST_SUCCESS; RC_LIST_WH_G_GL = *rc;
    RC_OBJ_WH_G orc = RC_OBJ_SUCCESS;
    Object_WH_G *tmp = NULL;
    List_WH_G *l = NULL;

    CHECK_DLL_ISINITED(thiz, *rc, NULL);

    l = List_WH_G_getInst(rc);
    CHECK_DLL_LISTDEAL_ERROR(*rc, NULL, );

    thiz->itr->iop->toFisrt(thiz, rc);
    CHECK_DLL_LISTDEAL_ERROR(*rc, NULL, l->obj.op->destory(l, &orc));

    while (*rc == RC_LIST_SUCCESS) {
        tmp = thiz->itr->iop->current(thiz, rc);
        CHECK_DLL_LISTDEAL_ERROR(*rc, NULL, l->obj.op->destory(l, &orc));

        tmp = tmp->op->clone(tmp, &orc);
        CHECK_DLL_LISTDEAL_ERROR(*rc, NULL, l->obj.op->destory(l, &orc));

        l->lop->append(l, rc, tmp);
        CHECK_DLL_LISTDEAL_ERROR(*rc, NULL, l->obj.op->destory(l, &orc));

        thiz->itr->iop->toNext(thiz, rc);
    }

    return l;
}

/*doc************************************************
 *funcName : DuLkLst_Set
 *funcDesc : 列表批量赋值
 *pamrList :
 *  List_WH_G *thiz 列表实例; RC_LIST_WH_G *rc 状态码;
 *  ... int + Object_WH_G* 赋值个数 + 实例序列;
 *retnValu : void
 *comment  : 1,清空队列;2,获取赋值个数;3,向列表追加值;
*/
static void DuLkLst_Set(List_WH_G *thiz, RC_LIST_WH_G *rc, ...){
    *rc = RC_LIST_SUCCESS; RC_LIST_WH_G_GL = *rc;
    va_list ap;
    long n = 0, i=0;

    CHECK_DLL_ISINITED(thiz, *rc, );

    //清空列表
    thiz->itr->iop->toFisrt(thiz, rc);
    CHECK_DLL_LISTDEAL_ERROR(*rc, , );
    while (*rc==RC_LIST_SUCCESS) {
        thiz->lop->removeC(thiz, rc);
        CHECK_DLL_LISTDEAL_ERROR(*rc, , );
    }

    va_start(ap,rc);
    //获取赋值个数
    n = *((int *)ap);
    //依次追加至队列
    for(i = 0; i < n; i++){
        va_arg(ap, void *);
        thiz->lop->append(thiz, rc, *((Object_WH_G **)ap));
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
 *  RC_LIST_WH_G *rc 状态码;
 *  long index 下标;
 *  Object_WH_G *value 追加值实例;
 *retnValu : void
 *comment  :
 *  1,判断下标位置是否超出范围;
 *  2,下标位置指向队尾,追加元素(调用append);
 *  3,itr移动至index,在itr位置插入元素(调用insertC);
*/
static void DuLkLst_Insert(List_WH_G *thiz, RC_LIST_WH_G *rc, long index, Object_WH_G *value){
    *rc = RC_LIST_SUCCESS; RC_LIST_WH_G_GL = *rc;
    long len;

    CHECK_DLL_ISINITED(thiz, *rc, );

    len = thiz->lop->length(thiz, rc);
    CHECK_DLL_LISTDEAL_ERROR(*rc, , );
    if(index == len + 1){ //下标位置为列表末尾
        thiz->lop->append(thiz, rc, value);
        CHECK_DLL_LISTDEAL_ERROR(rc, , );
    }
    else if(DuLkLst_isVaildIndex(thiz, rc, index) != 1){ //下标超出范围
        return;
    }

    DuLkLst_MoveToIndex(thiz, rc, index);
    CHECK_DLL_LISTDEAL_ERROR(*rc, , );

    thiz->lop->insertC(thiz, rc, value);

    return;
}

/*doc************************************************
 *funcName : DuLkLst_InsertC
 *funcDesc : 在iter所在位置插入元素value
 *pamrList : List_WH_G *thiz 列表实例; RC_LIST_WH_G *rc 状态码; Object_WH_G *value 追加值实例;
 *retnValu : void
 *comment  : 1,判断队列是否为空,在尾部追加;2,判断iter是否指向head,指向第一个元素;3,新建node;4,插入node;
*/
static void DuLkLst_InsertC(List_WH_G *thiz, RC_LIST_WH_G *rc, Object_WH_G *value){
    *rc = RC_LIST_SUCCESS; RC_LIST_WH_G_GL = *rc;
    DL_Node *n = NULL, *c = NULL; DL_LIST *l = NULL;

    CHECK_DLL_ISINITED(thiz, *rc, );
    l = (DL_LIST*)(thiz->obj.val); c = (DL_Node *)(thiz->itr->cur);

    if(thiz->itr->cur == l->head){ //iter指向head
        if(l->head->next == NULL){ //队列空
            thiz->lop->append(thiz, rc, value);
            CHECK_DLL_LISTDEAL_ERROR(*rc, , );
        }
        else { //队列不空
            thiz->itr->iop->toFisrt(thiz, rc);
            CHECK_DLL_LISTDEAL_ERROR(*rc, , );
        }
    }

    n = (DL_Node *)malloc(sizeof(DL_Node));
    if(n == NULL){*rc = RC_LIST_MEMORY_ALLOC_ERROR; RC_LIST_WH_G_GL = *rc; return;}

    n->data = value;
    n->next = c;
    n->prior = c->prior;
    c->prior->next = n;
    c->prior = n;
    l->length++;
    thiz->itr->cur = n;

    return;
}

/*doc************************************************
 *funcName : DuLkLst_Append
 *funcDesc : 队尾追加value
 *pamrList : List_WH_G *thiz 列表实例; RC_LIST_WH_G *rc 状态码; Object_WH_G *value 追加值实例;
 *retnValu : List_WH_G * 列表实例
 *comment  : 1,新建node;2,追加node;
*/
static void DuLkLst_Append(List_WH_G *thiz, RC_LIST_WH_G *rc, Object_WH_G *value){
    *rc = RC_LIST_SUCCESS; RC_LIST_WH_G_GL = *rc;
    DL_LIST *l = NULL; DL_Node *n = NULL;

    CHECK_DLL_ISINITED(thiz, *rc, );

    n = (DL_Node *)malloc(sizeof(DL_Node)); //新建node
    if(n == NULL){*rc = RC_LIST_MEMORY_ALLOC_ERROR; RC_LIST_WH_G_GL = *rc; return;}

    l = (DL_LIST *)(thiz->obj.val);

    n->data = value;
    n->next = NULL;
    n->prior = l->tail; //node的前置指向原队尾
    l->tail->next = n;  //原队尾的后置指向新node

    l->length++;

    l->tail = n; //队尾指针指向新node
    thiz->itr->cur = n; //iter指向新node

    return;
}

/*doc************************************************
 *funcName : DuLkLst_Update
 *funcDesc : 在index位置修改元素value(index范围为1...n)
 *pamrList :
 *  List_WH_G *thiz 列表实例;
 *  RC_LIST_WH_G *rc 状态码;
 *  long index 下标;
 *  Object_WH_G *value 追加值实例;
 *retnValu : void
 *comment  :
 *  1,判断下标位置是否超出范围; 2,itr移动至index,在itr位置更新元素(调用updateC);
*/
static void DuLkLst_Update(List_WH_G *thiz, RC_LIST_WH_G *rc, long index, Object_WH_G *value){
    *rc = RC_LIST_SUCCESS; RC_LIST_WH_G_GL = *rc;

    CHECK_DLL_ISINITED(thiz, *rc, );

    if(DuLkLst_isVaildIndex(thiz, rc, index) != 1){return;}//下标超出范围

    DuLkLst_MoveToIndex(thiz, rc, index);
    CHECK_DLL_LISTDEAL_ERROR(*rc, , );

    thiz->lop->updateC(thiz, rc, value);

    return;
}

/*doc************************************************
 *funcName : DuLkLst_UpdateC
 *funcDesc : 在iter所在位置更新元素为value
 *pamrList : List_WH_G *thiz 列表实例; RC_LIST_WH_G *rc 状态码; Object_WH_G *value 追加值实例;
 *retnValu : void
 *comment  : 1,判断iter是否指向有效的节点;2,释放原节点数据;3,更新节点数据为value;
*/
static void DuLkLst_UpdateC(List_WH_G *thiz, RC_LIST_WH_G *rc, Object_WH_G *value){
    *rc = RC_LIST_SUCCESS; RC_LIST_WH_G_GL = *rc;
    RC_OBJ_WH_G orc = RC_OBJ_SUCCESS;
    DL_Node *c = NULL; DL_LIST *l = NULL;

    CHECK_DLL_ISINITED(thiz, *rc, );
    l = (DL_LIST*)(thiz->obj.val); c = (DL_Node *)(thiz->itr->cur);

    if(c == l->head || c == NULL){ //iter指向范围判断
        *rc = RC_LIST_OUT_OF_RANG; RC_LIST_WH_G_GL = *rc; return;
    }

    c->data->op->destory(c->data, &orc);
    CHECK_DLL_OBJDEAL_ERROR(orc, *rc, , );

    c->data = value;

    return;
}

/*doc************************************************
 *funcName : DuLkLst_Remove
 *funcDesc : 在index位置删除元素(index范围为1...n)
 *pamrList : List_WH_G *thiz 列表实例; RC_LIST_WH_G *rc 状态码; long index 下标;
 *retnValu : void
 *comment  :
 *  1,判断下标位置是否超出范围;
 *  2,itr移动至index,在itr位置删除元素(调用removeC);
*/
static void DuLkLst_Remove(List_WH_G *thiz, RC_LIST_WH_G *rc, long index){
    *rc = RC_LIST_SUCCESS; RC_LIST_WH_G_GL = *rc;

    CHECK_DLL_ISINITED(thiz, *rc, );

    if(DuLkLst_isVaildIndex(thiz, rc, index) != 1){return;} //下标超出范围

    DuLkLst_MoveToIndex(thiz, rc, index);
    CHECK_DLL_LISTDEAL_ERROR(*rc, , );

    thiz->lop->removeC(thiz, rc);

    return;
}

/*doc************************************************
 *funcName : DuLkLst_RemoveC
 *funcDesc : 移除iter所在位置元素
 *pamrList : List_WH_G *thiz 列表实例; RC_LIST_WH_G *rc 状态码; retnValu : void
 *comment  : 1,判断iter是否指向有效的节点;2,释放节点数据;3,断开前后节点;4,释放节点;
*/
static void DuLkLst_RemoveC(List_WH_G *thiz, RC_LIST_WH_G *rc){
    *rc = RC_LIST_SUCCESS; RC_LIST_WH_G_GL = *rc;
    RC_OBJ_WH_G orc = RC_OBJ_SUCCESS;
    DL_Node *c = NULL; DL_LIST *l = NULL;

    CHECK_DLL_ISINITED(thiz, *rc, );
    l = (DL_LIST*)(thiz->obj.val); c = (DL_Node *)(thiz->itr->cur);

    if(c == l->head || c == NULL){ //iter指向范围判断
        *rc = RC_LIST_OUT_OF_RANG; RC_LIST_WH_G_GL = *rc; return;
    }

    c->data->op->destory(c->data, &orc); //释放节点数据
    CHECK_DLL_OBJDEAL_ERROR(orc, *rc, , );

    thiz->itr->cur = c->prior; //itr前移一位

    c->prior->next = c->next; //断开前后节点
    c->next->prior = c->prior;
    free(c); //释放节点
    l->length--;

    c = (DL_Node *)(thiz->itr->cur);
    if(c->next != NULL){ //itr后移一位
        thiz->itr->cur = c->next;
    }

    return;
}

/*doc************************************************
 *funcName : DuLkLst_FindByIndex
 *funcDesc : 返回index所在位置元素
 *pamrList : List_WH_G *thiz 列表实例; RC_LIST_WH_G *rc 状态码; long index 下标;
 *retnValu : Object_WH_G * 列表元素实例
 *comment  : 1,判断index是否在有效范围;2,itr移至index;3,返回节点元素;
*/
static Object_WH_G *DuLkLst_FindByIndex(List_WH_G *thiz, RC_LIST_WH_G *rc, long index){
    *rc = RC_LIST_SUCCESS; RC_LIST_WH_G_GL = *rc;
    Object_WH_G *o = NULL;

    CHECK_DLL_ISINITED(thiz, *rc, NULL);

    if(DuLkLst_isVaildIndex(thiz, rc, index) != 1){return NULL;}//下标超出范围

    DuLkLst_MoveToIndex(thiz, rc, index); //移至index
    CHECK_DLL_LISTDEAL_ERROR(*rc, NULL, );

    o = thiz->itr->iop->current(thiz, rc);
    return o;
}

/*doc************************************************
 *funcName : DuLkLst_Length
 *funcDesc : 返回列表长度
 *pamrList : List_WH_G *thiz 列表实例; RC_LIST_WH_G *rc 状态码;
 *retnValu : long 列表长度
 *comment  : 返回列表长度;
*/
static long DuLkLst_Length(List_WH_G *thiz, RC_LIST_WH_G *rc){
    *rc = RC_LIST_SUCCESS; RC_LIST_WH_G_GL = *rc;

    CHECK_DLL_ISINITED(thiz, *rc, -1);

    return ((DL_LIST *)thiz->obj.val)->length;
}

//implement iterator
/*doc************************************************
 *funcName : DuLkLst_toFisrt
 *funcDesc : iter移动到第一个结点
 *pamrList : List_WH_G *thiz 列表实例; RC_LIST_WH_G *rc 状态码;
 *retnValu : void
 *comment  : 1,判断head是否有下一个;2,iter移动到head的下一个;
*/
static void DuLkLst_toFisrt(List_WH_G *list, RC_Iterator_WH_G *rc){
    *rc = RC_LIST_SUCCESS; RC_LIST_WH_G_GL = *rc;
    DL_LIST *l = NULL;

    CHECK_DLL_ISINITED(list, *rc, );

    l = (DL_LIST*)(list->obj.val);

    if(l->head->next == NULL){
        *rc = RC_LIST_EMPTY; RC_LIST_WH_G_GL = *rc; return;
    }
    list->itr->cur = l->head->next;

    return;
}

/*doc************************************************
 *funcName : DuLkLst_toLast
 *funcDesc : iter移动到最后一个结点
 *pamrList : List_WH_G *thiz 列表实例; RC_LIST_WH_G *rc 状态码;
 *retnValu : void
 *comment  : 1,判断tail是否等于head;2,iter移动到tail;
*/
static void DuLkLst_toLast(List_WH_G *list, RC_Iterator_WH_G *rc){
    *rc = RC_LIST_SUCCESS; RC_LIST_WH_G_GL = *rc;
    DL_LIST *l = NULL;

    CHECK_DLL_ISINITED(list, *rc, );

    l = (DL_LIST*)(list->obj.val);

    if(l->tail == l->head){
        *rc = RC_LIST_EMPTY; RC_LIST_WH_G_GL = *rc; return;
    }
    list->itr->cur = l->tail;

    return;
}

/*doc************************************************
 *funcName : DuLkLst_toNext
 *funcDesc : iter移动下一个
 *pamrList : List_WH_G *thiz 列表实例; RC_LIST_WH_G *rc 状态码;
 *retnValu : void
 *comment  : 1,判断是否有下一个;2,iter移动到下一个;
*/
static void DuLkLst_toNext(List_WH_G *list, RC_Iterator_WH_G *rc){
    *rc = RC_LIST_SUCCESS; RC_LIST_WH_G_GL = *rc;
    DL_Node *c = NULL;

    CHECK_DLL_ISINITED(list, *rc, );

    c = (DL_Node *)(list->itr->cur);

    if(list->itr->iop->hasNext(list, rc) > 0){
        list->itr->cur = c->next;
    }

    return;
}

/*doc************************************************
 *funcName : DuLkLst_toPrior
 *funcDesc : iter移动到前一个
 *pamrList : List_WH_G *thiz 列表实例; RC_LIST_WH_G *rc 状态码;
 *retnValu : void
 *comment  : 1,判断是否有前一个;2,iter移动到前一个;
*/
static void DuLkLst_toPrior(List_WH_G *list, RC_Iterator_WH_G *rc){
    *rc = RC_LIST_SUCCESS; RC_LIST_WH_G_GL = *rc;
    DL_Node *c = NULL;

    CHECK_DLL_ISINITED(list, *rc, );
    c = (DL_Node *)(list->itr->cur);

    if(list->itr->iop->hasPrior(list, rc) > 0){
        list->itr->cur = c->prior;
    }

    return;
}

/*doc************************************************
 *funcName : DuLkLst_foreach
 *funcDesc : 遍历列表
 *pamrList :
 *  List_WH_G *list 列表实例;
 *  RC_LIST_WH_G *rc 状态码;
 *  void (*action) 元素值处理回调方法
 *  Object_WH_G *ctx 元素值处理回调上下文
 *retnValu : void
 *comment  : 1,遍历列表所有元素; 2,调用回调函数处理列表元素
*/
static void DuLkLst_foreach(
        List_WH_G *list,
        RC_Iterator_WH_G *rc,
        void (*action)(Object_WH_G *val, RC_Iterator_WH_G *rc ,Object_WH_G * ctx),
        Object_WH_G *ctx
        )
{
    *rc = RC_LIST_SUCCESS; RC_LIST_WH_G_GL = *rc;
    Object_WH_G *o = NULL;

    CHECK_DLL_ISINITED(list, *rc, );

    list->itr->iop->toFisrt(list, rc);
    CHECK_DLL_LISTDEAL_ERROR(*rc, ,);

    while(*rc == RC_LIST_SUCCESS){
        o = list->itr->iop->current(list, rc);
        CHECK_DLL_LISTDEAL_ERROR(*rc, ,);

        action(o, rc, ctx);
        CHECK_DLL_LISTDEAL_ERROR(*rc, ,);

        list->itr->iop->toNext(list, rc);
    }

    return;
}

/*doc************************************************
 *funcName : DuLkLst_Current
 *funcDesc : 返回当前结点的data值
 *pamrList : List_WH_G *list 列表实例; RC_LIST_WH_G *rc 状态码;
 *retnValu : Object_WH_G * 当前结点的data值
 *comment  : 1,判断iter是否指向head, 若是指向第一个;返回值
*/
static Object_WH_G *DuLkLst_Current(List_WH_G *list, RC_Iterator_WH_G *rc){
    *rc = RC_LIST_SUCCESS; RC_LIST_WH_G_GL = *rc;
    DL_Node *c = NULL; DL_LIST *l = NULL;

    CHECK_DLL_ISINITED(list, *rc, NULL);
    l = (DL_LIST*)(list->obj.val);
    c = (DL_Node *)(list->itr->cur);

    if(c == l->head){
        list->itr->iop->toFisrt(list, rc);
        CHECK_DLL_LISTDEAL_ERROR(*rc, NULL, );
    }

    return c->data;
}

/*doc************************************************
 *funcName : DuLkLst_Next
 *funcDesc : 返回当前结点的下一个data值
 *pamrList : List_WH_G *list 列表实例; RC_LIST_WH_G *rc 状态码;
 *retnValu : Object_WH_G * 下一结点的data值
 *comment  : 1,判断iter是否有下一个;2,返回值
*/
static Object_WH_G *DuLkLst_Next(List_WH_G *list, RC_Iterator_WH_G *rc){
    *rc = RC_LIST_SUCCESS; RC_LIST_WH_G_GL = *rc;
    DL_Node *c = NULL;

    CHECK_DLL_ISINITED(list, *rc, NULL);

    if(list->itr->iop->hasNext(list, rc) > 0){
        c = (DL_Node *)(list->itr->cur);
        return c->next->data;
    }

    return NULL;
}

/*doc************************************************
 *funcName : DuLkLst_Prior
 *funcDesc : 返回当前结点的前一个data值
 *pamrList : List_WH_G *list 列表实例; RC_LIST_WH_G *rc 状态码;
 *retnValu : Object_WH_G * 前一结点的data值
 *comment  : 1,判断iter是否有前一个;2,返回值
*/
static Object_WH_G *DuLkLst_Prior(List_WH_G *list, RC_Iterator_WH_G *rc){
    *rc = RC_LIST_SUCCESS; RC_LIST_WH_G_GL = *rc;
    DL_Node *c = NULL;

    CHECK_DLL_ISINITED(list, *rc, NULL);

    if(list->itr->iop->hasPrior(list, rc) > 0){
        c = (DL_Node *)(list->itr->cur);
        return c->prior->data;
    }

    return NULL;
}

/*doc************************************************
 *funcName : DuLkLst_First
 *funcDesc : 返回第一个data值
 *pamrList : List_WH_G *list 列表实例; RC_LIST_WH_G *rc 状态码;
 *retnValu : Object_WH_G * 第一个结点的data值
 *comment  : 1,判断列表是否空;2,返回值
*/
static Object_WH_G *DuLkLst_First(List_WH_G *list, RC_Iterator_WH_G *rc){
    *rc = RC_LIST_SUCCESS; RC_LIST_WH_G_GL = *rc;
    DL_LIST *l = NULL;

    CHECK_DLL_ISINITED(list, *rc, NULL);
    l = (DL_LIST*)(list->obj.val);

    if(l->head->next == NULL){
        *rc = RC_LIST_EMPTY; RC_LIST_WH_G_GL = *rc; return NULL;
    }

    return l->head->next->data;
}

/*doc************************************************
 *funcName : DuLkLst_Last
 *funcDesc : 返回最后一个data值
 *pamrList : List_WH_G *list 列表实例; RC_LIST_WH_G *rc 状态码;
 *retnValu : Object_WH_G * 最后一个结点的data值
 *comment  : 1,判断列表是否空;2,返回值
*/
static Object_WH_G *DuLkLst_Last(List_WH_G *list, RC_Iterator_WH_G *rc){
    *rc = RC_LIST_SUCCESS; RC_LIST_WH_G_GL = *rc;
    DL_LIST *l = NULL;

    CHECK_DLL_ISINITED(list, *rc, NULL);
    l = (DL_LIST*)(list->obj.val);

    if(l->tail == l->head){
        *rc = RC_LIST_EMPTY; RC_LIST_WH_G_GL = *rc; return NULL;
    }

    return l->tail->data;
}

/*doc************************************************
 *funcName : DuLkLst_hasNext
 *funcDesc : 判断iter是否有下一个
 *pamrList : List_WH_G *thiz 列表实例; RC_LIST_WH_G *rc 状态码;
 *retnValu : unsigned char 是否有下一个(1:有;0:无)
 *comment  : 1,判断是否有下一个;
*/
static unsigned char DuLkLst_hasNext(List_WH_G *list, RC_Iterator_WH_G *rc){
    *rc = RC_LIST_SUCCESS; RC_LIST_WH_G_GL = *rc;
    DL_Node *c = NULL;

    CHECK_DLL_ISINITED(list, *rc, 0);
    c = (DL_Node *)(list->itr->cur);

    if(c->next == NULL){
        *rc = RC_ITER_END_OF_LIST; RC_LIST_WH_G_GL = *rc; return 0;
    }

    return 1;
}

/*doc************************************************
 *funcName : DuLkLst_hasPrior
 *funcDesc : 判断iter是否有前一个
 *pamrList : List_WH_G *thiz 列表实例; RC_LIST_WH_G *rc 状态码;
 *retnValu : unsigned char 是否有下一个(1:有;0:无)
 *comment  : 1,判断是否有前一个;
*/
static unsigned char DuLkLst_hasPrior(List_WH_G *list, RC_Iterator_WH_G *rc){
    *rc = RC_LIST_SUCCESS; RC_LIST_WH_G_GL = *rc;
    DL_Node *c = NULL; DL_LIST *l = NULL;

    CHECK_DLL_ISINITED(list, *rc, 0);
    l = (DL_LIST*)(list->obj.val);
    c = (DL_Node *)(list->itr->cur);

    if(c->prior == l->head){
        *rc = RC_ITER_HEAD_OF_LIST; RC_LIST_WH_G_GL = *rc; return 0;
    }
    return 1;
}

//isInit
static int DuLkLst_isInit(List_WH_G *thiz){
    if(thiz == NULL)return 0;
    if(thiz->obj.val == NULL) return 0;
    if(thiz->obj.op == NULL) return 0;
    if(thiz->obj.op->destory == NULL) return 0;
    if(thiz->lop == NULL)return 0;
    if(thiz->itr == NULL)return 0;
    return 1;
}

//下标范围有效判断
static int DuLkLst_isVaildIndex(List_WH_G *thiz, RC_LIST_WH_G *rc, long index){
    *rc = RC_LIST_SUCCESS; RC_LIST_WH_G_GL = *rc;
    long len;

    CHECK_DLL_ISINITED(thiz, *rc, 0);
    len = thiz->lop->length(thiz, rc);
    CHECK_DLL_LISTDEAL_ERROR(*rc, 0, );
    if(index <= 0 || index > len){ //下标超出范围
        *rc = RC_LIST_OUT_OF_RANG; RC_LIST_WH_G_GL = *rc; return 0;
    }
    return 1;
}

//移至第n个元素
static void DuLkLst_MoveToIndex(List_WH_G *thiz, RC_LIST_WH_G *rc, long index){
    *rc = RC_LIST_SUCCESS; RC_LIST_WH_G_GL = *rc;
    long i;

    thiz->itr->iop->toFisrt(thiz, rc);
    CHECK_DLL_LISTDEAL_ERROR(*rc, , );
    for(i = 0; i < index - 1; i++){
        thiz->itr->iop->toNext(thiz, rc);
        CHECK_DLL_LISTDEAL_ERROR(*rc, , );
    }
    return;
}
