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
//    QMessageBox mb;
//    mb.setText("dubug:LoginPage::on_btnLogin_clicked in");
//    mb.exec();
    UserDAO dao;
    std::string un = ui->edtUsernm->text().toStdString();
    std::string pwd = ui->edtPasswd->text().toStdString();
//    if (1==1){
    if(dao.validUserByNamePasswd(un,pwd)){
        this->accept();
    }
//    mb.setText("dubug:LoginPage::on_btnLogin_clicked out");
//    mb.exec();
}

void LoginPage::on_btnCancel_clicked()
{
    this->close();
}
