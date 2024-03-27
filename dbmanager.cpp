#include "dbmanager.h"

#include <QtSql>
#include <QFile>
#include <QMessageBox>


DBManager::DBManager(const QString& path)
{
    if (!path.endsWith(".db")) {
        qCritical() << "Given path '" << path << "' does not end with '.db'";
        QMessageBox::critical(0, "Database Error", "Database path does not end with '.db'");
    }

    bool isNewDatabase = !QFile::exists(path);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);

    if (!db.open()) {
        qCritical() << "Database connection failed.";
        QMessageBox::critical(0, "Database Error", "Database connection failed.");
    }
    else qDebug() << "Database connection ok";

    qDebug() << isNewDatabase;

    if (isNewDatabase) {
        QSqlQuery query(db);

        // enable foreign keys
        query.exec("PRAGMA foreign_keys = ON");
        query.finish();

        // save contents of main.sql to queryStr
        QFile qf(":sql/main.sql");
        qf.open(QIODevice::ReadOnly);
        QString queryStr(qf.readAll());
        qf.close();

        // execute queries

        QStringList qList =  queryStr.trimmed().split(';', Qt::SkipEmptyParts);
        foreach(const QString &s, qList) {
            query.exec(s);
            if(query.lastError().type() != QSqlError::NoError) qDebug() << query.lastError().text();
            query.finish();
        }
    }
}

User* DBManager::getUser(int userId) {
    QSqlQuery query(db);
    query.prepare( "select (name, dob, avatar) from users where id = :id" );
    query.bindValue( ":id", userId );
    if( !query.exec() ) {
        qDebug() << "DBError: User#" << userId << " couldn't be fetched:\n"
                 << query.lastError();
        return nullptr;
    }
    query.first();

    User *user = new User;
    user->id = userId;
    user->name = query.value(0).toString();
    user->dob = query.value(1).toString();
    user->avatar = query.value(2).toByteArray();
    query.finish();
    return user;
}
