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
connect(ui->tableWidget_monthly, &QTableWidget::cellClicked, this, &QtWidgetsApplication3::handleMonthlyCellClick);
connect(ui->tableWidget_yearly, &QTableWidget::cellClicked, this, &QtWidgetsApplication3::handleYearlyCellClick);



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


// Full working edit and add subscription functionality

int selectedSubscriptionRow = -1;

void QtWidgetsApplication3::on_tableWidget_subscriptions_cellClicked(int row, int) {
    selectedSubscriptionRow = row;
}

//void QtWidgetsApplication3::refreshSubscriptionTable() {
//    ui->tableWidget_subscriptions->clearContents();
//    ui->tableWidget_subscriptions->setRowCount(num_of_subsc);
//    for (int i = 0; i < num_of_subsc; ++i) {
//        QString name = QString::fromStdString(arr_subscription[i].plan_name);
//        QString type = (arr_subscription[i].fixed == 'y') ? "Fixed" : "Wallet";
//
//        if (arr_subscription[i].month_count > 0)
//            type = "Monthly";
//        else if (arr_subscription[i].year_count > 0)
//            type = "Yearly";
//
//        ui->tableWidget_subscriptions->setItem(i, 0, new QTableWidgetItem(name));
//        ui->tableWidget_subscriptions->setItem(i, 1, new QTableWidgetItem("...")); // Placeholder
//        ui->tableWidget_subscriptions->setItem(i, 2, new QTableWidgetItem(type));
//    }
//}
// Full working edit functionality for all plans: Fixed, Wallet, Monthly, Yearly

void QtWidgetsApplication3::refreshSubscriptionTable() {
    ui->tableWidget_subscriptions->setRowCount(0);
    ui->tableWidget_subscriptions->setColumnCount(7);

    QStringList headers;
    headers << "Plan Name" << "Type" << "Sub-Plan" << "Duration/Trips" << "Zones" << "Zone Prices" << "Notes";
    ui->tableWidget_subscriptions->setHorizontalHeaderLabels(headers);

    int row = 0;
    for (int i = 0; i < num_of_subsc; ++i) {
        const plan& p = arr_subscription[i];
        QString planType = (p.fixed == 'y') ? "Fixed" : "Wallet";

        // Wallet plans
        if (p.fixed == 'n') {
            ui->tableWidget_subscriptions->insertRow(row);
            ui->tableWidget_subscriptions->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(p.plan_name)));
            ui->tableWidget_subscriptions->setItem(row, 1, new QTableWidgetItem("Wallet"));
            ui->tableWidget_subscriptions->setItem(row, 2, new QTableWidgetItem("Wallet"));
            ui->tableWidget_subscriptions->setItem(row, 3, new QTableWidgetItem("N/A"));
            ui->tableWidget_subscriptions->setItem(row, 4, new QTableWidgetItem(QString::number(p.wallet_sub.zone_num)));

            QString pricePreview;
            for (int z = 0; z < p.wallet_sub.zone_num; ++z) {
                if (z > 0) pricePreview += " ";
                pricePreview += QString::number(p.wallet_sub.zonesPrice[z]);
            }
            QString shortPrice = pricePreview.left(30);
            if (pricePreview.length() > 30) shortPrice += "...";

            QTableWidgetItem* item = new QTableWidgetItem(shortPrice);
            item->setToolTip(pricePreview);
            ui->tableWidget_subscriptions->setItem(row, 5, item);
            ui->tableWidget_subscriptions->setItem(row, 6, new QTableWidgetItem(QString::fromStdString(p.notes)));
            row++;
            continue; // Skip fixed plan processing for wallet plans
        }

        // Fixed plans (Monthly and Yearly)
        // Monthly subscriptions
        for (int m = 0; m < p.month_count; ++m) {
            // Check if this monthly subscription is already displayed
            bool duplicate = false;
            for (int r = 0; r < row; ++r) {
                if (ui->tableWidget_subscriptions->item(r, 0)->text() == QString::fromStdString(p.plan_name) &&
                    ui->tableWidget_subscriptions->item(r, 2)->text() == "Monthly" &&
                    ui->tableWidget_subscriptions->item(r, 3)->text() ==
                    (QString::number(p.month_sub[m].duration) + " months / " + QString::number(p.month_sub[m].no_of_trips) + " trips")) {
                    duplicate = true;
                    break;
                }
            }

            if (!duplicate) {
                ui->tableWidget_subscriptions->insertRow(row);
                ui->tableWidget_subscriptions->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(p.plan_name)));
                ui->tableWidget_subscriptions->setItem(row, 1, new QTableWidgetItem(planType));
                ui->tableWidget_subscriptions->setItem(row, 2, new QTableWidgetItem("Monthly"));

                QString durTrips = QString::number(p.month_sub[m].duration) + " months / " +
                    QString::number(p.month_sub[m].no_of_trips) + " trips";
                ui->tableWidget_subscriptions->setItem(row, 3, new QTableWidgetItem(durTrips));
                ui->tableWidget_subscriptions->setItem(row, 4, new QTableWidgetItem(QString::number(p.month_sub[m].zone_num)));

                QString pricePreview;
                for (int z = 0; z < p.month_sub[m].zone_num; ++z) {
                    if (z > 0) pricePreview += " ";
                    pricePreview += QString::number(p.month_sub[m].zonesPrice[z]);
                }
                QString shortPrice = pricePreview.left(30);
                if (pricePreview.length() > 30) shortPrice += "...";

                QTableWidgetItem* item = new QTableWidgetItem(shortPrice);
                item->setToolTip(pricePreview);
                ui->tableWidget_subscriptions->setItem(row, 5, item);
                ui->tableWidget_subscriptions->setItem(row, 6, new QTableWidgetItem(QString::fromStdString(p.notes)));
                row++;
            }
        }

        // Yearly subscriptions
        for (int y = 0; y < p.year_count; ++y) {
            // Check if this yearly subscription is already displayed
            bool duplicate = false;
            for (int r = 0; r < row; ++r) {
                if (ui->tableWidget_subscriptions->item(r, 0)->text() == QString::fromStdString(p.plan_name) &&
                    ui->tableWidget_subscriptions->item(r, 2)->text() == "Yearly" &&
                    ui->tableWidget_subscriptions->item(r, 3)->text() ==
                    (QString::number(p.year_sub[y].duration) + " years / " + QString::number(p.year_sub[y].no_of_trips) + " trips")) {
                    duplicate = true;
                    break;
                }
            }

            if (!duplicate) {
                ui->tableWidget_subscriptions->insertRow(row);
                ui->tableWidget_subscriptions->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(p.plan_name)));
                ui->tableWidget_subscriptions->setItem(row, 1, new QTableWidgetItem(planType));
                ui->tableWidget_subscriptions->setItem(row, 2, new QTableWidgetItem("Yearly"));

                QString durTrips = QString::number(p.year_sub[y].duration) + " years / " +
                    QString::number(p.year_sub[y].no_of_trips) + " trips";
                ui->tableWidget_subscriptions->setItem(row, 3, new QTableWidgetItem(durTrips));
                ui->tableWidget_subscriptions->setItem(row, 4, new QTableWidgetItem(QString::number(p.year_sub[y].zone_num)));

                QString pricePreview;
                for (int z = 0; z < p.year_sub[y].zone_num; ++z) {
                    if (z > 0) pricePreview += " ";
                    pricePreview += QString::number(p.year_sub[y].zonesPrice[z]);
                }
                QString shortPrice = pricePreview.left(30);
                if (pricePreview.length() > 30) shortPrice += "...";

                QTableWidgetItem* item = new QTableWidgetItem(shortPrice);
                item->setToolTip(pricePreview);
                ui->tableWidget_subscriptions->setItem(row, 5, item);
                ui->tableWidget_subscriptions->setItem(row, 6, new QTableWidgetItem(QString::fromStdString(p.notes)));
                row++;
            }
        }
    }
}
void QtWidgetsApplication3::on_addsub_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->add_sub);
    ui->stackedWidget_2->setCurrentIndex(0);

    ui->groupBox_monthly->hide();
    ui->groupBox_yearly->hide();
    ui->groupBox_fixed->hide();

    ui->spinBox_month_duration->setRange(1, 1000);
    ui->spinBox_month_trips->setRange(1, 1000);
    ui->spinBox_month_zones->setRange(0, 30);

    ui->spinBox_year_duration->setRange(1, 1000);
    ui->spinBox_year_trips->setRange(1, 1000);
    ui->spinBox_year_zones->setRange(0, 30);

    ui->spinBox_cardBalance->setRange(0, 100000);
    ui->spinBox->setRange(1, 1000);
    ui->spinBox_wallet_zones->setRange(0, 30);

    month_index = 0;
    year_index = 0;

    ui->tableWidget_walletZones->setRowCount(0);
    ui->tableWidget_walletZones->setColumnCount(1);
    ui->tableWidget_walletZones->clearContents();
    ui->tableWidget_walletZones->horizontalHeader()->hide();
}

void QtWidgetsApplication3::on_spinBox_wallet_zones_valueChanged(int value)
{
    ui->tableWidget_walletZones->clearContents();
    ui->tableWidget_walletZones->setRowCount(value);
    ui->tableWidget_walletZones->setColumnCount(1);
    ui->tableWidget_walletZones->horizontalHeader()->hide();
    for (int i = 0; i < value; ++i) {
        QTableWidgetItem* item = new QTableWidgetItem("");
        ui->tableWidget_walletZones->setItem(i, 0, item);
    }
}

void QtWidgetsApplication3::on_radioButton_fixed_clicked()
{
    ui->stackedWidget_2->setCurrentWidget(ui->page);
    ui->groupBox_fixed->show();
}

void QtWidgetsApplication3::on_radioButton_wallet_clicked()
{
    ui->stackedWidget_2->setCurrentWidget(ui->page_2);
    ui->groupBox_fixed->hide();
}

void QtWidgetsApplication3::on_pushButton_addMonth_clicked()
{
    ui->groupBox_monthly->show();
    ui->spinBox_month_zones->setValue(0);
    ui->tableWidget_month_zonePrices->clearContents();
    ui->tableWidget_month_zonePrices->setRowCount(0);
    ui->tableWidget_month_zonePrices->setColumnCount(1);
    ui->tableWidget_month_zonePrices->horizontalHeader()->hide();
    ui->stackedWidget_2->setCurrentWidget(ui->page_4);
}

void QtWidgetsApplication3::on_spinBox_month_zones_valueChanged(int value)
{
    ui->tableWidget_month_zonePrices->clearContents();
    ui->tableWidget_month_zonePrices->setRowCount(value);
    ui->tableWidget_month_zonePrices->setColumnCount(1);
    ui->tableWidget_month_zonePrices->horizontalHeader()->hide();
    for (int i = 0; i < value; ++i) {
        QTableWidgetItem* item = new QTableWidgetItem("");
        ui->tableWidget_month_zonePrices->setItem(i, 0, item);
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
    ui->stackedWidget_2->setCurrentWidget(ui->page);
}

void QtWidgetsApplication3::on_dialogButtonBox_month_rejected()
{
    ui->groupBox_monthly->hide();
    ui->stackedWidget_2->setCurrentWidget(ui->page);
}

void QtWidgetsApplication3::on_pushButton_13_clicked()
{
    ui->groupBox_yearly->show();
    ui->spinBox_year_zones->setValue(0);
    ui->tableWidget_year_zonePrices->clearContents();
    ui->tableWidget_year_zonePrices->setRowCount(0);
    ui->tableWidget_year_zonePrices->setColumnCount(1);
    ui->tableWidget_year_zonePrices->horizontalHeader()->hide();
    ui->stackedWidget_2->setCurrentWidget(ui->page_3);
}

void QtWidgetsApplication3::on_spinBox_year_zones_valueChanged(int value)
{
    ui->tableWidget_year_zonePrices->clearContents();
    ui->tableWidget_year_zonePrices->setRowCount(value);
    ui->tableWidget_year_zonePrices->setColumnCount(1);
    ui->tableWidget_year_zonePrices->horizontalHeader()->hide();
    for (int i = 0; i < value; ++i) {
        QTableWidgetItem* item = new QTableWidgetItem("");
        ui->tableWidget_year_zonePrices->setItem(i, 0, item);
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
    ui->stackedWidget_2->setCurrentWidget(ui->page);
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
                ui->tableWidget_walletZones->setItem(j, 0, new QTableWidgetItem(""));
            }
            QTableWidgetItem* item = ui->tableWidget_walletZones->item(j, 0);
            arr_subscription[i].wallet_sub.zonesPrice[j] = item ? item->text().toInt() : 0;
        }
    }

    arr_subscription[i].notes = ui->textEdit->toPlainText().toStdString();
    num_of_subsc++;
    save_subsc_data();

    QMessageBox::information(this, "Saved", "Subscription added successfully.");

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

    ui->stackedWidget_2->setCurrentIndex(0);
    ui->groupBox_fixed->hide();
    ui->tableWidget_subscriptions->clear();
    ui->stackedWidget->setCurrentWidget(ui->subscription_settings);
    refreshSubscriptionTable();
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
    ui->tableWidget_subscriptions->setRowCount(0);
    ui->tableWidget_subscriptions->setColumnCount(7);

    QStringList headers;
    headers << "Plan Name" << "Type" << "Sub-Plan" << "Duration/Trips" << "Zones" << "Zone Prices" << "Notes";
    ui->tableWidget_subscriptions->setHorizontalHeaderLabels(headers);

    int row = 0;

    for (int i = 0; i < num_of_subsc; ++i) {
        const plan& p = arr_subscription[i];

        QString planType = (p.fixed == 'y') ? "Fixed" : "Wallet";

        // Wallet plan
        if (planType == "Wallet") {
            ui->tableWidget_subscriptions->insertRow(row);

            ui->tableWidget_subscriptions->setItem(row, 0, new QTableWidgetItem(QString::fromUtf8(p.plan_name)));
            ui->tableWidget_subscriptions->setItem(row, 1, new QTableWidgetItem(planType));
            ui->tableWidget_subscriptions->setItem(row, 2, new QTableWidgetItem("Wallet"));
            ui->tableWidget_subscriptions->setItem(row, 3, new QTableWidgetItem("N/A"));
            ui->tableWidget_subscriptions->setItem(row, 4, new QTableWidgetItem(QString::number(p.wallet_sub.zone_num)));

            QString pricePreview;
            for (int z = 0; z < p.wallet_sub.zone_num; ++z) {
                pricePreview += QString::number(p.wallet_sub.zonesPrice[z]) + " ";
            }
            QString shortPrice = pricePreview.left(30);
            if (pricePreview.length() > 30)
                shortPrice += "...";

            QTableWidgetItem* item = new QTableWidgetItem(shortPrice);
            item->setToolTip(pricePreview);
            ui->tableWidget_subscriptions->setItem(row, 5, item);

            ui->tableWidget_subscriptions->setItem(row, 6, new QTableWidgetItem(QString::fromUtf8(p.notes)));

            row++;
        }

        // Monthly plans
        for (int m = 0; m < p.month_count; ++m) {
            ui->tableWidget_subscriptions->insertRow(row);

            ui->tableWidget_subscriptions->setItem(row, 0, new QTableWidgetItem(QString::fromUtf8(p.plan_name)));
            ui->tableWidget_subscriptions->setItem(row, 1, new QTableWidgetItem(planType));
            ui->tableWidget_subscriptions->setItem(row, 2, new QTableWidgetItem("Monthly"));

            QString durTrips = QString::number(p.month_sub[m].duration) + " months / " + QString::number(p.month_sub[m].no_of_trips) + " trips";
            ui->tableWidget_subscriptions->setItem(row, 3, new QTableWidgetItem(durTrips));
            ui->tableWidget_subscriptions->setItem(row, 4, new QTableWidgetItem(QString::number(p.month_sub[m].zone_num)));

            QString pricePreview;
            for (int z = 0; z < p.month_sub[m].zone_num; ++z) {
                pricePreview += QString::number(p.month_sub[m].zonesPrice[z]) + " ";
            }
            QString shortPrice = pricePreview.left(30);
            if (pricePreview.length() > 30)
                shortPrice += "...";

            QTableWidgetItem* item = new QTableWidgetItem(shortPrice);
            item->setToolTip(pricePreview);
            ui->tableWidget_subscriptions->setItem(row, 5, item);

            ui->tableWidget_subscriptions->setItem(row, 6, new QTableWidgetItem(QString::fromUtf8(p.notes)));

            row++;
        }

        // Yearly plans
        for (int y = 0; y < p.year_count; ++y) {
            ui->tableWidget_subscriptions->insertRow(row);

            ui->tableWidget_subscriptions->setItem(row, 0, new QTableWidgetItem(QString::fromUtf8(p.plan_name)));
            ui->tableWidget_subscriptions->setItem(row, 1, new QTableWidgetItem(planType));
            ui->tableWidget_subscriptions->setItem(row, 2, new QTableWidgetItem("Yearly"));

            QString durTrips = QString::number(p.year_sub[y].duration) + " years / " + QString::number(p.year_sub[y].no_of_trips) + " trips";
            ui->tableWidget_subscriptions->setItem(row, 3, new QTableWidgetItem(durTrips));
            ui->tableWidget_subscriptions->setItem(row, 4, new QTableWidgetItem(QString::number(p.year_sub[y].zone_num)));

            QString pricePreview;
            for (int z = 0; z < p.year_sub[y].zone_num; ++z) {
                pricePreview += QString::number(p.year_sub[y].zonesPrice[z]) + " ";
            }
            QString shortPrice = pricePreview.left(30);
            if (pricePreview.length() > 30)
                shortPrice += "...";

            QTableWidgetItem* item = new QTableWidgetItem(shortPrice);
            item->setToolTip(pricePreview);
            ui->tableWidget_subscriptions->setItem(row, 5, item);

            ui->tableWidget_subscriptions->setItem(row, 6, new QTableWidgetItem(QString::fromUtf8(p.notes)));

            row++;
        }
    }

}



// =========================
// QtWidgetsApplication3.cpp
// FULL FINAL VERSION - Fully Working
// =========================

// Full working edit functionality for all plans: Fixed, Wallet, Monthly, Yearly

// Full working edit functionality for all plans: Fixed, Wallet, Monthly, Yearly
// Full working edit functionality for all plans: Fixed, Wallet, Monthly, Yearly


void QtWidgetsApplication3::on_editsub_clicked() {
    if (selectedSubscriptionRow < 0) return;

    QString planName = ui->tableWidget_subscriptions->item(selectedSubscriptionRow, 0)->text();
    QString subType = ui->tableWidget_subscriptions->item(selectedSubscriptionRow, 2)->text(); // Wallet/Monthly/Yearly/Fixed

    int index = -1;
    for (int i = 0; i < num_of_subsc; ++i) {
        if (QString::fromUtf8(arr_subscription[i].plan_name) == planName) {
            index = i;
            break;
        }
    }
    if (index == -1) return;

    chosenSubscriptionIndex = index;
    plan& s = arr_subscription[index];

    ui->stackedWidget->setCurrentWidget(ui->edit_subscription);
    ui->stackedWidget_editType->show();

    if (subType == "Wallet") {
        ui->stackedWidget_editType->setCurrentWidget(ui->page_edit_wallet);
        ui->lineEdit_planName_wallet->setText(QString::fromStdString(s.plan_name));
        ui->spinBox_cardBalance_2->setValue(s.wallet_sub.card_balance);
        ui->spinBox_fundMultiple->setValue(s.wallet_sub.fund_multiple);
        ui->spinBox_zoneNum->setValue(s.wallet_sub.zone_num);
        ui->textEdit_notes_wallet->setText(QString::fromStdString(s.notes));
        ui->label_currentEditedPlanWallet->setText("Editing: " + QString::fromStdString(s.plan_name));
        on_spinBox_zoneNum_valueChanged(s.wallet_sub.zone_num);

        for (int i = 0; i < s.wallet_sub.zone_num; ++i) {
            QSpinBox* spin = ui->zonePricesWidget->findChild<QSpinBox*>("wallet_zone_" + QString::number(i));
            if (spin) spin->setValue(s.wallet_sub.zonesPrice[i]);
        }
    }
    else if (subType == "Monthly") {
        ui->stackedWidget_editType->setCurrentWidget(ui->page_edit_monthly);
        ui->label_currentEditedPlanMonthly->setText("Editing: " + QString::fromStdString(s.plan_name));

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

        // Select first row by default if any
        if (s.month_count > 0) {
            ui->tableWidget_monthly->selectRow(0);
            ui->spinBox_monthDuration->setValue(s.month_sub[0].duration);
            ui->spinBox_monthTrips->setValue(s.month_sub[0].no_of_trips);
            ui->spinBox_monthZones->setValue(s.month_sub[0].zone_num);
            on_spinBox_monthZones_valueChanged(s.month_sub[0].zone_num);
            for (int z = 0; z < s.month_sub[0].zone_num; ++z) {
                QSpinBox* spin = ui->zonePricesWidgetMonth->findChild<QSpinBox*>("monthly_zone_" + QString::number(z));
                if (spin) spin->setValue(s.month_sub[0].zonesPrice[z]);
            }
        }
    }
    else if (subType == "Yearly") {
        ui->stackedWidget_editType->setCurrentWidget(ui->page_edit_yearly);
        ui->label_currentEditedPlanYearly->setText("Editing: " + QString::fromStdString(s.plan_name));

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

        if (s.year_count > 0) {
            ui->tableWidget_yearly->selectRow(0);
            ui->spinBox_yearDuration->setValue(s.year_sub[0].duration);
            ui->spinBox_yearTrips->setValue(s.year_sub[0].no_of_trips);
            ui->spinBox_yearZones->setValue(s.year_sub[0].zone_num);
            on_spinBox_yearZones_valueChanged(s.year_sub[0].zone_num);
            for (int z = 0; z < s.year_sub[0].zone_num; ++z) {
                QSpinBox* spin = ui->zonePricesWidgetYear->findChild<QSpinBox*>("yearly_zone_" + QString::number(z));
                if (spin) spin->setValue(s.year_sub[0].zonesPrice[z]);
            }
        }
    }
    else if (subType == "Fixed") {
        ui->stackedWidget_editType->setCurrentWidget(ui->page_edit_fixed);
        ui->lineEdit_planName_fixed->setText(QString::fromStdString(s.plan_name));
        ui->textEdit_notes_fixed->setText(QString::fromStdString(s.notes));
        ui->label_currentEditedPlanFixed->setText("Editing: " + QString::fromStdString(s.plan_name));
    }
}


void QtWidgetsApplication3::handleMonthlyCellClick(int r, int) {
    if (chosenSubscriptionIndex < 0) return;
    plan& s = arr_subscription[chosenSubscriptionIndex];
    ui->spinBox_monthDuration->setValue(s.month_sub[r].duration);
    ui->spinBox_monthTrips->setValue(s.month_sub[r].no_of_trips);
    ui->spinBox_monthZones->blockSignals(true);
    ui->spinBox_monthZones->setValue(s.month_sub[r].zone_num);
    ui->spinBox_monthZones->blockSignals(false);
    on_spinBox_monthZones_valueChanged(s.month_sub[r].zone_num);

    for (int z = 0; z < s.month_sub[r].zone_num; ++z) {
        QSpinBox* spin = ui->zonePricesWidgetMonth->findChild<QSpinBox*>("monthly_zone_" + QString::number(z));
        if (spin) spin->setValue(s.month_sub[r].zonesPrice[z]);
    }
}

void QtWidgetsApplication3::handleYearlyCellClick(int r, int) {
    if (chosenSubscriptionIndex < 0) return;
    plan& s = arr_subscription[chosenSubscriptionIndex];
    ui->spinBox_yearDuration->setValue(s.year_sub[r].duration);
    ui->spinBox_yearTrips->setValue(s.year_sub[r].no_of_trips);
    ui->spinBox_yearZones->blockSignals(true);
    ui->spinBox_yearZones->setValue(s.year_sub[r].zone_num);
    ui->spinBox_yearZones->blockSignals(false);
    on_spinBox_yearZones_valueChanged(s.year_sub[r].zone_num);

    for (int z = 0; z < s.year_sub[r].zone_num; ++z) {
        QSpinBox* spin = ui->zonePricesWidgetYear->findChild<QSpinBox*>("yearly_zone_" + QString::number(z));
        if (spin) spin->setValue(s.year_sub[r].zonesPrice[z]);
    }
}

// Add these in your constructor or setup function
// connect(ui->tableWidget_monthly, &QTableWidget::cellClicked, this, &QtWidgetsApplication3::handleMonthlyCellClick);
// connect(ui->tableWidget_yearly, &QTableWidget::cellClicked, this, &QtWidgetsApplication3::handleYearlyCellClick);

// Back buttons...
// Save functions...
// Zone spin count handlers...
// (Remain unchanged from your previous version)

// Back buttons
void QtWidgetsApplication3::on_pushButton_backeditmonthly_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->edit_subscription);
    ui->stackedWidget_editType->hide();
}
void QtWidgetsApplication3::on_pushButton_cancel_changeseditmonthly_clicked() {
    ui->spinBox_monthDuration->setValue(0);
    ui->spinBox_monthTrips->setValue(0);
    ui->spinBox_monthZones->setValue(0);
    on_spinBox_monthZones_valueChanged(0);
}

void QtWidgetsApplication3::on_pushButton_cancel_changesedityearly_clicked() {
    ui->spinBox_yearDuration->setValue(0);
    ui->spinBox_yearTrips->setValue(0);
    ui->spinBox_yearZones->setValue(0);
    on_spinBox_yearZones_valueChanged(0);
}


void QtWidgetsApplication3::on_pushButton_backedityearly_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->edit_subscription);
    ui->stackedWidget_editType->hide();
}

void QtWidgetsApplication3::on_pushButton_cancel_changes_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->edit_subscription);
    ui->stackedWidget_editType->hide();
}
void QtWidgetsApplication3::on_pushButton_cancel_changes_2_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->edit_subscription);
    ui->stackedWidget_editType->hide();
}
void QtWidgetsApplication3::on_pushButton_backFromFixed_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->edit_subscription);
    ui->stackedWidget_editType->hide();
}
void QtWidgetsApplication3::on_pushButton_backFromWallet_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->edit_subscription);
    ui->stackedWidget_editType->hide();
}
void QtWidgetsApplication3::on_pushButton_backFrom_edit_monthly_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->edit_subscription);
    ui->stackedWidget_editType->hide();
}
void QtWidgetsApplication3::on_pushButton_backFrom_edit_yearly_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->edit_subscription);
    ui->stackedWidget_editType->hide();
}

// Save functions
void QtWidgetsApplication3::on_pushButton_save_changes_clicked() {
    if (chosenSubscriptionIndex < 0) return;
    plan& s = arr_subscription[chosenSubscriptionIndex];
    s.plan_name = ui->lineEdit_planName_fixed->text().toStdString();
    s.notes = ui->textEdit_notes_fixed->toPlainText().toStdString();
    QMessageBox::information(this, "Saved", "Fixed plan changes saved.");
    save_subsc_data();
}

void QtWidgetsApplication3::on_pushButton_save_changes_2_clicked() {
    if (chosenSubscriptionIndex < 0) return;
    plan& s = arr_subscription[chosenSubscriptionIndex];
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

void QtWidgetsApplication3::on_pushButton_editMonthSave_clicked() {
    if (chosenSubscriptionIndex < 0) return;
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

    // ✨ Also update name and notes
    s.plan_name = ui->subname_editmonthly->text().toStdString();
    s.notes = ui->textEdit_notes_editmonthly->toPlainText().toStdString();

    save_subsc_data();
    QMessageBox::information(this, "Saved", "Monthly plan edited.");
    on_editsub_clicked();
}

void QtWidgetsApplication3::on_pushButton_editYearSave_clicked() {
    if (chosenSubscriptionIndex < 0) return;
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

    // ✨ Also update name and notes
    s.plan_name = ui->subname_edityearly->text().toStdString();
    s.notes = ui->textEdit_notes_edityearly->toPlainText().toStdString();

    save_subsc_data();
    QMessageBox::information(this, "Saved", "Yearly plan edited.");
    on_editsub_clicked();
}

// Zone spin count handlers
void QtWidgetsApplication3::on_spinBox_zoneNum_valueChanged(int count) {
    QLayout* layout = ui->zonePricesWidget->layout();
    if (!layout) layout = new QVBoxLayout(ui->zonePricesWidget);
    QLayoutItem* child;
    while ((child = layout->takeAt(0)) != nullptr) {
        delete child->widget(); delete child;
    }
    for (int i = 0; i < count; ++i) {
        QSpinBox* box = new QSpinBox();
        box->setObjectName("wallet_zone_" + QString::number(i));
        box->setMaximum(9999);
        layout->addWidget(box);
    }
}

void QtWidgetsApplication3::on_spinBox_monthZones_valueChanged(int value) {
    QLayout* layout = ui->zonePricesWidgetMonth->layout();
    if (!layout) {
        layout = new QVBoxLayout(ui->zonePricesWidgetMonth);
        ui->zonePricesWidgetMonth->setLayout(layout);
    }
    // Clear existing
    QLayoutItem* child;
    while ((child = layout->takeAt(0)) != nullptr) {
        if (child->widget()) delete child->widget();
        delete child;
    }
    for (int i = 0; i < value; ++i) {
        QSpinBox* spin = new QSpinBox;
        spin->setMaximum(9999);
        spin->setObjectName("monthly_zone_" + QString::number(i));
        layout->addWidget(spin);
    }
}

void QtWidgetsApplication3::on_spinBox_yearZones_valueChanged(int value) {
    QLayout* layout = ui->zonePricesWidgetYear->layout();
    if (!layout) {
        layout = new QVBoxLayout(ui->zonePricesWidgetYear);
        ui->zonePricesWidgetYear->setLayout(layout);
    }
    // Clear existing
    QLayoutItem* child;
    while ((child = layout->takeAt(0)) != nullptr) {
        if (child->widget()) delete child->widget();
        delete child;
    }
    for (int i = 0; i < value; ++i) {
        QSpinBox* spin = new QSpinBox;
        spin->setMaximum(9999);
        spin->setObjectName("yearly_zone_" + QString::number(i));
        layout->addWidget(spin);
    }
}
void QtWidgetsApplication3::on_deletesub_clicked()
{
    // Get the selected row from the subscriptions table
    int selectedRow = ui->tableWidget_subscriptions->currentRow();

    if (selectedRow < 0) {
        QMessageBox::warning(this, "No Selection", "Please select a subscription to delete.");
        return;
    }

    // Get the plan name and sub-type from the selected row
    QString planName = ui->tableWidget_subscriptions->item(selectedRow, 0)->text();
    QString subType = ui->tableWidget_subscriptions->item(selectedRow, 2)->text(); // "Wallet", "Monthly", or "Yearly"

    // Find the matching subscription in your array
    int subIndex = -1;
    int subItemIndex = -1; // For monthly/yearly sub-items

    for (int i = 0; i < num_of_subsc; ++i) {
        if (QString::fromStdString(arr_subscription[i].plan_name) == planName) {
            if (subType == "Wallet" && arr_subscription[i].fixed == 'n') {
                subIndex = i;
                break;
            }
            else if (subType == "Monthly") {
                for (int m = 0; m < arr_subscription[i].month_count; m++) {
                    QString durTrips = QString::number(arr_subscription[i].month_sub[m].duration) + " months / " +
                        QString::number(arr_subscription[i].month_sub[m].no_of_trips) + " trips";
                    if (durTrips == ui->tableWidget_subscriptions->item(selectedRow, 3)->text()) {
                        subIndex = i;
                        subItemIndex = m;
                        break;
                    }
                }
                if (subIndex != -1) break;
            }
            else if (subType == "Yearly") {
                for (int y = 0; y < arr_subscription[i].year_count; y++) {
                    QString durTrips = QString::number(arr_subscription[i].year_sub[y].duration) + " years / " +
                        QString::number(arr_subscription[i].year_sub[y].no_of_trips) + " trips";
                    if (durTrips == ui->tableWidget_subscriptions->item(selectedRow, 3)->text()) {
                        subIndex = i;
                        subItemIndex = y;
                        break;
                    }
                }
                if (subIndex != -1) break;
            }
        }
    }

    if (subIndex == -1) {
        QMessageBox::warning(this, "Not Found", "Subscription not found in database.");
        return;
    }

    // Handle deletion based on subscription type
    if (subType == "Wallet") {
        // Shift all subscriptions after this one
        for (int i = subIndex; i < num_of_subsc - 1; ++i) {
            arr_subscription[i] = arr_subscription[i + 1];
        }
        num_of_subsc--;
    }
    else if (subType == "Monthly" && subItemIndex != -1) {
        // Remove the specific monthly subscription
        plan& p = arr_subscription[subIndex];
        for (int i = subItemIndex; i < p.month_count - 1; ++i) {
            p.month_sub[i] = p.month_sub[i + 1];
        }
        p.month_count--;

        // If no more subscriptions of any type, remove the entire plan
        if (p.month_count == 0 && p.year_count == 0) {
            for (int i = subIndex; i < num_of_subsc - 1; ++i) {
                arr_subscription[i] = arr_subscription[i + 1];
            }
            num_of_subsc--;
        }
    }
    else if (subType == "Yearly" && subItemIndex != -1) {
        // Remove the specific yearly subscription
        plan& p = arr_subscription[subIndex];
        for (int i = subItemIndex; i < p.year_count - 1; ++i) {
            p.year_sub[i] = p.year_sub[i + 1];
        }
        p.year_count--;

        // If no more subscriptions of any type, remove the entire plan
        if (p.month_count == 0 && p.year_count == 0) {
            for (int i = subIndex; i < num_of_subsc - 1; ++i) {
                arr_subscription[i] = arr_subscription[i + 1];
            }
            num_of_subsc--;
        }
    }

    // Save changes and refresh the table
    save_subsc_data();
    refreshSubscriptionTable();

    QMessageBox::information(this, "Deleted", "Subscription has been deleted successfully.");
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



