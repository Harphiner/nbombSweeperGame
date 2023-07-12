#include "editdialog.h"
#include "ui_editdialog.h"

editDialog::editDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editDialog)
{
    ui->setupUi(this);
    //设置对话框标题
    this->setWindowTitle("edit");
}

editDialog::~editDialog()
{
    delete ui;
}
