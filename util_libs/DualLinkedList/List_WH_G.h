#ifndef LIST_WH_G_H
#define LIST_WH_G_H

#include<Object_WH_G.h>
#include"Iterator_WH_G.h"

#define RC_LIST_WH_G_GL RC_LIST_13s13_163_COM

typedef enum _LIST_RC_13s13_163COM{
    RC_LIST_OUT_OF_RANG = -90002, //超出范围
    RC_LIST_EMPTY = -90001, //列表空
    RC_LIST_NOT_INIT = -3, //未初始化
    RC_LIST_MEMORY_ALLOC_ERROR = -2, //内存分配失败
    RC_LIST_ERROR = -1, //未定义的异常
    RC_LIST_SUCCESS = 0 //成功
} RC_LIST_WH_G;

extern RC_LIST_WH_G RC_LIST_13s13_163_COM; //列表操作状态码(全局), 非多线程环境可使用

typedef struct __LIST_13S13_163_COM_ List_WH_G;

typedef struct __LIST_OP_13S13_163_COM_{ //list operator
    void (*insert)(void *thiz, RC_LIST_WH_G *rc, long index, Object_WH_G *value);
    void (*insertC)(void *thiz, RC_LIST_WH_G *rc, Object_WH_G *value);
    void (*append)(void *thiz, RC_LIST_WH_G *rc, Object_WH_G *value);
    void (*update)(void *thiz, RC_LIST_WH_G *rc, long index, Object_WH_G *value);
    void (*updateC)(void *thiz, RC_LIST_WH_G *rc, Object_WH_G *value);
    void (*remove)(void *thiz, RC_LIST_WH_G *rc, long index);
    void (*removeC)(void *thiz, RC_LIST_WH_G *rc);
    Object_WH_G *(*findByIndex)(void *thiz, RC_LIST_WH_G *rc, long index);
    long (*length)(void *thiz, RC_LIST_WH_G *rc);
}List_Op_WH_G;

struct __LIST_13S13_163_COM_{ //list data
    Object_WH_G obj;
    Iter_WH_G *itr;
    List_Op_WH_G *lop;
};

List_WH_G *List_WH_G_getInst(RC_LIST_WH_G *rc);
void List_WH_G_Init(List_WH_G *thiz, RC_LIST_WH_G *rc);

#endif // LIST_WH_G_H
