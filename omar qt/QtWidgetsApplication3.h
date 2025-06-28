#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsApplication3.h"  // Include the generated UI header
#include <QApplication>
#include <QPushButton>
#include<QString>
#include"global.h"
#include"dependence.h"
#include"structures.h"
#include"stations.h"
#include "view users.h"
#include <QTableWidget>
#include"choose sub.cpp"
#include"register.h"

class QtWidgetsApplication3 : public QMainWindow
{
    Q_OBJECT

public:
    explicit QtWidgetsApplication3(QWidget* parent = nullptr);
    ~QtWidgetsApplication3();
    void gotoadmin();
    void setPage(int index);
    void start_up();
    void choose_sub();
   
    
private slots:
   /* void on_pushButton_23_clicked();*/
    void on_personal_details_clicked();
    void on_rides_clicked();
    void on_sub_settings_clicked();
   /* void on_logout_clicked();
    void on_pushButton_12_clicked();*/
    /*void on_pushButton_12_clicked();*/
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_15_clicked();
    //void on_pushButton_17_clicked();
    void on_delete_users_clicked();
    void on_change_users_clicked();
    void on_admin_mainmenu_clicked();
    void on_confirmride_clicked();

    //user information change

    void on_TOEDIT_clicked();
    //void on_pushButton_editInfo_clicked();
    void on_saveUsername_clicked();
    void on_saveEmail_clicked();
    void on_savePassword_clicked();

    void on_submit_balance_clicked();
    void on_back_from_balance_clicked();
    void on_back_to_renew_page_clicked();
    void on_confirm_wallet_balance_clicked();
    void on_recharge_main_bala_in_wallet_clicked();




    //modify but #admin

    void on_pushButton_18_clicked();
    //charge balance #admin
    void on_Chargeing_admin_balance_clicked();
    void on_pushButton_24_clicked();
    void on_pushButton_25_clicked();

  


    //change subsc #admin 
    void on_pushButton_23_clicked();

   /* void on_pushButton_13_clicked();
    void on_pushButton_sign_clicked();*/
    void on_back1_clicked();
    void on_back2_clicked();
    void on_back3_clicked();
    void on_back4_clicked();
    void on_back5_clicked();
    void on_back6_clicked();
    void on_back7_clicked();
    void on_back8_clicked();
    void on_back12_clicked();
    void on_exit1_clicked();
    void on_exit2_clicked();
    void on_exit3_clicked();
  /*  void on_exit01_clicked();*/
    void on_exit02_clicked();
    void on_exit4_clicked();
    void on_exit5_clicked();
    void on_exit6_clicked();
    void on_exit7_clicked();
    void on_exit8_clicked();
    void on_pushButton_confirm_clicked();
    void on_logout_clicked();
   
    string getCurrentDate();
    string saveExpiry();
    void on_change_sub_clicked();
    void on_renew_button_clicked();
    string check_expiry(st_of_users person[]);
    void on_confirm_renew_clicked();
    void on_cancel_renew_clicked();
    void on_recharge_button_clicked();
    /*ride stations */
   

 
private:
    Ui::MainWindow* ui;  // Use Ui::MainWindow, not Ui::QtWidgetsApplication3
   
signals: 
    void switchToDialog();
};
