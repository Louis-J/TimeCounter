#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "windows.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //新建一个QTimer对象
    timer = new QTimer();
    timer->setInterval(1000);

    time = NULL;


    connect(timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));
    connect(ui->three, SIGNAL(clicked()), this, SLOT(set3()));
    connect(ui->five, SIGNAL(clicked()), this, SLOT(set5()));
    connect(ui->start, SIGNAL(clicked()), this, SLOT(startorpause()));
    connect(ui->end, SIGNAL(clicked()), this, SLOT(end()));
    connect(ui->R1, SIGNAL(clicked()), this, SLOT(R1()));
    connect(ui->R2, SIGNAL(clicked()), this, SLOT(R2()));
    connect(ui->R3, SIGNAL(clicked()), this, SLOT(R3()));
    connect(ui->R4, SIGNAL(clicked()), this, SLOT(R4()));
    connect(ui->R5, SIGNAL(clicked()), this, SLOT(R5()));
    connect(ui->B1, SIGNAL(clicked()), this, SLOT(B1()));
    connect(ui->B2, SIGNAL(clicked()), this, SLOT(B2()));
    connect(ui->B3, SIGNAL(clicked()), this, SLOT(B3()));
    connect(ui->B4, SIGNAL(clicked()), this, SLOT(B4()));
    connect(ui->B5, SIGNAL(clicked()), this, SLOT(B5()));
    connect(ui->BlueClear, SIGNAL(clicked()), this, SLOT(BlueClear()));
    connect(ui->RedClear, SIGNAL(clicked()), this, SLOT(RedClear()));
    connect(ui->BlueSet, SIGNAL(clicked()), this, SLOT(BlueSet()));
    connect(ui->RedSet, SIGNAL(clicked()), this, SLOT(RedSet()));

    ui->lcdNumber->display("00:00");
    ui->RedScore->setStyleSheet("QLCDNumber{color:red}");
    ui->BlueScore->setStyleSheet("QLCDNumber{color:blue}");

}
void MainWindow::onTimerOut()
{
    timegone++;
    if(timegone>=timedist){
        Beep(800, 900);
        if(timedist==300)
            timer->stop();
        else{
            this->set5();
            this->startorpause();
        }
    }
    else if(timedist-timegone<10){
        Beep(523, 500);
    }
    //设置晶体管控件QLCDNumber上显示的内容
      QTime now=time->addSecs(-timegone);
      ui->lcdNumber->display(now.toString("mm:ss"));
}
void MainWindow::set3()
{
    time = new QTime(0,3);
    timer->stop();
    timedist=180;
    timegone=0;
    ui->lcdNumber->setStyleSheet("QLCDNumber{color:black}");
    ui->lcdNumber->display(time->toString("mm:ss"));
    ui->start->setText("开始");
}
void MainWindow::set5()
{
    time = new QTime(0,5);
    timer->stop();
    timedist=300;
    timegone=0;
    ui->lcdNumber->setStyleSheet("QLCDNumber{color:red}");
    ui->lcdNumber->display(time->toString("mm:ss"));
    ui->start->setText("开始");
}
void MainWindow::startorpause()
{
    if(timedist==0){
        ui->start->setText("傻逼");
        ui->three->setText("傻逼");
        ui->five->setText("傻逼");
        ui->end->setText("傻逼");
        this->setWindowTitle("傻逼");
        QMessageBox::information(this,"错误！","你还没设时间！");
        ui->start->setText("开始");
        ui->three->setText("3分钟");
        ui->five->setText("5分钟");
        ui->end->setText("结束");
        this->setWindowTitle("RCS计时器");
    }
    else if(timer->isActive()){
        timer->stop();
        ui->start->setText("暂停");
    }
    else{
        timer->start();
        ui->start->setText("开始");
    }
}
void MainWindow::end()
{
    if(timedist==0){
        ui->start->setText("傻逼");
        ui->three->setText("傻逼");
        ui->five->setText("傻逼");
        ui->end->setText("傻逼");
        this->setWindowTitle("傻逼");
        QMessageBox::information(this,"错误！","你还没设时间！");
        ui->start->setText("开始");
        ui->three->setText("3分钟");
        ui->five->setText("5分钟");
        ui->end->setText("结束");
        this->setWindowTitle("RCS计时器");
    }
    else{
        timegone=0;
        timer->stop();
        ui->lcdNumber->display(time->toString("mm:ss"));
        ui->start->setText("开始");
    }
}

void MainWindow::R1()
{
    RScore+=5;
    ui->RedScore->display(RScore);
}
void MainWindow::R2()
{
    RScore+=10;
    ui->RedScore->display(RScore);
}
void MainWindow::R3()
{
    RScore+=20;
    ui->RedScore->display(RScore);
}
void MainWindow::R4()
{
    RScore+=30;
    ui->RedScore->display(RScore);
}
void MainWindow::R5()
{
    RScore+=50;
    ui->RedScore->display(RScore);
}



void MainWindow::B1()
{
    BScore+=5;
    ui->BlueScore->display(BScore);
}
void MainWindow::B2()
{
    BScore+=10;
    ui->BlueScore->display(BScore);
}
void MainWindow::B3()
{
    BScore+=20;
    ui->BlueScore->display(BScore);
}
void MainWindow::B4()
{
    BScore+=30;
    ui->BlueScore->display(BScore);
}
void MainWindow::B5()
{
    BScore+=50;
    ui->BlueScore->display(BScore);
}
void MainWindow::RedClear()
{
    RScore=0;
    ui->RedScore->display(RScore);
}
void MainWindow::BlueClear()
{
    BScore=0;
    ui->BlueScore->display(BScore);
}
void MainWindow::RedSet()
{
    RScore=QInputDialog().getInt(NULL,"请输入分数","请输入分数");
    ui->RedScore->display(RScore);
}
void MainWindow::BlueSet()
{
    BScore=QInputDialog().getInt(NULL,"请输入分数","请输入分数");
    ui->BlueScore->display(BScore);
}

MainWindow::~MainWindow()
{
    delete ui;
}
