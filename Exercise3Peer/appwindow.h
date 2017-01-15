#ifndef APPWINDOW_H
#define APPWINDOW_H
#include <QListWidget>
#include <QMainWindow>
#include <QThread>
#include <thread>
#include "client.h"
#include <vector>
#include "message.h"
#include <stdlib.h>
#include <stdio.h>
#include <QString>
#include "udpclientsocket.h"
#include "getimage.h"
#include "server.h"
#include "dialog.h"
namespace Ui {
class AppWindow;
}

class AppWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AppWindow(QWidget *parent = 0);
    ~AppWindow();
    QListWidget* getlistwidget ();
    QListWidget* getlistwidget_2 ();
    QListWidget* getlistwidget_3 ();
    QListWidget* getlistwidget_4 ();
    QListWidget* getlistwidget_12 ();
    QListWidget* getlistwidget_13 ();
    getimage *im;
    Client *client;
    Server *server;
private slots:

    void on_pushButton_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_7_clicked();

    void on_listWidget_12_itemClicked(QListWidgetItem *item);

    void on_listWidget_4_itemClicked(QListWidgetItem *item);

    void on_pushButton_16_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_8_clicked();



    void on_listWidget_13_itemClicked(QListWidgetItem *item);

    void on_listWidget_6_itemClicked(QListWidgetItem *item);
public slots:
    void on_pushButton_5_clicked();
    void viewimage (QImage image,int x);
private:
    Ui::AppWindow *ui;
    Dialog dialog;
    QThread workerThread;
    QThread workerThread2;
signals:
    void operate2(QString,QString,UDPClientSocket *udpClientSocket);
    void operate3();
};

#endif // APPWINDOW_H
