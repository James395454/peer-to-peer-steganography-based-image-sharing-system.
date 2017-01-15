#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}
QLabel* Dialog::getlabel ()
{
    return ui->label;
}
Dialog::~Dialog()
{
    delete ui;
}
