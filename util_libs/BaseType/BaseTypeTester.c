#include <stdio.h>
#include"Object_WH_G.h"

void setter1(void **val, int c);
void releaser1(void* val);

Object_WH_G *testGetInst(RC_OBJ_WH_G *rc);
void testBindOP(RC_OBJ_WH_G *rc);
void testSet(RC_OBJ_WH_G *rc);
void testDestory(RC_OBJ_WH_G *rc);
Object_WH_G *testClone(RC_OBJ_WH_G *rc);

int main(void)
{
    Object_WH_G *o1 = NULL, *o2 = NULL;
    Obj_Op_WH_G *op = NULL;
    RC_OBJ_WH_G rc = RC_OBJ_SUCCESS;

    printf("create a object...\n");
    o1 = Object_WH_G_getInst(&rc);
    if(rc == RC_OBJ_SUCCESS){
        printf("getInst success!!!obj=%p\n",o1);
    }
    else {
        printf("getInst fail!!!\n");
    }

    printf("create a object op and init...\n");
    op = Object_WH_G_getOpInst(&rc);
    if(rc == RC_OBJ_SUCCESS){
        printf("init op success!!!op=%p\n",&op);
    }
    else {
        printf("init op fail!!!\n");
    }

    printf("bind setter...\n");
    op->bindSetter(op, &rc, setter1);

    printf("bind releaser...\n");
    op->bindReleaser(op, &rc, releaser1);

    printf("bind op...\n");
    Object_WH_G_bindOperation(o1, op, &rc);
    if(rc == RC_OBJ_SUCCESS){
        printf("bind op success!!!setter=%p\n",op->setter);
    }
    else {
        printf("bind op fail!!!\n");
    }

    printf("set value for o1...\n");
    o1->op->set(o1, &rc, 5);
    if(rc == RC_OBJ_SUCCESS){
        printf("set value success!!!o1.val=%d\n",(int)o1->val);
    }
    else {
        printf("set value fail!!!\n");
    }

    printf("clone o1 to o2...\n");
    o2 = o1->op->clone(o1, &rc);
    if(rc == RC_OBJ_SUCCESS){
        printf("clone o1 to o2 success!!!o2.val=%d\n",(int)o2->val);
    }
    else {
        printf("clone o1 to o2 fail!!!\n");
    }

    printf("destory o1...\n");
    o1->op->destory(o1, &rc);
    if(rc == RC_OBJ_SUCCESS){
        printf("destory o1 success!!!o2.val=%d\n",(int)o2->val);
    }
    else {
        printf("destory o1 fail!!!\n");
    }

    return 0;
}

void setter1(void **val, int c){
    *val = (void*)c;
    return;
}

void releaser1(void* val){
    val = 0;
    return;
}
