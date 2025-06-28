#include"QtWidgetsApplication3.h"





void  QtWidgetsApplication3::on_personal_details_clicked() {
    ui->email_label->setText(QString::fromStdString(arr_users[indexofuser].contactdet.email));
    ui->pass_label->setText(QString::fromStdString(arr_users[indexofuser].pass));
    ui->id_label->setText(QString::fromStdString(arr_users[indexofuser].id));
    ui->balance_label->setText(QString::number(arr_users[indexofuser].balance));
    ui->username_label->setText(QString::fromStdString(arr_users[indexofuser].username));
    ui->stackedWidget->setCurrentWidget(ui->current_data);
}



void QtWidgetsApplication3::on_saveUsername_clicked() {
    QString newName = ui->nameuser->text().trimmed();


    if (newName.isEmpty()) {
        QMessageBox::warning(this, "Error", "Username cannot be empty.");
        return;
    }

    arr_users[indexofuser].username = newName.toStdString();




    QMessageBox::information(this, "Success", "Username updated successfully.");
}



void QtWidgetsApplication3::on_TOEDIT_clicked() {
    //  on_pushButton_editInfo_clicked();
    ui->stackedWidget->setCurrentWidget(ui->changeinfo);
}




void QtWidgetsApplication3::on_saveEmail_clicked() {
    QString newEmail = ui->emaillabel->text();
    if (!newEmail.contains("@") || !newEmail.contains(".")) {
        QMessageBox::warning(this, "Error", "Invalid email format.");
        return;
    }
    arr_users[indexofuser].contactdet.email = newEmail.toStdString();
    QMessageBox::information(this, "Success", "Email updated successfully.");
}


void QtWidgetsApplication3::on_savePassword_clicked() {
    QString newPass = ui->passlabel->text();
    if (newPass.length() < 8) {
        QMessageBox::warning(this, "Error", "Password must be at least 8 characters.");
        return;
    }
    arr_users[indexofuser].pass = newPass.toStdString();
    QMessageBox::information(this, "Success", "Password updated successfully.");
}






