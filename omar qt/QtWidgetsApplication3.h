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
    void gotoadmin();

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
    void on_pushButton_15_clicked();
    void on_confirmride_clicked();
    void on_pushButton_16_clicked();
    void on_pushButton_22_clicked();
    void handleMonthlyCellClick(int r, int);
    void handleYearlyCellClick(int r, int);
   void on_editsub_clicked();
   // void on_pushButton_select_sub_clicked();
    void on_pushButton_save_changes_2_clicked();
    void on_pushButton_save_changes_clicked();
    void on_pushButton_cancel_changes_clicked();
    void on_pushButton_cancel_changes_2_clicked();
    void on_pushButton_backFromFixed_clicked();
    void on_pushButton_backFromWallet_clicked();
    void on_pushButton_backFrom_edit_monthly_clicked();
    void on_pushButton_backFrom_edit_yearly_clicked();
    void on_pushButton_cancel_changeseditmonthly_clicked();
    void on_pushButton_cancel_changesedityearly_clicked();
    void on_pushButton_backeditmonthly_clicked();
    void on_pushButton_backedityearly_clicked();
  //  void on_edityearly_button_clicked();
  //  void on_editmonthly_button_clicked();
    void on_pushButton_editMonthSave_clicked();
    void on_pushButton_editYearSave_clicked();
    void on_pushButton_13_clicked();
    void on_pushButton_14_clicked();
    void on_tableWidget_subscriptions_cellClicked(int row, int);
   // void clearLayout(QLayout* layout);
    void on_spinBox_monthZones_valueChanged(int value);
    void on_spinBox_yearZones_valueChanged(int value);
    void on_spinBox_zoneNum_valueChanged(int value);

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
    void on_back9_clicked();
    void on_back10_clicked();
    void on_back11_clicked();
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
    /*ride stations */
   
    void on_addsub_clicked();
    void on_radioButton_fixed_clicked();
    void on_radioButton_wallet_clicked();
    void on_pushButton_addMonth_clicked();
    void on_pushButton_addYear_clicked();
    void on_spinBox_month_zones_valueChanged(int);
    void on_spinBox_year_zones_valueChanged(int);
    void on_dialogButtonBox_month_accepted();
    void on_dialogButtonBox_month_rejected();
    void on_dialogButtonBox_year_accepted();
    void on_dialogButtonBox_year_rejected();
    void on_pushButton_submit_clicked();
    void on_spinBox_wallet_zones_valueChanged(int value);
    void refreshSubscriptionTable();
    void on_deletesub_clicked();
 
private:
    Ui::MainWindow* ui;  // Use Ui::MainWindow, not Ui::QtWidgetsApplication3
   
signals: 
    void switchToDialog();
};
