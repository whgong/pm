//this file:DualLinkedList.h
#ifdef __cplusplus
extern "C" {
#endif

#include"List_WH_G.h"

//marco list
#define GLOP_DLL_L_WH_G __OP_DLL_LST_13s13_163_COM_ //列表操作变量(全局)
#define GLOP_DLL_I_WH_G __OP_DLL_ITR_13s13_163_COM_ //迭代器操作变量(全局)
#define GLOP_DLL_O_WH_G __OP_DLL_OBJ_13s13_163_COM_ //操作变量(全局)
#define GLRC_DLL_WH_G __RC_DLL_13s13_163_COM_ //列表操作状态码(全局), 非多线程环境可使用

//variable list
extern List_Op_WH_G __OP_DLL_LST_13s13_163_COM_;
extern Iter_Op_WH_G __OP_DLL_ITR_13s13_163_COM_;
extern Object_Op_WH_G __OP_DLL_OBJ_13s13_163_COM_;
extern RC_LIST_WH_G __RC_DLL_13s13_163_COM_;

//method list
List_WH_G *DLL_WH_G_getInst(int *rc); //新建实例方法
void DLL_WH_G_Init(List_WH_G *thiz, int *rc); //实例初始化方法
void DLL_WH_G_Itr_Bind(Iter_WH_G *itr, int *rc, void *list, unsigned char soe); //迭代器绑定方法
void DLL_WH_G_Itr_Set(Iter_WH_G *itr, int *rc, Iter_WH_G *src); //迭代器赋值方法

#ifdef __cplusplus
}
#endif

