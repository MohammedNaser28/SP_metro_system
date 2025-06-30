#include "QtWidgetsApplication3.h"

//DONT PLAY IN SUBSCRIPTION .CPP FILE I WILL KILL YOU 


// DOOOONT PUT RECHARGE  OR SUBMIT BALANCE IN THIS FILE 
//DONT DO THAT I WILL KILL YOU 
//THEY ARE IN SUBSCRBITION .CPP  DONT PUT IT HERE 
//DONT PUT RECHARGE BUTTON OR SUBMIT BALANCE OR BACK FROM BALANCE LEAVE THEM ALONE 
//DANGEROUS 
//PLEASE DONT DO THAT IF YOU DO THAT I WILL KILL YOU 

//IF YOU PUT IT IT WILL BE A BIG MISTAKE


QtWidgetsApplication3::QtWidgetsApplication3(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)  // Correct link to the UI class generated from the .ui file
{
    ui->setupUi(this);  // Set up the UI components
    ui->stackedWidget->setCurrentWidget(ui->welcome2);

    ui->user_input_balance->setMaximum(10000.0);  // or whatever max you want
    ui->user_input_balance->setRange(0.0, 10000.0);     // sets both min and max
    ui->user_input_balance->setSingleStep(0.5);       // how much it increases/decreases per step
    connect(ui->admin_rech_balance_in_subsc, &QPushButton::clicked, this, [=]() {
        // Navigate to charge balance page
        ui->stackedWidget->setCurrentWidget(ui->charge_balance);
        });


    connect(ui->a_wallet, &QPushButton::clicked, this, [=]() {
        bool ok;
        int amount = ui->wallet_admin_enter_balancew->text().toInt(&ok);

        if (!ok || amount <= 0) {
            QMessageBox::warning(this, "Invalid Input", "Please enter a valid positive number.");
            return;
        }

        // Call handleWalletRecharge to process the recharge
        handleWalletRecharge();
        });
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





// DOOOONT PUT RECHARGE HERE OR SUBMIT BALANCE 
//DONT DO THAT I WILL KILL YOU 
//THEY ARE IN SUBSCRBITION .CPP  DONT PUT IT HERE 
//DONT PUT RECHARGE BUTTON OR SUBMIT BALANCE OR BACK FROM BALANCE LEAVE THEM ALONE 
//DANGEROUS 
//PLEASE DONT DO THAT IF YOU DO THAT I WILL KILL YOU 
//PLEASE DONT DO THAT IF YOU DO THAT I WILL KILL YOU 

//IF YOU PUT IT IT WILL BE A BIG MISTAKE


void QtWidgetsApplication3::start_up()
{

    ui->stackedWidget->setCurrentWidget(ui->welcome2);

}



void  QtWidgetsApplication3::on_admin_mainmenu_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->admin);
}


//DONT PUT THE USERNAME SAVE OR EMAIL SAVE OR TOEDIT HERE 
//THEY ARE IN THE PERSONAL DETAILS .CPP DONT PUT IT HERE AGAIN 
//SEEE THAT COMMENT 
//I WILL KILL THE PERSON WHO WILL PUT IT HERE 
//I 



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
    ui->stackedWidget->setCurrentWidget(ui->welcome2);
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



