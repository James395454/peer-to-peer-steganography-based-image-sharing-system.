#ifndef UDPSERVERSOCKET_H
#define UDPSERVERSOCKET_H
#include "udpsocket.h"
class UDPServerSocket: public UDPSocket
{
public:
UDPServerSocket ():UDPSocket(){}
bool initializeServer (char * _myAddr, int _myPort);
~UDPServerSocket ( );
};
#endif // UDP
