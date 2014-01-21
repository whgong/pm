//this file:DualLinkedList.h
#ifdef __cplusplus
extern "C" {
#endif 

#define RC_DUALLINKEDLIST RC_DUALLINKEDLIST_13s13_163_COM

//typedef int Ret;
typedef enum _DLLIST_RC_13s13_163COM{
    RC_DLL_SUCCESS=0,                       //成功
    RC_DLL_EMPTY_LIST  = -7, 				//列表空
    RC_DLL_HEAD_OF_LIST = -6,				//列表的头
    RC_DLL_END_OF_LIST = -5,                //列表的末尾
    RC_DLL_OUT_OF_RANG=-4,                  //超出列表范围，
    RC_DLL_LIST_NOT_INIT_ERROR=-3,          //列表未初始化
    RC_DLL_MEMORY_ALLOC_ERROR=-2,           //内存分配失败
    RC_DLL_ERROR=-1                         //未定义的异常
} DLL_RET_CD;

extern DLL_RET_CD RC_DUALLINKEDLIST_13s13_163_COM; //列表操作状态码(全局), 非多线程环境可使用

typedef struct _DLL_ST_List_13s13_163COM DualLinkedListST;
typedef struct _DualLinkedList_13s13_163COM DualLinkedList;

DualLinkedList* DuLkLst_getInstance(DLL_RET_CD *rc);

struct _DualLinkedList_13s13_163COM{
    //property-----------------------------------------------
    DualLinkedListST *data;
    //function-----------------------------------------------
    DLL_RET_CD (*destory)(DualLinkedList *thiz, DLL_RET_CD *rc);
    DLL_RET_CD (*append)(DualLinkedList *thiz, DLL_RET_CD *rc, void *data);
    DLL_RET_CD (*insert)(DualLinkedList *thiz, DLL_RET_CD *rc, long index, void* data);
    DLL_RET_CD (*remove)(DualLinkedList *thiz, DLL_RET_CD *rc, long index);
    DLL_RET_CD (*update)(DualLinkedList *thiz, DLL_RET_CD *rc, long index, void *data);
    DLL_RET_CD (*updateC)(DualLinkedList *thiz, DLL_RET_CD *rc, void *data);
    void * (*get)(DualLinkedList * thiz, DLL_RET_CD *rc,long index);
    void * (*getC)(DualLinkedList * thiz, DLL_RET_CD *rc);
    DLL_RET_CD (*toFirst)(DualLinkedList * thiz, DLL_RET_CD *rc);
    DLL_RET_CD (*toNext)(DualLinkedList * thiz, DLL_RET_CD *rc);
    DLL_RET_CD (*toPrior)(DualLinkedList * thiz, DLL_RET_CD *rc);
    DLL_RET_CD (*for_each)(DualLinkedList *thiz, DLL_RET_CD *rc, DLL_RET_CD (*action)(void *,void *), void *ctx);
    long (*getLen)(DualLinkedList *thiz, DLL_RET_CD *rc);
};

#ifdef __cplusplus
}
#endif

