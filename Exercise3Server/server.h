#ifndef SERVER_H
#define SERVER_H
#include "udpserversocket.h"
#include "message.h"
#include <thread>
#include <vector>
#include <mutex>
#include "database.h"
using namespace std;
class Server
{
private:

    UDPServerSocket * udpServerSocket;
    Message * getRequest();
    Message * doOperation();
    Message *setviewcount (char *info);
    Message *makeimageavailable (Message *m,string ip);
    Message *sendimage (Message *m);
    Message *getlistofimages (Message *m);
    Message *createaccount (Message *m);
    Message *authenticate (Message *m,string ip);
    Message* getlistofusers(Message *m);
    Message* getlistofownedimages(Message *m);
    Message* deletelistofimages(Message *m);
    Message* getlistofallowedviewers (Message *m);
    Message* addviewer (Message *m);
    Message* removeviewer (Message *m);
    Message* editviewcount (Message *m);
    Message * authenticateuser (Message *m);
    Message * decrementview(Message *m);
    void sendReply (Message * _message,struct sockaddr_in pAddr);
    database serverdatabase;
    bool exitmessage;
    mutex m;
    bool end;
    vector <thread> requesthandler;
    int requesthandlercount=30;
public:
    Server(char * _listen_hostname,int _listen_port);    
    void serveRequest();
    void listen();
    ~Server();
};
#endif
