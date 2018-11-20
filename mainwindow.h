#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>

#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QVBoxLayout>
#include <QTimer>
#include <QTime>
#include <QMessageBox>
#include <QInputDialog>

class QLCDNumber;
class QTimer;

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
    int timegone=0;
    int timedist=0;
    int RScore=0;
    int BScore=0;
signals:
public slots:
    void onTimerOut();
    void set3();
    void set5();
    void startorpause();
    void end();
    void R1();
    void R2();
    void R3();
    void R4();
    void R5();
    void B1();
    void B2();
    void B3();
    void B4();
    void B5();
    void RedClear();
    void BlueClear();
    void RedSet();
    void BlueSet();
private:
  QTimer *timer;
  QTime *time;
};

#endif // MAINWINDOW_H
