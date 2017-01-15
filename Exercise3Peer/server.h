#ifndef SERVER_H
#define SERVER_H
#include "udpserversocket.h"
#include "udpclientsocket.h"
#include "message.h"
#include "messagehandler.h"
#include <thread>
#include <vector>
#include <mutex>
#include "image.h"
#include "useraccount.h"
using namespace std;
class Server: public QObject
{
    Q_OBJECT
private:

    UDPServerSocket * udpServerSocket;
    UDPClientSocket * udpServerSocket2;
    Message* authenticateuser (string user,string image,string ownerusername);
    Message* decrementview (string username,string image,string ownerusername);
    Message * getRequest();
    Message * doOperation();
    Message * sendImage (Image I,struct sockaddr_in  pAddr,string username,string image,string ownerusername);
    void sendReply (Message * _message,struct sockaddr_in pAddr);
    vector <std::thread> requesthandler;
    int requesthandlercount=30;
public:
    UserAccount user;
    void initialize(char * _listen_hostname,int _listen_port);
    void initialize2(char * _hostname,int _port);
    void serveRequest();
    void setuser(UserAccount user);
    UserAccount getuser();

public slots:
    void listen();
};
#endif
