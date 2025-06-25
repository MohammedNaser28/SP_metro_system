//#include"QtWidgetsApplication3.h"
//#include"QtWidgetsApplication3.cpp"
//#include"ui_QtWidgetsApplication3.h"  // Include the generated UI class
//#include"dependence.h"
//#include"global.h"
//#include"structures.h"
//#include"stations.h"
//#include "view users.h"
//#include <QTableWidget>
//
//
//int chosenSubscriptionIndex = -1;
//QtWidgetsApplication3::QtWidgetsApplication3(QWidget* parent)
//    : QMainWindow(parent)
//    , ui(new Ui::MainWindow)  // Correct link to the UI class generated from the .ui file
//{
//    ui->setupUi(this);  // Set up the UI components
//    ui->stackedWidget->setCurrentWidget(ui->welcome2);
//
//}
//
//QtWidgetsApplication3::~QtWidgetsApplication3()
//{
//    delete ui;  // Clean up
//}
//void  choose_sub()
//{
//
//    if (num_of_subsc == 0) {
//        ui->listWidget_subscriptions->addItem("No available subscriptions");
//        return;
//    }
//
//    for (int i = 0; i < num_of_subsc; i++) {
//        QString planName = QString::fromStdString(arr_subscription[i].plan_name);
//        QListWidgetItem* item = new QListWidgetItem(QString::number(i + 1) + " - " + planName);
//        item->setData(Qt::UserRole, i);
//        QtWidgetsApplication3->ui->listWidget_subscriptions->addItem(item);
//    }
//
//    connect(ui->listWidget_subscriptions, &QListWidget::itemClicked, this, [=](QListWidgetItem* item) {
//        int i = item->data(Qt::UserRole).toInt();
//        chosenSubscriptionIndex = i;
//
//        QString details;
//        details += "📦 Plan Name: " + QString::fromStdString(arr_subscription[i].plan_name) + "\n";
//
//        if (arr_subscription[i].fixed == 'y') {
//            details += "\n🟦 Fixed Subscription:\n";
//
//            if (arr_subscription[i].month_count > 0) {
//                details += "\n📅 Monthly Plans:\n";
//                for (int j = 0; j < arr_subscription[i].month_count; j++) {
//                    details += "➤ " + QString::number(arr_subscription[i].month_sub[j].duration) + " month(s), "
//                        + QString::number(arr_subscription[i].month_sub[j].no_of_trips) + " trips\n";
//                    for (int k = 0; k < arr_subscription[i].month_sub[j].zone_num; k++) {
//                        details += "   • Zone " + QString::number(k + 1) + ": "
//                            + QString::number(arr_subscription[i].month_sub[j].zonesPrice[k]) + " LE\n";
//                    }
//                }
//            }
//
//            if (arr_subscription[i].year_count > 0) {
//                details += "\n📅 Yearly Plans:\n";
//                for (int j = 0; j < arr_subscription[i].year_count; j++) {
//                    details += "➤ " + QString::number(arr_subscription[i].year_sub[j].duration) + " year(s), "
//                        + QString::number(arr_subscription[i].year_sub[j].no_of_trips) + " trips\n";
//                    for (int k = 0; k < arr_subscription[i].year_sub[j].zone_num; k++) {
//                        details += "   • Zone " + QString::number(k + 1) + ": "
//                            + QString::number(arr_subscription[i].year_sub[j].zonesPrice[k]) + " LE\n";
//                    }
//                }
//            }
//        }
//        else {
//            details += "\n🟨 Wallet Subscription:\n";
//            details += "• Add balance in multiples of: " + QString::number(arr_subscription[i].wallet_sub.fund_multiple) + " LE\n";
//            details += "• Maximum card balance: " + QString::number(arr_subscription[i].wallet_sub.card_balance) + " LE\n";
//            details += "• Zones and Prices:\n";
//            for (int k = 0; k < arr_subscription[i].wallet_sub.zone_num; k++) {
//                details += "   • Zone " + QString::number(k + 1) + ": "
//                    + QString::number(arr_subscription[i].wallet_sub.zonesPrice[k]) + " LE\n";
//            }
//        }
//
//        if (!arr_subscription[i].notes.empty()) {
//            details += "\n📝 Notes:\n" + QString::fromStdString(arr_subscription[i].notes);
//        }
//
//        ui->label_subscription_details->setPlainText(details);  // For QTextEdit
//        });
//}