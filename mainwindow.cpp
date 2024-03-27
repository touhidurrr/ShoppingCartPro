#include "mainwindow.h"
#include "additemdialog.h"
#include "ui_mainwindow.h"

#include <QSettings>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    // load settings
    loadSettings();

    // initiate db
    _dbManager = new DBManager("test.db");

    // load user icon
    if (s_currentUserId == 0) {
        ui->userName->setText("Guest");
        ui->userIcon->setPixmap(QPixmap(":/assets/user.png"));
    } else {
        User* currentUser = _dbManager->getUser(s_currentUserId);
        if (currentUser) {
            ui->userName->setText(currentUser->name);
            ui->userIcon->setPixmap(QPixmap(currentUser->avatar));
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    saveSettings();
}

void MainWindow::initGui() {
    ui->mainContainer->layout()->setContentsMargins(0, 0, 0, 0);
    ui->windows->layout()->setContentsMargins(0, 0, 0, 0);
    ui->stackedWidget->layout()->setContentsMargins(0, 0, 0, 0);
    ui->stackedWidget->layout()->setParent(ui->windows);
}

void MainWindow::loadSettings() {
    _settingsFile = QApplication::applicationDirPath() + "/settings.ini";
    QSettings settings(_settingsFile, QSettings::NativeFormat);
    s_currentUserId = settings.value("currentUserId", 0).toInt();
}

void MainWindow::saveSettings() {
    QSettings settings(_settingsFile, QSettings::NativeFormat);
    settings.setValue("currentUserId", s_currentUserId);
}

void MainWindow::on_cartButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_historyButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_settingsButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_cartItemsAddButton_clicked()
{
    auto dialog = new AddItemDialog();
    dialog->show();
}

