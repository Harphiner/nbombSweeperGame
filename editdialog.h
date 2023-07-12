#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>

namespace Ui {
class editDialog;
}

class editDialog : public QDialog
{
    Q_OBJECT

public:
    editDialog(QWidget *parent = nullptr);
    ~editDialog();
     void signalAndSlotInit();//初始化信号与槽

private:
    Ui::editDialog *ui;
};

#endif // EDITDIALOG_H
