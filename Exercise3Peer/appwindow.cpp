#include "appwindow.h"
#include "ui_appwindow.h"

AppWindow::AppWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AppWindow)
{
    ui->setupUi(this);
    server=new Server();
    ui->label_3->setVisible(false);
    ui->label_8->setVisible(false);
    ui->label_9->setVisible(false);
    ui->label_10->setVisible(false);
    im = new getimage();
    QString temp=QCoreApplication::arguments().at(1);
    QString temp2=QCoreApplication::arguments().at(2);
    string ip=temp.toStdString();
    string _port=temp2.toStdString();
    int port=stoi(_port);
    im->initialize((char*)ip.c_str(),port);

    server->initialize("localhost",2000);
    server->initialize2((char*)ip.c_str(),port);

    server->moveToThread(&workerThread2);
    im->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, im, &QObject::deleteLater);
    connect(&workerThread2, &QThread::finished,server, &QObject::deleteLater);
    connect(this, &AppWindow::operate2, im, &getimage::sendimagerequest);
    connect(im, &getimage::operate, this, &AppWindow::viewimage);
    connect(this, &AppWindow::operate3, server, &Server::listen);
    workerThread.start();
    workerThread2.start();
    emit operate3();
}


QListWidget* AppWindow::getlistwidget ()
{
    return ui->listWidget;
}
QListWidget* AppWindow::getlistwidget_2 ()
{
    return ui->listWidget_2;
}
QListWidget* AppWindow::getlistwidget_3 ()
{
    return ui->listWidget_3;
}
QListWidget* AppWindow::getlistwidget_4 ()
{
    return ui->listWidget_4;
}
QListWidget* AppWindow::getlistwidget_12 ()
{
    return ui->listWidget_12;
}
QListWidget* AppWindow::getlistwidget_13 ()
{
    return ui->listWidget_13;
}



void AppWindow::on_pushButton_clicked()
{
    for (int i = 0; i < ui->listWidget_7->count(); i++)
    {
        if (ui->listWidget_7->item(i)->text() == ui->listWidget->currentItem()->text())
            return;
    }
    ui->listWidget_7->addItem(ui->listWidget->currentItem()->text());
}

void AppWindow::on_pushButton_12_clicked()
{
    if (ui->listWidget_8->count()<ui->listWidget_7->count())
        ui->listWidget_8->addItem(ui->lineEdit_3->text());
}

void AppWindow::on_pushButton_13_clicked()
{
    delete ui->listWidget_8->item(ui->listWidget_7->row(ui->listWidget_7->currentItem()));
    delete ui->listWidget_7->currentItem();
}

void AppWindow::on_pushButton_14_clicked()
{
    delete ui->listWidget_8->currentItem();
}

void AppWindow::on_pushButton_2_clicked()
{
    if((ui->lineEdit->text().isEmpty())||(ui->lineEdit_2->text().isEmpty())||(ui->listWidget_7->count()!=ui->listWidget_8->count()))
    {
        ui->label_3->setText("Some important field are left empty!");
    }
    else
    {
        Image I (client->getuser().getusername(),QString::fromStdString(ui->lineEdit->text().toStdString()),QString::fromStdString(ui->lineEdit_2->text().toStdString()));
        string allowedviewers="",viewcounts="";
        for (int i = 0; i < ui->listWidget_7->count(); i++)
        {
            allowedviewers+=ui->listWidget_7->item(i)->text().toStdString()+"\n";
        }
        for (int i = 0; i < ui->listWidget_8->count(); i++)
        {
            viewcounts+=ui->listWidget_8->item(i)->text().toStdString()+"\n";
        }
        allowedviewers=allowedviewers.substr(0, allowedviewers.size()-1);
        viewcounts=viewcounts.substr(0, viewcounts.size()-1);
        Message *reply=new Message();
        reply=client->sendrequesttoserver(I,allowedviewers,viewcounts);
        if (reply->getMessageSize()==2)
            ui->label_3->setText("You already uploaded an image with that name!");
        else if (reply->getMessageSize()==5)
            ui->label_3->setText("no response from server!");
        else
        {
            ui->listWidget_2->addItem(ui->lineEdit->text());
            ui->listWidget_13->addItem(ui->lineEdit->text());
            ui->listWidget_4->addItem(ui->lineEdit->text());
            ui->label_3->setText("Upload complete");
        }
    }
    ui->label_3->setVisible(true);
}


void AppWindow::on_pushButton_6_clicked()
{
    for (int i = 0; i < ui->listWidget_9->count(); i++)
    {
        if (ui->listWidget_9->item(i)->text() == ui->listWidget_2->currentItem()->text())
            return;
    }
    ui->listWidget_9->addItem(ui->listWidget_2->currentItem()->text());
}

void AppWindow::on_pushButton_3_clicked()
{
    delete ui->listWidget_9->currentItem();
}

void AppWindow::on_pushButton_7_clicked()
{
    string imagenames="";
    ui->label_9->setVisible(true);
    for (int i = 0; i < ui->listWidget_9->count(); i++)
    {
        imagenames+=ui->listWidget_9->item(i)->text().toStdString()+"\n";
    }
    imagenames=imagenames.substr(0, imagenames.size()-1);
    Message *reply=new Message();
    reply=client->sendrequesttoserverimage(imagenames);
    if (reply->getMessageSize()==5)
        ui->label_9->setText("no response from server!");
    else if (reply->getMessageSize()!=2)
    {
        for (int i = 0; i < ui->listWidget_2->count(); i++)
        {
            for (int j=0;j<ui->listWidget_9->count();j++)
                if (ui->listWidget_2->item(i)->text() == ui->listWidget_9->item(j)->text())
                {
                    delete ui->listWidget_2->item(i);
                    delete ui->listWidget_4->item(i);
                    delete ui->listWidget_13->item(i);
                    delete ui->listWidget_9->item(j);
                    i--;
                }
        }
        ui->label_9->setText("removed image!");
    }
}

void AppWindow::on_listWidget_12_itemClicked(QListWidgetItem *item)
{
    ui->listWidget_6->clear();
    ui->listWidget_11->clear();
    Message *r=new Message();
    cout<<"item is "<<item->text().toStdString()<<"\n";
    r->copy( client->sendrequesttoservername((item->text()).toStdString()));
    cout<<"message "<<(char*)(r->getMessage())<<" "<<stoi((char*)(r->getMessage()))<<endl;
    ui->label_8->setVisible(true);
    if (r->getMessageSize()==5)
    {
        ui->label_8->setText("no response from server!");
    }
    else if (r->getMessageSize()!=2)
    {
        string images = (char*)r->getMessage(),_images,_size;
        stringstream ss(images);
        getline(ss,_size,'\n');
        int size=stoi(_size);
        for (int i=0;i<size/2;i++)
        {
            getline(ss,_images,'\n');
            ui->listWidget_6->addItem(QString::fromStdString(_images));
        }
        for (int i=size/2;i<size;i++)
        {
            getline(ss,_images,'\n');
            ui->listWidget_11->addItem(QString::fromStdString(_images));
        }
        ui->label_8->setText("done!");
    }
}

void AppWindow::on_listWidget_4_itemClicked(QListWidgetItem *item)
{
    ui->listWidget_5->clear();
    ui->listWidget_10->clear();
    ui->label_10->setVisible(true);
    Message *r=new Message();
    cout<<"item is "<<item->text().toStdString()<<"\n";
    r->copy( client->sendrequesttoserver((item->text()).toStdString()));
    if (r->getMessageSize()==5)
        ui->label_10->setText("no response from server!");
    else
        if (r->getMessageSize()!=2)
        {
            string viewers = (char*)r->getMessage(),_viewers,_size;
            stringstream ss(viewers);
            getline(ss,_size,'\n');
            int size=stoi(_size);
            for (int i=0;i<size/2;i++)
            {
                getline(ss,_viewers,'\n');
                ui->listWidget_5->addItem(QString::fromStdString(_viewers));
            }
            for (int i=size/2;i<size;i++)
            {
                getline(ss,_viewers,'\n');
                ui->listWidget_10->addItem(QString::fromStdString(_viewers));
            }
            ui->label_10->setText("done!");
        }
}

void AppWindow::on_pushButton_16_clicked()
{
    Message *r=new Message();
    ui->label_10->setVisible(true);
    r->copy( client->sendrequesttoserverremove(ui->listWidget_4->currentItem()->text().toStdString(),ui->listWidget_5->currentItem()->text().toStdString()));
    if(r->getMessageSize()==5)
    {
        ui->label_10->setText("no response from server!");
    }
    else if (r->getMessageSize()!=2)
    {
        delete ui->listWidget_10->item(ui->listWidget_5->row(ui->listWidget_5->currentItem()));
        delete ui->listWidget_5->currentItem();
        ui->label_10->setText("done!");
    }
}


void AppWindow::on_pushButton_11_clicked()
{
    ui->label_10->setVisible(true);
    if ((!ui->lineEdit_9->text().isEmpty())&&(ui->listWidget_5->selectedItems().size()!=0))
    {
        Message *r=new Message();
        r->copy( client->sendrequesttoserver(ui->listWidget_4->currentItem()->text().toStdString(),ui->listWidget_5->currentItem()->text().toStdString(),stoi(ui->lineEdit_9->text().toStdString())));
        if(r->getMessageSize()==5)
        {
            ui->label_10->setText("no response from server!");
        }
        else if (r->getMessageSize()!=2)
        {
            if (ui->listWidget_5->selectedItems().size() != 0)
            {
                ui->listWidget_10->item(ui->listWidget_5->row(ui->listWidget_5->currentItem()))->setText(ui->lineEdit_9->text());
                ui->label_10->setText("done!");
                cout<<"added!\n";
            }
        }
    }
}

void AppWindow::on_pushButton_8_clicked()
{
    bool add=true;
    ui->label_10->setVisible(true);
    for (int i = 0; i < ui->listWidget_5->count(); i++)
    {
        if (ui->listWidget_5->item(i)->text()==ui->listWidget_3->currentItem()->text())
            add=false;
    }
    if ((ui->listWidget_3->selectedItems().size() != 0)&&(!ui->lineEdit_8->text().isEmpty())&&(add)&&(ui->listWidget_4->selectedItems().size() != 0))
    {
        Message *r=new Message();
        r->copy( client->sendrequesttoserveradd(ui->listWidget_4->currentItem()->text().toStdString(),ui->listWidget_3->currentItem()->text().toStdString(),stoi(ui->lineEdit_8->text().toStdString())));
        if(r->getMessageSize()==5)
        {
            ui->label_10->setText("no response from server!");
        }
        else if (r->getMessageSize()!=2)
        {
            ui->listWidget_5->addItem(ui->listWidget_3->currentItem()->text());
            ui->listWidget_10->addItem(ui->lineEdit_8->text());
            ui->label_10->setText("done!");
        }
    }
}

void AppWindow::on_pushButton_5_clicked()
{
    ui->label_8->setVisible(true);
    ui->label_8->clear();

    if (ui->listWidget_6->selectedItems().size()!=0)
    {
        if (ui->listWidget_11->item(ui->listWidget_6->row(ui->listWidget_6->currentItem()))->text().toStdString()!="0")
            emit operate2(ui->listWidget_6->currentItem()->text(),ui->listWidget_12->currentItem()->text(),client->udpClientSocket);
        else
        {
            ui->label_8->setText("Cant view this image anymore!");
            QImage image(QString::fromStdString("fake2.jpg"));
            dialog.getlabel()->setPixmap(QPixmap::fromImage(image));
            dialog.getlabel()->setScaledContents(true);
            dialog.show();
        }
    }
    else if (ui->listWidget_13->selectedItems().size()!=0)
    {
        emit operate2(ui->listWidget_13->currentItem()->text(),QString::fromStdString(client->getuser().getusername()),client->udpClientSocket);
    }

}
void AppWindow::viewimage (QImage image,int x)
{
    if (x)
    {
        cout<<"finalsss\n";
        dialog.getlabel()->setPixmap(QPixmap::fromImage(image));
        dialog.getlabel()->setScaledContents(true);
        dialog.show();

        Message *r=new Message();cout<<ui->listWidget_6->selectedItems().size()<<"\n";
        if (ui->listWidget_6->selectedItems().size()!=0)
        {
            ui->listWidget_6->clear();
            ui->listWidget_11->clear();
            r->copy( client->sendrequesttoservername((ui->listWidget_12->currentItem()->text()).toStdString()));

            if (r->getMessageSize()!=2)
            {
                string images = (char*)r->getMessage(),_images,_size;
                stringstream ss(images);
                getline(ss,_size,'\n');
                int size=stoi(_size);
                for (int i=0;i<size/2;i++)
                {
                    getline(ss,_images,'\n');
                    ui->listWidget_6->addItem(QString::fromStdString(_images));
                }
                for (int i=size/2;i<size;i++)
                {
                    getline(ss,_images,'\n');
                    ui->listWidget_11->addItem(QString::fromStdString(_images));
                }
                ui->label_8->setText("done!");
            }
            else ui->label_8->setText("cant view this image anymore!");
        }
    }
    else
    {
        ui->label_8->setText("no response!");
    }
}
void AppWindow::on_listWidget_13_itemClicked(QListWidgetItem *item)
{
    ui->listWidget_6->clearSelection();
}

void AppWindow::on_listWidget_6_itemClicked(QListWidgetItem *item)
{
    ui->listWidget_13->clearSelection();
}
AppWindow::~AppWindow()
{
    workerThread.quit();
    workerThread.wait();
    workerThread2.quit();
    workerThread2.wait();
    delete ui;
}
