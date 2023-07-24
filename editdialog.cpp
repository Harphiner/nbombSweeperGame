#include "editdialog.h"
#include "ui_editdialog.h"
#include <item.h>
#include <gamewindow.h>
#include <QMessageBox>

editDialog::editDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editDialog)
{
    ui->setupUi(this);
    //设置对话框标题
    this->setWindowTitle("edit");
    signalAndSlotInit();
    qDebug()<<QString("editdialog open");
}

void editDialog::signalAndSlotInit(){
    connect(ui->okbtn,&QPushButton::clicked,[this](){
        QString rowsstr=ui->rows->text();
        QString colsstr=ui->cols->text();
        QString minestr=ui->mine->text();
        bool rowok;
        bool colok;
        bool mineok;
        int rows=rowsstr.toInt(&rowok);
        int cols=colsstr.toInt(&colok);
        int mine=minestr.toInt(&mineok);
        if(rows>0&&rows<31&&cols>0&&cols<31&&mine>9&&mine<100&&rowok&&colok&&mineok)
        {
            GameWindow* mygame=new GameWindow(rows,cols,mine);
            mygame->diff=QString("%1×%2,%3").arg(rows).arg(cols).arg(mine);
            mygame->newGame();
            QWidget* oldWindow = this->parentWidget();

            // 确保旧窗口（parent widget）确实存在
            if(oldWindow != nullptr)
            {
                // 获取旧窗口的几何信息
                QPoint oldPos = oldWindow->pos();
                QSize oldSize = oldWindow->size();

                // 计算旧窗口的中心位置
                QPoint oldCenter = oldPos + QPoint(oldSize.width() / 2, oldSize.height() / 2);

                // 获取新窗口的大小
                QSize newSize = mygame->size();

                // 计算新窗口的左上角应该在哪里，以使新窗口的中心和旧窗口的中心重合
                QPoint newPos = oldCenter - QPoint(newSize.width() / 2, newSize.height() / 2);

                // 设置新窗口的位置
                mygame->move(newPos);
            }

            mygame->show();
            this->parentWidget()->close();
            this->close();
        }else{
             QMessageBox::warning(this, "错误", "输入数据有误!");
             ui->rows->clear();
             ui->cols->clear();
             ui->mine->clear();
        }

    });
    connect(ui->nobtn,&QPushButton::clicked,[this](){
        this->close();
    });
}

editDialog::~editDialog()
{
    delete ui;
    qDebug()<<QString("editdialog close");
}
