#include "contentpage.h"
#include "ui_contentpage.h"
#include "userpwdinfopage.h"
#include "updao.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QStringList>
#include <QCheckBox>

QMyPushButton::QMyPushButton(int row, int column, const QString &text, QWidget *parent):
    QPushButton(text,parent)
{
    this->row = row;
    this->column = column;
}

void QMyPushButton::mouseReleaseEvent(QMouseEvent * e){
    this->clicked();
    this->myClicked(this->row,this->column);
}

void ContentPage::setupUi(QMainWindow *ContentPage)
{
    if (ContentPage->objectName().isEmpty())
        ContentPage->setObjectName(QStringLiteral("ContentPage"));
    ContentPage->resize(640, 480);
    actionAddnew = new QAction(ContentPage);
    actionAddnew->setObjectName(QStringLiteral("actionAddnew"));
    actionModify = new QAction(ContentPage);
    actionModify->setObjectName(QStringLiteral("actionModify"));
    actionRemove = new QAction(ContentPage);
    actionRemove->setObjectName(QStringLiteral("actionRemove"));
    centralWidget = new QWidget(ContentPage);
    centralWidget->setObjectName(QStringLiteral("centralWidget"));
    widget = new QWidget(centralWidget);
    widget->setObjectName(QStringLiteral("widget"));
    widget->setGeometry(QRect(4, 4, 631, 401));
    gridLayout = new QGridLayout(widget);
    gridLayout->setSpacing(6);
    gridLayout->setContentsMargins(11, 11, 11, 11);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));
    gridLayout->setContentsMargins(0, 0, 0, 0);
    lblSearch = new QLabel(widget);
    lblSearch->setObjectName(QStringLiteral("lblSearch"));

    gridLayout->addWidget(lblSearch, 0, 0, 1, 1);

    btnAddnew = new QPushButton(widget);
    btnAddnew->setObjectName(QStringLiteral("btnAddnew"));

    gridLayout->addWidget(btnAddnew, 2, 3, 1, 1);

    btnModify = new QPushButton(widget);
    btnModify->setObjectName(QStringLiteral("btnModify"));

    gridLayout->addWidget(btnModify, 2, 4, 1, 1);

    btnRemove = new QPushButton(widget);
    btnRemove->setObjectName(QStringLiteral("btnRemove"));

    gridLayout->addWidget(btnRemove, 2, 5, 1, 1);

    btnClear = new QPushButton(widget);
    btnClear->setObjectName(QStringLiteral("btnClear"));

    gridLayout->addWidget(btnClear, 0, 5, 1, 1);

    btnSearch = new QPushButton(widget);
    btnSearch->setObjectName(QStringLiteral("btnSearch"));

    gridLayout->addWidget(btnSearch, 0, 4, 1, 1);

    edtSearchWord = new QLineEdit(widget);
    edtSearchWord->setObjectName(QStringLiteral("edtSearchWord"));

    gridLayout->addWidget(edtSearchWord, 0, 1, 1, 3);

    tblContent = new QTableWidget(widget);
    tblContent->setObjectName(QStringLiteral("tblContent"));

    gridLayout->addWidget(tblContent, 1, 0, 1, 6);

    ContentPage->setCentralWidget(centralWidget);
    menuBar = new QMenuBar(ContentPage);
    menuBar->setObjectName(QStringLiteral("menuBar"));
    menuBar->setGeometry(QRect(0, 0, 640, 26));
    mnFile = new QMenu(menuBar);
    mnFile->setObjectName(QStringLiteral("mnFile"));
    mnEdit = new QMenu(menuBar);
    mnEdit->setObjectName(QStringLiteral("mnEdit"));
    mnHelp = new QMenu(menuBar);
    mnHelp->setObjectName(QStringLiteral("mnHelp"));
    ContentPage->setMenuBar(menuBar);
    statusBar = new QStatusBar(ContentPage);
    statusBar->setObjectName(QStringLiteral("statusBar"));
    ContentPage->setStatusBar(statusBar);
    mainToolBar = new QToolBar(ContentPage);
    mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
    ContentPage->addToolBar(Qt::TopToolBarArea, mainToolBar);
    ContentPage->insertToolBarBreak(mainToolBar);

    menuBar->addAction(mnFile->menuAction());
    menuBar->addAction(mnEdit->menuAction());
    menuBar->addAction(mnHelp->menuAction());
    mainToolBar->addAction(actionAddnew);
    mainToolBar->addAction(actionModify);
    mainToolBar->addAction(actionRemove);

    this->retranslateUi(ContentPage);

    this->addEventListener();
//    QMetaObject::connectSlotsByName(ContentPage);
} // setupUi

void ContentPage::addEventListener(){
    connect(this->btnAddnew, SIGNAL(clicked()), this, SLOT(on_btnAddnew_clicked()));
    connect(this->btnModify, SIGNAL(clicked()), this, SLOT(on_btnModify_clicked()));
    connect(this->btnRemove, SIGNAL(clicked()), this, SLOT(on_btnRemove_clicked()));
    connect(this->btnSearch, SIGNAL(clicked()), this, SLOT(on_btnSearch_clicked()));
    connect(this->btnClear, SIGNAL(clicked()), this, SLOT(on_btnClear_clicked()));
}

void ContentPage::retranslateUi(QMainWindow *ContentPage)
{
    ContentPage->setWindowTitle(QApplication::translate("ContentPage", "ContentPage", 0));
    actionAddnew->setText(QApplication::translate("ContentPage", "\346\226\260\345\242\236", 0));
    actionModify->setText(QApplication::translate("ContentPage", "\344\277\256\346\224\271", 0));
    actionRemove->setText(QApplication::translate("ContentPage", "\345\210\240\351\231\244", 0));
#ifndef QT_NO_TOOLTIP
    actionRemove->setToolTip(QApplication::translate("ContentPage", "\345\210\240\351\231\244", 0));
#endif // QT_NO_TOOLTIP
    lblSearch->setText(QApplication::translate("ContentPage", "\346\220\234\347\264\242\357\274\232", 0));
    btnAddnew->setText(QApplication::translate("ContentPage", "\346\226\260\345\242\236", 0));
    btnModify->setText(QApplication::translate("ContentPage", "\344\277\256\346\224\271", 0));
    btnRemove->setText(QApplication::translate("ContentPage", "\345\210\240\351\231\244", 0));
    btnClear->setText(QApplication::translate("ContentPage", "X", 0));
    btnSearch->setText(QApplication::translate("ContentPage", "\346\220\234\347\264\242", 0));
    mnFile->setTitle(QApplication::translate("ContentPage", "\346\226\207\344\273\266", 0));
    mnEdit->setTitle(QApplication::translate("ContentPage", "\347\274\226\350\276\221", 0));
    mnHelp->setTitle(QApplication::translate("ContentPage", "\345\270\256\345\212\251", 0));
} // retranslateUi

ContentPage::ContentPage(QWidget *parent) :
    QMainWindow(parent)//,
//    ui(new Ui::ContentPage)
{
    pmsm::UPDao updao;
    this->setupUi(this);

    this->initContentTable();
    this->refleshContent(updao.getAllUserPassword());
} //ContentPage 构造函数

ContentPage::~ContentPage()
{
    delete this->contentList;
//    delete ui;
} //ContentPage 析构函数

void ContentPage::refleshContent(){ //更新表格内容
    QTableWidget *qtw;
    std::vector<UserPassword*>::iterator it;
    int i;

    qtw = this->tblContent;
    qtw->setRowCount(this->contentList->size());

    i = 0;
    for(it = this->contentList->begin();it!=this->contentList->end(); it++){
        qtw->setCellWidget(i,0,new QCheckBox());
        qtw->setItem(i,1,new QTableWidgetItem(tr((*it)->getObjName().c_str())));
        qtw->setItem(i,2,new QTableWidgetItem(tr((*it)->getUserName().c_str())));
        qtw->setItem(i,3,new QTableWidgetItem(tr((*it)->getPassword().c_str())));
        qtw->setItem(i,4,new QTableWidgetItem(tr((*it)->getDecriptor().c_str())));
        qtw->setCellWidget(i,5,new QMyPushButton(i,5,QString("删除")));
        connect((QMyPushButton*)(qtw->cellWidget(i,5)), SIGNAL(myClicked(int,int)),
                this, SLOT(on_CellWidgetButton_clicked(int,int)));
        qtw->setCellWidget(i,6,new QMyPushButton(i,6,QString("修改")));
        connect((QMyPushButton*)(qtw->cellWidget(i,6)), SIGNAL(myClicked(int,int)),
                this, SLOT(on_CellWidgetButton_clicked(int,int)));
        i++;
    }
} //更新表格内容

void ContentPage::refleshContent(std::vector<UserPassword *> *cl){ //更新表格内容

    delete this->contentList;

    this->contentList = cl;

    this->refleshContent();

} //更新表格内容

void ContentPage::initContentTable(){ //表格初始化设置
    QTableWidget *qtw;
    qtw = this->tblContent;
    qtw->setColumnCount(7);
    QStringList header;
    header<<""<<"名称"<<"用户名"<<"密码"<<"备注说明"<<""<<"";
    qtw->setHorizontalHeaderLabels(header);
    qtw->setColumnWidth(0,18);
    qtw->setColumnWidth(4,180);
    qtw->setColumnWidth(5,38);
    qtw->setColumnWidth(6,38);
} //表格初始化设置

std::vector<int> * ContentPage::getSelectedRowIndexs(){ //获取多选行号
    std::vector<int> * res;
    res = new std::vector<int>();

    int rn;
    for(rn=0;rn<(this->tblContent->rowCount());rn++){
        if(((QCheckBox*)(this->tblContent->cellWidget(rn,0)))->checkState()==Qt::Checked){
            res->push_back(rn);
        }
    }

    return res;
} //获取多选行号

void ContentPage::on_CellWidgetButton_clicked(int row, int column){ //表格内删除、修改按钮事件
    if(column==5){ //触发删除按钮
        this->removeRowN(row);//删除第n行记录
    }
    else if(column==6){ //触发修改按钮
        this->modifyRowN(row);//修改第n行记录
    }
} //表格内删除、修改按钮事件

void ContentPage::on_btnSearch_clicked() //搜索按钮点击事件
{
    std::string kword;
    std::string objnm, usrnm, desc;
    kword = this->edtSearchWord->text().toStdString();

    std::vector<UserPassword *>::iterator it;

    it = this->contentList->begin();

    while(it!=this->contentList->end()){
        objnm = (*it)->getObjName();
        usrnm = (*it)->getUserName();
        desc = (*it)->getDecriptor();

        if(objnm.find(kword)==std::string::npos
                &&usrnm.find(kword)==std::string::npos
                &&desc.find(kword)==std::string::npos){
            this->contentList->erase(it);
        }
        else {
            it++;
        }
    }

    this->refleshContent();
} //搜索按钮点击事件

void ContentPage::on_btnClear_clicked() //清除搜索按钮点击事件
{
    pmsm::UPDao updao;
    this->edtSearchWord->setText("");
    this->refleshContent(updao.getAllUserPassword());
} //清除搜索按钮点击事件

void ContentPage::on_btnAddnew_clicked() //新增按钮点击事件
{
    UserPwdInfoPage upip;
    upip.exec();
    pmsm::UPDao updao;
    this->refleshContent(updao.getAllUserPassword());
} //新增按钮点击事件

void ContentPage::on_btnModify_clicked() //多选修改按钮点击事件
{
    std::vector<int> * s;
    std::vector<int>::iterator it;
    s = this->getSelectedRowIndexs();

    for(it=s->begin();it!=s->end();it++){
        UserPwdInfoPage upip(this->contentList->at(*it));
        upip.exec();
    }
    pmsm::UPDao updao;
    this->refleshContent(updao.getAllUserPassword());
    delete s; //释放多选行号列表
} //多选修改按钮点击事件

void ContentPage::on_btnRemove_clicked() //多选删除按钮点击事件
{
    std::vector<int> * s;
    std::vector<int>::reverse_iterator it;
    s = this->getSelectedRowIndexs();

    for(it=s->rbegin();it!=s->rend();it++){
        this->removeRowN(*it);
    }

    pmsm::UPDao updao;
    this->refleshContent(updao.getAllUserPassword());
    delete s; //释放多选行号列表
} //多选删除按钮点击事件

void ContentPage::removeRowN(int row){ //删除第n行数据
    pmsm::UPDao updao;
    updao.removeUserPassword(*(this->contentList->at(row)));
    this->refleshContent(updao.getAllUserPassword());
} //删除第n行数据

void ContentPage::modifyRowN(int row){ //修改第n行数据
    UserPwdInfoPage upip(this->contentList->at(row));
    upip.exec();

    pmsm::UPDao updao;
    this->refleshContent(updao.getAllUserPassword());

} //修改第n行数据

void ContentPage::on_tblContent_cellClicked(int row, int column)
{
}
