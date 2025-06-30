#include"QtWidgetsApplication3.h"
//DONT PLAY IN SUBSCRIPTION .CPP FILE I WILL KILL YOU 
//ONLY WHO CAN ENTER IS ALY AND  OMAR AND HAYA ANY ONE IS BANNED IN THIS FILE 
//
//void QtWidgetsApplication3::choose_sub()
//{   // Set username and navigate to admin subscription page
//    
//    ui->stackedWidget->setCurrentWidget(ui->subscriptions);
//
//    // Clear previous data
//    ui->listWidget_subscriptions->clear();
//    ui->label_subscription_details->clear();
//    ui->admin_zone_list->clear();
//
//    // Hide recharge button by default
//    ui->admin_rech_balance_in_subsc->setVisible(false);
//
//    if (num_of_subsc == 0) {
//        ui->listWidget_subscriptions->addItem("No available subscriptions");
//        return;
//    }
//
//    // Populate main subscription plans
//    for (int i = 0; i < num_of_subsc; i++) {
//        QString planName = QString::fromStdString(arr_subscription[i].plan_name);
//        QListWidgetItem* item = new QListWidgetItem(QString::number(i + 1) + " - " + planName);
//        item->setData(Qt::UserRole, i); // Store index
//        ui->listWidget_subscriptions->addItem(item);
//    }
//
//    connect(ui->listWidget_subscriptions, &QListWidget::itemClicked, this, [=](QListWidgetItem* item) {
//        int subIndex = item->data(Qt::UserRole).toInt();
//        chosenSubscriptionIndex = subIndex;
//
//        // Clear lists
//        ui->label_subscription_details->clear();
//        ui->admin_zone_list->clear();
//
//        if (arr_subscription[subIndex].fixed == 'y') {
//            // Fixed subscriptions: Monthly / Yearly
//
//            for (int i = 0; i < arr_subscription[subIndex].month_count; i++) {
//                const auto& m = arr_subscription[subIndex].month_sub[i];
//
//                QString zonesPrices;
//                for (int z = 0; z < 4; z++) {
//                    if (z < 30 && m.zonesPrice[z] > 0) {
//                        if (z == 0)
//                            zonesPrices += QString("\nprice for zone %1 is %2").arg(z + 1).arg(m.zonesPrice[z]);
//                        else
//                            zonesPrices += QString("\nzone %1 is %2").arg(z + 1).arg(m.zonesPrice[z]);
//                    }
//                }
//
//                QString planText = QString("Monthly : %1 month(s) %2 trips").arg(m.duration).arg(m.no_of_trips);
//                if (!zonesPrices.isEmpty()) {
//                    planText += zonesPrices;
//                }
//
//                QListWidgetItem* item = new QListWidgetItem(planText);
//                item->setData(Qt::UserRole, i);
//                item->setData(Qt::UserRole + 1, "month");
//                ui->label_subscription_details->addItem(item);
//            }
//
//            for (int i = 0; i < arr_subscription[subIndex].year_count; i++) {
//                const auto& y = arr_subscription[subIndex].year_sub[i];
//
//                QString zonesPrices;
//                for (int z = 0; z < 4; z++) {
//                    if (z < 30 && y.zonesPrice[z] > 0) {
//                        if (z == 0)
//                            zonesPrices += QString("\nprice for zone %1 is %2").arg(z + 1).arg(y.zonesPrice[z]);
//                        else
//                            zonesPrices += QString("\nzone %1 is %2").arg(z + 1).arg(y.zonesPrice[z]);
//                    }
//                }
//
//                QString planText = QString("Yearly : %1 year(s) %2 trips").arg(y.duration).arg(y.no_of_trips);
//                if (!zonesPrices.isEmpty()) {
//                    planText += zonesPrices;
//                }
//
//                QListWidgetItem* item = new QListWidgetItem(planText);
//                item->setData(Qt::UserRole, i);
//                item->setData(Qt::UserRole + 1, "year");
//                ui->label_subscription_details->addItem(item);
//            }
//
//            // Populate zone list
//            for (int z = 1; z <= 4; z++) {
//                QListWidgetItem* zoneItem = new QListWidgetItem(QString("Zone %1").arg(z));
//                zoneItem->setData(Qt::UserRole, z); // Store zone number as user role
//                ui->admin_zone_list->addItem(zoneItem);
//            }
//
//            ui->admin_zone_list->setEnabled(true);
//
//        }
//        else {
//            // Smart Wallet subscription
//            const auto& w = arr_subscription[subIndex].wallet_sub;
//
//            QString plan = QString("Wallet - Max: %1 LE\nFund Multiple: %2 LE")
//                .arg(w.card_balance)
//                .arg(w.fund_multiple);
//
//            // Add all 4 zones
//            for (int z = 0; z < 4 && z < 30 && w.zonesPrice[z] > 0; z++) {
//                plan += QString("\nZone %1 is %2 LE").arg(z + 1).arg(w.zonesPrice[z]);
//            }
//
//            QListWidgetItem* item = new QListWidgetItem(plan);
//            item->setData(Qt::UserRole, 0);
//            item->setData(Qt::UserRole + 1, "wallet");
//            ui->label_subscription_details->addItem(item);
//
//            // Disable zone list
//            ui->admin_zone_list->setEnabled(false);
//            ui->admin_zone_list->clear();
//        }
//        });
//
//    // Connect submit button
//    connect(ui->submit_admin_subsc, &QPushButton::clicked, this, [=]() {
//        // Get selected plan
//        QListWidgetItem* selectedItem = ui->label_subscription_details->currentItem();
//        if (!selectedItem) {
//            QMessageBox::warning(this, "Selection Required", "Please select a subscription plan.");
//            return;
//        }
//
//        int planIndex = selectedItem->data(Qt::UserRole).toInt();
//        QString planType = selectedItem->data(Qt::UserRole + 1).toString();
//
//        user_subscriptions& userSub = arr_users[indexofuser].sub;
//        int subIndex = chosenSubscriptionIndex;
//
//        userSub.subscription_type = arr_subscription[subIndex].plan_name;
//        userSub.fixed = arr_subscription[subIndex].fixed;
//        userSub.plan_type = planType.toStdString();
//
//        int selectedZone = 0;
//        if (arr_subscription[subIndex].fixed == 'y') {
//            // Only require zone if it's fixed
//            if (!ui->admin_zone_list->currentItem()) {
//                QMessageBox::warning(this, "Selection Required", "Please select a zone.");
//                return;
//            }
//
//            selectedZone = ui->admin_zone_list->currentItem()->data(Qt::UserRole).toInt();
//        }
//
//        if (planType == "month") {
//            const auto& m = arr_subscription[subIndex].month_sub[planIndex];
//            userSub.duriation_plan_type = m.duration;
//            userSub.Num_trips = m.no_of_trips;
//            userSub.remaining_trips = m.no_of_trips;
//            userSub.zone = selectedZone;
//            if (selectedZone >= 1 && selectedZone <= 30)
//                userSub.zonePrice = m.zonesPrice[selectedZone - 1];
//
//        }
//        else if (planType == "year") {
//            const auto& y = arr_subscription[subIndex].year_sub[planIndex];
//            userSub.duriation_plan_type = y.duration;
//            userSub.Num_trips = y.no_of_trips;
//            userSub.remaining_trips = y.no_of_trips;
//            userSub.zone = selectedZone;
//            if (selectedZone >= 1 && selectedZone <= 30)
//                userSub.zonePrice = y.zonesPrice[selectedZone - 1];
//
//        }
//        else if (planType == "wallet") {
//            const auto& w = arr_subscription[subIndex].wallet_sub;
//            userSub.wallet_name = w.zone_num > 0 ? "Smart Wallet" : "Unknown";
//            userSub.zone = w.zone_num;
//            userSub.zonePrice = w.zonesPrice[0];
//
//            // Show success message
//            QMessageBox::information(this, "Success",
//                "Now you will go to charge the wallet for the user: " +
//                QString::fromStdString(arr_users[indexofuser].username));
//
//            // Redirect to wallet continuation page
//            ui->stackedWidget->setCurrentWidget(ui->admin_wallet_contin);
//
//            // ✅ UPDATE LABEL TO SHOW CURRENT WALLET BALANCE
//            ui->label_current_balance->setText(
//                QString("Current Wallet Balance: %1 LE")
//                .arg(arr_users[indexofuser].sub.balancew)
//            );
//
//            // Clear input field and set focus
//            ui->wallet_admin_enter_balancew->clear();
//            ui->wallet_admin_enter_balancew->setFocus();
//
//            return;
//        }
//        // 🔍 Balance Check
//        long long userBalance = arr_users[indexofuser].balance;
//        long long requiredBalance = userSub.zonePrice;
//
//        if (userBalance < requiredBalance) {
//            QMessageBox::warning(this, "Insufficient Balance",
//                "❌ Insufficient balance. Please recharge your account.");
//
//            // Show and connect recharge button
//            ui->admin_rech_balance_in_subsc->setVisible(true);
//            connect(ui->admin_rech_balance_in_subsc, &QPushButton::clicked, this, [=]() {
//                ui->stackedWidget->setCurrentWidget(ui->charge_balance);
//                });
//
//            return;
//        }
//
//        // Deduct balance
//        arr_users[indexofuser].balance -= requiredBalance;
//
//
//        // Set activation date
//        userSub.activation = QString::fromStdString(getCurrentDate()).toStdString();
//
//        time_t now = time(NULL);
//        tm localTime;
//        localtime_s(&localTime, &now);
//
//        if (userSub.fixed == 'y') {
//            if (planType == "month") {
//                localTime.tm_mon += userSub.duriation_plan_type;
//            }
//            else if (planType == "year") {
//                localTime.tm_year += userSub.duriation_plan_type;
//            }
//            mktime(&localTime);
//            userSub.expiry = QString("%1/%2/%3")
//                .arg(localTime.tm_mday)
//                .arg(localTime.tm_mon + 1)
//                .arg(localTime.tm_year + 1900)
//                .toStdString();
//        }
//        else {
//            userSub.expiry = "0";
//        }
//
//        // Show success message
//        QMessageBox::information(this, "Success",
//            "✅ Subscription successfully updated for user: " +
//            QString::fromStdString(arr_users[indexofuser].username));
//
//        // Hide recharge button after successful purchase
//        ui->admin_rech_balance_in_subsc->setVisible(false);
//        ui->stackedWidget->setCurrentWidget(ui->admin);
//        });
//}
//
//
//
//
//
//void QtWidgetsApplication3::handleWalletRecharge() {
//    bool ok;
//    int amount = ui->wallet_admin_enter_balancew->text().toInt(&ok);
//
//    if (!ok || amount <= 0) {
//        QMessageBox::warning(this, "Invalid Input", "Please enter a valid positive number.");
//        return;
//    }
//
//    // Get current user and selected subscription
//    user_subscriptions& userSub = arr_users[admin_chosen_user].sub;
//    const wallet& w = arr_subscription[chosenSubscriptionIndex].wallet_sub;
//
//    int currentWalletBalance = userSub.balancew;
//    int cardBalanceLimit = w.card_balance;
//    int fundMultiple = w.fund_multiple;
//
//    // 🔍 Check: Must be multiple of fund_multiple
//    if (amount % fundMultiple != 0) {
//        QMessageBox::warning(this, "Invalid Amount",
//            QString("Amount must be a multiple of %1 LE.").arg(fundMultiple));
//        return;
//    }
//
//    // 🔍 Check: New wallet balance must not exceed card_balance
//    if (currentWalletBalance + amount > cardBalanceLimit) {
//        QMessageBox::warning(this, "Balance Exceeded",
//            QString("Total wallet balance cannot exceed %1 LE.").arg(cardBalanceLimit));
//        return;
//    }
//
//    // 🔍 Check: User has enough main balance
//    long long& mainBalance = arr_users[admin_chosen_user].balance;
//    if (mainBalance < amount) {
//        QMessageBox::warning(this, "Insufficient Balance",
//            "❌ Insufficient main balance. Please recharge your account.");
//
//        // Show and connect recharge button
//        ui->admin_rech_balance_in_wallet->setVisible(true);
//        connect(ui->admin_rech_balance_in_wallet, &QPushButton::clicked, this, [=]() {
//            ui->stackedWidget->setCurrentWidget(ui->charge_balance);
//            });
//
//        return;
//    }
//
//    // Deduct from main balance and add to wallet
//    mainBalance -= amount;
//    userSub.balancew += amount;
//
//    // Notify and update label
//    QMessageBox::information(this, "Success",
//        QString("✅ Successfully added %1 LE to wallet.").arg(amount));
//
//    // ✅ Update label to reflect new balance
//    ui->label_current_balance->setText(
//        QString("Current Wallet Balance: %1 LE").arg(userSub.balancew));
//
//    // Clear input field
//    ui->wallet_admin_enter_balancew->clear();
//
//
//    // Optional: Go back to admin page
//    ui->stackedWidget->setCurrentWidget(ui->admin);
//}


void  QtWidgetsApplication3::on_sub_settings_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->manage_plan);
}

void  QtWidgetsApplication3::on_pushButton_8_clicked() {
    view_subscription();
    ui->stackedWidget->setCurrentWidget(ui->view_sub);

}

//from here 
//? DANGEROUS DONT touch 


void  QtWidgetsApplication3::on_pushButton_9_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->renew_sub);


    QString current_date = QString::fromStdString(getCurrentDate());
    ui->cur_date->setText(current_date);

    if (arr_users[indexofuser].sub.fixed == 'y') {
        QString expiry_date = QString::fromStdString(saveExpiry());
        ui->exp_date->setText(expiry_date);

        QString status = QString::fromStdString(check_expiry(arr_users));
        ui->sub_status->setText(status);
    }


    else {

        ui->exp_date->setText("this subscription doesn't have an expiry date");


        ui->sub_status->setText("doesn't have remaining days ");


    }

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


    if (arr_users[indexofuser].sub.fixed == 'y') {
        ui->cur_balance->setText(QString::fromStdString(to_string(arr_users[indexofuser].balance)));
        ui->rem_trips->setText(QString::fromStdString(to_string(arr_users[indexofuser].sub.remaining_trips)));

    }

    else {
        ui->cur_balance->setText("in the wallet " + (QString::fromStdString(to_string(arr_users[indexofuser].balance))));

        ui->rem_trips->setText("you doesn't have trips in this subscription ");

    }


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
   /* / cout << "Expiry date: " << datestring << endl; /*/
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
    if (arr_users[indexofuser].sub.fixed == 'n')
    {
        ui->stackedWidget->setCurrentWidget(ui->renew_in_wallet_subsc);
        ui->old_wallet_balance->setText(QString::number(arr_users[indexofuser].sub.balancew));


    }

    if (arr_users[indexofuser].sub.fixed == 'y') {


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


}



void QtWidgetsApplication3::on_confirm_wallet_balance_clicked()
{



    bool ok;
    int wallet_recharge = ui->wallet_new_balance->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Input Error", "Please enter a valid number.");
        return;
    }


    for (int i = 0;i < num_of_subsc;i++) {

        if (arr_subscription[i].plan_name == arr_users[indexofuser].sub.subscription_type)
        {

            if (arr_subscription[i].wallet_sub.card_balance < wallet_recharge)
            {
                why_grater = true;

                if (arr_subscription[i].wallet_sub.fund_multiple % wallet_recharge == 0) {
                    why = true;

                    if (arr_users[indexofuser].balance >= wallet_recharge) {

                        arr_users[indexofuser].sub.balancew += wallet_recharge;
                        arr_users[indexofuser].balance -= wallet_recharge;

                        QMessageBox::information(this, "Success", "Recharged successful!");


                    }

                    else {

                        QMessageBox::warning(this, "Dont have enough balnace. your balance is " + arr_users[indexofuser].balance, "Please Recharge Your Balance.");
                    }
                }
                if (!why) {

                    QMessageBox::warning(
                        this,
                        "Invalid Balance",
                        "Wallet balance must be in multiple of: " + QString::number(arr_subscription[i].wallet_sub.fund_multiple)
                    );


                }
                if (!why_grater) {
                    QMessageBox::warning(this,
                        "Invalid Balance",
                        "Put a num less than this balance : " + QString::number(arr_subscription[i].wallet_sub.card_balance)
                    );
                }
            }
        }
    }


    ui->old_wallet_balance->setText(QString::number(arr_users[indexofuser].sub.balancew));

}

void QtWidgetsApplication3::on_back_to_renew_page_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->renew_page);

}

void QtWidgetsApplication3::on_recharge_main_bala_in_wallet_clicked() {

    ui->stackedWidget->setCurrentWidget(ui->charge_user_balance_page);

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


//? DONT TOUCH 
//to here 
//DONT PLAY IN THIS FILE I WILL KILL YOU 

void QtWidgetsApplication3::on_recharge_button_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->charge_user_balance_page);
    ui->old_user_balance->setText(QString::fromStdString(to_string(arr_users[indexofuser].balance)));

}


void QtWidgetsApplication3::on_submit_balance_clicked()
{
    double value = ui->user_input_balance->value();

    arr_users[indexofuser].balance += value;
    QMessageBox::information(this, "Success", "Your balance has charged correctly !");
    //update balance 
    ui->old_user_balance->setText(QString::fromStdString(to_string(arr_users[indexofuser].balance)));
    ui->cur_balance->setText(QString::fromStdString(to_string(arr_users[indexofuser].balance)));
}

void QtWidgetsApplication3::on_back_from_balance_clicked()

{

    ui->stackedWidget->setCurrentWidget(ui->renew_page);


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