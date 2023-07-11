#include "gamechoose.h"
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
    btngrp->setFixedSize(600,600);
    QVBoxLayout *layout = new QVBoxLayout(btngrp);
    layout->setSpacing(10);
    layout->setContentsMargins(5,5,5,5);

    // 5个按钮
    btnDiff1=new QPushButton("easy");
    btnDiff2=new QPushButton("normal");
    btnDiff3=new QPushButton("hard");
    btnDiffDiy=new QPushButton("diy");
    btnDiffSaved=new QPushButton("saved");
    // 将按钮添加到布局
    layout->addWidget(btnDiff1);
    layout->addWidget(btnDiff2);
    layout->addWidget(btnDiff3);
    layout->addWidget(btnDiffDiy);
    layout->addWidget(btnDiffSaved);
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
gameChoose::~gameChoose()
{
}
