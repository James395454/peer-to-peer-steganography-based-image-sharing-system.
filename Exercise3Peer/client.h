#ifndef CLIENT_H
#define CLIENT_H
#include "udpclientsocket.h"
#include "message.h"
#include "messagehandler.h"
#include "image.h"
#include "useraccount.h"
#include <vector>
#include <QString>
#include <QCoreApplication>
class Client
{

private:

Message * editallowedviewers (Image I,string usernames);
Message *createaccount ();
Message *authenticate ();
Message* getlistofimages (string username);
Message * makeimageavailable (Image I,string allowedviewers,string viewcounts);
Message* getlistofusers();
Message*  getlistofownedimages ();
Message*  deletelistofimages (string imagenames) ;
Message*  getlistofallowedviewers (string imagename);
Message*  addviewer (string imagename,string viewer,int viewcount);
Message*  removeviewer (string imagename,string viewer);
Message*  editviewcount (string imagename,string viewer,int newcount);
char buffer[100000];
UserAccount user;
public:
UDPClientSocket * udpClientSocket;
Client(char * _hostname,int _port);
Client(){}
Message * execute(Message * _message);
Message* sendrequesttoserver(int operation);
Message* sendrequesttoserver(Image I,string request);
Message* sendrequesttoserver(Image I,string allowedviewers,string viewcounts);
Message* sendrequesttoserverimage(string imagenames);
Message* sendrequesttoserveradd(string image,string viewer,int viewcount);
Message* sendrequesttoserverremove(string image,string viewer);
Message* sendrequesttoserver(string image,string viewer,int newcount);
Message* sendrequesttoservername(string username);
Message* sendrequesttoserver(string imagename);
Message * getRequest();
Message* getReply ();
Message* executewithtimeout (Message * message);
void setuser(UserAccount user);
UserAccount getuser();
~Client();

};
#endif //

