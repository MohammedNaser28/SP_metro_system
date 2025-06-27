#include "QtWidgetsApplication3.h"
#include "ui_QtWidgetsApplication3.h"  // Include the generated UI class


#include <QTableWidget>


QtWidgetsApplication3::QtWidgetsApplication3(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)  // Correct link to the UI class generated from the .ui file
{
    ui->setupUi(this);  // Set up the UI components
    ui->stackedWidget->setCurrentWidget(ui->welcome2);
   

}

QtWidgetsApplication3::~QtWidgetsApplication3()
{
    delete ui;  // Clean up
}

void QtWidgetsApplication3::setPage(int index)
{
    ui->stackedWidget->setCurrentIndex(index);

}



void QtWidgetsApplication3::choose_sub()
{

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

std::string QtWidgetsApplication3::getCurrentDate()
{
   
        auto now = chrono::system_clock::now();
        time_t now_time = chrono::system_clock::to_time_t(now);

        struct tm timeinfo;
        localtime_s(&timeinfo, &now_time);

        char buffer[80];
        strftime(buffer, sizeof(buffer), "%d/%m/%Y", &timeinfo);
        return string(buffer);
    
}

std::string QtWidgetsApplication3::saveExpiry()
{
    time_t now = time(NULL);
    tm localTime;
    localtime_s(&localTime, &now);
    string exp_date;
    if (arr_users[indexofuser].sub.fixed == 'y') {
        if (arr_users[indexofuser].sub.plan_type == "month") {
            localTime.tm_mon += arr_users[indexofuser].sub.duriation_plan_type;
        }
        else if (arr_users[indexofuser].sub.plan_type == "year") {
            localTime.tm_year += arr_users[indexofuser].sub.duriation_plan_type;
        }
        mktime(&localTime);
        int day = localTime.tm_mday;
        int month = localTime.tm_mon + 1;
        int year = localTime.tm_year + 1900;
         exp_date = arr_users[indexofuser].sub.expiry = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
    }
    else if (arr_users[indexofuser].sub.fixed == 'n') {
         exp_date = arr_users[indexofuser].sub.expiry = "0";

    }

    return exp_date;
}

void QtWidgetsApplication3::on_change_sub_clicked()
{
    choose_sub();
    ui->stackedWidget->setCurrentWidget(ui->subscriptions);

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
    if (final == 0) { status+= "It's time to renew your subscription !" ; }
    else if (final < 0) { status += "Your subscription has expired !" ; }
    else if (final == 1) { status += "Renew is in 1 Day " ; }
    else if (final > 0) { status += ("Renew is in " + to_string(final) + " Days") ; }
    return status;

}

void QtWidgetsApplication3::on_confirm_renew_clicked()
{

    

     if ((arr_users[indexofuser].balance - arr_users[indexofuser].sub.zonePrice) < 0)
     {
        
        QMessageBox::warning(this, "Not enough balnace.", "Please Recharge Your Balance.");
        return;
    }

   

    // Update the Text Browser to show old balance (before recharge)
    ui->admin_change_balance->setText(QString::number(arr_users[indexofuser].balance));

    // Update the Line Edit to show the new balance (after recharge)
    ui->new_balance->setText(QString::number(arr_users[indexofuser].balance));

    // Show success message
    QMessageBox::information(this, "Success", "Recharge successful!");

    
}

void QtWidgetsApplication3::on_cancel_renew_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->welcome2);

}

void QtWidgetsApplication3::on_recharge_button_clicked()
{
    /*ui->user_balance->setText(QString::fromStdString(to_string(arr_users[indexofuser].balance)));
    
    bool ok;
    int chargeAmount = ui->new_balance->text().toInt(&ok);
    arr_users[indexofuser].balance += chargeAmount;
    ui->stackedWidget->setCurrentWidget(ui->renew_page);*/
}


void QtWidgetsApplication3::start_up()
{

    ui->stackedWidget->setCurrentWidget(ui->welcome2);

}


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

//
//void  QtWidgetsApplication3::on_pushButton_17_clicked() {
//    ui->stackedWidget->setCurrentWidget(ui->view_users_toadmin);
//
//
//    ui->tableWidget_users->setRowCount(0);
//    ui->tableWidget_users->setColumnCount(5);
//    QStringList headers;
//    headers << "Name" << "Complaints" << "Email" << "Balance" << "Subscription Type";
//    ui->tableWidget_users->setHorizontalHeaderLabels(headers);
//
//    int row = 0;
//    for (int i = 0; i < number_of_users_in_array; ++i) {
//        if (arr_users[i].admin_role == 0) {
//            ui->tableWidget_users->insertRow(row);
//
//            ui->tableWidget_users->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(arr_users[i].username)));
//
//
//            QString complaintText = QString::fromStdString(arr_users[i].complaints);
//            QString shortenedText = complaintText.left(30);
//            if (complaintText.length() > 30)
//                shortenedText += "...";
//
//            QTableWidgetItem* item = new QTableWidgetItem(shortenedText);
//            item->setToolTip(complaintText);
//            ui->tableWidget_users->setItem(row, 1, item);
//
//            ui->tableWidget_users->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(arr_users[i].contactdet.email)));
//            ui->tableWidget_users->setItem(row, 3, new QTableWidgetItem(QString::number(arr_users[i].balance)));
//            ui->tableWidget_users->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(arr_users[i].sub.subscription_type)));
//
//            row++;
//        }
//        /* ui->stackedWidget->setCurrentWidget(ui->view_users_toadmin);
//
//         ui->tableWidget_users->setRowCount(0);
//         ui->tableWidget_users->setColumnCount(5);
//         QStringList headers;
//         headers << "Name" << "Complaints" << "Email" << "Balance" << "Subscription Type";
//         ui->tableWidget_users->setHorizontalHeaderLabels(headers);
//
//         int row = 0;
//         for (int i = 0; i < number_of_users_in_array; ++i) {
//             if (arr_users[i].admin_role == 0) {
//                 ui->tableWidget_users->insertRow(row);
//
//                 ui->tableWidget_users->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(arr_users[i].username)));
//
//
//                 QString complaintText = QString::fromStdString(arr_users[i].complaints);
//                 QString shortenedText = complaintText.left(30);
//                 if (complaintText.length() > 30)
//                     shortenedText += "...";
//
//                 QTableWidgetItem* item = new QTableWidgetItem(shortenedText);
//                 item->setToolTip(complaintText);
//                 ui->tableWidget_users->setItem(row, 1, item);
//
//                 ui->tableWidget_users->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(arr_users[i].contactdet.email)));
//                 ui->tableWidget_users->setItem(row, 3, new QTableWidgetItem(QString::number(arr_users[i].balance)));
//                 ui->tableWidget_users->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(arr_users[i].sub.subscription_type)));
//
//                 row++;
//             }
//         }*/
//
//    }
//}



void  QtWidgetsApplication3::on_pushButton_9_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->renew_sub);

    QString current_date = QString::fromStdString(getCurrentDate());
    ui->cur_date->setText(current_date);

    QString expiry_date = QString::fromStdString(saveExpiry());
    ui->exp_date->setText(expiry_date);

    QString status= QString::fromStdString(check_expiry(arr_users));
    ui->sub_status->setText(status);

}

void  QtWidgetsApplication3::on_delete_users_clicked()
{
    QString theindex = ui->NumOfUser->text().trimmed();
    bool ok;
    int admin_chosen_index = theindex.toInt(&ok);

    if (!ok ||admin_chosen_index<=0 || admin_chosen_index>number_of_users_in_array) {
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

/// for try run 
//void  QtWidgetsApplication3::on_pushButton_15_clicked() {
//   /* ui->stackedWidget->setCurrentWidget(ui->view_users_toadmin);
//
//
//        ui->tableWidget_users->setRowCount(0);
//        ui->tableWidget_users->setColumnCount(5);
//        QStringList headers;
//        headers << "Name"<<"Complaints" << "Email" << "Balance" << "Subscription Type";
//        ui->tableWidget_users->setHorizontalHeaderLabels(headers);
//
//        int row = 0;
//        for (int i = 0; i < number_of_users_in_array; ++i) {
//            if (arr_users[i].admin_role == 0) {
//                ui->tableWidget_users->insertRow(row);
//
//                ui->tableWidget_users->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(arr_users[i].username)));
//                ui->tableWidget_users->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(arr_users[i].complaints)));
//                ui->tableWidget_users->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(arr_users[i].contactdet.email)));
//                ui->tableWidget_users->setItem(row, 3, new QTableWidgetItem(QString::number(arr_users[i].balance)));
//                ui->tableWidget_users->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(arr_users[i].sub.subscription_type)));
//           
//
//                row++;
//            }
//        }*/
//    ui->stackedWidget->setCurrentWidget(ui->view_users_toadmin);
//
//    ui->tableWidget_users->setRowCount(0);
//    ui->tableWidget_users->setColumnCount(5);
//    QStringList headers;
//    headers << "Name" << "Complaints" << "Email" << "Balance" << "Subscription Type";
//    ui->tableWidget_users->setHorizontalHeaderLabels(headers);
//
//    int row = 0;
//    for (int i = 0; i < number_of_users_in_array; ++i) {
//        if (arr_users[i].admin_role == 0) {
//            ui->tableWidget_users->insertRow(row);
//
//            ui->tableWidget_users->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(arr_users[i].username)));
//
//
//            QString complaintText = QString::fromStdString(arr_users[i].complaints);
//            QString shortenedText = complaintText.left(30);
//            if (complaintText.length() > 30)
//                shortenedText += "...";
//
//            QTableWidgetItem* item = new QTableWidgetItem(shortenedText);
//            item->setToolTip(complaintText);
//            ui->tableWidget_users->setItem(row, 1, item);
//
//            ui->tableWidget_users->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(arr_users[i].contactdet.email)));
//            ui->tableWidget_users->setItem(row, 3, new QTableWidgetItem(QString::number(arr_users[i].balance)));
//            ui->tableWidget_users->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(arr_users[i].sub.subscription_type)));
//
//            row++;
//        }
//    }
//    
//}

void QtWidgetsApplication3::gotoadmin() {
    ui->stackedWidget->setCurrentWidget(ui->admin);  
}
//modify #admin

void QtWidgetsApplication3::on_pushButton_18_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->modify_user);




}

//charge balance #admin

void QtWidgetsApplication3::on_pushButton_12_clicked() {
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
        arr_users[admin_chosen_user ].balance += chargeAmount;

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




void QtWidgetsApplication3::on_pushButton_confirm_clicked() {
    if (chosenSubscriptionIndex == -1) 
    {
        QMessageBox::warning(this, "No Selection", "Please choose a subscription first.");
        return;
    }

    QString selectedPlan = QString::fromStdString(arr_subscription[chosenSubscriptionIndex].plan_name);
    QMessageBox::information(this, "Subscribed!", "You selected: " + selectedPlan);
}


void  QtWidgetsApplication3::on_confirmride_clicked()
{

    string start_st, end_st;
    start_st = ui->startstation->currentText().toStdString();
    end_st = ui->endstation->currentText().toStdString();
  
    
    
    buildGraph();

     
    // Assuming this runs after user chooses start and end station
    int real_zone = 0;

    if (stationcnt >= 1 && stationcnt <= 9)
        real_zone = 1;
    else if (stationcnt >= 10 && stationcnt <= 16)
        real_zone = 2;
    else if (stationcnt >= 17 && stationcnt <= 23)
        real_zone = 3;
    else if (stationcnt >= 24)
        real_zone = 4;

    // Assume 'indexofuser', 'arr_users', etc. are already loaded.
    if (arr_users[indexofuser].sub.fixed == 'n') {
        for (int i = 0; i < num_of_subsc; i++) {
            if (arr_users[indexofuser].sub.subscription_type == arr_subscription[i].plan_name) {
                double requiredBalance = arr_subscription[i].wallet_sub.zonesPrice[real_zone - 1];
                if (arr_users[indexofuser].sub.balancew >= requiredBalance) {

                    string path = findShortestPath(find_st_num(start_st), find_st_num(end_st));
                    ui->viewride->clear();
                    ui->viewride->setText(QString::fromStdString(path));

                    rides[ride_cnt].entryStation = start_st;
                    rides[ride_cnt].ExitStation = end_st;
                    rides[ride_cnt].RideFare = not_fixed(stationcnt);
                    rides[ride_cnt].Date = getCurrentDate();
                    rides[ride_cnt].id = arr_users[indexofuser].id;
                    ride_cnt++;

                    QMessageBox::information(this, "Success", "Trip recorded successfully!");

                }


                // will fix this when we put subscreption or with haya 
                //else { 
                //    QMessageBox msgBox;
                //    msgBox.setText("Your wallet balance is low, please charge it.");
                //    msgBox.setInformativeText("To renew press 'Yes'. To choose another station press 'No'.");
                //    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
                //    int ret = msgBox.exec();

                //    if (ret == QMessageBox::Yes) {
                //       /* renew_time(arr_users[indexofuser].sub);*/
                //    }
                //    else {
                //        return;
                //    }
                //}
            }
        }
    }
    else if (arr_users[indexofuser].sub.fixed == 'y') {
        bool not_your_zone = real_zone > arr_users[indexofuser].sub.zone;

        if (!not_your_zone) {
            if (arr_users[indexofuser].sub.remaining_trips > 0) {

                string path = findShortestPath(find_st_num(start_st), find_st_num(end_st));
                ui->viewride->clear();
                ui->viewride->setText(QString::fromStdString(path));

                rides[ride_cnt].entryStation = start_st;
                rides[ride_cnt].ExitStation = end_st;
                rides[ride_cnt].RideFare = calculated_fare(real_zone);
                rides[ride_cnt].Date = getCurrentDate();
                rides[ride_cnt].id = arr_users[indexofuser].id;
                ride_cnt++;

                QMessageBox::information(this, "Success", "Trip recorded successfully!");

            }
            //also will fix this with haya 
            /*else {
                QMessageBox msgBox;
                msgBox.setText("You have reached the maximum number of trips.");
                msgBox.setInformativeText("Renew subscription? Press Yes. Main menu? Press No.");
                msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
                int ret = msgBox.exec();

                if (ret == QMessageBox::Yes) {
                    renew_time(arr_users[indexofuser].sub);
                }
                else {
                    return;
                }
            }*/
        }
        else {
            QMessageBox::warning(this, "Zone Error", "You didn't subscribe to this zone. Try another one.");
            return;
        }
    }

    // Ask for another trip
    //QMessageBox againBox;
    //againBox.setText("Do you want another trip?");
    //againBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    //int againResponse = againBox.exec();
    //if (againResponse == QMessageBox::No) {
    //    close(); // Or go to main menu
    //}

 string path= findShortestPath(find_st_num(start_st),find_st_num(end_st));
  
    ui->viewride->clear();
   ui->viewride->setText(QString::fromStdString(path));


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


void QtWidgetsApplication3::on_logout_clicked() {
    emit switchToDialog();
}



