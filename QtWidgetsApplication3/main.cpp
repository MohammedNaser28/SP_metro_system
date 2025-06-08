#include<QObject>
#include "QtWidgetsApplication3.h"
#include <QApplication>
#include"register.h"
#include"data.h"
int main(int argc, char* argv[])
{
    QApplication a(argc, argv);  // Initialize the application

    ReadFromFile();  // <<< LOAD USERS BEFORE ANYTHING

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
        });

    x.show();
    return a.exec();  // Start the Qt event loop
}

//int main(int argc, char* argv[])
//{
//    QApplication a(argc, argv);  // Initialize the application
//    Register x;
//    QtWidgetsApplication3 w;      // Create the main window object
//    ReadFromFile();
//    QObject::connect(&x, &Register::switchToMainWindow, &x, [&x, &w]() {
//        x.hide();
//        w.show();
//        });
//
//    QObject::connect(&w, &QtWidgetsApplication3::switchToDialog, &w, [&x, &w]() {
//      w.hide();
//       x.show();
//        });
//
//    // Connect signal to save data whan app is about to Quit
//    QObject::connect(&a, &QCoreApplication::aboutToQuit, [&]() {
//       saveusersinfo();
//        });
//    x.show();
//    return a.exec();             // Start the Qt event loop
//}
