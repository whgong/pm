#ifndef ITERATOR_WH_G_H
#define ITERATOR_WH_G_H

#include <Object_WH_G.h>

typedef enum __ITERATOR_RC_13s13_163COM_{
    RC_ITER_HEAD_OF_LIST = -91002,          //列表的头
    RC_ITER_END_OF_LIST = -91001,           //列表的末尾
    RC_ITER_NOT_INIT_ERROR=-3,              //列表未初始化
    RC_ITER_MEMORY_ALLOC_ERROR=-2,          //内存分配失败
    RC_ITER_ERROR=-1,                       //未定义的异常
    RC_ITER_SUCCESS=0                       //成功
} RC_Iterator_WH_G;

typedef struct __ITERATOR_13s13_163_COM_ Iter_WH_G;
typedef struct __ITERATOR_OP_13s13_163_COM_ Iter_Op_WH_G;

struct __ITERATOR_OP_13s13_163_COM_{
    void (*toFisrt)(Iter_WH_G *itr, int *rc);
    void (*toLast)(Iter_WH_G *itr, int *rc);
    void (*toNext)(Iter_WH_G *itr, int *rc);
    void (*toPrior)(Iter_WH_G *itr, int *rc);

    Object_WH_G *(*current)(Iter_WH_G *itr, int *rc);
    Object_WH_G *(*next)(Iter_WH_G *itr, int *rc);
    Object_WH_G *(*prior)(Iter_WH_G *itr, int *rc);
    Object_WH_G *(*first)(Iter_WH_G *itr, int *rc);
    Object_WH_G *(*last)(Iter_WH_G *itr, int *rc);

    unsigned char (*hasNext)(Iter_WH_G *itr, int *rc);
    unsigned char (*hasPrior)(Iter_WH_G *itr, int *rc);

    void (*insertC)(Iter_WH_G *itr, int *rc, Object_WH_G *value);
    void (*updateC)(Iter_WH_G *itr, int *rc, Object_WH_G *value);
    void (*removeC)(Iter_WH_G *itr, int *rc);

};

struct __ITERATOR_13s13_163_COM_{
    void *cur;
    void *list;
    Iter_Op_WH_G *itr_op;
};

//vitual function
//void (*bind)(Iter_WH_G *itr, int *rc, void *list, unsigned char soe);
//void (*set)(Iter_WH_G *itr, int *rc, Iter_WH_G *src);

#endif // ITERATOR_WH_G_H
