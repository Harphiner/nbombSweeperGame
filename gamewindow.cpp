#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <item.h>
#include <QTime>
#include <QPainter>
#include "QRandomGenerator"
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>
#include <gamechoose.h>
#include <QFont>
#include <item.h>
#include <QRect>
#include <QMouseEvent>
#include <QMessageBox>
#include <QPixmap>
#include <QHBoxLayout>
#include <QTimer>

GameWindow::GameWindow(int rows,int cols,int mine) :
    rows(rows),cols(cols),mine(mine),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    //设置主窗口标题
    this->setWindowTitle("GameWindow");
    //设置主窗口icon
    this->setWindowIcon(QPixmap(":/icon/res/icon/windowtitle.png"));
    //设置固定大小
    this->setFixedSize(600,150+rows*600/cols);
    flagimg.load(":/icon/res/icon/qizhi.png");
    mineimg.load(":/icon/res/icon/bomb.png");
        // 获取主窗口的状态栏
        QStatusBar *statusBar = this->statusBar();

        // 创建进度条，并添加到状态栏
        progressBar = new QProgressBar(this);
        progressBar->setMinimum(0);
        progressBar->setMaximum(100);
        progressBar->setValue(0); // 设置进度条当前值，你可以根据实际情况设置
        statusBar->addWidget(progressBar);


        QFont font;
        font.setPointSize(16);
        // 创建返回按钮，并添加到状态栏
        returnButton = new QPushButton("返回", this);
        returnButton->setFont(font);
        statusBar->addPermanentWidget(returnButton);

        // 连接按钮的槽函数，你可以在这里添加返回按钮的点击事件处理逻辑
        connect(returnButton, &QPushButton::clicked, [this](){
            chosce=new gameChoose();
            chosce->show();
            this->~GameWindow();
        });
        ui->groupBox->setFixedSize(600,100);
        ui->groupBox->move(0,0);
        QPixmap pixmap(":/icon/res/icon/tongyong_timu_nandu2.png");
        font.setPointSize(20);
        font.setBold(true);
        ui->timerlable->setFont(font);
        ui->counterlable->setFont(font);
        ui->imagelable->setPixmap(pixmap.scaled(60, 60, Qt::KeepAspectRatio));
        ui->counterlable->setText(QString("已插旗帜数：%1").arg(0));
        ui->timerlable->setText(QString("计时器：%1%2:%3%4").arg(0).arg(0).arg(0).arg(0));
qDebug()<<QString("gamewindow open");
}

void GameWindow::newGame(){
    isFail=false;
    releaseItems();
    initGame();
    openCount=0;
    flagCount=0;
    progressBar->setValue(0);
   seconds=0;
    pause=false;
    timerId = startTimer(1000);
    //创建一个QTimer对象
    timer2 = new QTimer(this);
    connect(timer2, &QTimer::timeout, this,[this](){
       ui->counterlable->setText(QString("已插旗帜数：%1").arg(flagCount));
    });
    timer2->start(10);
}

void GameWindow::releaseItems(){
    for(int i=0;i<items.size();i++)
    {
        for(int j=0;j<items[i].size();j++)
        {
            if(items[i][j]!=nullptr){
                delete items[i][j];
                items[i][j]=nullptr;
            }
        }
    }
    items.clear();
}

void GameWindow::initGame(){
    //初始化雷坐标
    Mines.clear();
    for(int i=0;i<mine;i++)
    {
        srand(QTime::currentTime().msec());
        int x=rand()%cols;
        int y=rand()%rows;
        while(Mines.contains(QPoint(x,y))){
             x=rand()%cols;
             y=rand()%rows;
        }
        Mines.append(QPoint(x,y));
    }
    //初始化格子类
    for(int i=0;i<cols;i++)
    {
        QVector<item*> rowItems;
        for(int j=0;j<rows;j++)
        {
             QPoint pos=QPoint(i,j);
             item* it= new item(pos);
             if(Mines.contains(pos))
             {
                it->isMine=true;
             }
             rowItems.append(it);
        }
        items.append(rowItems);
    }
    //初始化数字
    for(int i=0;i<cols;i++)
    {
        for(int j=0;j<rows;j++)
        {
             if(items[i][j]->isMine)
             {continue;}
             int Count=0;
             for(int m=-1;m<=1;m++)
             {
                for(int n=-1;n<=1;n++)
                {
                    if(m==0&&n==0)
                    {
                        continue;
                    }
                    QPoint nei(i+m,j+n);
                    if(i+m<0||j+n<0||i+m>=cols||j+n>=rows)
                    {
                        continue;
                    }
                    if(items[i+m][j+n]->isMine)
                    {
                        Count++;
                    }
                }
             }
             items[i][j]->number=Count;
        }
    }
}

void GameWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    //设置渐变背景
    QLinearGradient gradient(0, 0, width(), height());
    gradient.setColorAt(0.0, QColor(171,165,166));
    gradient.setColorAt(1.0, QColor(208,242,248,128));
    painter.setBrush(gradient);
    painter.drawRect(0, 0, width(), height());
    painter.end();
    //设置格子
    QPainter p=QPainter(this);
    QPainter* pp=&p;
    pp->setPen(Qt::black);
    for(int i=0;i<cols;i++)
    {
        for(int j=0;j<rows;j++)
        {
             drawItem(pp,items[i][j]);
             //p.drawRect(items[i][j]->my_pos.x()*600/cols,100+items[i][j]->my_pos.y()*600/rows,600/cols,600/rows);
        }
    }
    update();
}

void GameWindow::drawItem(QPainter* p,item* it)
{
    if(it->isMarked)
    {
        if(isFail)
        {
             QRect rcSrc(0,0,flagimg.width(),flagimg.height());
             QRect rcTar(0+it->my_pos.x()*600.0/cols+2,100+it->my_pos.y()*600.0/cols+2,600.0/cols-4,600.0/cols-4);
             p->drawPixmap(rcTar,mineimg,rcSrc);
        }
        else
        {
             QRect rcSrc(0,0,flagimg.width(),flagimg.height());
             QRect rcTar(0+it->my_pos.x()*600.0/cols+2,100+it->my_pos.y()*600.0/cols+2,600.0/cols-4,600.0/cols-4);
             p->drawPixmap(rcTar,flagimg,rcSrc);
        }
        p->setBrush(Qt::transparent);
        p->drawRect(it->my_pos.x()*600.0/cols,100+it->my_pos.y()*600.0/cols,600.0/cols,600.0/cols);
        return;
    }
    else if(it->isOpen)
    {
        if(it->number==0)
        {
             p->setBrush(Qt::white);
             p->setPen(Qt::black);
        }else
        {
             QFont font;
             font.setPointSize(200/cols);
             font.setBold(true);
             font.setStyleName("color:red");
             p->setBrush(Qt::white);
             p->drawRect(it->my_pos.x()*600/cols,100+it->my_pos.y()*600.0/cols,600/cols,600.0/cols);
             p->setBrush(Qt::black);
             p->setFont(font);
             p->drawText(it->my_pos.x()*600/cols+200/cols,100+it->my_pos.y()*600.0/cols+400/cols,QString("%1").arg(it->number));
             return;
        }
    }
    else
    {
        p->setBrush(Qt::darkGray);
    }
    p->drawRect(it->my_pos.x()*600/cols,100+it->my_pos.y()*600.0/cols,600/cols,600.0/cols);
}

void GameWindow::mousePressEvent(QMouseEvent *event){
    QPoint pt;
    int x=event->pos().x()/(600/cols);
    int y=(event->pos().y()-100)/(600.0/cols);
    pt.setX(x);
    pt.setY(y);
    if(x<0||x>=cols||event->pos().y()<100||y>=rows) return;
    item*it=items[x][y];
    if(event->button()==Qt::LeftButton)
    {
        if(!it->isMarked&&!it->isOpen)
        {
             if(it->isMine)
             {
                gameover();
                pause=true;
                QMessageBox::StandardButton ret;
                ret=QMessageBox::information(nullptr,"游戏结束","是否要重新开始？",QMessageBox::Yes,QMessageBox::No);
                if(ret==QMessageBox::Yes)
                {
                    newGame();
                }else
                {
                    QApplication::quit();
                }
                return;
             }
             else
             {
                it->isOpen=true;
                openCount++;
                 progressBar->setValue(openCount*100/(rows*cols-mine));
                if(it->number==0)
                {
                    openEmptyItem(pt);
                }
                if(findAll())
                {
                    pause=true;
                    QMessageBox::StandardButton ret;
                     ret=QMessageBox::information(nullptr,"游戏结束","游戏胜利！是否要重新开始？",QMessageBox::Yes,QMessageBox::No);
                    if(ret==QMessageBox::Yes)
                     {
                        newGame();
                     }
                    else
                    {
                        QApplication::quit();
                    }
                     return;
                }
             }
        }
    }
    else if(event->button()==Qt::RightButton)
    {
        if(it->isMarked)
        {
             it->isMarked=false;
             openCount--;
             flagCount--;
              progressBar->setValue(openCount*100/(rows*cols-mine));
        }else if(!it->isOpen)
        {
             it->isMarked=true;
              openCount++;
             flagCount++;
              progressBar->setValue(openCount*100/(rows*cols-mine));
                if(findAll())
                {
                 pause=true;
                    QMessageBox::StandardButton ret;
                     ret=QMessageBox::information(nullptr,"游戏结束","游戏胜利！是否要重新开始？",QMessageBox::Yes,QMessageBox::No);
                    if(ret==QMessageBox::Yes)
                     {
                        newGame();
                     }
                    else
                    {
                        QApplication::quit();
                    }
                     return;
                }
        }
    }
}

bool GameWindow::findAll()
{
    for(int i=0;i<items.size();i++)
    {
        for(int j=0;j<items[i].size();j++)
        {
                item*it =items[i][j];
                if(it->isMine)
                {
                     if(!it->isMarked)
                     {
                        return false;
                     }
                }
                else
                {
                     if(!it->isOpen)
                     {
                        return false;
                     }
                }
        }
    }
    return true;
}

void GameWindow::openEmptyItem(QPoint pt)
{
    QPoint ptNow=pt;
    QVector<QPoint> directions;
    directions.push_back(QPoint(-1,0));
    directions.push_back(QPoint(0,1));
    directions.push_back(QPoint(1,0));
    directions.push_back(QPoint(1,0));
    directions.push_back(QPoint(0,-1));
    directions.push_back(QPoint(0,-1));
    directions.push_back(QPoint(-1,0));
    directions.push_back(QPoint(-1,0));
    for(int i=0;i<8;i++)
    {
        ptNow+=directions[i];
        if(ptNow.x()<0||ptNow.x()>=cols||ptNow.y()<0||ptNow.y()>=rows) continue;
        item* it=items[ptNow.x()][ptNow.y()];
        if(!it->isMine&&!it->isOpen&&!it->isMarked)
        {
                it->isOpen=true;
                 openCount++;
                 progressBar->setValue(openCount*100/(rows*cols-mine));
                if(it->number==0)
                {
                     openEmptyItem(ptNow);
                }
        }
    }
}

void GameWindow::gameover()
{
    isFail=true;
    for(int i=0;i<items.size();i++)
    {
        for(int j=0;j<items[i].size();j++)
        {
                if(items[i][j]->isMine)
                {
                     items[i][j]->isMarked=true;

                }
                else
                {
                     items[i][j]->isMarked=false;
                     items[i][j]->isOpen=true;

                }
        }
    }
}

GameWindow::~GameWindow()
{
    delete ui;
    //delete chosce;
    delete returnButton;
    delete progressBar;
    delete timer2;
    releaseItems();
    qDebug()<<QString("gamewindow close");
}

void GameWindow::timerEvent(QTimerEvent *event) {
    if (event->timerId() == timerId&&(!pause)) {
        seconds++;

        int secondss = seconds % 60;
        int secondsm = seconds / 60;
        int seLow = secondss % 10;
        int seHig = secondss / 10;
        int miLow = secondsm % 10;
        int miHig = secondsm / 10;
        ui->timerlable->setText(QString("计时器：%1%2:%3%4").arg(miHig).arg(miLow).arg(seHig).arg(seLow));
    }
}
