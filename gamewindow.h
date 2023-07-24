#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <gamechoose.h>
#include <item.h>

#include <QApplication>
#include <QMainWindow>
#include <QProgressBar>
#include <QVector>

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow {
    Q_OBJECT

   public:
    explicit GameWindow(int rows, int cols, int bombNum);
    void startMyGame();
    void endGame();
    void initMyGame();
    void paintEvent(QPaintEvent *);  // 重定义绘图事件
    void updateWindow(QPainter *p, item *it);
    void gameover();
    void mousePressEvent(QMouseEvent *event);
    void dfs(QPoint pt);
    bool victory();
    ~GameWindow();
    QProgressBar *progressBar;
    QPushButton *returnButton;
    gameChoose *chosce = nullptr;
    int openCount;
    int flagCount;
    QTimer *timer2;
    void closeEvent(QCloseEvent *event) {
        event->accept();  // 允许窗口关闭

        // 在关闭事件处理结束后删除窗口对象
        QTimer::singleShot(0, this, &GameWindow::deleteLater);
    }

   protected:
    void timerEvent(QTimerEvent *event);

   private:
    int timerId;
    int seconds;
    QPixmap flagImg;
    QPixmap bombImg;
    int rows;
    int cols;
    int bombNum;
    QVector<QPoint> Mines;
    QVector<QVector<item *>> items;
    bool ifDead;
    Ui::GameWindow *ui;
    bool pause;
};

#endif  // GAMEWINDOW_H
