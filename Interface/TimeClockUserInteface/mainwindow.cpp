#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QTimer>
#include <QApplication>


QSqlDatabase db;
QFont inputIDLine("Comic Sans", 36);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("timeclock");
    db.setUserName("TCAdmin");
    db.setPassword("TCAdmin");
    ui->lineEdit->setFont(inputIDLine);

}

MainWindow::~MainWindow()
{
    delete ui;
}

// Start Shift button
void MainWindow::on_pushButton_clicked()
{
    QString inputEmpID = ui->lineEdit->text();
    bool openDB = db.open();
    if(openDB){
        QSqlQuery punchInQuery;
        punchInQuery.prepare("INSERT INTO punches (employeeID, punchTime, punchType) "
                             "VALUES(:employeeID, NOW(), 1)");

        punchInQuery.bindValue(":employeeID", inputEmpID);
        bool punchAccepted = punchInQuery.exec();
        if(punchAccepted){
            QMessageBox::information(
                        this,
                        tr("TimeClock"),
                        tr("Punch Accepted")
                        );
        }
        else {
            QMessageBox::information(
                        this,
                        tr("TimeClock"),
                        tr("Punch Denied")
                        );
        }

        ui->lineEdit->setText("");

    }
    else {
        ui->lineEdit->setText("Failed to open Database");
    }
}

// Start Lunch
void MainWindow::on_pushButton_2_clicked()
{
    QString inputEmpID = ui->lineEdit->text();
    bool openDB = db.open();
    if(openDB){
        QSqlQuery punchInQuery;
        punchInQuery.prepare("INSERT INTO punches (employeeID, punchTime, punchType) "
                             "VALUES(:employeeID, NOW(), 3)");

        punchInQuery.bindValue(":employeeID", inputEmpID);
        bool punchAccepted = punchInQuery.exec();
        if(punchAccepted){
            QMessageBox::information(
                        this,
                        tr("TimeClock"),
                        tr("Punch Accepted")
                        );
        }
        else {
            QMessageBox::information(
                        this,
                        tr("TimeClock"),
                        tr("Punch Denied")
                        );
        }

        ui->lineEdit->setText("");

    }
    else {
        ui->lineEdit->setText("Failed to open Database");
    }
}

// End lunch button
void MainWindow::on_pushButton_3_clicked()
{
    QString inputEmpID = ui->lineEdit->text();
    bool openDB = db.open();
    if(openDB){
        QSqlQuery punchInQuery;
        punchInQuery.prepare("INSERT INTO punches (employeeID, punchTime, punchType) "
                             "VALUES(:employeeID, NOW(), 4)");

        punchInQuery.bindValue(":employeeID", inputEmpID);
        bool punchAccepted = punchInQuery.exec();
        if(punchAccepted){
            QMessageBox::information(
                        this,
                        tr("TimeClock"),
                        tr("Punch Accepted")
                        );
        }
        else {
            QMessageBox::information(
                        this,
                        tr("TimeClock"),
                        tr("Punch Denied")
                        );
        }

        ui->lineEdit->setText("");

    }
    else {
        ui->lineEdit->setText("Failed to open Database");
    }
}

// End shift button
void MainWindow::on_pushButton_4_clicked()
{
    QString inputEmpID = ui->lineEdit->text();
    bool openDB = db.open();
    if(openDB){
        QSqlQuery punchInQuery;
        punchInQuery.prepare("INSERT INTO punches (employeeID, punchTime, punchType) "
                             "VALUES(:employeeID, NOW(), 2)");

        punchInQuery.bindValue(":employeeID", inputEmpID);
        bool punchAccepted = punchInQuery.exec();
        if(punchAccepted){
            QMessageBox::information(
                        this,
                        tr("TimeClock"),
                        tr("Punch Accepted")
                        );
        }
        else {
            QMessageBox::information(
                        this,
                        tr("TimeClock"),
                        tr("Punch Denied")
                        );
        }

        ui->lineEdit->setText("");

    }
    else {
        ui->lineEdit->setText("Failed to open Database");
    }
}

