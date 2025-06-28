#include"QtWidgetsApplication3.h"


void QtWidgetsApplication3::choose_sub()
{
    ui->listWidget_subscriptions->clear();
    if (num_of_subsc == 0) {
        ui->listWidget_subscriptions->addItem("No available subscriptions");
        return;
    }

    for (int i = 0; i < num_of_subsc; i++) {
        QString planName = QString::fromStdString(arr_subscription[i].plan_name);
        QListWidgetItem* item = new QListWidgetItem(QString::number(i + 1) + " - " + planName);
        item->setData(Qt::UserRole, i);
        ui->listWidget_subscriptions->addItem(item);
    }

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

void  QtWidgetsApplication3::on_sub_settings_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->manage_plan);
}

void  QtWidgetsApplication3::on_pushButton_8_clicked() {
    view_subscription();
    ui->stackedWidget->setCurrentWidget(ui->view_sub);
    
}

void  QtWidgetsApplication3::on_pushButton_9_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->renew_sub);
    

    QString current_date = QString::fromStdString(getCurrentDate());
    ui->cur_date->setText(current_date);

    QString expiry_date = QString::fromStdString(saveExpiry());
    ui->exp_date->setText(expiry_date);

    QString status = QString::fromStdString(check_expiry(arr_users));
    ui->sub_status->setText(status);

}


void QtWidgetsApplication3::on_pushButton_10_clicked() {

    ui->stackedWidget->setCurrentWidget(ui->subscriptions);
    
}

void QtWidgetsApplication3::on_pushButton_confirm_clicked() {
    if (chosenSubscriptionIndex == -1)
    {
        QMessageBox::warning(this, "No Selection", "Please choose a subscription first.");
        return;
    }

    QString selectedPlan = QString::fromStdString(arr_subscription[chosenSubscriptionIndex].plan_name);
    QMessageBox::information(this, "Subscribed!", "You selected: " + selectedPlan);
}


void QtWidgetsApplication3::on_renew_button_clicked()
{

    ui->stackedWidget->setCurrentWidget(ui->renew_page);
    ui->cur_balance->setText(QString::fromStdString(to_string(arr_users[indexofuser].balance)));
    ui->rem_trips->setText(QString::fromStdString(to_string(arr_users[indexofuser].sub.remaining_trips)));
}

string QtWidgetsApplication3::check_expiry(st_of_users person[])
{

    string status;

    time_t now = time(NULL);
    tm localTime;
    localtime_s(&localTime, &now);
    int day = localTime.tm_mday;
    int month = localTime.tm_mon + 1;
    int year = localTime.tm_year + 1900;
    localTime.tm_hour = 0;
    localTime.tm_min = 0;
    localTime.tm_sec = 0;
    now = mktime(&localTime);//setting time to midnight to compare dates

    //cout << "Current date: " << day << "/" << month << "/" << year << endl;
    //to get expiry date
    string datestring = person[indexofuser].sub.expiry;
    tm expiryTime = {};
    stringstream ss(datestring);
    ss >> get_time(&expiryTime, "%d/%m/%Y");
    time_t expiry = mktime(&expiryTime);
    /*cout << "Expiry date: " << datestring << endl;*/
    //to get their differecnce 
    time_t final = expiry - now;
    final = final / (60 * 60 * 24);
    if (final == 0) { status += "It's time to renew your subscription !"; }
    else if (final < 0) { status += "Your subscription has expired !"; }
    else if (final == 1) { status += "Renew is in 1 Day "; }
    else if (final > 0) { status += ("Renew is in " + to_string(final) + " Days"); }
    return status;

}

void QtWidgetsApplication3::on_confirm_renew_clicked()
{

    /// aly will fix it or i will kill him();

    if ((arr_users[indexofuser].balance - arr_users[indexofuser].sub.zonePrice) < 0)
    {

        QMessageBox::warning(this, "Not enough balnace.", "Please Recharge Your Balance.");
        return;
    }

    arr_users[indexofuser].balance -= arr_users[indexofuser].sub.zonePrice;
    arr_users[indexofuser].sub.remaining_trips = arr_users[indexofuser].sub.Num_trips;

    // Update the Text Browser to show old balance (before recharge)
    ui->cur_balance->setText(QString::number(arr_users[indexofuser].balance));

    // Update the Line Edit to show the new balance (after recharge)
    ui->new_balance->setText(QString::number(arr_users[indexofuser].balance));

    // Show success message
    QMessageBox::information(this, "Success", "Recharge successful!");


}


void QtWidgetsApplication3::on_cancel_renew_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->welcome2);

}


void QtWidgetsApplication3::on_change_sub_clicked()
{
    choose_sub();
    ui->stackedWidget->setCurrentWidget(ui->subscriptions);

}
void QtWidgetsApplication3::view_subscription() {


    ui->name_in_sub->setText(QString::fromStdString(arr_users[indexofuser].username));
    ui->cur_bl_in_view->setText(QString::fromStdString(to_string(arr_users[indexofuser].balance)));
    ui->sub_name->setText(QString::fromStdString(arr_users[indexofuser].sub.subscription_type));
    ui->actv_dt->setText(QString::fromStdString(arr_users[indexofuser].sub.activation));


    

    if (arr_users[indexofuser].sub.fixed == 'y') {

        ui->nonfixed_sub_balnce_lb->setVisible(false);
        


         ui->mixed->setText(QString::fromStdString(arr_users[indexofuser].sub.plan_type));
         ui->exp_dt->setText(QString::fromStdString(arr_users[indexofuser].sub.expiry)) ;
         ui->rm_tr->setText(QString::fromStdString(to_string(arr_users[indexofuser].sub.remaining_trips )));
    }

    else if (arr_users[indexofuser].sub.fixed == 'n') {

        ui->rm_tr_lb->setVisible(false);
        ui->rm_tr->setVisible(false);
        ui->nonfixed_sub_balnce_lb->setVisible(false);
        
       
        ui->exp_dt->setText("There is no expiry Date for this subscription" );
        ui->plan_type_lb->setText( "<b>Balance in " + QString::fromStdString( arr_users[indexofuser].sub.subscription_type) + " plan:</b>");
        ui->mixed->setText(QString::fromStdString(to_string(arr_users[indexofuser].sub.balancew))) ;
    }

}