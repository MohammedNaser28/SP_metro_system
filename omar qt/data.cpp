
#include "data.h"
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QCoreApplication> // Required for QCoreApplication::applicationDirPath()
#define l Qt::endl
using namespace std;
//hello iam nour


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
//void load_subsc_data() {
//    QFile file("subsc data.txt");
//    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
//        cout << "No subscription data found!" << endl;
//        return;
//    }
//
//    QTextStream in(&file);
//    in >> num_of_subsc;
//
//    for (int i = 0; i < num_of_subsc; i++) {
//      QString qPlanName;
//in >> qPlanName;
//arr_subscription[i].plan_name = qPlanName.toStdString();  // ✅ Correct!
//
//        in >> arr_subscription[i].fixed;
//
//        if (arr_subscription[i].fixed == 'y') {
//
//            in >> arr_subscription[i].month_count;
//            for (int j = 0; j < arr_subscription[i].month_count; j++) {
//                in >> arr_subscription[i].month_sub[j].duration
//                    >> arr_subscription[i].month_sub[j].no_of_trips
//                    >> arr_subscription[i].month_sub[j].zone_num;
//                for (int k = 0; k < arr_subscription[i].month_sub[j].zone_num; k++) {
//                    in >> arr_subscription[i].month_sub[j].zonesPrice[k];
//                }
//            }
//
//            in >> arr_subscription[i].year_count;
//            for (int j = 0; j < arr_subscription[i].year_count; j++) {
//                in >> arr_subscription[i].year_sub[j].duration
//                    >> arr_subscription[i].year_sub[j].no_of_trips
//                    >> arr_subscription[i].year_sub[j].zone_num;
//                for (int k = 0; k < arr_subscription[i].year_sub[j].zone_num; k++) {
//                    in >> arr_subscription[i].year_sub[j].zonesPrice[k];
//                }
//            }
//
//            in.readLine(); // to move to next line
//            arr_subscription[i].notes = in.readLine().toStdString();
//
//        }
//        else if (arr_subscription[i].fixed == 'n') {
//
//            in >> arr_subscription[i].wallet_sub.card_balance
//                >> arr_subscription[i].wallet_sub.fund_multiple
//                >> arr_subscription[i].wallet_sub.zone_num;
//
//            for (int k = 0; k < arr_subscription[i].wallet_sub.zone_num; k++) {
//                in >> arr_subscription[i].wallet_sub.zonesPrice[k];
//            }
//
//            in.readLine(); // to move to next line
//            arr_subscription[i].notes = in.readLine().toStdString();
//        }
//    }
//
//    file.close();
//}
//void load_subsc_data() {
//    QFile file("subsc data.txt");
//    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
//        qDebug() << "No subscription data found!";
//        return;
//    }
//
//    QTextStream in(&file);
//
//    in >> num_of_subsc;
//    in.readLine();  // Move to the next line after number
//
//    for (int i = 0; i < num_of_subsc; i++) {
//        QString qPlanName;
//        in >> qPlanName;
//        arr_subscription[i].plan_name = qPlanName.toStdString();
//
//        in >> arr_subscription[i].fixed;
//        in.readLine();  // Consume newline
//
//        if (arr_subscription[i].fixed == 'y') {
//            in >> arr_subscription[i].month_count;
//            for (int j = 0; j < arr_subscription[i].month_count; j++) {
//                in >> arr_subscription[i].month_sub[j].duration
//                    >> arr_subscription[i].month_sub[j].no_of_trips
//                    >> arr_subscription[i].month_sub[j].zone_num;
//                for (int k = 0; k < arr_subscription[i].month_sub[j].zone_num; k++) {
//                    in >> arr_subscription[i].month_sub[j].zonesPrice[k];
//                }
//            }
//
//            in >> arr_subscription[i].year_count;
//            for (int j = 0; j < arr_subscription[i].year_count; j++) {
//                in >> arr_subscription[i].year_sub[j].duration
//                    >> arr_subscription[i].year_sub[j].no_of_trips
//                    >> arr_subscription[i].year_sub[j].zone_num;
//                for (int k = 0; k < arr_subscription[i].year_sub[j].zone_num; k++) {
//                    in >> arr_subscription[i].year_sub[j].zonesPrice[k];
//                }
//            }
//
//            in.readLine();  // Skip to the note line
//            arr_subscription[i].notes = in.readLine().toStdString();
//        }
//        else if (arr_subscription[i].fixed == 'n') {
//            in >> arr_subscription[i].wallet_sub.card_balance
//                >> arr_subscription[i].wallet_sub.fund_multiple
//                >> arr_subscription[i].wallet_sub.zone_num;
//
//            for (int k = 0; k < arr_subscription[i].wallet_sub.zone_num; k++) {
//                in >> arr_subscription[i].wallet_sub.zonesPrice[k];
//            }
//
//            in.readLine();  // Skip to the note line
//            arr_subscription[i].notes = in.readLine().toStdString();
//        }
//    }
//
//    file.close();
//}
//


void load_subsc_data() {
    QFile file("subsc data.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "No subscription data found!";
        return;
    }

    QTextStream in(&file);

    QString line = in.readLine(); // read number of subscriptions
    num_of_subsc = line.trimmed().toInt();

    for (int i = 0; i < num_of_subsc; ++i) {
        // 1. plan name
        arr_subscription[i].plan_name = in.readLine().trimmed().toStdString();

        // 2. type (fixed or not)
        QString fixedStr = in.readLine().trimmed();
        arr_subscription[i].fixed = fixedStr.isEmpty() ? 'n' : fixedStr[0].toLatin1();

        if (arr_subscription[i].fixed == 'y') {
            // Monthly
            arr_subscription[i].month_count = in.readLine().trimmed().toInt();
            for (int j = 0; j < arr_subscription[i].month_count; ++j) {
                QString monthlyLine = in.readLine().trimmed();
                QTextStream monthlyStream(&monthlyLine);
                monthlyStream >> arr_subscription[i].month_sub[j].duration
                    >> arr_subscription[i].month_sub[j].no_of_trips
                    >> arr_subscription[i].month_sub[j].zone_num;

                for (int k = 0; k < arr_subscription[i].month_sub[j].zone_num; ++k) {
                    monthlyStream >> arr_subscription[i].month_sub[j].zonesPrice[k];
                }
            }

            // Yearly
            arr_subscription[i].year_count = in.readLine().trimmed().toInt();
            for (int j = 0; j < arr_subscription[i].year_count; ++j) {
                QString yearlyLine = in.readLine().trimmed();
                QTextStream yearlyStream(&yearlyLine);
                yearlyStream >> arr_subscription[i].year_sub[j].duration
                    >> arr_subscription[i].year_sub[j].no_of_trips
                    >> arr_subscription[i].year_sub[j].zone_num;

                for (int k = 0; k < arr_subscription[i].year_sub[j].zone_num; ++k) {
                    yearlyStream >> arr_subscription[i].year_sub[j].zonesPrice[k];
                }
            }

            // Notes
            arr_subscription[i].notes = in.readLine().toStdString();

        }
        else if (arr_subscription[i].fixed == 'n') {
            // Wallet
            QString walletLine = in.readLine().trimmed();
            QTextStream walletStream(&walletLine);
            walletStream >> arr_subscription[i].wallet_sub.card_balance
                >> arr_subscription[i].wallet_sub.fund_multiple
                >> arr_subscription[i].wallet_sub.zone_num;

            for (int k = 0; k < arr_subscription[i].wallet_sub.zone_num; ++k) {
                walletStream >> arr_subscription[i].wallet_sub.zonesPrice[k];
            }

            // Notes
            arr_subscription[i].notes = in.readLine().toStdString();
        }
    }

    file.close();
    qDebug() << "✅ Subscription data loaded successfully.";
}

void save_subsc_data() {
    QFile file("subsc data.txt");

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "❌ Error opening file for writing!";
        return;
    }

    QTextStream out(&file);

    // عدد الاشتراكات
    out << num_of_subsc << "\n";

    for (int i = 0; i < num_of_subsc; ++i) {
        const auto& sub = arr_subscription[i];

        // 1. plan name
        out << QString::fromStdString(sub.plan_name) << "\n";

        // 2. type
        out << sub.fixed << "\n";

        if (sub.fixed == 'y') {
            // Monthly
            out << sub.month_count << "\n";
            for (int j = 0; j < sub.month_count; ++j) {
                out << sub.month_sub[j].duration << " "
                    << sub.month_sub[j].no_of_trips << " "
                    << sub.month_sub[j].zone_num << " ";
                for (int k = 0; k < sub.month_sub[j].zone_num; ++k) {
                    out << sub.month_sub[j].zonesPrice[k] << " ";
                }
                out << "\n";
            }

            // Yearly
            out << sub.year_count << "\n";
            for (int j = 0; j < sub.year_count; ++j) {
                out << sub.year_sub[j].duration << " "
                    << sub.year_sub[j].no_of_trips << " "
                    << sub.year_sub[j].zone_num << " ";
                for (int k = 0; k < sub.year_sub[j].zone_num; ++k) {
                    out << sub.year_sub[j].zonesPrice[k] << " ";
                }
                out << "\n";
            }

            // Notes (حتى لو فاضية)
            out << QString::fromStdString(sub.notes) << "\n";

        }
        else if (sub.fixed == 'n') {
            // Wallet-based
            out << sub.wallet_sub.card_balance << " "
                << sub.wallet_sub.fund_multiple << " "
                << sub.wallet_sub.zone_num << " ";
            for (int k = 0; k < sub.wallet_sub.zone_num; ++k) {
                out << sub.wallet_sub.zonesPrice[k] << " ";
            }
            out << "\n";

            // Notes
            out << QString::fromStdString(sub.notes) << "\n";
        }

        // إضافة سطر فاصل بين الاشتراكات (اختياري فقط للوضوح)
        // out << "\n";
    }

    file.close();
    qDebug() << "✅ Subscription data saved successfully.";
}


//void save_subsc_data() {
//    QFile file("subsc data.txt");
//    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
//        cout << "Error opening file for writing!" << l;
//        return;
//    }
//
//    QTextStream out(&file);
//
//    out << num_of_subsc << l;
//
//    for (int i = 0; i < num_of_subsc; i++) {
//        if (arr_subscription[i].fixed == 'y') {
//
//            out << arr_subscription[i].plan_name.c_str() << l;
//            out << arr_subscription[i].fixed << l;
//
//            out << arr_subscription[i].month_count << l;
//            for (int j = 0; j < arr_subscription[i].month_count; j++) {
//                out << arr_subscription[i].month_sub[j].duration << "   "
//                    << arr_subscription[i].month_sub[j].no_of_trips << "   "
//                    << arr_subscription[i].month_sub[j].zone_num << "   ";
//                for (int k = 0; k < arr_subscription[i].month_sub[j].zone_num; k++) {
//                    out << arr_subscription[i].month_sub[j].zonesPrice[k] << "   ";
//                }
//                out << l;
//            }
//
//            out << arr_subscription[i].year_count << l;
//            for (int j = 0; j < arr_subscription[i].year_count; j++) {
//                out << arr_subscription[i].year_sub[j].duration << "   "
//                    << arr_subscription[i].year_sub[j].no_of_trips << "   "
//                    << arr_subscription[i].year_sub[j].zone_num << "   ";
//                for (int k = 0; k < arr_subscription[i].year_sub[j].zone_num; k++) {
//                    out << arr_subscription[i].year_sub[j].zonesPrice[k] << "   ";
//                }
//                out << l;
//            }
//
//            out << arr_subscription[i].notes.c_str() << l;
//        }
//        else if (arr_subscription[i].fixed == 'n') {
//
//            out << arr_subscription[i].plan_name.c_str() << l
//                << arr_subscription[i].fixed << l
//                << arr_subscription[i].wallet_sub.card_balance << "   "
//                << arr_subscription[i].wallet_sub.fund_multiple << "   "
//                << arr_subscription[i].wallet_sub.zone_num << "   ";
//            for (int k = 0; k < arr_subscription[i].wallet_sub.zone_num; k++) {
//                out << arr_subscription[i].wallet_sub.zonesPrice[k] << "   ";
//            }
//
//            out << l;
//            out << arr_subscription[i].notes.c_str() << "   " << l;
//        }
//    }
//
//    file.close();
//}
//
//void save_subsc_data() {
//    QFile file("subsc data.txt");
//    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
//        qDebug() << "Error opening file for writing!";
//        return;
//    }
//
//    QTextStream out(&file);
//
//    out << num_of_subsc << Qt::endl;
//
//    for (int i = 0; i < num_of_subsc; i++) {
//        // 1. Write plan name
//        out << QString::fromStdString(arr_subscription[i].plan_name) << Qt::endl;
//
//        // 2. Write type
//        out << arr_subscription[i].fixed << Qt::endl;
//
//        if (arr_subscription[i].fixed == 'y') {
//            // Monthly section
//            out << arr_subscription[i].month_count << Qt::endl;
//            for (int j = 0; j < arr_subscription[i].month_count; j++) {
//                out << arr_subscription[i].month_sub[j].duration << " "
//                    << arr_subscription[i].month_sub[j].no_of_trips << " "
//                    << arr_subscription[i].month_sub[j].zone_num << " ";
//                for (int k = 0; k < arr_subscription[i].month_sub[j].zone_num; k++) {
//                    out << arr_subscription[i].month_sub[j].zonesPrice[k] << " ";
//                }
//                out << Qt::endl;
//            }
//
//            // Yearly section
//            out << arr_subscription[i].year_count << Qt::endl;
//            for (int j = 0; j < arr_subscription[i].year_count; j++) {
//                out << arr_subscription[i].year_sub[j].duration << " "
//                    << arr_subscription[i].year_sub[j].no_of_trips << " "
//                    << arr_subscription[i].year_sub[j].zone_num << " ";
//                for (int k = 0; k < arr_subscription[i].year_sub[j].zone_num; k++) {
//                    out << arr_subscription[i].year_sub[j].zonesPrice[k] << " ";
//                }
//                out << Qt::endl;
//            }
//
//            // Notes
//            out << QString::fromStdString(arr_subscription[i].notes) << Qt::endl;
//        }
//        else if (arr_subscription[i].fixed == 'n') {
//            // Wallet-based
//            out << arr_subscription[i].wallet_sub.card_balance << " "
//                << arr_subscription[i].wallet_sub.fund_multiple << " "
//                << arr_subscription[i].wallet_sub.zone_num << " ";
//            for (int k = 0; k < arr_subscription[i].wallet_sub.zone_num; k++) {
//                out << arr_subscription[i].wallet_sub.zonesPrice[k] << " ";
//            }
//
//            out << Qt::endl;
//
//            // Notes
//            out << QString::fromStdString(arr_subscription[i].notes) << Qt::endl;
//        }
//    }
//
//    file.close();
//}
//



//user subsc


//void save_user_subsc() {
//    QFile file("subsc.txt");
//    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
//        cout << "Error opening file for writing!" << l;
//        return;
//    }
//
//    QTextStream out(&file);
//    QString qUsername, qid, qSubsctype, qplantype, qactivation, qExpir;
//    for (int i = 0; i < number_of_users_in_array; i++) {
//        out << arr_users[i].sub.fixed;
//
//        out << QString::fromStdString(arr_users[i].username) << " ";
//
//
//        out << qid;
//        arr_users[i].id = qid.toStdString();
//
//        if (arr_users[i].sub.fixed == 'y') {
//            out << qSubsctype;
//            arr_users[i].sub.subscription_type = qSubsctype.toStdString();
//
//
//            out << qplantype;
//            arr_users[i].sub.plan_type = qplantype.toStdString();
//
//            out << arr_users[i].sub.duriation_plan_type
//                << arr_users[i].sub.Num_trips
//                << arr_users[i].sub.remaining_trips
//                << arr_users[i].sub.zone
//                << arr_users[i].sub.zonePrice;
//
//
//            out << qactivation;
//            arr_users[i].sub.activation = qactivation.toStdString();
//            out << qExpir;
//            arr_users[i].sub.expiry = qExpir.toStdString();;
//        }
//        else if (arr_users[i].sub.fixed == 'n') {
//            out << qSubsctype;
//            arr_users[i].sub.subscription_type = qSubsctype.toStdString();
//            out << arr_users[i].sub.zone
//                << arr_users[i].sub.zonePrice;
//
//            out << qactivation;
//            arr_users[i].sub.activation = qactivation.toStdString();
//
//            out << arr_users[i].sub.balancew;
//
//
//        }
//    }
//
//    file.close();
//}
void save_user_subsc() {
    QFile file("subsc.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        cout << "Error opening file for writing!" << Qt::endl;
        return;
    }

    QTextStream out(&file);

    for (int i = 0; i < number_of_users_in_array; i++) {
        const st_of_users& user = arr_users[i];
        const user_subscriptions& sub = user.sub;

        out << sub.fixed << " "
            << QString::fromStdString(user.username) << " "
            << QString::fromStdString(user.id) << " ";

        if (sub.fixed == 'y') {
            out << QString::fromStdString(sub.subscription_type) << " "
                << QString::fromStdString(sub.plan_type) << " "
                << sub.duriation_plan_type << " "
                << sub.Num_trips << " "
                << sub.remaining_trips << " "
                << sub.zone << " "
                << sub.zonePrice << " "
                << QString::fromStdString(sub.activation) << " "
                << QString::fromStdString(sub.expiry) << "\n";
        }
        else {
            out << QString::fromStdString(sub.subscription_type) << " "
                << sub.zone << " "
                << sub.zonePrice << " "
                << QString::fromStdString(sub.activation) << " "
                << sub.balancew << "\n";
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

        in >> qUsername;
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





//
////history rides 
//
//
////stations 
//#include "data.h"
//#include <iostream>
//#include <QFile>
//#include <QTextStream>
//#include <QDebug>
//#include <QCoreApplication>
//#include <QStandardPaths>
//#define l Qt::endl
//
//using namespace std;
//#include <QCoreApplication> // Required for QCoreApplication::applicationDirPath()
//
//// Global helper function to get data file path
//QString getDataFilePath(const QString& filename) {
//    QString appPath = QCoreApplication::applicationDirPath();
//    return appPath + "/" + filename;
//}
//
////register 
//void ReadFromFile() {
//    QString filePath = getDataFilePath("data of users.txt");
//    ifstream inputfromfile(filePath.toStdString());
//
//    if (!inputfromfile.is_open()) {
//        qDebug() << "Error: Cannot open 'data of users.txt' at" << filePath;
//        return;
//    }
//
//    inputfromfile.ignore(1000, '\n'); // Skip header
//    inputfromfile >> number_of_users_in_array;
//
//    for (int i = 0; i < number_of_users_in_array; ++i) {
//        inputfromfile >> arr_users[i].username
//            >> arr_users[i].id
//            >> arr_users[i].admin_role
//            >> arr_users[i].balance
//            >> arr_users[i].pass
//            >> arr_users[i].contactdet.email;
//    }
//
//    inputfromfile.close();
//
//    filePath = getDataFilePath("complains.txt");
//    ifstream inputcomplaint(filePath.toStdString());
//    if (!inputcomplaint.is_open()) {
//        qDebug() << "Error: Cannot open 'complains.txt' at" << filePath;
//        return;
//    }
//
//    inputcomplaint.ignore(1000, '\n'); // Skip header
//
//    for (int i = 0; i < number_of_users_in_array; ++i) {
//        string skip1, skip2;
//        inputcomplaint >> skip1 >> skip2;
//        inputcomplaint.ignore(); // Skip space or newline
//        getline(inputcomplaint, arr_users[i].complaints);
//    }
//
//    inputcomplaint.close();
//}
//
//
//void saveusersinfo() {
//    QString filePath = getDataFilePath("complains.txt");
//    ofstream outfile_complaints(filePath.toStdString());
//
//    if (!outfile_complaints.is_open()) {
//        qDebug() << "Error: Cannot open 'complains.txt' for writing at" << filePath;
//        return;
//    }
//
//    outfile_complaints << "The sequence of data is (name---> id ----> complaints)\n\n";
//
//    for (int i = 0; i < number_of_users_in_array; i++) {
//        qDebug() << "Saving user:" << QString::fromStdString(arr_users[i].username)
//            << "with pass:" << QString::fromStdString(arr_users[i].pass);
//
//        outfile_complaints << arr_users[i].username << " " << arr_users[i].id << " ";
//
//        if (arr_users[i].complaints.empty()) {
//            outfile_complaints << "NO COMPLAINTS" << '\n';
//        }
//        else {
//            outfile_complaints << arr_users[i].complaints << '\n';
//        }
//    }
//
//    outfile_complaints.close();
//
//    filePath = getDataFilePath("data of users.txt");
//    ofstream dataofusers(filePath.toStdString());
//    if (!dataofusers.is_open()) {
//        qDebug() << "Error: Cannot open 'data of users.txt' for writing at" << filePath;
//        return;
//    }
//
//    dataofusers << "information of person is in this sequence:"
//        << "(name --> id --> role --> balance --> password --> email)\n";
//    dataofusers << number_of_users_in_array << "\n\n";
//
//    for (int i = 0; i < number_of_users_in_array; i++) {
//        const st_of_users& user = arr_users[i];
//        dataofusers << user.username << " "
//            << user.id << " "
//            << user.admin_role << " "
//            << user.balance << " "
//            << user.pass << " "
//            << user.contactdet.email << "\n";
//    }
//
//    dataofusers.close();
//}
//
////subsc data 
//void load_subsc_data() {
//    QFile file("subsc data.txt");
//    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
//        cout << "No subscription data found!" << endl;
//        return;
//    }
//
//    QTextStream in(&file);
//    in >> num_of_subsc;
//
//    for (int i = 0; i < num_of_subsc; i++) {
//        QString qUsername;
//        in >> qUsername;
//        arr_users[i].username = qUsername.toStdString();
//        in >> arr_subscription[i].fixed;
//
//        if (arr_subscription[i].fixed == 'y') {
//
//            in >> arr_subscription[i].month_count;
//            for (int j = 0; j < arr_subscription[i].month_count; j++) {
//                in >> arr_subscription[i].month_sub[j].duration
//                    >> arr_subscription[i].month_sub[j].no_of_trips
//                    >> arr_subscription[i].month_sub[j].zone_num;
//                for (int k = 0; k < arr_subscription[i].month_sub[j].zone_num; k++) {
//                    in >> arr_subscription[i].month_sub[j].zonesPrice[k];
//                }
//            }
//
//            in >> arr_subscription[i].year_count;
//            for (int j = 0; j < arr_subscription[i].year_count; j++) {
//                in >> arr_subscription[i].year_sub[j].duration
//                    >> arr_subscription[i].year_sub[j].no_of_trips
//                    >> arr_subscription[i].year_sub[j].zone_num;
//                for (int k = 0; k < arr_subscription[i].year_sub[j].zone_num; k++) {
//                    in >> arr_subscription[i].year_sub[j].zonesPrice[k];
//                }
//            }
//
//            in.readLine(); // to move to next line
//            arr_subscription[i].notes = in.readLine().toStdString();
//
//        }
//        else if (arr_subscription[i].fixed == 'n') {
//
//            in >> arr_subscription[i].wallet_sub.card_balance
//                >> arr_subscription[i].wallet_sub.fund_multiple
//                >> arr_subscription[i].wallet_sub.zone_num;
//
//            for (int k = 0; k < arr_subscription[i].wallet_sub.zone_num; k++) {
//                in >> arr_subscription[i].wallet_sub.zonesPrice[k];
//            }
//
//            in.readLine(); // to move to next line
//            arr_subscription[i].notes = in.readLine().toStdString();
//        }
//    }
//
//    file.close();
//}
//
//void save_subsc_data() {
//    QFile file("subsc data.txt");
//    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
//        cout << "Error opening file for writing!" << endl;
//        return;
//    }
//
//    QTextStream out(&file);
//
//    out << num_of_subsc << l;
//
//    for (int i = 0; i < num_of_subsc; i++) {
//        if (arr_subscription[i].fixed == 'y') {
//
//            out << arr_subscription[i].plan_name.c_str() << l;
//            out << arr_subscription[i].fixed << l;
//
//            out << arr_subscription[i].month_count << l;
//            for (int j = 0; j < arr_subscription[i].month_count; j++) {
//                out << arr_subscription[i].month_sub[j].duration << "   "
//                    << arr_subscription[i].month_sub[j].no_of_trips << "   "
//                    << arr_subscription[i].month_sub[j].zone_num << "   ";
//                for (int k = 0; k < arr_subscription[i].month_sub[j].zone_num; k++) {
//                    out << arr_subscription[i].month_sub[j].zonesPrice[k] << "   ";
//                }
//                out << l;
//            }
//
//            out << arr_subscription[i].year_count << l;
//            for (int j = 0; j < arr_subscription[i].year_count; j++) {
//                out << arr_subscription[i].year_sub[j].duration << "   "
//                    << arr_subscription[i].year_sub[j].no_of_trips << "   "
//                    << arr_subscription[i].year_sub[j].zone_num << "   ";
//                for (int k = 0; k < arr_subscription[i].year_sub[j].zone_num; k++) {
//                    out << arr_subscription[i].year_sub[j].zonesPrice[k] << "   ";
//                }
//                out << l;
//            }
//
//            out << arr_subscription[i].notes.c_str() << l;
//        }
//        else if (arr_subscription[i].fixed == 'n') {
//
//            out << arr_subscription[i].plan_name.c_str() << l
//                << arr_subscription[i].fixed << l
//                << arr_subscription[i].wallet_sub.card_balance << "   "
//                << arr_subscription[i].wallet_sub.fund_multiple << "   "
//                << arr_subscription[i].wallet_sub.zone_num << "   ";
//            for (int k = 0; k < arr_subscription[i].wallet_sub.zone_num; k++) {
//                out << arr_subscription[i].wallet_sub.zonesPrice[k] << "   ";
//            }
//
//            out << l;
//            out << arr_subscription[i].notes.c_str() << "   " << l;
//        }
//    }
//
//    file.close();
//}
//
//
//
////user subsc
//
//
//void save_user_subsc() {
//    QFile file("subsc.txt");
//    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
//        cout << "Error opening file for writing!" << endl;
//        return;
//    }
//
//    QTextStream out(&file);
//    QString qUsername, qid, qSubsctype, qplantype, qactivation, qExpir;
//    for (int i = 0; i < number_of_users_in_array; i++) {
//        out << arr_users[i].sub.fixed;
//
//        out << qUsername;
//        arr_users[i].username = qUsername.toStdString();
//
//        out<< qid;
//        arr_users[i].id = qid.toStdString();
//
//        if (arr_users[i].sub.fixed == 'y') {
//            out << qSubsctype;
//            arr_users[i].sub.subscription_type = qSubsctype.toStdString();
//
//
//            out <<qplantype;
//            arr_users[i].sub.plan_type = qplantype.toStdString();
//
//            out << arr_users[i].sub.duriation_plan_type
//                << arr_users[i].sub.Num_trips
//                << arr_users[i].sub.remaining_trips
//                << arr_users[i].sub.zone
//                << arr_users[i].sub.zonePrice;
//
//
//            out << qactivation;
//            arr_users[i].sub.activation = qactivation.toStdString();
//            out << qExpir;
//            arr_users[i].sub.expiry = qExpir.toStdString();;
//        }
//        else if (arr_users[i].sub.fixed == 'n') {
//            out << qSubsctype;
//            arr_users[i].sub.subscription_type = qSubsctype.toStdString();
//            out << arr_users[i].sub.zone
//                << arr_users[i].sub.zonePrice;
//                
//            out << qactivation;
//            arr_users[i].sub.activation = qactivation.toStdString();
//
//            out << arr_users[i].sub.balancew;
//
//
//        }
//    }
//
//    file.close();
//}
//
//void load_user_subsc() {
//    QFile file("subsc.txt");
//    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
//        cout << "No subscription data found!" << endl;
//        return;
//    }
//
//    QTextStream in(&file);
//    QString qUsername, qid, qSubsctype, qplantype, qactivation, qExpir;
//    for (int i = 0; i < number_of_users_in_array; i++) {
//        in >> arr_users[i].sub.fixed;
//        
//        in <<qUsername;
//        arr_users[i].username = qUsername.toStdString();
//
//        in >> qid;
//        arr_users[i].id = qid.toStdString();
//
//        if (arr_users[i].sub.fixed == 'y') {
//            in >> qSubsctype;
//            arr_users[i].sub.subscription_type= qSubsctype.toStdString();
//              
//                
//            in >> qplantype;
//            arr_users[i].sub.plan_type = qplantype.toStdString();
//                
//            in >> arr_users[i].sub.duriation_plan_type
//                >> arr_users[i].sub.Num_trips
//                >> arr_users[i].sub.remaining_trips
//                >> arr_users[i].sub.zone
//                >> arr_users[i].sub.zonePrice;
//
//
//            in >> qactivation;
//            arr_users[i].sub.activation = qactivation.toStdString();
//            in >> qExpir;
//            arr_users[i].sub.expiry= qExpir.toStdString();;
//        }
//        else if (arr_users[i].sub.fixed == 'n') {
//            in >> qSubsctype;
//            arr_users[i].sub.subscription_type = qSubsctype.toStdString();
//            in >> arr_users[i].sub.zone
//                >> arr_users[i].sub.zonePrice;
//               
//            in >> qactivation;
//             arr_users[i].sub.activation = qactivation.toStdString();
//              
//             in>> arr_users[i].sub.balancew;
//        }
//
//        in.readLine(); // to consume leftover newline
//    }
//
//    file.close();
//}
//
////history rides 


///-----         STATIONS PART          ----///

void read_stations() {
    ifstream input_stations("stations.txt");
    if (!input_stations.is_open()) {
        cout << "Error: Could not open stations.txt\n";
        return;
    }

    input_stations.ignore(1000, '\n');

    for (int i = 0; i < MAX_STATIONS_PER_LINE; i++) {
        for (int j = 0; j < NUM_LINES; j++) {
            input_stations >> allStations[i][j].name;
            if (allStations[i][j].name != "-" || allStations[i][j].name != "Switching.") {
                num_stations++;
            }
            allStations[i][j].number = (j * MAX_STATIONS_PER_LINE) + (i + 1);
            allStations[i][j].line = j + 1;
        }
    }

    input_stations.close();
}


void stations2file() {
    ofstream output("stations.txt", ios::out);
    if (!output.is_open()) {
        cout << "Error: Could not open stations.txt for writing\n";
        return;
    }

    output << "line 1" << "  \t\t\t\tline 2" << "  \t\t\t\t\tline 3" << endl << endl;

    for (int i = 0; i < MAX_STATIONS_PER_LINE; i++) {
        for (int j = 0; j < NUM_LINES; j++) {
            output << left << setw(20) << allStations[i][j].name << "\t";
        }
        output << endl;
    }

    output.close();
}






//history 

void loadRideHist() {
    QFile file("history rides.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "🚫 No ride history found yet.";
        return;
    }

    QTextStream in(&file);
    ride_cnt = 0;

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty())
            continue;

        QTextStream linestream(&line);
        QString id, entry, exit, date;
        float fare;

        linestream >> id >> entry >> exit >> fare >> date;

        rides[ride_cnt].id = id.toStdString();
        rides[ride_cnt].entryStation = entry.toStdString();
        rides[ride_cnt].ExitStation = exit.toStdString();
        rides[ride_cnt].RideFare = fare;
        rides[ride_cnt].Date = date.toStdString();

        // Debug
        qDebug() << "📦 Loaded ride:" << id << entry << exit << fare << date;

        ride_cnt++;
    }

    file.close();
}

void save_rides_to_file() {
    QFile file("history rides.txt");

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << " Error opening file for writing!";
        return;
    }

    QTextStream out(&file);

    for (int i = 0; i < ride_cnt; ++i) {
        out << QString::fromStdString(rides[i].id) << "     "
            << QString::fromStdString(rides[i].entryStation) << "     "
            << QString::fromStdString(rides[i].ExitStation) << "     "
            << rides[i].RideFare << "     "
            << QString::fromStdString(rides[i].Date) << "\n";
    }

    file.close();
    qDebug() << "Rides saved to file successfully.";
}