//thisfile : USChar_WH_G.c
#include<stdlib.h>
#include<stdio.h>
#include"USCHAR_WH_G.h"

#define CHECK_USCHAR_ISINITED(OBJ_STR, RC_STR, RETVAL) \
    if(isInited(OBJ_STR) == 1){\
        RC_STR = RC_USCHAR_NOT_INIT; GLRC_USCHAR_WH_G = RC_STR; \
        return RETVAL; \
    }

#define CHECK_USCHAR_DEAL(RC_STR, RETVAL, BEF_RET) \
    if(RC_STR != RC_USCHAR_SUCCESS){ \
        GLRC_USCHAR_WH_G = RC_STR; \
        BEF_RET; \
        return RETVAL; \
    }

//object declare
USChar_WH_G *USChar_WH_G_getInst(int *rc);
void USChar_WH_G_Init(USChar_WH_G *thiz, int *rc);

static void USChar_Set(USChar_WH_G *thiz, int *rc, unsigned char val);
static unsigned char USChar_Get(USChar_WH_G *thiz, int *rc);
static void USChar_WH_G_destory(Object_WH_G *thiz, int *rc);
static void *USChar_Clone(Object_WH_G *thiz, int *rc);
void USChar_toString(Object_WH_G *thiz, int *rc, char *str);
short USChar_Compare(Object_WH_G *thiz, int *rc, Object_WH_G *aVal);

USChar_Op_WH_G GLOP_USCHAR_WH_G={
    USChar_Set, //set
    USChar_Get //get
};

Object_Op_WH_G GLOP_USCHAR_OBJ_WH_G={
    USChar_WH_G_destory, //void (*destory)(Object_WH_G *thiz, int *rc);
    USChar_Clone, //void *(*clone)(Object_WH_G *thiz, int *rc);
    NULL, //void (*set)(Object_WH_G *thiz,
    //            int *rc,
    //            ... //void* vals[] or void* val
    //            );
    USChar_toString, //void (*toString)(Object_WH_G *thiz, int *rc, char *str);
    USChar_Compare, //short (*compare)(Object_WH_G *thiz, int *rc, Object_WH_G *aVal);
    NULL, //void (*releaser)(Object_WH_G *obj);
    NULL //void (*setter)(Object_WH_G *pVal, ...); //void* vals[] or void* val
};

RC_USCHAR_WH_G GLRC_USCHAR_WH_G = RC_USCHAR_SUCCESS;


//tool method
static unsigned char isInited(USChar_WH_G *thiz){
    if(thiz == NULL)return 0;
    return 1;
}

//object implementation
void USChar_WH_G_Init(USChar_WH_G *thiz, int *rc){
    *rc = RC_USCHAR_SUCCESS; GLRC_USCHAR_WH_G = *rc;
	
    CHECK_USCHAR_ISINITED(thiz, *rc, );

    Obj_WH_G_Init(&(thiz->obj), rc);
    if(*rc != RC_OBJ_SUCCESS){GLRC_USCHAR_WH_G = *rc; return;}

    thiz->obj.data = (unsigned char *)malloc(sizeof(unsigned char));
    if(thiz->obj.data == NULL){
        *rc = RC_USCHAR_MEMORY_ALLOC_FAIL; GLRC_USCHAR_WH_G = *rc;
        return;
    }

    thiz->uschar_op = &GLOP_USCHAR_WH_G;
    thiz->obj.obj_op = &GLOP_USCHAR_OBJ_WH_G;
    thiz->obj.obj_op->set = GLOP_OBJ_WH_G.set;

    thiz->uschar_op->set(thiz, rc, 0);

    return;
}

USChar_WH_G * USChar_WH_G_getInst(int *rc){
    USChar_WH_G *obj = NULL;

    obj = (USChar_WH_G *)malloc(sizeof(USChar_WH_G));
    if(NULL == obj){
        *rc = RC_USCHAR_MEMORY_ALLOC_FAIL; GLRC_USCHAR_WH_G = *rc;
        return NULL;
    }

    USChar_WH_G_Init(obj, rc);

	return obj;
}

static void USChar_Set(USChar_WH_G *thiz, int *rc, unsigned char val){
    *rc = RC_USCHAR_SUCCESS; GLRC_USCHAR_WH_G = *rc;

    CHECK_USCHAR_ISINITED(thiz, *rc, );

    *((unsigned char *)(thiz->obj.data)) = val;

    return;
}

static unsigned char USChar_Get(USChar_WH_G *thiz, int *rc){
    *rc = RC_USCHAR_SUCCESS; GLRC_USCHAR_WH_G = *rc;

    CHECK_USCHAR_ISINITED(thiz, *rc, 0);

    return *((unsigned char *)(thiz->obj.data));
}

static void USChar_WH_G_destory(Object_WH_G *thiz, int *rc){
    *rc = RC_USCHAR_SUCCESS; GLRC_USCHAR_WH_G = *rc;

    CHECK_USCHAR_ISINITED(thiz, *rc, );

    if(thiz->obj_op->releaser != NULL){
        thiz->obj_op->releaser(thiz);
    }

    free(thiz->data);
    free(thiz);
    return;
}

static void *USChar_Clone(Object_WH_G *thiz, int *rc){
    *rc = RC_USCHAR_SUCCESS; GLRC_USCHAR_WH_G = *rc;
    USChar_WH_G *res = NULL;

    CHECK_USCHAR_ISINITED(thiz, *rc, res);

    res = USChar_WH_G_getInst(rc);
    CHECK_USCHAR_DEAL(*rc, res, res->obj.obj_op->destory(res, rc));

    *((unsigned char *)(res->obj.data)) = *((unsigned char *)(thiz->data));

    return res;
}

void USChar_toString(Object_WH_G *thiz, int *rc, char *str){
    *rc = RC_USCHAR_SUCCESS; GLRC_USCHAR_WH_G = *rc;

    CHECK_USCHAR_ISINITED(thiz, *rc, );

    sprintf(str, "USChar(@%p:%d)\0", thiz, *((unsigned char *)(thiz->data)));

    return;
}

short USChar_Compare(Object_WH_G *thiz, int *rc, Object_WH_G *aVal){
    *rc = RC_USCHAR_SUCCESS; GLRC_USCHAR_WH_G = *rc;

    unsigned char a, b;

    CHECK_USCHAR_ISINITED(thiz, *rc, -1);
    CHECK_USCHAR_ISINITED(aVal, *rc, -1);

    a = *((unsigned char *)(thiz->data));
    b = *((unsigned char *)(aVal->data));

    if(a > b){
        return 1;
    }
    else if(a == b){
        return 0;
    }
    return -1;

}
