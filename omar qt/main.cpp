#include<QObject>
#include "QtWidgetsApplication3.h"
#include <QApplication>
#include"register.h"
#include"data.h"
//last one 
int main(int argc, char* argv[])
{
    QApplication a(argc, argv);  // Initialize the application

    ReadFromFile();  // <<< LOAD USERS BEFORE ANYTHING
    load_subsc_data();
    load_user_subsc();//problem is here dont use it 
    read_stations();  //LOAD STATIONS
    loadRideHist();
   

    Register x;
    QtWidgetsApplication3 w;

    QObject::connect(&x, &Register::switchToMainWindow, &x, [&x, &w]() {
        x.hide();
        w.show();
        });

    QObject::connect(&w, &QtWidgetsApplication3::switchToDialog, &w, [&x, &w]() {
        w.hide();
        x.show();
        });

    QObject::connect(&a, &QCoreApplication::aboutToQuit, [&]() {
        saveusersinfo();
        save_subsc_data();
        save_user_subsc();
        save_rides_to_file();
        });

    x.show();
    return a.exec();  // Start the Qt event loop
}





//#include<QObject>
//#include "QtWidgetsApplication3.h"
//#include <QApplication>
//#include"register.h"
//#include"data.h"
//
//int main(int argc, char* argv[]) {
//    QApplication a(argc, argv);
//
//    // Load data in proper order
//    ReadFromFile();
//    load_subsc_data();
//    load_user_subsc();
//
//    Register x;
//    QtWidgetsApplication3 w;
//
//    // Connect signals
//    QObject::connect(&x, &Register::switchToMainWindow, &x, [&x, &w]() {
//        x.hide();
//        w.show();
//        });
//
//    QObject::connect(&w, &QtWidgetsApplication3::switchToDialog, &w, [&x, &w]() {
//        w.hide();
//        x.show();
//        });
//
//    // Save data on exit
//    QObject::connect(&a, &QCoreApplication::aboutToQuit, [&]() {
//        saveusersinfo();
//        save_subsc_data();
//        save_user_subsc();
//        qDebug() << "Application exiting - saved all data";
//        });
//
//    x.show();
//    return a.exec();
//}