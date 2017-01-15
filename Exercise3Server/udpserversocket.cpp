#include "udpserversocket.h"
bool UDPServerSocket::initializeServer (char* _myAddr, int _myPort)
{
    myAddress=_myAddr;
    myPort=_myPort;
    myAddr.sin_family = AF_INET;
    myAddr.sin_port = (myPort);
    myAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    peerAddr.sin_family = AF_INET;

    if (bind(sock,(struct sockaddr*)&myAddr, sizeof(myAddr))!=0)
        return false;
    enabled=true;
    cout<<"initialized server \n";
    return true;
}

UDPServerSocket::~UDPServerSocket ( )
{
    close(sock);
}
