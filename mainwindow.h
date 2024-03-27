#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dbmanager.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_cartButton_clicked();

    void on_historyButton_clicked();

    void on_settingsButton_clicked();

    void on_cartItemsAddButton_clicked();

private:
    Ui::MainWindow *ui;
private:
    void initGui();

    void loadSettings();

    void saveSettings();

private:
    QString _settingsFile;
    DBManager* _dbManager;

    int s_currentUserId;
};
#endif // MAINWINDOW_H
