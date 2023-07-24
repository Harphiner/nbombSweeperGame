#ifndef GAMECHOOSE_H
#define GAMECHOOSE_H

#include <QMainWindow>
#include <QApplication>
#include <QPushButton>
#include <QCloseEvent>
#include <QTimer>

class gameChoose : public QMainWindow
{
    Q_OBJECT
public:
    gameChoose(QWidget *parent = nullptr);
    ~gameChoose();
    void paintEvent (QPaintEvent*);//重定义绘图事件
    void signalAndSlotInit();//初始化信号与槽
    void closeEvent(QCloseEvent *event)
    {
        event->accept();  // 允许窗口关闭

        // 在关闭事件处理结束后删除窗口对象
        QTimer::singleShot(0, this, &gameChoose::deleteLater);
    }

private:
    QPushButton* btnDiff1;
    QPushButton* btnDiff2;
    QPushButton* btnDiff3;
    QPushButton* btnDiffDiy;
signals:

};

#endif // GAMECHOOSE_H
