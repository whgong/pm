#ifndef ITERATOR_WH_G_H
#define ITERATOR_WH_G_H

#include <Object_WH_G.h>

typedef enum __ITERATOR_RC_13s13_163COM_{
//    RC_ITER_EMPTY_LIST  = -91003,         //列表空
    RC_ITER_HEAD_OF_LIST = -91002,          //列表的头
    RC_ITER_END_OF_LIST = -91001,           //列表的末尾
//    RC_ITER_OUT_OF_RANG=-4,               //超出列表范围
    RC_ITER_NOT_INIT_ERROR=-3,              //列表未初始化
    RC_ITER_MEMORY_ALLOC_ERROR=-2,          //内存分配失败
    RC_ITER_ERROR=-1,                       //未定义的异常
    RC_ITER_SUCCESS=0                       //成功
} RC_Iterator_WH_G;

typedef struct __ITERATOR_13s13_163_COM_ Iter_WH_G;
typedef struct __ITERATOR_OP_13s13_163_COM_ Iter_Op_WH_G;

struct __ITERATOR_OP_13s13_163_COM_{
    void (*toFisrt)(void *list, RC_Iterator_WH_G *rc);
    void (*toLast)(void *list, RC_Iterator_WH_G *rc);
    void (*toNext)(void *list, RC_Iterator_WH_G *rc);
    void (*toPrior)(void *list, RC_Iterator_WH_G *rc);

    void (*for_each)(void *list, RC_Iterator_WH_G *rc,
                            void (*action)(void *val, RC_Iterator_WH_G *rc ,Object_WH_G * ctx),
                            Object_WH_G *ctx);

    Object_WH_G *(*current)(void *list, RC_Iterator_WH_G *rc);
    Object_WH_G *(*next)(void *list, RC_Iterator_WH_G *rc);
    Object_WH_G *(*prior)(void *list, RC_Iterator_WH_G *rc);
    Object_WH_G *(*first)(void *list, RC_Iterator_WH_G *rc);
    Object_WH_G *(*last)(void *list, RC_Iterator_WH_G *rc);

    unsigned char (*hasNext)(void *list, RC_Iterator_WH_G *rc);
    unsigned char (*hasPrior)(void *list, RC_Iterator_WH_G *rc);
};

struct __ITERATOR_13s13_163_COM_{
    void *cur;
    Iter_Op_WH_G *iop;
};

#endif // ITERATOR_WH_G_H
