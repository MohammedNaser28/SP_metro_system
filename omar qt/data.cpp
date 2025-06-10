
#include "data.h"
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QCoreApplication> // Required for QCoreApplication::applicationDirPath()
#define l Qt::endl
using namespace std;


//register 
void ReadFromFile() {
    ifstream inputfromfile("data of users.txt");
    if (!inputfromfile.is_open()) {
        cerr << "Error: Cannot open 'data of users.txt'" << l;
        return;
    }

    inputfromfile.ignore(1000, '\n'); // Skip header
    inputfromfile >> number_of_users_in_array;

    for (int i = 0; i < number_of_users_in_array; ++i) {
        inputfromfile >> arr_users[i].username
            >> arr_users[i].id
            >> arr_users[i].admin_role
            >> arr_users[i].balance
            >> arr_users[i].pass
            >> arr_users[i].contactdet.email;
    }

    inputfromfile.close();

    ifstream inputcomplaint("complains.txt");
    if (!inputcomplaint.is_open()) {
        cerr << "Error: Cannot open 'complains.txt'" << l;
        return;
    }

    inputcomplaint.ignore(1000, '\n'); // Skip header

    for (int i = 0; i < number_of_users_in_array; ++i) {
        string skip1, skip2;
        inputcomplaint >> skip1 >> skip2;
        inputcomplaint.ignore(); // Skip space or newline
        getline(inputcomplaint, arr_users[i].complaints);
    }

    inputcomplaint.close();
}

void saveusersinfo() {
    ofstream outfile_complaints("complains.txt");
    if (!outfile_complaints.is_open()) {
        cerr << "Error: Cannot open 'complains.txt' for writing.\n";
        return;
    }

    outfile_complaints << "The sequence of data is (name---> id ----> complaints)\n\n";

    for (int i = 0; i < number_of_users_in_array; i++) {
        qDebug() << "Checking user:" << QString::fromStdString(arr_users[i].username)
            << "with pass:" << QString::fromStdString(arr_users[i].pass);

        outfile_complaints << arr_users[i].username << " " << arr_users[i].id << " ";

        if (arr_users[i].complaints.empty()) {
            outfile_complaints << "NO COMPLAINTS" << '\n';
        }
        else {
            outfile_complaints << arr_users[i].complaints << '\n';
        }
    }

    outfile_complaints.close();

    ofstream dataofusers("data of users.txt");
    if (!dataofusers.is_open()) {
        cerr << "Error: Cannot open 'data of users.txt' for writing.\n";
        return;
    }

    dataofusers << "information of person is in this sequence:"
        << "(name --> id --> role --> balance --> password --> email)\n";

    dataofusers << number_of_users_in_array << "\n\n";

    for (int i = 0; i < number_of_users_in_array; i++) {
        const st_of_users& user = arr_users[i];

        dataofusers << user.username << " "
            << user.id << " "
            << user.admin_role << " "
            << user.balance << " "
            << user.pass << " "
            << user.contactdet.email << "\n";
    }

    dataofusers.close();
}

//subsc data 
void load_subsc_data() {
    QFile file("subsc data.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        cout << "No subscription data found!" << endl;
        return;
    }

    QTextStream in(&file);
    in >> num_of_subsc;

    for (int i = 0; i < num_of_subsc; i++) {
        QString qUsername;
        in >> qUsername;
        arr_users[i].username = qUsername.toStdString();
        in >> arr_subscription[i].fixed;

        if (arr_subscription[i].fixed == 'y') {

            in >> arr_subscription[i].month_count;
            for (int j = 0; j < arr_subscription[i].month_count; j++) {
                in >> arr_subscription[i].month_sub[j].duration
                    >> arr_subscription[i].month_sub[j].no_of_trips
                    >> arr_subscription[i].month_sub[j].zone_num;
                for (int k = 0; k < arr_subscription[i].month_sub[j].zone_num; k++) {
                    in >> arr_subscription[i].month_sub[j].zonesPrice[k];
                }
            }

            in >> arr_subscription[i].year_count;
            for (int j = 0; j < arr_subscription[i].year_count; j++) {
                in >> arr_subscription[i].year_sub[j].duration
                    >> arr_subscription[i].year_sub[j].no_of_trips
                    >> arr_subscription[i].year_sub[j].zone_num;
                for (int k = 0; k < arr_subscription[i].year_sub[j].zone_num; k++) {
                    in >> arr_subscription[i].year_sub[j].zonesPrice[k];
                }
            }

            in.readLine(); // to move to next line
            arr_subscription[i].notes = in.readLine().toStdString();

        }
        else if (arr_subscription[i].fixed == 'n') {

            in >> arr_subscription[i].wallet_sub.card_balance
                >> arr_subscription[i].wallet_sub.fund_multiple
                >> arr_subscription[i].wallet_sub.zone_num;

            for (int k = 0; k < arr_subscription[i].wallet_sub.zone_num; k++) {
                in >> arr_subscription[i].wallet_sub.zonesPrice[k];
            }

            in.readLine(); // to move to next line
            arr_subscription[i].notes = in.readLine().toStdString();
        }
    }

    file.close();
}

void save_subsc_data() {
    QFile file("subsc data.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        cout << "Error opening file for writing!" << l;
        return;
    }

    QTextStream out(&file);

    out << num_of_subsc << l;

    for (int i = 0; i < num_of_subsc; i++) {
        if (arr_subscription[i].fixed == 'y') {

            out << arr_subscription[i].plan_name.c_str() << l;
            out << arr_subscription[i].fixed << l;

            out << arr_subscription[i].month_count << l;
            for (int j = 0; j < arr_subscription[i].month_count; j++) {
                out << arr_subscription[i].month_sub[j].duration << "   "
                    << arr_subscription[i].month_sub[j].no_of_trips << "   "
                    << arr_subscription[i].month_sub[j].zone_num << "   ";
                for (int k = 0; k < arr_subscription[i].month_sub[j].zone_num; k++) {
                    out << arr_subscription[i].month_sub[j].zonesPrice[k] << "   ";
                }
                out << l;
            }

            out << arr_subscription[i].year_count << l;
            for (int j = 0; j < arr_subscription[i].year_count; j++) {
                out << arr_subscription[i].year_sub[j].duration << "   "
                    << arr_subscription[i].year_sub[j].no_of_trips << "   "
                    << arr_subscription[i].year_sub[j].zone_num << "   ";
                for (int k = 0; k < arr_subscription[i].year_sub[j].zone_num; k++) {
                    out << arr_subscription[i].year_sub[j].zonesPrice[k] << "   ";
                }
                out << l;
            }

            out << arr_subscription[i].notes.c_str() << l;
        }
        else if (arr_subscription[i].fixed == 'n') {

            out << arr_subscription[i].plan_name.c_str() << l
                << arr_subscription[i].fixed << l
                << arr_subscription[i].wallet_sub.card_balance << "   "
                << arr_subscription[i].wallet_sub.fund_multiple << "   "
                << arr_subscription[i].wallet_sub.zone_num << "   ";
            for (int k = 0; k < arr_subscription[i].wallet_sub.zone_num; k++) {
                out << arr_subscription[i].wallet_sub.zonesPrice[k] << "   ";
            }

            out << l;
            out << arr_subscription[i].notes.c_str() << "   " << l;
        }
    }

    file.close();
}



//user subsc


void save_user_subsc() {
    QFile file("subsc.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        cout << "Error opening file for writing!" << l;
        return;
    }

    QTextStream out(&file);
    QString qUsername, qid, qSubsctype, qplantype, qactivation, qExpir;
    for (int i = 0; i < number_of_users_in_array; i++) {
        out << arr_users[i].sub.fixed;

        out << qUsername;
        arr_users[i].username = qUsername.toStdString();

        out << qid;
        arr_users[i].id = qid.toStdString();

        if (arr_users[i].sub.fixed == 'y') {
            out << qSubsctype;
            arr_users[i].sub.subscription_type = qSubsctype.toStdString();


            out << qplantype;
            arr_users[i].sub.plan_type = qplantype.toStdString();

            out << arr_users[i].sub.duriation_plan_type
                << arr_users[i].sub.Num_trips
                << arr_users[i].sub.remaining_trips
                << arr_users[i].sub.zone
                << arr_users[i].sub.zonePrice;


            out << qactivation;
            arr_users[i].sub.activation = qactivation.toStdString();
            out << qExpir;
            arr_users[i].sub.expiry = qExpir.toStdString();;
        }
        else if (arr_users[i].sub.fixed == 'n') {
            out << qSubsctype;
            arr_users[i].sub.subscription_type = qSubsctype.toStdString();
            out << arr_users[i].sub.zone
                << arr_users[i].sub.zonePrice;

            out << qactivation;
            arr_users[i].sub.activation = qactivation.toStdString();

            out << arr_users[i].sub.balancew;


        }
    }

    file.close();
}

void load_user_subsc() {
    QFile file("subsc.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        cout << "No subscription data found!" << l;
        return;
    }

    QTextStream in(&file);
    QString qUsername, qid, qSubsctype, qplantype, qactivation, qExpir;
    for (int i = 0; i < number_of_users_in_array; i++) {
        in >> arr_users[i].sub.fixed;

        in << qUsername;
        arr_users[i].username = qUsername.toStdString();

        in >> qid;
        arr_users[i].id = qid.toStdString();

        if (arr_users[i].sub.fixed == 'y') {
            in >> qSubsctype;
            arr_users[i].sub.subscription_type = qSubsctype.toStdString();


            in >> qplantype;
            arr_users[i].sub.plan_type = qplantype.toStdString();

            in >> arr_users[i].sub.duriation_plan_type
                >> arr_users[i].sub.Num_trips
                >> arr_users[i].sub.remaining_trips
                >> arr_users[i].sub.zone
                >> arr_users[i].sub.zonePrice;


            in >> qactivation;
            arr_users[i].sub.activation = qactivation.toStdString();
            in >> qExpir;
            arr_users[i].sub.expiry = qExpir.toStdString();;
        }
        else if (arr_users[i].sub.fixed == 'n') {
            in >> qSubsctype;
            arr_users[i].sub.subscription_type = qSubsctype.toStdString();
            in >> arr_users[i].sub.zone
                >> arr_users[i].sub.zonePrice;

            in >> qactivation;
            arr_users[i].sub.activation = qactivation.toStdString();

            in >> arr_users[i].sub.balancew;
        }

        in.readLine(); // to consume leftover newline
    }

    file.close();
}

//history rides 


//stations 