#include "udpclientsocket.h"
bool UDPClientSocket::initializeClient (char * _peerAddr, int _peerPort)
{
    myAddr.sin_family = AF_INET;
    myAddr.sin_port = 0;
    myAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sock,(struct sockaddr*)&myAddr, sizeof(myAddr))!=0)
        return false;

    peerAddress=_peerAddr;
    peerPort=_peerPort;
    peerAddr.sin_family = AF_INET;
    peerAddr.sin_port = peerPort;
    inet_pton(AF_INET, peerAddress, &(peerAddr.sin_addr));
    enabled=true;
    //cout<<"initialized client \n";
    return true;
}

UDPClientSocket::~UDPClientSocket ( )
{
    close(sock);
}
