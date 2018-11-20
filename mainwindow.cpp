#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "windows.h"//Beep

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //新建一个QTimer对象
    timer = new QTimer();
    timer->setInterval(1000);
    signalMapper = new QSignalMapper(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(time_onTimerOut()));

    signalMapper->setMapping(ui->time_3, 3);
    signalMapper->setMapping(ui->time_7, 7);
    signalMapper->setMapping(ui->time_10, 10);
    connect(ui->time_3, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->time_7, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(ui->time_10, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(time_set(int)));
    connect(ui->time_start, SIGNAL(clicked()), this, SLOT(time_startorpause()));
    connect(ui->time_end, SIGNAL(clicked()), this, SLOT(time_end()));


    ui->time_lcd->display("00:00");
    ui->time_lcd->setStyleSheet("QLCDNumber{color:black}");

    //一、添加表头：
    QStandardItemModel  *model = new QStandardItemModel();
    model->setColumnCount(4);
    for(int i = 0; i < 4; i++)
        model->setHeaderData(i,Qt::Horizontal,header[i]);
    //二、设置表格属性：
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//均分列
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);//均分行
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//设置整行选中
    //三、添加行
    for(int i = 0; i < 4; i++)
    {
        model->setItem(i,0,new QStandardItem(name[i]));
        model->item(i,0)->setForeground(QBrush(QColor(255, 0, 0)));//设置字符颜色
        model->item(i,0)->setTextAlignment(Qt::AlignCenter);//设置字符位置
        model->item(i,0)->setEditable(true);
        for(int j = 1; j < 4; j++){
            model->setItem(i,j,new QStandardItem(QString("0")));
            model->item(i,j)->setTextAlignment(Qt::AlignCenter);
            //model->item(i,j)->setAccessibleDescription();
            model->item(i,j)->setAccessibleText("0123456789");
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::time_onTimerOut()
{
    timeleft--;
    if(timeleft==0){
        std::thread(Beep,800,900).detach();
        ui->time_lcd->setStyleSheet("QLCDNumber{color:black}");
        if(timedist==3*60){
            this->time_set(7);
            this->time_startorpause();
        }
        else if(timedist==7*60){
            this->time_set(10);
            this->time_startorpause();
        }
        else{
            timer->stop();
            ui->time_start->setText("开始");
        }
    }
    else if(timeleft<=10){
        std::thread(Beep,523,500).detach();
        ui->time_lcd->setStyleSheet("QLCDNumber{color:red}");
    }
    //设置晶体管控件QLCDNumber上显示的内容
    QTime now(0,0,timeleft);
    ui->time_lcd->display(QTime(0,timeleft/60,timeleft%60).toString("mm:ss"));
}
void MainWindow::time_set(int settime)
{
    timer->stop();
    timedist=settime*2;
    timeleft=settime*2;
    ui->time_lcd->setStyleSheet("QLCDNumber{color:black}");
    ui->time_lcd->display(QTime(0,timeleft/60,timeleft%60).toString("mm:ss"));
    ui->time_start->setText("开始");
}
void MainWindow::time_startorpause()
{
    if(timeleft==0){
//        ui->time_3->setText("傻逼");
//        ui->time_7->setText("傻逼");
//        ui->time_10->setText("傻逼");
//        ui->time_start->setText("傻逼");
//        ui->time_end->setText("傻逼");
//        this->setWindowTitle("傻逼");
        QMessageBox::information(this,"错误！","你还没设时间！");
//        ui->time_start->setText("开始");
//        ui->time_3->setText("3分钟");
//        ui->time_7->setText("7分钟");
//        ui->time_10->setText("10分钟");
//        ui->time_end->setText("结束");
//        this->setWindowTitle("计时器");
    }
    else if(timer->isActive()){
        timer->stop();
        ui->time_start->setText("开始");
    }
    else{
        timer->start();
        ui->time_start->setText("暂停");
    }
}
void MainWindow::time_end()
{
    if(timeleft==0){
//        ui->time_3->setText("傻逼");
//        ui->time_7->setText("傻逼");
//        ui->time_10->setText("傻逼");
//        ui->time_start->setText("傻逼");
//        ui->time_end->setText("傻逼");
//        this->setWindowTitle("傻逼");
        QMessageBox::information(this,"错误！","你还没开始！");
//        ui->time_start->setText("开始");
//        ui->time_3->setText("3分钟");
//        ui->time_7->setText("7分钟");
//        ui->time_10->setText("10分钟");
//        ui->time_end->setText("结束");
//        this->setWindowTitle("计时器");
    }
    else{
        timeleft=0;
        timer->stop();
        ui->time_lcd->display(QTime(0,timeleft/60,timeleft%60).toString("mm:ss"));
        ui->time_lcd->setStyleSheet("QLCDNumber{color:black}");
        ui->time_start->setText("开始");
    }
}


