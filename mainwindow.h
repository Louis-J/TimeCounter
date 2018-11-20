#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <thread>
#include <QThread>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QVBoxLayout>
#include <QTimer>
#include <QTime>
#include <QLabel>
#include <QStandardItemModel>
#include <QSignalMapper>
#include <QMessageBox>
#include <QInputDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QSignalMapper *signalMapper;
    QString name[4]={"RNG-xm","NMD-2","赛博人队","FB2"};
    QString header[4]={"队名","小积分","大积分","比赛场次"};


signals:
public slots:
    void time_onTimerOut();
    void time_set(int settime);
    void time_startorpause();
    void time_end();
private:
    int timedist=0;
    int timeleft=0;
    std::thread *beep1;
    std::thread *beep2;
};

#endif // MAINWINDOW_H
