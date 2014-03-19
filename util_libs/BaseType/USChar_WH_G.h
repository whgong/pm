#ifndef USCHAR_WH_G_H
#define USCHAR_WH_G_H

#include<Object_WH_G.h>
#define GLOP_USCHAR_WH_G __GLOP_USCHAR_13S13_COM_
#define GLOP_USCHAR_OBJ_WH_G __GLOP_USCHAR_OBJ_13S13_COM_
#define GLRC_USCHAR_WH_G __GLRC_USCHAR_13S13_COM_

typedef enum _USCHAR_RC_13S13_163COM{
    RC_USCHAR_NOT_INIT = -3, //未初始化
    RC_USCHAR_MEMORY_ALLOC_FAIL = -2, //内存分配失败
    RC_USCHAR_ERROR = -1, //未定义的异常
    RC_USCHAR_SUCCESS = 0 //成功
} RC_USCHAR_WH_G;

typedef struct __USCHAR_13S13_163_COM_ USChar_WH_G;
typedef struct __USCHAR_OPER_13S13_163_COM_ USChar_Op_WH_G;

extern USChar_Op_WH_G __GLOP_USCHAR_13S13_COM_;
extern Object_Op_WH_G __GLOP_USCHAR_OBJ_13S13_COM_;
extern RC_USCHAR_WH_G __GLRC_USCHAR_13S13_COM_;

struct __USCHAR_OPER_13S13_163_COM_  { //opertions
    void (*set)(USChar_WH_G *thiz, int *rc, unsigned char val);
    unsigned char (*get)(USChar_WH_G *thiz, int *rc);
};

struct __USCHAR_13S13_163_COM_ {
    Object_WH_G obj;
    USChar_Op_WH_G *uschar_op;
};

USChar_WH_G *USChar_WH_G_getInst(int *rc);
void USChar_WH_G_Init(USChar_WH_G *obj, int *rc);
//void Obj_Op_WH_G_Init(Object_Op_WH_G *op, int *rc);

#endif // USCHAR_WH_G_H
