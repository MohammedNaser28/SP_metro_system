#include "QtWidgetsApplication3.h"


QtWidgetsApplication3::QtWidgetsApplication3(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)  // Correct link to the UI class generated from the .ui file
{
    ui->setupUi(this);  // Set up the UI components
    ui->stackedWidget->setCurrentWidget(ui->welcome2);

    ui->user_input_balance->setMaximum(10000.0);  // or whatever max you want
    ui->user_input_balance->setRange(0.0, 10000.0);     // sets both min and max
    ui->user_input_balance->setSingleStep(0.5);       // how much it increases/decreases per step

  
}

QtWidgetsApplication3::~QtWidgetsApplication3()
{
    delete ui;  // Clean up
}




void QtWidgetsApplication3::setPage(int index)
{
    ui->stackedWidget->setCurrentIndex(index);

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

void QtWidgetsApplication3::start_up()
{

    ui->stackedWidget->setCurrentWidget(ui->welcome2);

}








void  QtWidgetsApplication3::on_admin_mainmenu_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->admin);
}






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


void QtWidgetsApplication3::on_TOEDIT_clicked() {
  //  on_pushButton_editInfo_clicked();
    ui->stackedWidget->setCurrentWidget(ui->changeinfo);
}

//void QtWidgetsApplication3::on_pushButton_editInfo_clicked() {
//    ui->stackedWidget->setCurrentWidget(ui->changeinfo);
//
//    ui->username_label->setText(QString::fromStdString(arr_users[indexofuser].username));
//    ui->email_label->setText(QString::fromStdString(arr_users[indexofuser].contactdet.email));
//    ui->pass_label->setText(QString::fromStdString(arr_users[indexofuser].pass));
//}


void QtWidgetsApplication3::on_saveUsername_clicked() {
    QString newName = ui->nameuser->text().trimmed();
    //qDebug() << "Save Username clicked with name:" << newName;

    if (newName.isEmpty() ){
        QMessageBox::warning(this, "Error", "Username cannot be empty.");
        return;
    }

    arr_users[indexofuser].username = newName.toStdString();


   // ui->nameuser->setText(newName);

    QMessageBox::information(this, "Success", "Username updated successfully.");
}




void QtWidgetsApplication3::on_saveEmail_clicked() {
    QString newEmail = ui->emaillabel->text();
    if (!newEmail.contains("@") || !newEmail.contains(".")) {
        QMessageBox::warning(this, "Error", "Invalid email format.");
        return;
    }
    arr_users[indexofuser].contactdet.email = newEmail.toStdString();
    QMessageBox::information(this, "Success", "Email updated successfully.");
}


void QtWidgetsApplication3::on_savePassword_clicked() {
    QString newPass = ui->passlabel->text();
    if (newPass.length() < 8) {
        QMessageBox::warning(this, "Error", "Password must be at least 8 characters.");
        return;
    }
    arr_users[indexofuser].pass = newPass.toStdString();
    QMessageBox::information(this, "Success", "Password updated successfully.");
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

void QtWidgetsApplication3::on_back12_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->current_data);
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



