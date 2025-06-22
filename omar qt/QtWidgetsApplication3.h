#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsApplication3.h"  // Include the generated UI header
#include <QApplication>
#include <QPushButton>
#include<QString>

class QtWidgetsApplication3 : public QMainWindow
{
    Q_OBJECT

public:
    explicit QtWidgetsApplication3(QWidget* parent = nullptr);
    ~QtWidgetsApplication3();

private slots:
   /* void on_pushButton_23_clicked();*/
    void on_personal_details_clicked();
    void on_rides_clicked();
    void on_sub_settings_clicked();
   /* void on_logout_clicked();
    void on_pushButton_12_clicked();*/
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_10_clicked();
    void on_confirmride_clicked();
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
    /*ride stations */
   

 
private:
    Ui::MainWindow* ui;  // Use Ui::MainWindow, not Ui::QtWidgetsApplication3
   
signals: 
    void switchToDialog();
};
