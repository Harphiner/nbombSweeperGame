#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <item.h>
#include <QApplication>
#include <gamechoose.h>
#include <QProgressBar>

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(int rows,int cols,int mine);
    void newGame();
    void releaseItems();
    void initGame();
     void paintEvent (QPaintEvent*);//重定义绘图事件
    void drawItem(QPainter* p,item* it);
     void gameover();
    void mousePressEvent(QMouseEvent * event);
     void openEmptyItem(QPoint pt);
    bool findAll();
    ~GameWindow();
    QString diff;
    QProgressBar *progressBar;
   // QTimer *timer2 ;
protected:
//    void timerEvent(QTimerEvent *event);

private:
    //int timerId;
    //int seconds;
    QPixmap flagimg;
    QPixmap mineimg;
    int rows;
    int cols;
    int mine;
    QVector<QPoint> Mines;
    QVector<QVector<item*>> items;
    bool isFail;
    int openCount;
    //int flagCount;
    Ui::GameWindow *ui;
    //bool pause=false;
};

#endif // GAMEWINDOW_H
