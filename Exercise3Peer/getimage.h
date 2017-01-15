#ifndef GETIMAGE_H
#define GETIMAGE_H
#include "udpclientsocket.h"
#include "message.h"
#include "messagehandler.h"
#include "image.h"
#include "useraccount.h"
#include <vector>
#include <QString>
#include <QCoreApplication>
#include "client.h"
#include "udpclientsocket.h"
class getimage: public QObject
{
    Q_OBJECT
private:
    UDPClientSocket *udpClientSocket;
public:
    UserAccount user;
    QImage executeimage(Message * _message,UDPClientSocket *udpClientSocket,int &x);
    QImage getImage (string name,string ownerusername,string ip,int port,string path,int&b);
    Message* getimageinfo (string name,string ownerusername);
    void setuser(UserAccount user);
    UserAccount getuser();
    void initialize(char * _hostname,int _port);
public slots:
    void sendimagerequest(QString name,QString ownerusername,UDPClientSocket *udpClientSocket);
signals:
    void operate(QImage,int);
};

#endif // GETIMAGE_H
