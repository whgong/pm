#include "contentpage.h"
#include "ui_contentpage.h"
#include "userpwdinfopage.h"
#include "updao.h"
#include<QTableView>

ContentPage::ContentPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ContentPage)
{
    ui->setupUi(this);
    this->refleshContent();
}

ContentPage::~ContentPage()
{
    delete ui;
}

void ContentPage::refleshContent(){
    QTableWidget *qtw;
    pmsm::UPDao updao;
    std::vector<UserPassword*>::iterator it;
    int i;
    delete this->contentList;
    this->contentList = updao.getAllUserPassword();
    qtw = this->ui->tblContent;
    qtw->setRowCount(this->contentList->size());
    qtw->setColumnCount(4);
    i = 1;
    for(it = this->contentList->begin();it!=this->contentList->end(); it++){
        qtw->setItem(i,1,new QTableWidgetItem(QString((*it)->getObjName().c_str())));
        qtw->setItem(i,2,new QTableWidgetItem(QString((*it)->getUserName().c_str())));
        qtw->setItem(i,3,new QTableWidgetItem(QString((*it)->getPassword().c_str())));
        qtw->setItem(i,4,new QTableWidgetItem(QString((*it)->getDecriptor().c_str())));
    }
}


void ContentPage::on_btnSearch_clicked()
{

}

void ContentPage::on_btnClear_clicked()
{

}

void ContentPage::on_btnAddnew_clicked()
{
    UserPwdInfoPage upip;
    upip.exec();
}

void ContentPage::on_btnModify_clicked()
{
    UserPwdInfoPage upip;
    upip.exec();
}

void ContentPage::on_btnRemove_clicked()
{

}
