#pragma once
#include<QDialog>
#include"ui_register.h"
#include"dependence.h"
#include"structures.h"
#include<string>
using namespace std;
namespace Ui { class Register; };
class Register : public QDialog
{
    Q_OBJECT

public:
    Register(QWidget *parent = nullptr);
    ~Register();

private:
    Ui::Register *ui;

private slots:
    bool SignInFun(const string& username, const string& userpass, bool& validpasskey);
    bool newaccount(const string& username, const string& userpass, const string& email);
    void on_create_button_clicked();
    void on_login_button_clicked();
    void on_back_clicked();
    void on_back2_clicked();
    void on_pushButton_sign_clicked();
    void on_pushButton_login_clicked();

signals:
    void switchToMainWindow();
    void windowadmin();
};
