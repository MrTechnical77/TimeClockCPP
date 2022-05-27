#ifndef TIMECLOCK_H
#define TIMECLOCK_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class TimeClock; }
QT_END_NAMESPACE

class TimeClock : public QMainWindow
{
    Q_OBJECT

public:
    TimeClock(QWidget *parent = nullptr);
    ~TimeClock();

private:
    Ui::TimeClock *ui;
};
#endif // TIMECLOCK_H
