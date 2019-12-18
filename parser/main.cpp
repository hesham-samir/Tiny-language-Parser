#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setGeometry(QRect(350,200,700,500));
    w.showMaximized();
    //w.show();

    return a.exec();
}
