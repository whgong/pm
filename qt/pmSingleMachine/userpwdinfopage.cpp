#include "userpwdinfopage.h"
#include "ui_userpwdinfopage.h"
#include "updao.h"

UserPwdInfoPage::UserPwdInfoPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserPwdInfoPage)
{
    ui->setupUi(this);
    this->ptp = Ui::addnew;
}

UserPwdInfoPage::UserPwdInfoPage(UserPassword *up, QWidget *parent):
    QDialog(parent),
    ui(new Ui::UserPwdInfoPage)
{
    ui->setupUi(this);
    this->ptp = Ui::modify;
    this->crup = up;
    this->setInitValue();
}

UserPwdInfoPage::~UserPwdInfoPage()
{
    delete ui;
}

void UserPwdInfoPage::setInitValue(){
    this->ui->led_objnm->setText(QString(this->crup->getObjName().c_str()));
    this->ui->led_usernm->setText(QString(this->crup->getUserName().c_str()));
    this->ui->led_passwd->setText(QString(this->crup->getPassword().c_str()));
    this->ui->txed_desc->setPlainText(QString(this->crup->getDecriptor().c_str()));
}

void UserPwdInfoPage::on_btn_cancel_clicked()
{
    this->reject();
}

void UserPwdInfoPage::on_btn_OK_clicked()
{
    std::string objnm(ui->led_objnm->text().toStdString());
    std::string usernm(ui->led_usernm->text().toStdString());
    std::string passwd(ui->led_passwd->text().toStdString());
    std::string desc(ui->txed_desc->toPlainText().toStdString());
    if(this->ptp == Ui::addnew){
        pmsm::UPDao updao;
        updao.createUserPassword(UserPassword(objnm, usernm, passwd, desc));
    }
    else if(this->ptp == Ui::modify){
        this->crup->setObjName(objnm);
        this->crup->setUserName(usernm);
        this->crup->setPassword(passwd);
        this->crup->setDecriptor(desc);
        pmsm::UPDao updao;
        updao.modifyUserPassword(*(this->crup));
    }
    this->accept();
}
