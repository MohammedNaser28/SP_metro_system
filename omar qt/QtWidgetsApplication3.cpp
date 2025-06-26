#include "QtWidgetsApplication3.h"
#include "ui_QtWidgetsApplication3.h"  // Include the generated UI class
#include"dependence.h"
#include"global.h"
#include"structures.h"
#include"stations.h"
#include "view users.h"
#include <QTableWidget>


#include"register.h"
int chosenSubscriptionIndex = -1;
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

void QtWidgetsApplication3::start_up()
{

    ui->stackedWidget->setCurrentWidget(ui->welcome2);

}

void  QtWidgetsApplication3::on_personal_details_clicked() {
    ui->email_label->setText(QString::fromStdString(arr_users[indexofuser].contactdet.email));
    ui->pass_label->setText(QString::fromStdString(arr_users[indexofuser].pass));
    ui->id_label->setText(QString::fromStdString(arr_users[indexofuser].id));
    ui->balance_label->setText(QString::number(arr_users[indexofuser].balance));
    ui->username_label->setText(QString::fromStdString(arr_users[indexofuser].username));
    ui->stackedWidget->setCurrentWidget(ui->current_data);
}
void  QtWidgetsApplication3::on_rides_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->rides_2);
}
void  QtWidgetsApplication3::on_sub_settings_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->manage_plan);
}

void  QtWidgetsApplication3::on_pushButton_6_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->new_rides);

    ///--------           FILL STATIONS COMBOBOX            ----------///

    for (int i = 0; i < NUM_LINES; i++)
    {
        for (int j = 0; j < MAX_STATIONS_PER_LINE; j++)
        {

            if (allStations[j][i].name == "-" || allStations[j][i].name == "Switching.")
            {
                continue;
            }
            ui->startstation->addItem(QString::fromStdString(allStations[j][i].name));
            ui->endstation->addItem(QString::fromStdString(allStations[j][i].name));
        }
    }
}

void QtWidgetsApplication3::on_pushButton_7_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->rides_history);

    QString output;
    output += "\n--- Ride History for User ID: " + QString::fromStdString(arr_users[indexofuser].id) + " ---\n";
    bool found = false;
    int cntride = 1;

    for (int i = 0; i < MAX_rides; i++) {
        if (rides[i].id == arr_users[indexofuser].id) {
            output += "Trip number " + QString::number(cntride) + "\n";
            output += " Entry station : " + QString::fromStdString(rides[i].entryStation) + "\n";
            output += " Exit station : " + QString::fromStdString(rides[i].ExitStation) + "\n";
            output += " Your subscription is : " + QString::fromStdString(arr_users[indexofuser].sub.subscription_type) + "\n";

            if (arr_users[indexofuser].sub.fixed == 'n') {
                output += " And you take : " + QString::number(rides[i].RideFare) + " From Your balance\n";
                output += " Your remaining balance is : " + QString::number(arr_users[indexofuser].sub.balancew) + "\n";
            }
            else if (arr_users[indexofuser].sub.fixed == 'y') {
                output += " And you used one trip from your travel balance and your remaining trips is : "
                    + QString::number(rides[i].RideFare) + "\n";
            }

            output += "  Date of trip : " + (rides[i].Date) + "\n";
            output += "____________________________________________________________\n\n";
            found = true;
            cntride++;
        }
    }

    if (!found) {
        output += "No rides found.\n";
    }

    ui->textEdit_rideHistory->setText(output);  // Replace with your QTextEdit or QLabel name
}

void  QtWidgetsApplication3::on_pushButton_8_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->view_sub);
}

void  QtWidgetsApplication3::on_pushButton_15_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->user_settings);
}

void  QtWidgetsApplication3::on_pushButton_17_clicked() {
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
        /* ui->stackedWidget->setCurrentWidget(ui->view_users_toadmin);

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
         }*/

    }
}



void  QtWidgetsApplication3::on_pushButton_9_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->renew_sub);
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

    /// admin_chosen_index is the index use it 
   ui->stackedWidget->setCurrentWidget(ui->admin); /// !!! change "admin" with the name of the widget of ali
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

void QtWidgetsApplication3::on_pushButton_12_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->charge_balance);
    // should put the index that moaz will give me 
    ui->admin_change_balance->setText(QString::number(arr_users[indexofuser].balance));
    ui->admin_change_balance->clear();

}
//moazz put in the index of array the index that you will give us please 
void QtWidgetsApplication3::on_pushButton_24_clicked()
{
        bool ok;
        int chargeAmount = ui->new_balance->text().toInt(&ok);

        if (!ok || chargeAmount <= 0) {
            QMessageBox::warning(this, "Invalid Input", "Please enter a valid positive number.");
            return;
        }

        // Update user balance
        arr_users[indexofuser].balance += chargeAmount;

        // Update the Text Browser to show old balance (before recharge)
        ui->admin_change_balance->setText(QString::number(arr_users[indexofuser].balance));

        // Update the Line Edit to show the new balance (after recharge)
        ui->new_balance->setText(QString::number(arr_users[indexofuser].balance));

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



