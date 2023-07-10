#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <QFontDatabase>

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
    welcomeInit();
}
//析构函数
MainWindow::~MainWindow()
{
    delete ui;
}
//绘图事件，设置背景图片
void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/res/image/background.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/icon/res/icon/windowtitle.png");
    painter.drawPixmap(20,50,50,50,pix);
    pix.load(":/image/res/image/title_red.png");
    painter.drawPixmap(70,35,900,100,pix);
}
void MainWindow::welcomeInit()
{
    // 设置欢迎信息
    QString welcomeStr = "Welcome to nbombSweeperGame!\nLet's start now!";
    int index = 0;  // 创建索引来追踪字符串中的字符
    //设置plaintext文本框透明,边框属性，并且设置字体颜色
    ui->textEdit_welcome->setStyleSheet("background-color: transparent; border: none;color:white");
    //设置字体家族
    int id = QFontDatabase::addApplicationFont(":/font/res/font/foreign/Blackhawk-webfont.woff2.ttf");
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
