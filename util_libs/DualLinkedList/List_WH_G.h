#ifndef LIST_WH_G_H
#define LIST_WH_G_H

#include<Object_WH_G.h>
#include"Iterator_WH_G.h"

typedef enum _LIST_RC_13s13_163COM{
    RC_LIST_OUT_OF_RANG = -90002, //超出范围
    RC_LIST_EMPTY = -90001, //列表空
    RC_LIST_NOT_INIT = -3, //未初始化
    RC_LIST_MEMORY_ALLOC_FAIL = -2, //内存分配失败
    RC_LIST_ERROR = -1, //未定义的异常
    RC_LIST_SUCCESS = 0 //成功
} RC_LIST_WH_G;

typedef struct __LIST_13S13_163_COM_ List_WH_G;

typedef struct __LIST_OP_13S13_163_COM_{ //list operator
    void (*insert)(void *thiz, int *rc, long index, Object_WH_G *value);
    void (*append)(void *thiz, int *rc, Object_WH_G *value);
    void (*update)(void *thiz, int *rc, long index, Object_WH_G *value);
    void (*remove)(void *thiz, int *rc, long index);
    Object_WH_G *(*findByIndex)(void *thiz, int *rc, long index);
    long (*length)(void *thiz, int *rc);
    void (*for_each)(void *thiz, int *rc,
                     void (*action)(Object_WH_G *val, int *rc ,void *ctx),
                     void *ctx);
} List_Op_WH_G;

struct __LIST_13S13_163_COM_{ //list data
    void *data;
    Object_Op_WH_G *obj_op;
    List_Op_WH_G *lst_op;
};

#endif // LIST_WH_G_H
