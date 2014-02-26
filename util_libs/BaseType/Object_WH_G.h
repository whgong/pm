#ifndef OBJECT_WH_G_H
#define OBJECT_WH_G_H

typedef enum _OBJ_RC_13S13_163COM{
    RC_OBJ_NOT_INIT = -3, //未初始化
    RC_OBJ_MEMORY_ALLOC_FAIL = -2, //内存分配失败
    RC_OBJ_ERROR = -1, //未定义的异常
    RC_OBJ_SUCCESS = 0 //成功
} RC_OBJ_WH_G;

typedef struct __OBJECT_13S13_163_COM_ Object_WH_G;
typedef struct __OBJECT_OPER_13S13_163_COM_ Object_Op_WH_G;

extern Object_Op_WH_G GLOP_OBJ_WH_G;

struct __OBJECT_OPER_13S13_163_COM_  { //object opertions
    void (*destory)(Object_WH_G *thiz, int *rc);
    void *(*clone)(Object_WH_G *thiz, int *rc);
    void (*set)(Object_WH_G *thiz,
                int *rc,
                ... //void* vals[] or void* val
                );
    void (*toString)(Object_WH_G *thiz, int *rc, char *str);
    short (*compare)(Object_WH_G *thiz, int *rc, Object_WH_G *aVal);

    void (*releaser)(Object_WH_G *obj);
    void (*setter)(Object_WH_G *pVal, ...); //void* vals[] or void* val
};

struct __OBJECT_13S13_163_COM_ {
    void *data;
    Object_Op_WH_G *obj_op;
};

Object_WH_G *Obj_WH_G_getInst(int *rc);
void Obj_WH_G_Init(Object_WH_G *obj, int *rc);
void Obj_Op_WH_G_Init(Object_Op_WH_G *op, int *rc);

#endif // OBJECT_WH_G_H
