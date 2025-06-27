#include"QtWidgetsApplication3.h"





void  QtWidgetsApplication3::on_personal_details_clicked() {
    ui->email_label->setText(QString::fromStdString(arr_users[indexofuser].contactdet.email));
    ui->pass_label->setText(QString::fromStdString(arr_users[indexofuser].pass));
    ui->id_label->setText(QString::fromStdString(arr_users[indexofuser].id));
    ui->balance_label->setText(QString::number(arr_users[indexofuser].balance));
    ui->username_label->setText(QString::fromStdString(arr_users[indexofuser].username));
    ui->stackedWidget->setCurrentWidget(ui->current_data);
}



