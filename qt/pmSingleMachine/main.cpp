#include "loginpage.h"
#include <QApplication>
#include "userpassword.h"
#include <iostream>
#include "contentpage.h"

#include "globalvariable.h"
#include "utilconfig.h"
#include <map>

std::map<std::string,std::string> *cfg;

void funcExitAction(){
    delete cfg;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); //初始化QT应用

    cfg = UtilConfig::loadConfig(); //获取配置信息

    atexit(funcExitAction); //绑定退出时执行的动作

    LoginPage lp; //登陆页面
    lp.show();
    int drc = lp.exec();
    if(drc==QDialog::Accepted){
        ContentPage cp;
        cp.show();
        return a.exec();
    }
    return 0;
}
