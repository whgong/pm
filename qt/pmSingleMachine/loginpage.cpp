#include "loginpage.h"
#include "ui_loginpage.h"
#include "userdao.h"
#include <iostream>
#include <QMessageBox>

LoginPage::LoginPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginPage)
{
    ui->setupUi(this);
}

LoginPage::~LoginPage()
{
    delete ui;
}

void LoginPage::on_btnLogin_clicked()
{
    UserDAO dao;
    std::string un = ui->edtUsernm->text().toStdString();
    std::string pwd = ui->edtPasswd->text().toStdString();
    if(dao.validUserByNamePasswd(un,pwd)){
        this->accept();
    }
    else {
        QMessageBox mb;
        mb.setText("用户名密码错误！！！");
        mb.exec();
    }
}

void LoginPage::on_btnCancel_clicked()
{
    this->close();
}
