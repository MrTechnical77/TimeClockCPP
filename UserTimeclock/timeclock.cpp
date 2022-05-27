#include "timeclock.h"
#include "./ui_timeclock.h"

TimeClock::TimeClock(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TimeClock)
{
    ui->setupUi(this);
}

TimeClock::~TimeClock()
{
    delete ui;
}

