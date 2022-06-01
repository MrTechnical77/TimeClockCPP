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
        QSqlQuery query;
        query.prepare("INSERT INTO punches (employeeID, punchTime, punchType) "
                      "VALUES(:employeeID, NOW(), :punchType)");

        QString inputEmpID = ui->lineEdit->text();
        query.bindValue(":employeeID", inputEmpID);
        query.bindValue(":punchType", 1);
        query.exec();

    }
    else {
        ui->lineEdit->setText("Failed to Connect");
    }
}










