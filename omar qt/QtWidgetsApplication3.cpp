//#include "QtWidgetsApplication3.h"
//
//QtWidgetsApplication3::QtWidgetsApplication3(QWidget *parent)
//    : QMainWindow(parent)
//{
//    ui.setupUi(this);
//}
//
//QtWidgetsApplication3::~QtWidgetsApplication3()
//{}
#include "QtWidgetsApplication3.h"
#include "ui_QtWidgetsApplication3.h"  // Include the generated UI class
#include"dependence.h"
#include"global.h"
#include"structures.h"

QtWidgetsApplication3::QtWidgetsApplication3(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)  // Correct link to the UI class generated from the .ui file
{
    ui->setupUi(this);  // Set up the UI components
    ui->stackedWidget->setCurrentWidget(ui->welcome2);


    ///--------           FILL STATIONS COMBOBOX            ----------///

    for (int i = 0; i < MAX_STATIONS_PER_LINE; i++)
    {
        for (int j = 0; j < NUM_LINES; j++) 
        {
           
            if (allStations[i][j].name == "-" || allStations[i][j].name == "Switching.")
            {
                continue;
            }
            ui->startstation->addItem(QString::fromStdString(allStations[i][j].name));
            ui->endstation->addItem(QString::fromStdString(allStations[i][j].name));
        }
    }
}

QtWidgetsApplication3::~QtWidgetsApplication3()
{
    delete ui;  // Clean up
}

//void  QtWidgetsApplication3::on_pushButton_12_clicked() {
//    ui->stackedWidget->setCurrentWidget(ui->create_account);
//}
//void  QtWidgetsApplication3::on_pushButton_13_clicked() {
//    ui->stackedWidget->setCurrentWidget(ui->login);
//}

void  QtWidgetsApplication3::on_personal_details_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->current_data);
}
void  QtWidgetsApplication3::on_rides_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->rides_2);
}
void  QtWidgetsApplication3::on_sub_settings_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->manage_plan);
}
//void  QtWidgetsApplication3::on_logout_clicked() {
//    ui->stackedWidget->setCurrentWidget(ui->welcome1);
//}
void  QtWidgetsApplication3::on_pushButton_6_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->new_rides);
}
void  QtWidgetsApplication3::on_pushButton_7_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->rides_history);
}
void  QtWidgetsApplication3::on_pushButton_8_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->view_sub);
}
void  QtWidgetsApplication3::on_pushButton_9_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->renew_sub);
}
void  QtWidgetsApplication3::on_pushButton_10_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->subscriptions);
}

void QtWidgetsApplication3::on_back1_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->welcome2);
}
void QtWidgetsApplication3::on_back2_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->welcome2);
}
void QtWidgetsApplication3::on_back3_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->welcome2);
}
void QtWidgetsApplication3::on_back4_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->rides_2);
}
void QtWidgetsApplication3::on_back5_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->rides_2);
}
void QtWidgetsApplication3::on_back6_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->manage_plan);
}
void QtWidgetsApplication3::on_back7_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->manage_plan);
}
void QtWidgetsApplication3::on_back8_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->manage_plan);
}
void QtWidgetsApplication3::on_exit1_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->end);
}
void QtWidgetsApplication3::on_exit2_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->end);
}
void QtWidgetsApplication3::on_exit3_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->end);
}
//void QtWidgetsApplication3::on_exit01_clicked() {
//    ui->stackedWidget->setCurrentWidget(ui->end);
//}
void QtWidgetsApplication3::on_exit02_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->end);
}
void QtWidgetsApplication3::on_exit4_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->end);
}
void QtWidgetsApplication3::on_exit5_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->end);
}
void QtWidgetsApplication3::on_exit6_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->end);
}
void QtWidgetsApplication3::on_exit7_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->end);
}
void QtWidgetsApplication3::on_exit8_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->end);
}






