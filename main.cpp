#include "mainwindow.h"
#include <QApplication>

#include <list>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    std::list<unsigned>  amount;
    std::list<float> time;
/*
    amount.push_back(100);
    amount.push_back(1800);
    amount.push_back(1200);
    amount.push_back(10);

    time.push_back(1);
    time.push_back(10);
    time.push_back(120);
    time.push_back(10);

    w.initValues(amount, time);
*/
    w.show();
    return a.exec();
}
