#ifndef DBMANAGER_H
#define DBMANAGER_H

#include "qsqldatabase.h"

struct User {
    int id;
    QString name;
    QString dob;
    QByteArray avatar;
};

struct Item {
    int id;
    QString name;
    double price;
    int unitAmount;
    QString unit;
    QByteArray image;
};

struct CartItem {
    int id;
    int itemId;
    int cartId;
    int qty;
};

struct Cart {
    int id;
    int userId;
    CartItem items[];
};


class DBManager {
private:
    QSqlDatabase db;
public:
    DBManager(const QString &path);
    User *getUser(int userId);
};

#endif // DBMANAGER_H
