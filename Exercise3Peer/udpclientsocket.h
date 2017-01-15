#ifndef UDPCLIENTSOCKET_H
#define UDPCLIENTSOCKET_H
#include "udpsocket.h"
class UDPClientSocket: public UDPSocket
{
public:
UDPClientSocket ():UDPSocket(){}
bool initializeClient (char * _peerAddr, int _peerPort);
~UDPClientSocket ( );
};
#endif // UDP

