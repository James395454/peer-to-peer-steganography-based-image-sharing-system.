#ifndef UDPSOCKET_H
#define UDPSOCKET_H
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include<thread>
using namespace std;
class UDPSocket
{
public:
int sock;   //socket
struct sockaddr_in myAddr;
struct sockaddr_in peerAddr;
char * myAddress;
char * peerAddress;
int myPort;
int peerPort;
bool enabled;
public:
UDPSocket ();
void setFilterAddress (char * _filterAddress);
char * getFilterAddress ();
//bool initializeServer (char * _myAddr, int _myPort);
//bool initializeClient (char * _peerAddr, int _peerPort);
int writeToSocket (char * buffer,  int maxBytes );
int writeToSocket (char * buffer,  int maxBytes,struct sockaddr_in  pAddr );
int writeToSocketAndWait (char * buffer, int  maxBytes,int microSec );
int readFromSocketWithNoBlock (char * buffer, int  maxBytes);
int readFromSocketWithTimeout (char * buffer, int maxBytes, int timeoutSec, int timeoutMilli);
int readFromSocketWithBlock (char * buffer,  int maxBytes );
int readFromSocketWithBlock (char * buffer,  int maxBytes,struct sockaddr_in  &pAddr );
int readSocketWithNoBlock (char * buffer, int  maxBytes );
int readSocketWithTimeout (char * buffer, int maxBytes, int timeoutSec, int timeoutMilli);
int readSocketWithBlock (char * buffer,  int maxBytes );
int getMyPort ();
int getPeerPort ();
void enable();
void disable();
bool isEnabled();
void lock();
void unlock();
int getSocketHandler();
~UDPSocket ( );
};
#endif // UDPS
