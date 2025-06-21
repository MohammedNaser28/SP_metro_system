
#include "QtWidgetsApplication3.h"
#include "ui_QtWidgetsApplication3.h"  // Include the generated UI class
#include"dependence.h"
#include"global.h"
#include"structures.h"


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
void  QtWidgetsApplication3::on_pushButton_7_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->rides_history);
}
void  QtWidgetsApplication3::on_pushButton_8_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->view_sub);
}
void  QtWidgetsApplication3::on_pushButton_9_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->renew_sub);
}
void  QtWidgetsApplication3::on_pushButton_10_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->subscriptions);
    QString output;

    if (num_of_subsc == 0) {
        output += "No available subscriptions\n";
    }
    else {
        output += "* There are many options, choose what suits you *\n\n";

        for (int i = 0; i < num_of_subsc; i++) {
            output += "\t*" + QString::number(i + 1) + " - " + QString::fromStdString(arr_subscription[i].plan_name) + "\n";

            if (arr_subscription[i].fixed == 'y') {
                output += "Fixed Payment every:\n";

                
                for (int j = 0; j < arr_subscription[i].month_count; j++) {
                    output += QString::number(arr_subscription[i].month_sub[j].duration) +
                        " months for " +
                        QString::number(arr_subscription[i].month_sub[j].no_of_trips) +
                        " trips with limited stations access\n";

                    for (int k = 0; k < arr_subscription[i].month_sub[j].zone_num; k++) {
                        output += "For Zone " + QString::number(k + 1) + " : " +
                            QString::number(arr_subscription[i].month_sub[j].zonesPrice[k]) +
                            " LE\n";
                    }

                    output += "\n";
                }

                // Yearly subscriptions
                for (int j = 0; j < arr_subscription[i].year_count; j++) {
                    output += QString::number(arr_subscription[i].year_sub[j].duration) +
                        " years for " +
                        QString::number(arr_subscription[i].year_sub[j].no_of_trips) +
                        " trips with limited stations access\n";

                    for (int k = 0; k < arr_subscription[i].year_sub[j].zone_num; k++) {
                        output += "For Zone " + QString::number(k + 1) + " : " +
                            QString::number(arr_subscription[i].year_sub[j].zonesPrice[k]) +
                            " LE\n";
                    }

                    output += "\n";
                }

                output += "*******************************\n\n";

            }
            else if (arr_subscription[i].fixed == 'n') {
                
                output += "You can add funds in multiples of " +
                    QString::number(arr_subscription[i].wallet_sub.fund_multiple) +
                    " LE at any time\n";

                output += "The card balance cannot exceed " +
                    QString::number(arr_subscription[i].wallet_sub.card_balance) +
                    " LE\n";

                output += "No time restrictions\n";
                output += "Zones prices:\n";

                for (int k = 0; k < arr_subscription[i].wallet_sub.zone_num; k++) {
                    output += "For Zone " + QString::number(k + 1) + " : " +
                        QString::number(arr_subscription[i].wallet_sub.zonesPrice[k]) +
                        " LE\n";
                }

                output += "\n*******************************\n\n";
            }

            // Add notes
            output += QString::fromStdString(arr_subscription[i].notes) + "\n\n";
        }
    }

    
    ui->list_info->setText(output);

}

void  QtWidgetsApplication3::on_confirmride_clicked()
{
    string start_st, end_st;
    start_st = ui->startstation->currentText().toStdString();
    end_st = ui->endstation->currentText().toStdString();
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






