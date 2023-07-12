#include "gamechoose.h"
#include "editdialog.h"
#include <QPainter>
#include <QDebug>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QGroupBox>
gameChoose::gameChoose(QWidget *parent)
    : QMainWindow{parent}
{
    //设置主窗口标题
    this->setWindowTitle("Difficulty Selcetion");
    //设置主窗口icon
    this->setWindowIcon(QPixmap(":/icon/res/icon/windowtitle.png"));
    //设置固定大小
    this->setFixedSize(600,600);
    // 创建一个新的菜单栏
    QMenuBar *menuBar = new QMenuBar(this);

    // 创建一个新的菜单
    QMenu *fileMenu_more = new QMenu(tr("查看"), this);

    // 在菜单中添加两个动作
    QAction *openAction_history = new QAction(tr("history"), this);
    QIcon icon1(":/icon/res/icon/chakan.png");
    openAction_history->setIcon(icon1);
    fileMenu_more->addAction(openAction_history);
    QAction *openAction_assistant = new QAction(tr("assistant"), this);
    QIcon icon2(":/icon/res/icon/bangzhuwendang.png");
    openAction_assistant->setIcon(icon2);
    fileMenu_more->addAction(openAction_assistant);
    // 将菜单添加到菜单栏
    menuBar->addMenu(fileMenu_more);
    // 将菜单栏设置为窗口的菜单栏
    setMenuBar(menuBar);
    //排列按钮
    QGroupBox* btngrp=new QGroupBox(this);
    btngrp->setFixedSize(200,600);
    btngrp->move((this->width()-btngrp->width())/2,0);
    btngrp->setStyleSheet("border:none");
    QVBoxLayout *layout = new QVBoxLayout(btngrp);
    layout->setSpacing(10);
    layout->setContentsMargins(5,5,5,5);

    // 5个按钮
    btnDiff1=new QPushButton("简单");
    btnDiff2=new QPushButton("正常");
    btnDiff3=new QPushButton("困难");
    btnDiffDiy=new QPushButton("自定义");
    btnDiff1->setFixedSize(200,80);
    btnDiff2->setFixedSize(200,80);
    btnDiff3->setFixedSize(200,80);
    btnDiffDiy->setFixedSize(200,80);
    QFont font=btnDiff1->font();
    font.setPointSize(20);
    font.setBold(true);
    btnDiff1->setFont(font);
    btnDiff2->setFont(font);
    btnDiff3->setFont(font);
    btnDiffDiy->setFont(font);
    btnDiff1->setStyleSheet("background-color: transparent;");
    btnDiff2->setStyleSheet("background-color: transparent;");
    btnDiff3->setStyleSheet("background-color: transparent;");
    btnDiffDiy->setStyleSheet("background-color: transparent;");
    btnDiff1->setCursor(QCursor(Qt::PointingHandCursor));
    btnDiff2->setCursor(QCursor(Qt::PointingHandCursor));
    btnDiff3->setCursor(QCursor(Qt::PointingHandCursor));
    btnDiffDiy->setCursor(QCursor(Qt::PointingHandCursor));
    // 将按钮添加到布局
    layout->addWidget(btnDiff1);
    layout->addWidget(btnDiff2);
    layout->addWidget(btnDiff3);
    layout->addWidget(btnDiffDiy);
    signalAndSlotInit();

}

void gameChoose::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    //设置渐变背景
    QLinearGradient gradient(0, 0, width(), height());
    gradient.setColorAt(0.0, QColor(171,165,166));
    gradient.setColorAt(1.0, QColor(208,242,248,128));
    painter.setBrush(gradient);
    painter.drawRect(0, 0, width(), height());
}
void gameChoose::signalAndSlotInit(){
    connect(btnDiffDiy,&QPushButton::clicked,[this](){
        editDialog dlg(this);
        dlg.exec();
    });
}

gameChoose::~gameChoose()
{
}
