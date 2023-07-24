#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QLinearGradient>
#include <QColor>
#include <QTimer>
#include <QPushButton>
#include <QDebug>
#include <QFontDatabase>
#include "gamechoose.h"
#include "editdialog.h"
#include <gamewindow.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //用ui来初始化mainwindow
    ui->setupUi(this);
    //设置主窗口标题
    this->setWindowTitle("nbombSweeper");
    //设置主窗口icon
    this->setWindowIcon(QPixmap(":/icon/res/icon/windowtitle.png"));
    //设置固定大小
    this->setFixedSize(600,600);
    //pixbtn为切换场景按钮
    pixbtn=new QPushButton(this);
    pixbtn->setStyleSheet("background-color: transparent;");
    pixbtn->setCursor(QCursor(Qt::PointingHandCursor));
    //设置pixbtn的信号与槽
    connect(pixbtn,&QPushButton::clicked,this,[=](){
        //切换场景
        gameChoSecen = new gameChoose();
        gameChoSecen->show();
        this->~MainWindow();
    });
    this->pixbtn->setFixedSize(118,50);
    this->pixbtn->move(241,350);
    welcomeInit();
    signalAndSlotInit();//初始化信号与槽
    qDebug()<<QString("mainwindow open");
}
//析构函数
MainWindow::~MainWindow()
{
    delete ui;
    delete pixbtn;
    //delete gameChoSecen;
   // delete mygame1;
    qDebug()<<QString("mainwindow close");
}
//绘图事件，设置背景渐变色，设置titleicon，设置startgame图片
void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    //设置渐变背景
    QLinearGradient gradient(0, 0, width(), height());
    gradient.setColorAt(0.0, QColor(171,165,166));
    gradient.setColorAt(1.0, QColor(208,242,248,128));
    painter.setBrush(gradient);
    painter.drawRect(0, 0, width(), height());
    QPixmap pix;
//    pix.load(":/image/res/image/background.jpg");
//    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/icon/res/icon/windowtitle.png");
    painter.drawPixmap(20,50,50,50,pix);
    pix.load(":/image/res/image/title_red.png");
    painter.drawPixmap(70,35,900,100,pix);
    //设置pixbtn的图片
    pix.load(":/icon/res/icon/startgame.png");
    QPixmap scaledPix = pix.scaled(118, 50, Qt::KeepAspectRatio);
    QIcon ButtonIcon(scaledPix);
    pixbtn->setIconSize(scaledPix.rect().size()); // 设置按钮图标大小为图片的大小
    pixbtn->setIcon(ButtonIcon);
}
void MainWindow::welcomeInit()
{
    // 设置欢迎信息
    QString welcomeStr = "Welcome to nbombSweeperGame!\nLet's start now!";
    int index = 0;  // 创建索引来追踪字符串中的字符
    //设置plaintext文本框透明,边框属性，并且设置字体颜色
    ui->textEdit_welcome->setStyleSheet("background-color: transparent; border: none;color:white");
    //设置字体家族
    int id = QFontDatabase::addApplicationFont(":/font/res/font/foreign/Comic Sans MS.ttf");
    QString family;
    if (id != -1) {
        family = QFontDatabase::applicationFontFamilies(id).at(0);
    }
    //设置字体
    QFont font;
    font.setFamily(family);  // 字体类型
    font.setPointSize(20);  // 字体大小
    font.setBold(true);  // 粗体
    ui->textEdit_welcome->setFont(font);
    //设置文字居中,文本框只读
    ui->textEdit_welcome->setAlignment(Qt::AlignCenter);
    ui->textEdit_welcome->setReadOnly(true);
    QTimer *timer_typeit = new QTimer(this);
    // 启动定时器，每隔500ms进行一次
    timer_typeit->start(100);
    // 关联定时器和打字机
    connect(timer_typeit, &QTimer::timeout, this,[=]() mutable {
        // 如果索引小于字符串长度，添加字符
        if (index < welcomeStr.length()) {
            QString currentText = ui->textEdit_welcome->toPlainText();
            currentText.append(welcomeStr.at(index));
            ui->textEdit_welcome->setText(currentText);
            index++;
        } else {
            // 否则，停止定时器
            timer_typeit->stop();
        }
    });

}

void MainWindow::signalAndSlotInit(){
    connect(ui->actionedit,&QAction::triggered,[this](){
        editDialog dlg(this);
        dlg.exec();
    });
    connect(ui->actioneasy,&QAction::triggered,[this](){
        mygame1=new GameWindow(10,10,10);
        mygame1->diff=QString("简单");
        mygame1->newGame();
        mygame1->show();
        this->~MainWindow();
    });
    connect(ui->actionmiddle,&QAction::triggered,[this](){
        mygame1=new GameWindow(20,20,40);
        mygame1->diff=QString("中等");
        mygame1->newGame();
        mygame1->show();
        this->~MainWindow();
    });
    connect(ui->actionhard,&QAction::triggered,[this](){
        mygame1=new GameWindow(30,30,99);
        mygame1->diff=QString("困难");
        mygame1->newGame();
        mygame1->show();
        this->~MainWindow();
    });
}
