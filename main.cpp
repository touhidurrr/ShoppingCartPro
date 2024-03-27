#include "mainwindow.h"

#include <QApplication>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("Md. Touhidur Rahman");
    QCoreApplication::setApplicationName("ShoppingCartPro");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
