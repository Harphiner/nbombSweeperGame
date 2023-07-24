#include "gamewindow.h"

#include <gamechoose.h>
#include <item.h>

#include <QFont>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QProgressBar>
#include <QPushButton>
#include <QRect>
#include <QTime>
#include <QTimer>

#include "QRandomGenerator"
#include "ui_gamewindow.h"

GameWindow::GameWindow(int rows, int cols, int bombNum)
    : rows(rows), cols(cols), bombNum(bombNum), ui(new Ui::GameWindow) {
    ui->setupUi(this);
    // 设置主窗口标题
    this->setWindowTitle("GameWindow");
    // 设置主窗口icon
    this->setWindowIcon(QPixmap(":/icon/res/icon/windowtitle.png"));
    // 设置固定大小
    this->setFixedSize(600, 150 + rows * 600 / cols);
    flagImg.load(":/icon/res/icon/qizhi.png");
    bombImg.load(":/icon/res/icon/bomb.png");
    // 获取主窗口的状态栏
    QStatusBar* statusBar = this->statusBar();

    // 创建进度条，并添加到状态栏
    progressBar = new QProgressBar(this);
    progressBar->setMinimum(0);
    progressBar->setMaximum(100);
    progressBar->setValue(0);  // 设置进度条当前值，你可以根据实际情况设置
    statusBar->addWidget(progressBar);

    QFont font;
    font.setPointSize(16);
    // 创建返回按钮，并添加到状态栏
    returnButton = new QPushButton("返回", this);
    returnButton->setFont(font);
    statusBar->addPermanentWidget(returnButton);

    // 连接按钮的槽函数，你可以在这里添加返回按钮的点击事件处理逻辑
    connect(returnButton, &QPushButton::clicked, [this]() {
        chosce = new gameChoose();
        chosce->show();
        this->~GameWindow();
    });
    ui->groupBox->setFixedSize(600, 100);
    ui->groupBox->move(0, 0);
    QPixmap pixmap(":/icon/res/icon/tongyong_timu_nandu2.png");
    font.setPointSize(20);
    font.setBold(true);
    ui->timerlable->setFont(font);
    ui->counterlable->setFont(font);
    ui->imagelable->setPixmap(pixmap.scaled(60, 60, Qt::KeepAspectRatio));
    ui->counterlable->setText(QString("已插旗帜数：%1").arg(0));
    ui->timerlable->setText(QString("计时器：%1%2:%3%4").arg(0).arg(0).arg(0).arg(0));
    qDebug() << QString("gamewindow open");
}

void GameWindow::startMyGame() {
    ifDead = false;
    endGame();
    initMyGame();
    openCount = 0;
    flagCount = 0;
    progressBar->setValue(0);
    seconds = 0;
    pause = false;
    timerId = startTimer(1000);
    // 创建一个QTimer对象
    timer2 = new QTimer(this);
    connect(timer2, &QTimer::timeout, this,
            [this]() { ui->counterlable->setText(QString("已插旗帜数：%1").arg(flagCount)); });
    timer2->start(10);
}

void GameWindow::endGame() {
    for (int i = 0; i < items.size(); i++) {
        for (int j = 0; j < items[i].size(); j++) {
            if (items[i][j] != nullptr) {
                delete items[i][j];
                items[i][j] = nullptr;
            }
        }
    }
    items.clear();
}

void GameWindow::initMyGame() {
    // 初始化雷坐标
    Mines.clear();
    while (Mines.size() < bombNum) {
        QPoint p(rand() % cols, rand() % rows);
        if (!Mines.contains(p)) Mines.append(p);
    }
    // 初始化格子类
    for (int i = 0; i < cols; i++) {
        QVector<item*> rowsRect;
        for (int j = 0; j < rows; j++) {
            QPoint pos = QPoint(i, j);
            item* it = new item(pos);
            it->isBomb = Mines.contains(pos);
            rowsRect.append(it);
        }
        items.append(rowsRect);
    }
    // 初始化数字
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            if (items[i][j]->isBomb) {
                continue;
            }
            int Count = 0;
            for (int m = -1; m <= 1; m++) {
                for (int n = -1; n <= 1; n++) {
                    if (m == 0 && n == 0) {
                        continue;
                    }
                    QPoint nei(i + m, j + n);
                    if (i + m < 0 || j + n < 0 || i + m >= cols || j + n >= rows) {
                        continue;
                    }
                    if (items[i + m][j + n]->isBomb) {
                        Count++;
                    }
                }
            }
            items[i][j]->number = Count;
        }
    }
}

void GameWindow::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    // 设置渐变背景
    QLinearGradient gradient(0, 0, width(), height());
    gradient.setColorAt(0.0, QColor(171, 165, 166));
    gradient.setColorAt(1.0, QColor(208, 242, 248, 128));
    painter.setBrush(gradient);
    painter.drawRect(0, 0, width(), height());
    painter.end();
    // 设置格子
    QPainter p = QPainter(this);
    QPainter* pp = &p;
    pp->setPen(Qt::black);
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            updateWindow(pp, items[i][j]);
            // p.drawRect(items[i][j]->my_pos.x()*600/cols,100+items[i][j]->my_pos.y()*600/rows,600/cols,600/rows);
        }
    }
    update();
}

void GameWindow::updateWindow(QPainter* p, item* it) {
    if (it->ifFlaged) {
        QRect res1(0, 0, flagImg.width(), flagImg.height());
        QRect res2(0 + it->my_pos.x() * 600.0 / cols + 2, 100 + it->my_pos.y() * 600.0 / cols + 2,
                   600.0 / cols - 4, 600.0 / cols - 4);
        p->drawPixmap(res2, ifDead ? bombImg : flagImg, res1);
        p->setBrush(Qt::transparent);
        p->drawRect(it->my_pos.x() * 600.0 / cols, 100 + it->my_pos.y() * 600.0 / cols,
                    600.0 / cols, 600.0 / cols);
    } else if (it->ifLighted) {
        if (it->number == 0) {
            p->setBrush(Qt::white);
            p->setPen(Qt::black);
        } else {
            p->setBrush(Qt::white);
            p->drawRect(it->my_pos.x() * 600 / cols, 100 + it->my_pos.y() * 600.0 / cols,
                        600 / cols, 600.0 / cols);
            p->setBrush(Qt::black);
            QFont font;
            font.setPointSize(200 / cols);
            font.setBold(true);
            font.setStyleName("color:red");

            p->setFont(font);
            p->drawText(it->my_pos.x() * 600 / cols + 200 / cols,
                        100 + it->my_pos.y() * 600.0 / cols + 400 / cols,
                        QString("%1").arg(it->number));
            return;
        }
    } else {
        p->setBrush(Qt::darkGray);
    }
    p->drawRect(it->my_pos.x() * 600 / cols, 100 + it->my_pos.y() * 600.0 / cols, 600 / cols,
                600.0 / cols);
}

void GameWindow::mousePressEvent(QMouseEvent* event) {
    QPoint pt;
    int x = event->pos().x() / (600 / cols);
    int y = (event->pos().y() - 100) / (600.0 / cols);
    pt.setX(x);
    pt.setY(y);
    if (x < 0 || x >= cols || event->pos().y() < 100 || y >= rows) return;
    item* it = items[x][y];
    if (event->button() == Qt::LeftButton) {
        if (victory()) {
            pause = true;
            QMessageBox::StandardButton ans;
            ans = QMessageBox::information(nullptr, "游戏结束", "游戏胜利！是否要重新开始？",
                                           QMessageBox::Yes, QMessageBox::No);
            if (ans == QMessageBox::Yes) {
                startMyGame();
            } else {
                QApplication::quit();
            }
            return;
        } else if (!it->ifFlaged && !it->ifLighted) {
            if (it->isBomb) {
                gameover();
                pause = true;
                QMessageBox::StandardButton ans;
                ans = QMessageBox::information(nullptr, "游戏结束", "是否要重新开始？",
                                               QMessageBox::Yes, QMessageBox::No);
                if (ans == QMessageBox::Yes) {
                    startMyGame();
                } else {
                    QApplication::quit();
                }
                return;
            } else {
                it->ifLighted = true;
                openCount++;
                progressBar->setValue(openCount * 100 / (rows * cols - bombNum));
                if (it->number == 0) {
                    bfs(pt);
                }
            }
        }
    } else if (event->button() == Qt::RightButton) {
        if (it->ifFlaged) {
            it->ifFlaged = false;
            openCount--;
            flagCount--;
            progressBar->setValue(openCount * 100 / (rows * cols - bombNum));
        } else if (!it->ifLighted) {
            it->ifFlaged = true;
            openCount++;
            flagCount++;
            progressBar->setValue(openCount * 100 / (rows * cols - bombNum));
            if (victory()) {
                pause = true;
                QMessageBox::StandardButton ans;
                ans = QMessageBox::information(nullptr, "游戏结束", "游戏胜利！是否要重新开始？",
                                               QMessageBox::Yes, QMessageBox::No);
                if (ans == QMessageBox::Yes) {
                    startMyGame();
                } else {
                    QApplication::quit();
                }
                return;
            }
        }
    }
}

bool GameWindow::victory() {
    for (int i = 0; i < items.size(); i++) {
        for (int j = 0; j < items[i].size(); j++) {
            item* it = items[i][j];
            if (it->isBomb) {
                if (!it->ifFlaged) {
                    return false;
                }
            } else {
                if (!it->ifLighted) {
                    return false;
                }
            }
        }
    }
    return true;
}

void GameWindow::bfs(QPoint pt) {
    QPoint cur = pt;
    QVector<QPoint> choices;
    choices.push_back(QPoint(-1, 0));
    choices.push_back(QPoint(0, 1));
    choices.push_back(QPoint(1, 0));
    choices.push_back(QPoint(1, 0));
    choices.push_back(QPoint(0, -1));
    choices.push_back(QPoint(0, -1));
    choices.push_back(QPoint(-1, 0));
    choices.push_back(QPoint(-1, 0));
    for (int i = 0; i < 8; i++) {
        cur += choices[i];
        if (cur.x() < 0 || cur.x() >= cols || cur.y() < 0 || cur.y() >= rows) continue;
        item* it = items[cur.x()][cur.y()];
        if (!it->isBomb && !it->ifLighted && !it->ifFlaged) {
            it->ifLighted = true;
            openCount++;
            progressBar->setValue(openCount * 100 / (rows * cols - bombNum));
            if (it->number == 0) {
                bfs(cur);
            }
        }
    }
}

void GameWindow::gameover() {
    ifDead = true;
    for (int i = 0; i < items.size(); i++) {
        for (int j = 0; j < items[i].size(); j++) {
            if (items[i][j]->isBomb) {
                items[i][j]->ifFlaged = true;

            } else {
                items[i][j]->ifFlaged = false;
                items[i][j]->ifLighted = true;
            }
        }
    }
}

GameWindow::~GameWindow() {
    delete ui;
    // delete chosce;
    delete returnButton;
    delete progressBar;
    delete timer2;
    endGame();
    qDebug() << QString("gamewindow close");
}

void GameWindow::timerEvent(QTimerEvent* event) {
    if (event->timerId() == timerId && (!pause)) {
        seconds++;

        int secondss = seconds % 60;
        int secondsm = seconds / 60;
        int seLow = secondss % 10;
        int seHig = secondss / 10;
        int miLow = secondsm % 10;
        int miHig = secondsm / 10;
        ui->timerlable->setText(
            QString("计时器：%1%2:%3%4").arg(miHig).arg(miLow).arg(seHig).arg(seLow));
    }
}
