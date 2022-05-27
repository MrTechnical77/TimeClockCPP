#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_lineEdit_editingFinished()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("timeclock");
    db.setUserName("TCAdmin");
    db.setPassword("TCAdmin");
    bool ok = db.open();
    if(ok){
        QSqlQuery query("SELECT * FROM admin");
        QString username = query.value(1).toString();
        ui->lineEdit->setText(username);
    }
    else {
        ui->lineEdit->setText("Failed to Connect");
    }
}

