#include"QtWidgetsApplication3.h"





void  QtWidgetsApplication3::on_rides_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->rides_2);
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










    //IMP IMP IMP IMP IMP DONT DELETE 
    //void QtWidgetsApplication3::on_pushButton_AdminRideHistory_clicked() {
    //    ui->stackedWidget->setCurrentWidget(ui->admin_rides_history);

    //    QString output;
    //    output += "\n--- Ride History for ADMIN name : " + QString::fromStdString(arr_users[indexofuser].username) + " ---\n";
    //    bool found = false;
    //    int cntride = 1;

    //    for (int i = 0; i < MAX_rides; i++) {
    //        if (rides[i].entryStation != "") {
    //            output += "\nTrip number " + QString::number(cntride) + "\n";
    //            output += " User ID : " + QString::number(rides[i].id) + "\n";
    //            output += " Entry station : " + QString::fromStdString(rides[i].entryStation) + "\n";
    //            output += " Exit station : " + QString::fromStdString(rides[i].ExitStation) + "\n";
    //            output += " Fare : " + QString::number(rides[i].RideFare) + "\n";
    //            output += " Date of trip : " + rides[i].Date + "\n";
    //            output += "____________________________________________________________\n";

    //            found = true;
    //            cntride++;
    //        }
    //    }

    //    if (!found) {
    //        output += "No rides found.\n";
    //    }

    //    ui->textEdit_AdminRideHistory->setText(output); // QTextEdit name in admin UI
    //}












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

    string path = findShortestPath(find_st_num(start_st), find_st_num(end_st));

    ui->viewride->clear();
    ui->viewride->setText(QString::fromStdString(path));


}
