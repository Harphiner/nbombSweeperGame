#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPushButton>
#include "gamechoose.h"
#include <gamewindow.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT  //引入宏，实现信号与槽

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent*);//重定义绘图事件
    void welcomeInit();
    void signalAndSlotInit();//初始化信号与槽
    QPushButton* pixbtn=nullptr;
private:
    Ui::MainWindow *ui;//引入ui
    gameChoose* gameChoSecen=nullptr;
    GameWindow* mygame1=nullptr;
};
#endif // MAINWINDOW_H
