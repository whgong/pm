#include "loginpage.h"
#include <QApplication>
#include "userpassword.h"
#include <iostream>
#include "contentpage.h"

int main(int argc, char *argv[])
{
    //UserPassword up("jd","13s13","jdqqq111=","jd");
    //std::cout <<"test:up=" << up.toString()<<'\n';
    QApplication a(argc, argv);
    LoginPage lp;
    lp.show();
    int drc = lp.exec();
    std::cout<<"Dialog Return Code:"<<drc<<'\n';
    if(drc==QDialog::Accepted){
        ContentPage cp;
        cp.show();
        return a.exec();
    }
    return 0;
}
