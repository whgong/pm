#include"Object_WH_G.h"
#include<stdlib.h>
#include<stdio.h>
#include<stdarg.h>

//macro================================================================
#define CHECK_OBJ_ISINITED(OBJ_STR, RC_STR, RET_STR) \
    if(!objIsInit(OBJ_STR)){ \
        RC_STR = RC_OBJ_NOT_INIT; \
        return RET_STR; \
    }

#define CHECK_OBJOP_ISINITED(OP_STR, RC_STR, RET_STR) \
    if(!opIsInit(OP_STR)){ \
        RC_STR = RC_OBJ_NOT_INIT; \
        return RET_STR; \
    }

#define CHECK_OBJ_OBJDEAL(RC_STR, RET_STR) \
    if(RC_STR != RC_OBJ_SUCCESS){ \
        RC_STR = RC_OBJ_NOT_INIT; \
        return RET_STR; \
    }

//declare==============================================================
Object_WH_G *Object_WH_G_getInst(RC_OBJ_WH_G *rc);
void Object_WH_G_Init(Object_WH_G *obj, RC_OBJ_WH_G *rc);
Obj_Op_WH_G *Object_WH_G_getOpInst(RC_OBJ_WH_G *rc);
void Obj_Op_WH_G_Init(Obj_Op_WH_G *op, RC_OBJ_WH_G *rc);
static void Object_WH_G_freeOpInst(Obj_Op_WH_G *op, RC_OBJ_WH_G *rc);
void Object_WH_G_bindOperation(Object_WH_G *obj, Obj_Op_WH_G *op, RC_OBJ_WH_G *rc);
static void Object_WH_G_bindSetter(Obj_Op_WH_G *op, RC_OBJ_WH_G *rc, void (*setter)(void **val, ...));
static void Object_WH_G_bindReleaser(Obj_Op_WH_G *op, RC_OBJ_WH_G *rc, void (*releaser)(void* val));
static void Object_WH_G_toString(void *thiz, RC_OBJ_WH_G *rc, char* str);
static short Object_WH_G_compare(void *thiz, RC_OBJ_WH_G *rc, void *aVal);

static void Object_WH_G_destory(void *thiz, RC_OBJ_WH_G *rc);
static void *Object_WH_G_clone(void *thiz, RC_OBJ_WH_G *rc);
static void Object_WH_G_set(void *thiz, RC_OBJ_WH_G *rc, ...);
//tool method
static unsigned char objIsInit(void *obj);
static unsigned char opIsInit(void *op);

//global variable==================================================
static Obj_Op_WH_G OP_OBJECT_GL={ //全局op
    Object_WH_G_destory, //destory
    Object_WH_G_clone, //clone
    Object_WH_G_set, //set
    NULL, //setter
    Object_WH_G_bindSetter, //bindSetter
    NULL, //releaser
    Object_WH_G_bindReleaser, //bindReleaser
    Object_WH_G_toString, //toString
    Object_WH_G_compare, //compare
    Object_WH_G_freeOpInst //freeOp
    };

//implements===========================================================
void Object_WH_G_Init(Object_WH_G *obj, RC_OBJ_WH_G *rc){
    *rc = RC_OBJ_SUCCESS;

    CHECK_OBJ_ISINITED(obj, *rc, );

    Obj_Op_WH_G_Init(&OP_OBJECT_GL, rc);
    CHECK_OBJ_OBJDEAL(*rc, );

    obj->val = NULL;
    obj->op = &OP_OBJECT_GL;

    return;
}

void Obj_Op_WH_G_Init(Obj_Op_WH_G *op, RC_OBJ_WH_G *rc){
    *rc = RC_OBJ_SUCCESS;

    if(NULL == op){
        *rc = RC_OBJ_NOT_INIT;
        return;
    }

    if(op->destory != Object_WH_G_destory){
        op->destory = Object_WH_G_destory;
        op->clone = Object_WH_G_clone;
        op->set = Object_WH_G_set;
        op->bindSetter = Object_WH_G_bindSetter;
        op->bindReleaser = Object_WH_G_bindReleaser;
        op->freeOp = Object_WH_G_freeOpInst;
        op->setter = NULL;
        op->releaser = NULL;
    }

    return;
}

void Object_WH_G_bindOperation(Object_WH_G *obj, Obj_Op_WH_G *op, RC_OBJ_WH_G *rc){
    *rc = RC_OBJ_SUCCESS;

    CHECK_OBJ_ISINITED(obj, *rc, );
    CHECK_OBJOP_ISINITED(op, *rc, );

    obj->op = op;

    return;
}

Object_WH_G *Object_WH_G_getInst(RC_OBJ_WH_G *rc){
    *rc = RC_OBJ_SUCCESS;
    Object_WH_G *obj = NULL;
    obj = (Object_WH_G *)malloc(sizeof(Object_WH_G));
    if(NULL == obj){
        *rc = RC_OBJ_MEMORY_ALLOC_ERROR;
        return NULL;
    }

    Object_WH_G_Init(obj, rc);
    CHECK_OBJ_OBJDEAL(*rc, NULL)

    return obj;
}

static void Object_WH_G_destory(void *thiz, RC_OBJ_WH_G *rc){
    *rc = RC_OBJ_SUCCESS;
    Object_WH_G *obj = thiz;

    CHECK_OBJ_ISINITED(obj, *rc, );
    CHECK_OBJOP_ISINITED(obj->op, *rc, );

    if(NULL != obj->op->releaser){
        obj->op->releaser(obj->val);
    }

    free(thiz);
    return;
}

static void *Object_WH_G_clone(void *thiz, RC_OBJ_WH_G *rc){
    *rc = RC_OBJ_SUCCESS;
    Object_WH_G *obj = thiz, *res = NULL;

    CHECK_OBJ_ISINITED(obj, *rc, NULL);
    CHECK_OBJOP_ISINITED(obj->op, *rc, NULL);

    res = (Object_WH_G *)Object_WH_G_getInst(rc);
    CHECK_OBJ_OBJDEAL(*rc, NULL);

    res->val = obj->val;
    res->op = obj->op;

    return res;
}

static void Object_WH_G_set(void *thiz, RC_OBJ_WH_G *rc, ...){
    *rc = RC_OBJ_SUCCESS;
    Object_WH_G *obj = thiz;
    va_list ap;

    CHECK_OBJ_ISINITED(obj, *rc, );
    CHECK_OBJOP_ISINITED(obj->op, *rc, );

    va_start(ap,rc);

    if(NULL != obj->op->setter){
        obj->op->setter(&(obj->val), *((void**)ap));
    }

    obj->val = *((void**)ap);

    va_end(ap);

    return;
}

static void Object_WH_G_bindSetter(Obj_Op_WH_G *op, RC_OBJ_WH_G *rc, void (*setter)(void **val, ...)){
    *rc = RC_OBJ_SUCCESS;
    CHECK_OBJOP_ISINITED(op, *rc, );

    op->setter = setter;

    return;
}

static void Object_WH_G_bindReleaser(Obj_Op_WH_G *op, RC_OBJ_WH_G *rc, void (*releaser)(void* val)){
    *rc = RC_OBJ_SUCCESS;
    CHECK_OBJOP_ISINITED(op, *rc, );

    op->releaser = releaser;

    return;
}

static unsigned char objIsInit(void *obj){

    if(NULL == obj){
        return 0;
    }
    if(NULL == ((Object_WH_G*)obj)->op){
        return 0;
    }
    return 1;
}

static unsigned char opIsInit(void *op){
    if(NULL == op){
        return 0;
    }
    if(NULL == ((Obj_Op_WH_G*)op)->destory){
        return 0;
    }
    return 1;
}

Obj_Op_WH_G *Object_WH_G_getOpInst(RC_OBJ_WH_G *rc){
    *rc = RC_OBJ_SUCCESS;
    Obj_Op_WH_G *res = NULL;

    res = (Obj_Op_WH_G *)malloc(sizeof(Obj_Op_WH_G));
    if(NULL == res){
        *rc = RC_OBJ_MEMORY_ALLOC_ERROR;
        return NULL;
    }

    Obj_Op_WH_G_Init(res, rc);
    CHECK_OBJ_OBJDEAL(*rc, NULL);

    return res;
}

static void Object_WH_G_freeOpInst(Obj_Op_WH_G *op, RC_OBJ_WH_G *rc){
    *rc = RC_OBJ_SUCCESS;

    free(op);

    return;
}

static void Object_WH_G_toString(void *thiz, RC_OBJ_WH_G *rc, char* str){
    *rc = RC_OBJ_SUCCESS;

    sprintf(str, "OBJ(@%p)", thiz);
    return;
}

static short Object_WH_G_compare(void *thiz, RC_OBJ_WH_G *rc, void *aVal){
    *rc = RC_OBJ_SUCCESS;

    if(thiz == aVal)return 0;
    else if(thiz > aVal)return 1;
    else return -1;
}
