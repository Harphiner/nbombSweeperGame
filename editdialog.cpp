#include "editdialog.h"
#include "ui_editdialog.h"

editDialog::editDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editDialog)
{
    ui->setupUi(this);
    //设置对话框标题
    this->setWindowTitle("edit");
    signalAndSlotInit();
}

void editDialog::signalAndSlotInit(){
    connect(ui->okbtn,&QPushButton::clicked,[this](){
        this->close();
    });
    connect(ui->nobtn,&QPushButton::clicked,[this](){
        this->close();
    });
}

editDialog::~editDialog()
{
    delete ui;
}
