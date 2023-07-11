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
protected:
    void closeEvent(QCloseEvent *event)  {
        if(event==nullptr){qDebug()<<"harphiner";}
        QApplication::quit();  // 关闭整个应用程序
    }
private:
    QPushButton* btnDiff1;
    QPushButton* btnDiff2;
    QPushButton* btnDiff3;
    QPushButton* btnDiffDiy;
    QPushButton* btnDiffSaved;
signals:

};

#endif // GAMECHOOSE_H
