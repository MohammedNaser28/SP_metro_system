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
    admin_chosen_user = admin_chosen_index;

    /// admin_chosen_index is the index use it 
    ui->stackedWidget->setCurrentWidget(ui->admin); /// !!! change "admin" with the name of the widget of maher
}

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

    /// admin_chosen_index is the index use it 
    ui->stackedWidget->setCurrentWidget(ui->modify_user); /// !!! change "admin" with the name of the widget of ali








}

void  QtWidgetsApplication3::on_admin_mainmenu_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->admin);
}


void QtWidgetsApplication3::on_pushButton_10_clicked() {


    connect(ui->listWidget_subscriptions, &QListWidget::itemClicked, this, [=](QListWidgetItem* item) {
        int i = item->data(Qt::UserRole).toInt();
        chosenSubscriptionIndex = i;

        QString details;
        details += "📦 Plan Name: " + QString::fromStdString(arr_subscription[i].plan_name) + "\n";

        if (arr_subscription[i].fixed == 'y') {
            details += "\n🟦 Fixed Subscription:\n";

            if (arr_subscription[i].month_count > 0) {
                details += "\n📅 Monthly Plans:\n";
                for (int j = 0; j < arr_subscription[i].month_count; j++) {
                    details += "➤ " + QString::number(arr_subscription[i].month_sub[j].duration) + " month(s), "
                        + QString::number(arr_subscription[i].month_sub[j].no_of_trips) + " trips\n";
                    for (int k = 0; k < arr_subscription[i].month_sub[j].zone_num; k++) {
                        details += "   • Zone " + QString::number(k + 1) + ": "
                            + QString::number(arr_subscription[i].month_sub[j].zonesPrice[k]) + " LE\n";
                    }
                }
            }

            if (arr_subscription[i].year_count > 0) {
                details += "\n📅 Yearly Plans:\n";
                for (int j = 0; j < arr_subscription[i].year_count; j++) {
                    details += "➤ " + QString::number(arr_subscription[i].year_sub[j].duration) + " year(s), "
                        + QString::number(arr_subscription[i].year_sub[j].no_of_trips) + " trips\n";
                    for (int k = 0; k < arr_subscription[i].year_sub[j].zone_num; k++) {
                        details += "   • Zone " + QString::number(k + 1) + ": "
                            + QString::number(arr_subscription[i].year_sub[j].zonesPrice[k]) + " LE\n";
                    }
                }
            }
        }
        else {
            details += "\n🟨 Wallet Subscription:\n";
            details += "• Add balance in multiples of: " + QString::number(arr_subscription[i].wallet_sub.fund_multiple) + " LE\n";
            details += "• Maximum card balance: " + QString::number(arr_subscription[i].wallet_sub.card_balance) + " LE\n";
            details += "• Zones and Prices:\n";
            for (int k = 0; k < arr_subscription[i].wallet_sub.zone_num; k++) {
                details += "   • Zone " + QString::number(k + 1) + ": "
                    + QString::number(arr_subscription[i].wallet_sub.zonesPrice[k]) + " LE\n";
            }
          
        }

        if (!arr_subscription[i].notes.empty()) {
            details += "\n📝 Notes:\n" + QString::fromStdString(arr_subscription[i].notes);
        }

        ui->label_subscription_details->setPlainText(details);  // For QTextEdit
        });
}

/// for try run 

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

 