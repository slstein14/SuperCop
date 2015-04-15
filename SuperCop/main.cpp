//Alex Portolese and Sam Stein
//This file contains the coding to start the app.
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setKeyboardInputInterval(10);
    MainWindow w;
    w.show();

    return a.exec();
}//Runs the program
