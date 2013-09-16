#ifndef USERPWDINFOPAGE_H
#define USERPWDINFOPAGE_H

#include <QDialog>
#include "userpassword.h"

namespace Ui {
    class UserPwdInfoPage;

    enum pagetype{
        addnew = 0,
        modify = 1
    };
}

class UserPwdInfoPage : public QDialog
{
    Q_OBJECT
    
public:
    explicit UserPwdInfoPage(QWidget *parent = 0);
    UserPwdInfoPage(UserPassword *up, QWidget *parent = 0);
    ~UserPwdInfoPage();
    
private slots:
    void on_btn_cancel_clicked();

    void on_btn_OK_clicked();

private:
    Ui::UserPwdInfoPage *ui;
    Ui::pagetype ptp;
    UserPassword *crup;

    void setInitValue();
};

#endif // USERPWDINFOPAGE_H
