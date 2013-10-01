#ifndef CONTENTPAGE_H
#define CONTENTPAGE_H

#include<vector>
#include"userpassword.h"

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

namespace Ui {
class ContentPage;
}

class ContentPage : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ContentPage(QWidget *parent = 0);
    ~ContentPage();

    std::vector<UserPassword *> *contentList;

    QAction *actionAddnew;
    QAction *actionModify;
    QAction *actionRemove;
    QWidget *centralWidget;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *lblSearch;
    QPushButton *btnAddnew;
    QPushButton *btnModify;
    QPushButton *btnRemove;
    QPushButton *btnClear;
    QPushButton *btnSearch;
    QLineEdit *edtSearchWord;
    QTableWidget *tblContent;
    QMenuBar *menuBar;
    QMenu *mnFile;
    QMenu *mnEdit;
    QMenu *mnHelp;
    QStatusBar *statusBar;
    QToolBar *mainToolBar;

private slots:
    void on_btnSearch_clicked();

    void on_btnClear_clicked();

    void on_btnAddnew_clicked();

    void on_btnModify_clicked();

    void on_btnRemove_clicked();

    void on_tblContent_cellClicked(int row, int column);

    void on_CellWidgetButton_clicked(int row, int column);

private:
//    Ui::ContentPage *ui;
    void refleshContent(std::vector<UserPassword *> *cl);
    void refleshContent();
    void initContentTable();
    void removeRowN(int row);
    void modifyRowN(int row);

    void setupUi(QMainWindow *ContentPage);
    void retranslateUi(QMainWindow *ContentPage);
    void addEventListener();
    std::vector<int> *  getSelectedRowIndexs();
};

class QMyPushButton : public QPushButton{
    Q_OBJECT
public:
    QMyPushButton(int row, int column, const QString &text, QWidget *parent=0);
signals:
    void myClicked(int row, int column);

private:
    int row;
    int column;
protected:
    void mouseReleaseEvent(QMouseEvent * e);
};

#endif // CONTENTPAGE_H
