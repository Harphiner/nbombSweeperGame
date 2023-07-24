#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <item.h>
#include <QApplication>
#include <QProgressBar>
#include <gamechoose.h>

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
    QPushButton *returnButton;
    gameChoose* chosce=nullptr;
    int openCount;
    int flagCount;
    QTimer *timer2 ;
    void closeEvent(QCloseEvent *event)
    {
        event->accept();  // 允许窗口关闭

        // 在关闭事件处理结束后删除窗口对象
        QTimer::singleShot(0, this, &GameWindow::deleteLater);
    }
protected:
    void timerEvent(QTimerEvent *event);

private:
    int timerId;
    int seconds;
    QPixmap flagimg;
    QPixmap mineimg;
    int rows;
    int cols;
    int mine;
    QVector<QPoint> Mines;
    QVector<QVector<item*>> items;
    bool isFail;
    Ui::GameWindow *ui;
    bool pause;
};

#endif // GAMEWINDOW_H
