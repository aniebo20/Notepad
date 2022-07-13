#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w; //Creates the main application object
    w.show(); //displays the object on the screen
    return a.exec(); //puts application into a loop where different events are handled
}
