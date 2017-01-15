#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->authresult->setVisible(false);
    QString temp=QCoreApplication::arguments().at(1);
    QString temp2=QCoreApplication::arguments().at(2);
    string ip=temp.toStdString();
    string _port=temp2.toStdString();
    int port=stoi(_port);
    app.client=new Client((char*)ip.c_str(),port);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_login_clicked()
{
    app.client->setuser(UserAccount(ui->lineEdit_username->text().toStdString(),ui->lineEdit_password->text().toStdString()));
    Message *reply = new Message();
    reply= app.client->sendrequesttoserver(3);
    if (stoi((char*)(reply->getMessage()))==0)
    {
        ui->authresult->setText("username or password incorrect");
        ui->authresult->setVisible(true);
    }
    else  if (stoi((char*)(reply->getMessage()))==4444)
    {
        ui->authresult->setText("server did not respond \n");
        ui->authresult->setVisible(true);
    }
    else
    {
        this->close();
        app.show();
        Message *r=new Message();
        r->copy( app.client->sendrequesttoserver(6));   //get username
        string users = (char*)r->getMessage(),_users;
        stringstream ss(users);
        while (getline(ss,_users,'\n'))
        {
            app.getlistwidget()->addItem(QString::fromStdString(_users));
            app.getlistwidget_3()->addItem(QString::fromStdString(_users));
            app.getlistwidget_12()->addItem(QString::fromStdString(_users));
        }
        r=new Message();
        r->copy( app.client->sendrequesttoserver(7));
        string images = (char*)r->getMessage(),_images;
        stringstream dd(images);
        while (getline(dd,_images,'\n'))
        {
            app.getlistwidget_2()->addItem(QString::fromStdString(_images));
            app.getlistwidget_4()->addItem(QString::fromStdString(_images));
            app.getlistwidget_13()->addItem(QString::fromStdString(_images));
        }
        app.im->user.settoken(app.client->getuser().gettoken());
        app.im->user.setusername(app.client->getuser().getusername());
        app.server->user.settoken(app.client->getuser().gettoken());
        app.server->user.setusername(app.client->getuser().getusername());
    }
}

void MainWindow::on_pushButton_createaccount_clicked()
{
    app.client->setuser(UserAccount(ui->lineEdit_username->text().toStdString(),ui->lineEdit_password->text().toStdString()));
    Message *reply = new Message();
    reply= app.client->sendrequesttoserver(2);
    if (stoi((char*)(reply->getMessage()))==0)
    {
        ui->authresult->setText("username already exists!");
        ui->authresult->setVisible(true);
    }
    else  if (stoi((char*)(reply->getMessage()))==4444)
    {
        ui->authresult->setText("server did not respond \n");
        ui->authresult->setVisible(true);
    }
    else
    {
        this->close();
        app.show();
        Message *r=new Message();
        r->copy( app.client->sendrequesttoserver(6));   //get username
        string users = (char*)r->getMessage(),_users;
        stringstream ss(users);
        while (getline(ss,_users,'\n'))
        {
            app.getlistwidget()->addItem(QString::fromStdString(_users));
            app.getlistwidget_3()->addItem(QString::fromStdString(_users));
            app.getlistwidget_12()->addItem(QString::fromStdString(_users));
        }
        r=new Message();
        r->copy( app.client->sendrequesttoserver(7));
        string images = (char*)r->getMessage(),_images;
        stringstream dd(images);
        while (getline(dd,_images,'\n'))
        {
            app.getlistwidget_2()->addItem(QString::fromStdString(_images));
            app.getlistwidget_4()->addItem(QString::fromStdString(_images));
            app.getlistwidget_13()->addItem(QString::fromStdString(_images));
        }
        app.im->user.settoken(app.client->getuser().gettoken());
        app.im->user.setusername(app.client->getuser().getusername());
        app.server->user.settoken(app.client->getuser().gettoken());
        app.server->user.setusername(app.client->getuser().getusername());
    }
}
