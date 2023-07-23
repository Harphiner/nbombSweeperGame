#ifndef GAMECHOOSE_H
#define GAMECHOOSE_H

#include <QMainWindow>
#include <QApplication>
#include <QPushButton>

class gameChoose : public QMainWindow
{
    Q_OBJECT
public:
    gameChoose(QWidget *parent = nullptr);
    ~gameChoose();
    void paintEvent (QPaintEvent*);//重定义绘图事件
    void signalAndSlotInit();//初始化信号与槽
private:
    QPushButton* btnDiff1;
    QPushButton* btnDiff2;
    QPushButton* btnDiff3;
    QPushButton* btnDiffDiy;
signals:

};

#endif // GAMECHOOSE_H
