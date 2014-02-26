#include <stdio.h>
#include"Object_WH_G.h"

void setter1(void **val, int c);
//void releaser1(void* val);

//object
void testObject(){
    Object_WH_G *o1 = NULL, *o2 = NULL, *o3 = NULL, *o4 = NULL;
    char tmp[20];
    RC_OBJ_WH_G rc = RC_OBJ_SUCCESS;

    o1 = Obj_WH_G_getInst(&rc);
    o2 = Obj_WH_G_getInst(&rc);
    o3 = Obj_WH_G_getInst(&rc);
    o4 = Obj_WH_G_getInst(&rc);

    o1->obj_op->set(o1, &rc, (void *)1);
    o2->obj_op->set(o2, &rc, (void *)2);
    o3->obj_op->set(o3, &rc, (void *)3);

    o4 = o2->obj_op->clone(o2, &rc);

    o3->obj_op->destory(o3, &rc);

    o1->obj_op->compare(o1, &rc, o4);

    o2->obj_op->toString(o2, &rc, tmp);
    printf("o2 is %s\n", tmp);

    return ;
}

int main(void)
{
    testObject();
    return 0;
}

void setter1(void **val, int c){
    *val = (void*)c;
    return;
}

//void releaser1(void* val){
//    val = 0;
//    return;
//}
