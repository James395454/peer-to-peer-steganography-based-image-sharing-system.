#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <thread>
#include "client.h"
#include <vector>
#include "message.h"
#include <stdlib.h>
#include <stdio.h>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    /*Client client(argv[1],3000);
    Message *r=new Message();
    string input="";
    Image I (1234,5,"james","large","/home/james/Pictures/big.jpg");
    /* Image I2 (1234,5,"sherif","small","/home/james/Pictures/winter-mountain-lake.jpg");
        string allowedviewers1="sherif",viewcounts1="10";
        string allowedviewers2="james",viewcounts2="10";
        client.setuser(UserAccount("james","123"));
        client.sendrequesttoserver(2);
        client.sendrequesttoserver(3);
        client.sendrequesttoserver(I,allowedviewers1,viewcounts1);
        client.sendrequesttoserver(I2,allowedviewers2,viewcounts2);
        r->copy(client.sendrequesttoserver(4));
        cout<<(char*)r->getMessage();
    //client.sendImage(I);
    cout<<"Done \n";*/
    return a.exec();
}
