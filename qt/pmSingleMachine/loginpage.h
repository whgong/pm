#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QDialog>

namespace Ui {
class LoginPage;
}

class LoginPage : public QDialog
{
    Q_OBJECT
    
public:
    explicit LoginPage(QWidget *parent = 0);
    ~LoginPage();
    
private slots:
    void on_btnLogin_clicked();

    void on_btnCancel_clicked();

private:
    Ui::LoginPage *ui;
};

#endif // LOGINPAGE_H
