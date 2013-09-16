#ifndef CONTENTPAGE_H
#define CONTENTPAGE_H

#include <QMainWindow>
#include<vector>
#include"userpassword.h"

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
    
private slots:
    void on_btnSearch_clicked();

    void on_btnClear_clicked();

    void on_btnAddnew_clicked();

    void on_btnModify_clicked();

    void on_btnRemove_clicked();

private:
    Ui::ContentPage *ui;
    void refleshContent();
};

#endif // CONTENTPAGE_H
