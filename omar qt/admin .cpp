#include"QtWidgetsApplication3.h"




void  QtWidgetsApplication3::on_pushButton_15_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->view_users_toadmin);

    ui->tableWidget_users->setRowCount(0);
    ui->tableWidget_users->setColumnCount(5);
    QStringList headers;
    headers << "Name" << "Complaints" << "Email" << "Balance" << "Subscription Type";
    ui->tableWidget_users->setHorizontalHeaderLabels(headers);

    int row = 0;
    for (int i = 0; i < number_of_users_in_array; ++i) {
        if (arr_users[i].admin_role == 0) {
            ui->tableWidget_users->insertRow(row);

            ui->tableWidget_users->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(arr_users[i].username)));


            QString complaintText = QString::fromStdString(arr_users[i].complaints);
            QString shortenedText = complaintText.left(30);
            if (complaintText.length() > 30)
                shortenedText += "...";

            QTableWidgetItem* item = new QTableWidgetItem(shortenedText);
            item->setToolTip(complaintText);
            ui->tableWidget_users->setItem(row, 1, item);

            ui->tableWidget_users->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(arr_users[i].contactdet.email)));
            ui->tableWidget_users->setItem(row, 3, new QTableWidgetItem(QString::number(arr_users[i].balance)));
            ui->tableWidget_users->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(arr_users[i].sub.subscription_type)));

            row++;
        }
    }
}
 //?TODO: maher put the function hint the func is loop and the index and make it clear and please push it correctly becuse we are done 
void  QtWidgetsApplication3::on_delete_users_clicked()
{
    QString theindex = ui->NumOfUser->text().trimmed();
    bool ok;
    int admin_chosen_index = theindex.toInt(&ok);

    if (!ok || admin_chosen_index <= 0 || admin_chosen_index > number_of_users_in_array) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid number.");
        return;
    }
    admin_chosen_index--;

  

    for (int i = admin_chosen_index; i < number_of_users_in_array - 1; ++i) {
        arr_users[i] = arr_users[i + 1];
    }

    number_of_users_in_array--;

    // Show success message
    QMessageBox::information(this, "Deleted", "User has been deleted successfully.");
}

//THIS IS THE CORRECT FUNCTION DONT CHANGE IT 

void  QtWidgetsApplication3::on_change_users_clicked()
{

    QString theindex = ui->NumOfUser->text().trimmed();
    bool ok;
    int admin_chosen_index = theindex.toInt(&ok);

    if (!ok || admin_chosen_index <= 0 || admin_chosen_index > number_of_users_in_array) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid number.");
        return;
    }
    admin_chosen_index--;

    admin_chosen_user = admin_chosen_index;


   ui->stackedWidget->setCurrentWidget(ui->modify_user);//DONT GHANGE IT I WILL KILL YOU 
   //DONT CHANGE IT IMP IMP IMP IMP IMP IMP IMP IMP IMP 
}


void QtWidgetsApplication3::gotoadmin() {
    ui->stackedWidget->setCurrentWidget(ui->admin);
}
//modify #admin

void QtWidgetsApplication3::on_pushButton_18_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->modify_user);




}

//charge balance #admin

void QtWidgetsApplication3::on_Chargeing_admin_balance_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->charge_balance);
    // should put the index that moaz will give me 
    ui->admin_change_balance->clear();
    ui->admin_change_balance->setText(QString::number(arr_users[admin_chosen_user].balance));

}
//moazz put in the index of array the index that you will give us please 
void QtWidgetsApplication3::on_pushButton_24_clicked()
{
    bool ok;
    long long chargeAmount = ui->new_balance->text().toInt(&ok);

    if (!ok || chargeAmount <= 0) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid positive number.");
        return;
    }

    // Update user balance
    arr_users[admin_chosen_user].balance += chargeAmount;

    // Update the Text Browser to show old balance (before recharge)
    ui->admin_change_balance->setText(QString::number(arr_users[admin_chosen_user].balance));

    // Update the Line Edit to show the new balance (after recharge)
    ui->new_balance->setText(QString::number(arr_users[admin_chosen_user].balance));

    // Show success message
    QMessageBox::information(this, "Success", "Recharge successful!");

    // Optionally move to the admin page
    ui->stackedWidget->setCurrentWidget(ui->admin);


}

void QtWidgetsApplication3::on_pushButton_25_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->modify_user);

}



//change subsc #admin 


void QtWidgetsApplication3::on_pushButton_23_clicked() {

    ui->stackedWidget->setCurrentWidget(ui->admin);//should change to the subscription changed by admin 



}

 











