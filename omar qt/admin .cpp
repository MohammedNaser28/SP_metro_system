#include"QtWidgetsApplication3.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <QStringList>
#include <QListWidgetItem>
#include "global.h"
#include "structures.h"

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



void QtWidgetsApplication3::on_pushButton_23_clicked() {
    // Set username and navigate to admin subscription page
    ui->user_name_in_admin_subsc->setText(QString::fromStdString(arr_users[admin_chosen_user].username));
    ui->stackedWidget->setCurrentWidget(ui->admin_change_user_subsc);

    // Clear previous data
    ui->admin_main_subscriptions->clear();
    ui->admin_plan_subscription_details->clear();
    ui->admin_zone_list->clear();

    // Hide recharge button by default
    ui->admin_rech_balance_in_subsc->setVisible(false);

    if (num_of_subsc == 0) {
        ui->admin_main_subscriptions->addItem("No available subscriptions");
        return;
    }

    // Populate main subscription plans
    for (int i = 0; i < num_of_subsc; i++) {
        QString planName = QString::fromStdString(arr_subscription[i].plan_name);
        QListWidgetItem* item = new QListWidgetItem(QString::number(i + 1) + " - " + planName);
        item->setData(Qt::UserRole, i); // Store index
        ui->admin_main_subscriptions->addItem(item);
    }

    connect(ui->admin_main_subscriptions, &QListWidget::itemClicked, this, [=](QListWidgetItem* item) {
        int subIndex = item->data(Qt::UserRole).toInt();
        chosenSubscriptionIndex = subIndex;

        // Clear lists
        ui->admin_plan_subscription_details->clear();
        ui->admin_zone_list->clear();

        if (arr_subscription[subIndex].fixed == 'y') {
            // Fixed subscriptions: Monthly / Yearly

            for (int i = 0; i < arr_subscription[subIndex].month_count; i++) {
                const auto& m = arr_subscription[subIndex].month_sub[i];

                QString zonesPrices;
                for (int z = 0; z < 4; z++) {
                    if (z < 30 && m.zonesPrice[z] > 0) {
                        if (z == 0)
                            zonesPrices += QString("\nprice for zone %1 is %2").arg(z + 1).arg(m.zonesPrice[z]);
                        else
                            zonesPrices += QString("\nzone %1 is %2").arg(z + 1).arg(m.zonesPrice[z]);
                    }
                }

                QString planText = QString("Monthly : %1 month(s) %2 trips").arg(m.duration).arg(m.no_of_trips);
                if (!zonesPrices.isEmpty()) {
                    planText += zonesPrices;
                }

                QListWidgetItem* item = new QListWidgetItem(planText);
                item->setData(Qt::UserRole, i);
                item->setData(Qt::UserRole + 1, "month");
                ui->admin_plan_subscription_details->addItem(item);
            }

            for (int i = 0; i < arr_subscription[subIndex].year_count; i++) {
                const auto& y = arr_subscription[subIndex].year_sub[i];

                QString zonesPrices;
                for (int z = 0; z < 4; z++) {
                    if (z < 30 && y.zonesPrice[z] > 0) {
                        if (z == 0)
                            zonesPrices += QString("\nprice for zone %1 is %2").arg(z + 1).arg(y.zonesPrice[z]);
                        else
                            zonesPrices += QString("\nzone %1 is %2").arg(z + 1).arg(y.zonesPrice[z]);
                    }
                }

                QString planText = QString("Yearly : %1 year(s) %2 trips").arg(y.duration).arg(y.no_of_trips);
                if (!zonesPrices.isEmpty()) {
                    planText += zonesPrices;
                }

                QListWidgetItem* item = new QListWidgetItem(planText);
                item->setData(Qt::UserRole, i);
                item->setData(Qt::UserRole + 1, "year");
                ui->admin_plan_subscription_details->addItem(item);
            }

            // Populate zone list
            for (int z = 1; z <= 4; z++) {
                QListWidgetItem* zoneItem = new QListWidgetItem(QString("Zone %1").arg(z));
                zoneItem->setData(Qt::UserRole, z); // Store zone number as user role
                ui->admin_zone_list->addItem(zoneItem);
            }

            ui->admin_zone_list->setEnabled(true);

        }
        else {
            // Smart Wallet subscription
            const auto& w = arr_subscription[subIndex].wallet_sub;

            QString plan = QString("Wallet - Max: %1 LE\nFund Multiple: %2 LE")
                .arg(w.card_balance)
                .arg(w.fund_multiple);

            // Add all 4 zones
            for (int z = 0; z < 4 && z < 30 && w.zonesPrice[z] > 0; z++) {
                plan += QString("\nZone %1 is %2 LE").arg(z + 1).arg(w.zonesPrice[z]);
            }

            QListWidgetItem* item = new QListWidgetItem(plan);
            item->setData(Qt::UserRole, 0);
            item->setData(Qt::UserRole + 1, "wallet");
            ui->admin_plan_subscription_details->addItem(item);

            // Disable zone list
            ui->admin_zone_list->setEnabled(false);
            ui->admin_zone_list->clear();
        }
        });

    // Connect submit button
    connect(ui->submit_admin_subsc, &QPushButton::clicked, this, [=]() {
        // Get selected plan
        QListWidgetItem* selectedItem = ui->admin_plan_subscription_details->currentItem();
        if (!selectedItem) {
            QMessageBox::warning(this, "Selection Required", "Please select a subscription plan.");
            return;
        }

        int planIndex = selectedItem->data(Qt::UserRole).toInt();
        QString planType = selectedItem->data(Qt::UserRole + 1).toString();

        user_subscriptions& userSub = arr_users[admin_chosen_user].sub;
        int subIndex = chosenSubscriptionIndex;

        userSub.subscription_type = arr_subscription[subIndex].plan_name;
        userSub.fixed = arr_subscription[subIndex].fixed;
        userSub.plan_type = planType.toStdString();

        int selectedZone = 0;
        if (arr_subscription[subIndex].fixed == 'y') {
            // Only require zone if it's fixed
            if (!ui->admin_zone_list->currentItem()) {
                QMessageBox::warning(this, "Selection Required", "Please select a zone.");
                return;
            }

            selectedZone = ui->admin_zone_list->currentItem()->data(Qt::UserRole).toInt();
        }

        if (planType == "month") {
            const auto& m = arr_subscription[subIndex].month_sub[planIndex];
            userSub.duriation_plan_type = m.duration;
            userSub.Num_trips = m.no_of_trips;
            userSub.remaining_trips = m.no_of_trips;
            userSub.zone = selectedZone;
            if (selectedZone >= 1 && selectedZone <= 30)
                userSub.zonePrice = m.zonesPrice[selectedZone - 1];

        }
        else if (planType == "year") {
            const auto& y = arr_subscription[subIndex].year_sub[planIndex];
            userSub.duriation_plan_type = y.duration;
            userSub.Num_trips = y.no_of_trips;
            userSub.remaining_trips = y.no_of_trips;
            userSub.zone = selectedZone;
            if (selectedZone >= 1 && selectedZone <= 30)
                userSub.zonePrice = y.zonesPrice[selectedZone - 1];

        }
        else if (planType == "wallet") {
            const auto& w = arr_subscription[subIndex].wallet_sub;
            userSub.wallet_name = w.zone_num > 0 ? "Smart Wallet" : "Unknown";
            userSub.zone = w.zone_num;
            userSub.zonePrice = w.zonesPrice[0];

            // Show success message
            QMessageBox::information(this, "Success",
                "Now you will go to charge the wallet for the user: " +
                QString::fromStdString(arr_users[admin_chosen_user].username));

            // Redirect to wallet continuation page
            ui->stackedWidget->setCurrentWidget(ui->admin_wallet_contin);

            // ✅ UPDATE LABEL TO SHOW CURRENT WALLET BALANCE
            ui->label_current_balance->setText(
                QString("Current Wallet Balance: %1 LE")
                .arg(arr_users[admin_chosen_user].sub.balancew)
            );

            // Clear input field and set focus
            ui->wallet_admin_enter_balancew->clear();
            ui->wallet_admin_enter_balancew->setFocus();

            return;
        }
        // 🔍 Balance Check
        long long userBalance = arr_users[admin_chosen_user].balance;
        long long requiredBalance = userSub.zonePrice;

        if (userBalance < requiredBalance) {
            QMessageBox::warning(this, "Insufficient Balance",
                "❌ Insufficient balance. Please recharge your account.");

            // Show and connect recharge button
            ui->admin_rech_balance_in_subsc->setVisible(true);
            connect(ui->admin_rech_balance_in_subsc, &QPushButton::clicked, this, [=]() {
                ui->stackedWidget->setCurrentWidget(ui->charge_balance);
                });

            return;
        }

        // Deduct balance
        arr_users[admin_chosen_user].balance -= requiredBalance;

       
        // Set activation date
        userSub.activation = QString::fromStdString(getCurrentDate()).toStdString();

        time_t now = time(NULL);
        tm localTime;
        localtime_s(&localTime, &now);

        if (userSub.fixed == 'y') {
            if (planType == "month") {
                localTime.tm_mon += userSub.duriation_plan_type;
            }
            else if (planType == "year") {
                localTime.tm_year += userSub.duriation_plan_type;
            }
            mktime(&localTime);
            userSub.expiry = QString("%1/%2/%3")
                .arg(localTime.tm_mday)
                .arg(localTime.tm_mon + 1)
                .arg(localTime.tm_year + 1900)
                .toStdString();
        }
        else {
            userSub.expiry = "0";
        }

        // Show success message
        QMessageBox::information(this, "Success",
            "✅ Subscription successfully updated for user: " +
            QString::fromStdString(arr_users[admin_chosen_user].username));
     
        // Hide recharge button after successful purchase
        ui->admin_rech_balance_in_subsc->setVisible(false);
        ui->stackedWidget->setCurrentWidget(ui->admin);
        });
}





void QtWidgetsApplication3::handleWalletRecharge() {
    bool ok;
    int amount = ui->wallet_admin_enter_balancew->text().toInt(&ok);

    if (!ok || amount <= 0) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid positive number.");
        return;
    }

    // Get current user and selected subscription
    user_subscriptions& userSub = arr_users[admin_chosen_user].sub;
    const wallet& w = arr_subscription[chosenSubscriptionIndex].wallet_sub;

    int currentWalletBalance = userSub.balancew;
    int cardBalanceLimit = w.card_balance;
    int fundMultiple = w.fund_multiple;

    // 🔍 Check: Must be multiple of fund_multiple
    if (amount % fundMultiple != 0) {
        QMessageBox::warning(this, "Invalid Amount",
            QString("Amount must be a multiple of %1 LE.").arg(fundMultiple));
        return;
    }

    // 🔍 Check: New wallet balance must not exceed card_balance
    if (currentWalletBalance + amount > cardBalanceLimit) {
        QMessageBox::warning(this, "Balance Exceeded",
            QString("Total wallet balance cannot exceed %1 LE.").arg(cardBalanceLimit));
        return;
    }

    // 🔍 Check: User has enough main balance
    long long& mainBalance = arr_users[admin_chosen_user].balance;
    if (mainBalance < amount) {
        QMessageBox::warning(this, "Insufficient Balance",
            "❌ Insufficient main balance. Please recharge your account.");

        // Show and connect recharge button
        ui->admin_rech_balance_in_wallet->setVisible(true);
        connect(ui->admin_rech_balance_in_wallet, &QPushButton::clicked, this, [=]() {
            ui->stackedWidget->setCurrentWidget(ui->charge_balance);
            });

        return;
    }
}




void QtWidgetsApplication3::shiftStationsUp(int line, int index)
{
    for (int i = index; i < numStationsInLine[line] - 1; ++i) {
        allStations[line][i] = allStations[line][i + 1];

        if (allStations[line][i].name != "-" && allStations[line][i].name != "_") {
            allStations[line][i].number -= 1;
        }
    }

    numStationsInLine[line]--;
    allStations[line][numStationsInLine[line]].name = "-";
}

//DELETE STATION 

void QtWidgetsApplication3::on_delete55_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->deletestation);
}


bool QtWidgetsApplication3::isInterchangeStation(const QString& name) {
    return name == "Sadat" || name == "Al_Shohadaa" || name == "Attaba" || name == "Kit_Kat" || name == "Cairo_University";
}


void QtWidgetsApplication3::on_pushButton_26_clicked()
{
    int line = ui->line->text().toInt();
    int index = ui->index->text().toInt() - 1;

    if (line < 1 || line > 3 || index < 0 || index >= MAX_STATIONS_PER_LINE) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid line number and station index.");
        return;
    }

    if (allStations[index][line - 1].name == "-") {
        QMessageBox::warning(this, "Error", "Station does not exist.");
        return;
    }

    // if (isInterchangeStation(allStations[index][line - 1].name)) {
    //    QMessageBox::warning(this, "Error", "You cannot delete an interchange station.");
    //    return;
    //}

    shiftStationsUp(line - 1, index);
    num_stations--;
    buildGraph();

    saveStationsToFile(); // ✅ دي أهم خطوة

    QMessageBox::information(this, "Done", "Station deleted successfully.");
}



void QtWidgetsApplication3::saveStationsToFile() {
    QFile file("stations.txt");  

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);

        for (int l = 0; l < 3; ++l) {
            for (int i = 0; i < MAX_STATIONS_PER_LINE; ++i) {
                if (allStations[i][l].name != "-") {
                    out << QString::fromStdString(allStations[i][l].name) << "," << (l + 1) << "\n";
                }
            }
        }

        file.close();
    }
    else {
        QMessageBox::warning(this, "Error", "Could not write to file!");
    }
}


void QtWidgetsApplication3::write_stations()
{
    std::ofstream file("stations.txt");
    if (!file.is_open()) {
        QMessageBox::warning(this, "Error", "Could not open file for writing!");
        return;
    }

    // احسب الخط الأطول
    int maxStations = 0;
    for (int line = 0; line < 3; ++line) {
        if (numStationsInLine[line] > maxStations) {
            maxStations = numStationsInLine[line];
        }
    }

    // اكتب الأعمدة كسطور متوازية
    for (int i = 0; i < maxStations; ++i) {
        for (int line = 0; line < 3; ++line) {
            if (i < numStationsInLine[line]) {
                file << allStations[line][i].name;
            }
            else {
                file << "-";
            }

            if (line < 3 - 1) {
                file << "\t";
            }
        }
        file << "\n";
    }

    file.close();
}




void QtWidgetsApplication3::read_stations()
{
    std::ifstream file("stations.txt");
    if (!file.is_open()) {
        QMessageBox::warning(this, "Error", "Could not open stations.txt for reading!");
        return;
    }

    // صفّر العدادات
    for (int line = 0; line < 3; ++line) {
        numStationsInLine[line] = 0;
    }

    std::string name;
    int lineNumber;

    while (file >> name >> lineNumber) {
        int lineIndex = lineNumber - 1; // لأن index بيبدأ من صفر
        int stationIndex = numStationsInLine[lineIndex];

        allStations[lineIndex][stationIndex].name = name;
        allStations[lineIndex][stationIndex].number = lineNumber;

        numStationsInLine[lineIndex]++;
    }

    file.close();
}



void  QtWidgetsApplication3::on_pushButton_27_clicked() {

    ui->stackedWidget->setCurrentWidget(ui->ride_settings);

//? ERROR HERE
    //user_subscriptions& userSub = arr_users[admin_chosen_user].sub;
    //long long& mainBalance = arr_users[admin_chosen_user].balance;

    //// Deduct from main balance and add to wallet
    //mainBalance -= amount;
    //userSub.balancew += amount;

    // Notify and update label
 /*   QMessageBox::information(this, "Success",
        QString("✅ Successfully added %1 LE to wallet.").arg(amount));*/

    // ✅ Update label to reflect new balance
    //ui->label_current_balance->setText(
    //    QString("Current Wallet Balance: %1 LE").arg(userSub.balancew));

    // Clear input field
    ui->wallet_admin_enter_balancew->clear();

   
    // Optional: Go back to admin page
    ui->stackedWidget->setCurrentWidget(ui->admin);
}