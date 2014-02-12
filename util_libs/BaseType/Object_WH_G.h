#ifndef OBJECT_WH_G_H
#define OBJECT_WH_G_H

typedef enum _OBJ_RC_13s13_163COM{
    RC_OBJ_NOT_INIT = -3, //未初始化
    RC_OBJ_MEMORY_ALLOC_ERROR = -2, //内存分配失败
    RC_OBJ_ERROR = -1, //未定义的异常
    RC_OBJ_SUCCESS = 0 //成功
} RC_OBJ_WH_G;

typedef struct __OBJECT_13S13_163_COM_ Object_WH_G;
typedef struct __OBJECT_OPER_13S13_163_COM_ Obj_Op_WH_G;

struct __OBJECT_OPER_13S13_163_COM_  { //object opertions
    void (*destory)(void *thiz, RC_OBJ_WH_G *rc);
    void *(*clone)(void *thiz, RC_OBJ_WH_G *rc);
    void (*set)(void *thiz, RC_OBJ_WH_G *rc, ...);
    void (*setter)(void **val, ...);
    void (*bindSetter)(Obj_Op_WH_G *op, RC_OBJ_WH_G *rc, void (*setter)(void **val, ...));
    void (*releaser)(void *val);
    void (*bindReleaser)(Obj_Op_WH_G *op, RC_OBJ_WH_G *rc, void (*releaser)(void* val));
    void (*toString)(void *thiz, RC_OBJ_WH_G *rc, char *str);
    short (*compare)(void *thiz, RC_OBJ_WH_G *rc, void *aVal);
    void (*freeOp)(Obj_Op_WH_G *op, RC_OBJ_WH_G *rc);
};

struct __OBJECT_13S13_163_COM_{ //object
    void *val; //data
    Obj_Op_WH_G *op; //operation
};

Object_WH_G *Object_WH_G_getInst(RC_OBJ_WH_G *rc);
void Object_WH_G_Init(Object_WH_G *obj, RC_OBJ_WH_G *rc);
Obj_Op_WH_G *Object_WH_G_getOpInst(RC_OBJ_WH_G *rc);
void Obj_Op_WH_G_Init(Obj_Op_WH_G *op, RC_OBJ_WH_G *rc);
void Object_WH_G_bindOperation(Object_WH_G *obj, Obj_Op_WH_G *op, RC_OBJ_WH_G *rc);

#endif // OBJECT_WH_G_H
