#include "QtWidgetsApplication3.h"
#include "ui_QtWidgetsApplication3.h"  // Include the generated UI class
#include"dependence.h"
#include"global.h"
#include"structures.h"
#include"stations.h"
#include "view users.h"
#include <QTableWidget>

int month_index = 0;
int year_index = 0;
//
//extern user_subscriptions subs[MAX];
//extern int num_of_subsc;
//extern int chosenSubscriptionIndex;
// plan subs[100];
// int num_of_subsc;
// int chosenSubscriptionIndex;
//

#include"register.h"
int chosenSubscriptionIndex = -1;
QtWidgetsApplication3::QtWidgetsApplication3(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)  // Correct link to the UI class generated from the .ui file
{
    ui->setupUi(this);  // Set up the UI components
    ui->stackedWidget->setCurrentWidget(ui->welcome2);
    // Month: zone spinbox controls row count in table
connect(ui->spinBox_month_zones, QOverload<int>::of(&QSpinBox::valueChanged),
        this, &QtWidgetsApplication3::on_spinBox_month_zones_valueChanged);

// Year: zone spinbox controls row count in table
connect(ui->spinBox_year_zones, QOverload<int>::of(&QSpinBox::valueChanged),
        this, &QtWidgetsApplication3::on_spinBox_year_zones_valueChanged);

// Month: OK and Cancel buttons
connect(ui->dialogButtonBox_month, &QDialogButtonBox::accepted,
        this, &QtWidgetsApplication3::on_dialogButtonBox_month_accepted);
connect(ui->dialogButtonBox_month, &QDialogButtonBox::rejected,
        this, &QtWidgetsApplication3::on_dialogButtonBox_month_rejected);

// Year: OK and Cancel buttons
connect(ui->dialogButtonBox_year, &QDialogButtonBox::accepted,
        this, &QtWidgetsApplication3::on_dialogButtonBox_year_accepted);
connect(ui->dialogButtonBox_year, &QDialogButtonBox::rejected,
        this, &QtWidgetsApplication3::on_dialogButtonBox_year_rejected);

// Show/hide based on plan type selection
connect(ui->radioButton_fixed, &QRadioButton::clicked,
        this, &QtWidgetsApplication3::on_radioButton_fixed_clicked);
connect(ui->radioButton_wallet, &QRadioButton::clicked,
        this, &QtWidgetsApplication3::on_radioButton_wallet_clicked);


}

QtWidgetsApplication3::~QtWidgetsApplication3()
{
    delete ui;  // Clean up
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
void  QtWidgetsApplication3::on_pushButton_9_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->renew_sub);
}


void QtWidgetsApplication3::on_pushButton_10_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->subscriptions);
    ui->listWidget_subscriptions->clear();
    ui->label_subscription_details->clear();  // QTextEdit (not QLabel anymore)
    chosenSubscriptionIndex = -1;

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

void  QtWidgetsApplication3::on_pushButton_15_clicked() {
   /* ui->stackedWidget->setCurrentWidget(ui->view_users_toadmin);


        ui->tableWidget_users->setRowCount(0);
        ui->tableWidget_users->setColumnCount(5);
        QStringList headers;
        headers << "Name"<<"Complaints" << "Email" << "Balance" << "Subscription Type";
        ui->tableWidget_users->setHorizontalHeaderLabels(headers);

        int row = 0;
        for (int i = 0; i < number_of_users_in_array; ++i) {
            if (arr_users[i].admin_role == 0) {
                ui->tableWidget_users->insertRow(row);

                ui->tableWidget_users->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(arr_users[i].username)));
                ui->tableWidget_users->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(arr_users[i].complaints)));
                ui->tableWidget_users->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(arr_users[i].contactdet.email)));
                ui->tableWidget_users->setItem(row, 3, new QTableWidgetItem(QString::number(arr_users[i].balance)));
                ui->tableWidget_users->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(arr_users[i].sub.subscription_type)));
           

                row++;
            }
        }*/
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

void QtWidgetsApplication3::gotoadmin() {
    ui->stackedWidget->setCurrentWidget(ui->admin);  
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


void QtWidgetsApplication3::on_addsub_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->add_sub);
    ui->stackedWidget_2->setCurrentIndex(0); // Show neutral/empty page first

    ui->groupBox_monthly->hide();
    ui->groupBox_yearly->hide();
    ui->groupBox_fixed->hide(); // Hide fixed options initially

    // Reset spin boxes with valid ranges
    ui->spinBox_month_duration->setRange(1, 1000);
    ui->spinBox_month_trips->setRange(1, 1000);
    ui->spinBox_month_zones->setRange(0, 30);

    ui->spinBox_year_duration->setRange(1, 1000);
    ui->spinBox_year_trips->setRange(1, 1000);
    ui->spinBox_year_zones->setRange(0, 30);

    ui->spinBox_cardBalance->setRange(0, 100000);
    ui->spinBox->setRange(1, 1000); // fund multiple

    month_index = 0;
    year_index = 0;
}

void QtWidgetsApplication3::on_radioButton_fixed_clicked()
{
    ui->stackedWidget_2->setCurrentWidget(ui->page); // Show fixed page
    ui->groupBox_fixed->show(); // Show fixed options
}

void QtWidgetsApplication3::on_radioButton_wallet_clicked()
{
    ui->stackedWidget_2->setCurrentWidget(ui->page_2); // Show wallet page
    ui->groupBox_fixed->hide(); // Hide fixed options
}

void QtWidgetsApplication3::on_pushButton_addMonth_clicked()
{
    ui->groupBox_monthly->show();
    ui->spinBox_month_zones->setValue(0);
    ui->tableWidget_month_zonePrices->setRowCount(0);
    ui->tableWidget_month_zonePrices->setColumnCount(1); // Ensure single column
    ui->stackedWidget_2->setCurrentWidget(ui->page_4); // Monthly form
}

void QtWidgetsApplication3::on_spinBox_month_zones_valueChanged(int value)
{
    ui->tableWidget_month_zonePrices->setRowCount(value);
    ui->tableWidget_month_zonePrices->setColumnCount(1);
    for (int i = 0; i < value; ++i) {
        ui->tableWidget_month_zonePrices->setItem(i, 0, new QTableWidgetItem());
    }
}

void QtWidgetsApplication3::on_dialogButtonBox_month_accepted()
{
    auto& m = arr_subscription[num_of_subsc].month_sub[month_index];
    m.duration = ui->spinBox_month_duration->value();
    m.no_of_trips = ui->spinBox_month_trips->value();
    m.zone_num = ui->spinBox_month_zones->value();

    for (int i = 0; i < m.zone_num; ++i) {
        QTableWidgetItem* item = ui->tableWidget_month_zonePrices->item(i, 0);
        m.zonesPrice[i] = item ? item->text().toInt() : 0;
    }

    month_index++;
    ui->groupBox_monthly->hide();
    ui->stackedWidget_2->setCurrentWidget(ui->page); // Return to fixed page
}

void QtWidgetsApplication3::on_dialogButtonBox_month_rejected()
{
    ui->groupBox_monthly->hide();
    ui->stackedWidget_2->setCurrentWidget(ui->page);
}

void QtWidgetsApplication3::on_pushButton_13_clicked() // Add yearly button
{
    ui->groupBox_yearly->show();
    ui->spinBox_year_zones->setValue(0);
    ui->tableWidget_year_zonePrices->setRowCount(0);
    ui->tableWidget_year_zonePrices->setColumnCount(1); // Ensure single column
    ui->stackedWidget_2->setCurrentWidget(ui->page_3); // Yearly form
}

void QtWidgetsApplication3::on_spinBox_year_zones_valueChanged(int value)
{
    ui->tableWidget_year_zonePrices->setRowCount(value);
    ui->tableWidget_year_zonePrices->setColumnCount(1);
    for (int i = 0; i < value; ++i) {
        ui->tableWidget_year_zonePrices->setItem(i, 0, new QTableWidgetItem());
    }
}

void QtWidgetsApplication3::on_dialogButtonBox_year_accepted()
{
    auto& y = arr_subscription[num_of_subsc].year_sub[year_index];
    y.duration = ui->spinBox_year_duration->value();
    y.no_of_trips = ui->spinBox_year_trips->value();
    y.zone_num = ui->spinBox_year_zones->value();

    for (int i = 0; i < y.zone_num; ++i) {
        QTableWidgetItem* item = ui->tableWidget_year_zonePrices->item(i, 0);
        y.zonesPrice[i] = item ? item->text().toInt() : 0;
    }

    year_index++;
    ui->groupBox_yearly->hide();
    ui->stackedWidget_2->setCurrentWidget(ui->page); // Back to fixed page
}

void QtWidgetsApplication3::on_dialogButtonBox_year_rejected()
{
    ui->groupBox_yearly->hide();
    ui->stackedWidget_2->setCurrentWidget(ui->page);
}

void QtWidgetsApplication3::on_pushButton_submit_clicked()
{
    int i = num_of_subsc;
    arr_subscription[i].plan_name = ui->lineEdit_7->text().trimmed().toStdString();

    if (arr_subscription[i].plan_name.empty()) {
        QMessageBox::warning(this, "Missing", "Please enter a plan name.");
        return;
    }

    if (ui->radioButton_fixed->isChecked()) {
        arr_subscription[i].fixed = 'y';
        arr_subscription[i].month_count = month_index;
        arr_subscription[i].year_count = year_index;
    }
    else if (ui->radioButton_wallet->isChecked()) {
        arr_subscription[i].fixed = 'n';
        arr_subscription[i].wallet_sub.card_balance = ui->spinBox_cardBalance->value();
        arr_subscription[i].wallet_sub.fund_multiple = ui->spinBox->value();

        int rowCount = ui->tableWidget_walletZones->rowCount();
        arr_subscription[i].wallet_sub.zone_num = rowCount;
        ui->tableWidget_walletZones->setColumnCount(1);
        for (int j = 0; j < rowCount; ++j) {
            if (!ui->tableWidget_walletZones->item(j, 0)) {
                ui->tableWidget_walletZones->setItem(j, 0, new QTableWidgetItem());
            }
            QTableWidgetItem* item = ui->tableWidget_walletZones->item(j, 0);
            arr_subscription[i].wallet_sub.zonesPrice[j] = item ? item->text().toInt() : 0;
        }
    }

    arr_subscription[i].notes = ui->textEdit->toPlainText().toStdString();
    num_of_subsc++;
    save_subsc_data();

    QMessageBox::information(this, "Saved", "Subscription added successfully.");

    // Reset form
    ui->lineEdit_7->clear();
    ui->textEdit->clear();
    month_index = 0;
    year_index = 0;

    ui->radioButton_fixed->setAutoExclusive(false);
    ui->radioButton_fixed->setChecked(false);
    ui->radioButton_fixed->setAutoExclusive(true);
    ui->radioButton_wallet->setAutoExclusive(false);
    ui->radioButton_wallet->setChecked(false);
    ui->radioButton_wallet->setAutoExclusive(true);

    ui->stackedWidget_2->setCurrentIndex(0); // back to empty page
    ui->groupBox_fixed->hide(); // hide again after adding
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
                //        renew_time(arr_users[indexofuser].sub);
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
void QtWidgetsApplication3::on_pushButton_16_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->ride_settings);
}

void QtWidgetsApplication3::on_pushButton_22_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->allRideHistory);
    //aly ekteb hena el function 
}
void QtWidgetsApplication3::on_pushButton_14_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->subscription_settings);
}



// COMPLETE FIXED & WALLET PLAN EDITING CODE BASED ON YOUR STRUCT
//extern plan arr_subscription[20];
//int chosenSubscriptionIndex = -1;

void QtWidgetsApplication3::on_editsub_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->edit_subscription);
    ui->listWidget_subscriptions_2->clear();
    ui->stackedWidget_editType->setCurrentWidget(ui->page_edit_fixed);

    load_subsc_data();

    for (int i = 0; i < num_of_subsc; ++i) {
        ui->listWidget_subscriptions_2->addItem(QString::fromStdString(arr_subscription[i].plan_name));
    }
}

void QtWidgetsApplication3::on_pushButton_select_sub_clicked() {
    int index = ui->listWidget_subscriptions_2->currentRow();
    if (index < 0 || index >= num_of_subsc) return;

    chosenSubscriptionIndex = index;
    plan& s = arr_subscription[index];

    if (s.fixed == 'n') { // wallet plan
        ui->stackedWidget_editType->setCurrentWidget(ui->page_edit_wallet);
        ui->lineEdit_planName_wallet->setText(QString::fromStdString(s.plan_name));
        ui->spinBox_cardBalance_2->setValue(s.wallet_sub.card_balance);
        ui->spinBox_fundMultiple->setValue(s.wallet_sub.fund_multiple);
        ui->spinBox_zoneNum->setValue(s.wallet_sub.zone_num);
        ui->textEdit_notes_wallet->setText(QString::fromStdString(s.notes));
        ui->label_currentEditedPlanWallet->setText("Editing: " + QString::fromStdString(s.plan_name));

        // clear old layout
        QLayout* oldLayout = ui->zonePricesWidget->layout();
        if (oldLayout) {
            QLayoutItem* child;
            while ((child = oldLayout->takeAt(0)) != nullptr) delete child->widget();
            delete oldLayout;
        }

        QVBoxLayout* layout = new QVBoxLayout();
        for (int i = 0; i < s.wallet_sub.zone_num; ++i) {
            QHBoxLayout* row = new QHBoxLayout;
            QLabel* label = new QLabel(QString("Zone %1 Price:").arg(i + 1));
            QSpinBox* spin = new QSpinBox;
            spin->setMinimum(0);
            spin->setMaximum(999);
            spin->setValue(s.wallet_sub.zonesPrice[i]);
            spin->setObjectName("wallet_zone_" + QString::number(i));
            row->addWidget(label);
            row->addWidget(spin);
            layout->addLayout(row);
        }
        ui->zonePricesWidget->setLayout(layout);
    }
    else { // fixed plan
        ui->stackedWidget_editType->setCurrentWidget(ui->page_edit_fixed);
        ui->lineEdit_planName_fixed->setText(QString::fromStdString(s.plan_name));
        ui->textEdit_notes_fixed->setText(QString::fromStdString(s.notes));
        ui->label_currentEditedPlanFixed->setText("Editing: " + QString::fromStdString(s.plan_name));
    }
}

void QtWidgetsApplication3::on_pushButton_save_changes_clicked() {
    if (chosenSubscriptionIndex < 0) return;
    plan& s = arr_subscription[chosenSubscriptionIndex];
    if (s.fixed != 'y') return;

    s.plan_name = ui->lineEdit_planName_fixed->text().toStdString();
    s.notes = ui->textEdit_notes_fixed->toPlainText().toStdString();

    QMessageBox::information(this, "Saved", "Fixed plan changes saved.");
    save_subsc_data();
}

void QtWidgetsApplication3::on_pushButton_save_changes_2_clicked() {
    if (chosenSubscriptionIndex < 0) return;
    plan& s = arr_subscription[chosenSubscriptionIndex];
    if (s.fixed != 'n') return;

    s.plan_name = ui->lineEdit_planName_wallet->text().toStdString();
    s.wallet_sub.card_balance = ui->spinBox_cardBalance_2->value();
    s.wallet_sub.fund_multiple = ui->spinBox_fundMultiple->value();
    s.wallet_sub.zone_num = ui->spinBox_zoneNum->value();
    s.notes = ui->textEdit_notes_wallet->toPlainText().toStdString();

    for (int i = 0; i < s.wallet_sub.zone_num; ++i) {
        QSpinBox* spin = ui->zonePricesWidget->findChild<QSpinBox*>("wallet_zone_" + QString::number(i));
        if (spin) s.wallet_sub.zonesPrice[i] = spin->value();
    }

    QMessageBox::information(this, "Saved", "Wallet plan changes saved.");
    save_subsc_data();
}

void QtWidgetsApplication3::on_pushButton_12_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->page_edit_monthly);
    ui->label_currentEditedPlanMonthly->setText(ui->label_currentEditedPlanFixed->text());

    plan& s = arr_subscription[chosenSubscriptionIndex];
    ui->tableWidget_monthly->clearContents();
    ui->tableWidget_monthly->setRowCount(s.month_count);
    ui->tableWidget_monthly->setColumnCount(3);
    QStringList headers;
    headers << "Duration" << "Trips" << "Zones";
    ui->tableWidget_monthly->setHorizontalHeaderLabels(headers);

    for (int i = 0; i < s.month_count; ++i) {
        ui->tableWidget_monthly->setItem(i, 0, new QTableWidgetItem(QString::number(s.month_sub[i].duration)));
        ui->tableWidget_monthly->setItem(i, 1, new QTableWidgetItem(QString::number(s.month_sub[i].no_of_trips)));
        ui->tableWidget_monthly->setItem(i, 2, new QTableWidgetItem(QString::number(s.month_sub[i].zone_num)));
    }
}

void QtWidgetsApplication3::on_pushButton_editMonthSave_clicked() {
    int row = ui->tableWidget_monthly->currentRow();
    if (row < 0) return;

    plan& s = arr_subscription[chosenSubscriptionIndex];
    s.month_sub[row].duration = ui->spinBox_monthDuration->value();
    s.month_sub[row].no_of_trips = ui->spinBox_monthTrips->value();
    s.month_sub[row].zone_num = ui->spinBox_monthZones->value();

    for (int i = 0; i < s.month_sub[row].zone_num; ++i) {
        QSpinBox* spin = ui->zonePricesWidgetMonth->findChild<QSpinBox*>("monthly_zone_" + QString::number(i));
        if (spin) s.month_sub[row].zonesPrice[i] = spin->value();
    }

    save_subsc_data();
    QMessageBox::information(this, "Saved", "Monthly plan edited.");
    on_pushButton_12_clicked();
}

void QtWidgetsApplication3::on_pushButton_23_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->page_edit_yearly);
    ui->label_currentEditedPlanYearly->setText(ui->label_currentEditedPlanFixed->text());

    plan& s = arr_subscription[chosenSubscriptionIndex];
    ui->tableWidget_yearly->clearContents();
    ui->tableWidget_yearly->setRowCount(s.year_count);
    ui->tableWidget_yearly->setColumnCount(3);
    QStringList headers;
    headers << "Duration" << "Trips" << "Zones";
    ui->tableWidget_yearly->setHorizontalHeaderLabels(headers);

    for (int i = 0; i < s.year_count; ++i) {
        ui->tableWidget_yearly->setItem(i, 0, new QTableWidgetItem(QString::number(s.year_sub[i].duration)));
        ui->tableWidget_yearly->setItem(i, 1, new QTableWidgetItem(QString::number(s.year_sub[i].no_of_trips)));
        ui->tableWidget_yearly->setItem(i, 2, new QTableWidgetItem(QString::number(s.year_sub[i].zone_num)));
    }
}

void QtWidgetsApplication3::on_pushButton_editYearSave_clicked() {
    int row = ui->tableWidget_yearly->currentRow();
    if (row < 0) return;

    plan& s = arr_subscription[chosenSubscriptionIndex];
    s.year_sub[row].duration = ui->spinBox_yearDuration->value();
    s.year_sub[row].no_of_trips = ui->spinBox_yearTrips->value();
    s.year_sub[row].zone_num = ui->spinBox_yearZones->value();

    for (int i = 0; i < s.year_sub[row].zone_num; ++i) {
        QSpinBox* spin = ui->zonePricesWidgetYear->findChild<QSpinBox*>("yearly_zone_" + QString::number(i));
        if (spin) s.year_sub[row].zonesPrice[i] = spin->value();
    }

    save_subsc_data();
    QMessageBox::information(this, "Saved", "Yearly plan edited.");
    on_pushButton_23_clicked();
}
void QtWidgetsApplication3::on_pushButton_cancel_changes_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->edit_subscription);
}

void QtWidgetsApplication3::on_pushButton_cancel_changes_2_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->edit_subscription);
}

void QtWidgetsApplication3::on_pushButton_backFromFixed_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->edit_subscription);
}

void QtWidgetsApplication3::on_pushButton_backFromWallet_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->edit_subscription);
}

void QtWidgetsApplication3::on_pushButton_addYear_clicked() {
    ui->stackedWidget_2->setCurrentWidget(ui->page_3);
    ui->spinBox_year_zones->setValue(0);
    ui->tableWidget_year_zonePrices->setRowCount(0);
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
void QtWidgetsApplication3::on_back9_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->subscription_settings);
}
void QtWidgetsApplication3::on_back10_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->subscription_settings);
}
void QtWidgetsApplication3::on_back11_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->subscription_settings);
}
void QtWidgetsApplication3::on_back12_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->admin);
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



