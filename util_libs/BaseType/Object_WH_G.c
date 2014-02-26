#include"Object_WH_G.h"
#include<stdlib.h>
#include<stdio.h>
#include<stdarg.h>

//declare==============================================================
Object_WH_G *Obj_WH_G_getInst(int *rc);
void Obj_WH_G_Init(Object_WH_G *obj, int *rc);
//Object_Op_WH_G *Obj_WH_G_getOpInst(int *rc);
void Obj_Op_WH_G_Init(Object_Op_WH_G *op, int *rc);
static void Object_WH_G_toString(Object_WH_G *thiz, int *rc, char* str);
static short Object_WH_G_compare(Object_WH_G *thiz, int *rc, Object_WH_G *aVal);

static void Object_WH_G_destory(Object_WH_G *thiz, int *rc);
static void *Object_WH_G_clone(Object_WH_G *thiz, int *rc);
static void Object_WH_G_set(Object_WH_G *thiz, int *rc,...);

//global variable==================================================
Object_Op_WH_G GLOP_OBJ_WH_G = { //全局op
    Object_WH_G_destory, //destory
    Object_WH_G_clone, //clone
    Object_WH_G_set, //set
    Object_WH_G_toString, //toString
    Object_WH_G_compare, //compare
    NULL,
    NULL
    };

//implements===========================================================
Object_WH_G *Obj_WH_G_getInst(int *rc){
    *rc = RC_OBJ_SUCCESS;
    Object_WH_G *res = NULL;

    res = (Object_WH_G *)malloc(sizeof(Object_WH_G));
    if(res == NULL){
        *rc = RC_OBJ_MEMORY_ALLOC_FAIL; return NULL;
    }

    Obj_WH_G_Init(res, rc);
    if(*rc != RC_OBJ_SUCCESS)
        return NULL;

    return res;
}

void Obj_WH_G_Init(Object_WH_G *obj, int *rc){
    *rc = RC_OBJ_SUCCESS;

    if(obj == NULL){*rc = RC_OBJ_NOT_INIT; return;}

    obj->obj_op = &GLOP_OBJ_WH_G;
    obj->data = NULL;

    return ;
}

void Obj_Op_WH_G_Init(Object_Op_WH_G *op, int *rc){
    *rc = RC_OBJ_SUCCESS;

    if(NULL == op){*rc = RC_OBJ_NOT_INIT; return;}

    if(op->destory != GLOP_OBJ_WH_G.destory){
        op->destory = GLOP_OBJ_WH_G.destory;
        op->clone = GLOP_OBJ_WH_G.clone;
        op->set = GLOP_OBJ_WH_G.set;
        op->toString = GLOP_OBJ_WH_G.toString;
        op->compare = GLOP_OBJ_WH_G.compare;
        op->setter = GLOP_OBJ_WH_G.setter;
        op->releaser = GLOP_OBJ_WH_G.releaser;
    }

    return ;
}

static void Object_WH_G_destory(Object_WH_G *thiz, int *rc){
    *rc = RC_OBJ_SUCCESS;

    if(thiz->obj_op->releaser != NULL){
        thiz->obj_op->releaser(thiz);
    }

    free(thiz);
    return;
}

static void *Object_WH_G_clone(Object_WH_G *thiz, int *rc){
    *rc = RC_OBJ_SUCCESS;
    Object_WH_G *res = NULL;

    res = (Object_WH_G*)malloc(sizeof(Object_WH_G));
    if(res == NULL){*rc = RC_OBJ_MEMORY_ALLOC_FAIL; return NULL;}

    res->data = thiz->data;
    res->obj_op = thiz->obj_op;

    return res;
}

static void Object_WH_G_set(Object_WH_G *thiz, int *rc, ...){
    *rc = RC_OBJ_SUCCESS;
    va_list ap;

    va_start(ap,rc);

    if(thiz->obj_op->setter != NULL){
        thiz->obj_op->setter(thiz, *((void **)ap));
    }

    thiz->data = *((void **)ap);

    va_end(ap);

    return;
}

static void Object_WH_G_toString(Object_WH_G *thiz, int *rc, char *str){
    *rc = RC_OBJ_SUCCESS;

    sprintf(str, "OBJ(@%p)", thiz);
    return;
}

static short Object_WH_G_compare(Object_WH_G *thiz, int *rc, Object_WH_G *aVal){
    *rc = RC_OBJ_SUCCESS;

    if(thiz == aVal)return 0;
    else if(thiz > aVal)return 1;
    else return -1;
}
