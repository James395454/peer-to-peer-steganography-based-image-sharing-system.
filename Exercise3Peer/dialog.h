#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    QLabel* getlabel ();
    ~Dialog();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
