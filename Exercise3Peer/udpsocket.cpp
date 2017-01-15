#include "udpsocket.h"
#include <cstring>
using namespace std;
UDPSocket::UDPSocket()
{
    sock=socket(AF_INET,SOCK_DGRAM, 0);
    if (sock < 0)
        perror("Could not open socket");
}
int UDPSocket::writeToSocket (char * buffer,  int maxBytes )
{
    int sendvalue;
    if (!enabled)
    {
        perror("Writing to disabled socket");
        return -1;
    }
    if (sendvalue=sendto(sock,buffer, maxBytes, 0, (struct sockaddr *)&peerAddr, sizeof(peerAddr)) < 0) {
        perror("Failed to write to socket");
        return -1;
    }
    // else cout<<"Sent message: "<<buffer<<" to peer with ip: "<<inet_ntoa(peerAddr.sin_addr)<<"\n";
    return sendvalue;
}
int UDPSocket::writeToSocket (char * buffer,  int maxBytes,struct sockaddr_in  pAddr )
{

    //cout<<"writing to ip"<<(char*)ip.c_str()<<"and port"<<pAddr.sin_port<<"\n";
    int sendvalue;
    if (!enabled)
    {
        perror("Writing to disabled socket");
        return -1;
    }
    if (sendvalue=sendto(sock,buffer, maxBytes, 0, (struct sockaddr *)&pAddr, sizeof(pAddr)) < 0) {
        perror("Failed to write to socket");
        return -1;
    }
    //else cout<<"Sent message: "<<buffer<<" to peer with ip: "<<inet_ntoa(pAddr.sin_addr)<<" and port "<<pAddr.sin_port<<"\n";
    return sendvalue;
}
int UDPSocket::readFromSocketWithBlock (char * buffer,  int maxBytes )
{
    int receivevalue,size=sizeof(peerAddr);
    if (!enabled)
    {
        perror("Receiving from disabled socket");
        return -1;
    }
    if(receivevalue=recvfrom(sock, buffer, maxBytes, 0, (struct sockaddr *)&peerAddr,(socklen_t*)&size)<0)
    {
        return -1;
    }
    //else cout<<"Received message: "<<buffer<<" From peer with ip: "<<inet_ntoa(peerAddr.sin_addr)<<"\n";
    return receivevalue;
}
int UDPSocket::readFromSocketWithBlock (char * buffer,  int maxBytes,struct sockaddr_in  &pAddr)
{
    int receivevalue;
    pAddr.sin_family = AF_INET;
    int size=sizeof(pAddr);
    if (!enabled)
    {
        perror("Receiving from disabled socket");
        return -1;
    }
    if(receivevalue=recvfrom(sock, buffer, maxBytes, 0, (struct sockaddr *)&pAddr,(socklen_t*)&size)<0)
    {
        return -1;
    }
    //else cout<<"Received message: "<<buffer<<" From peer with ip: "<<inet_ntoa(pAddr.sin_addr)<<" and port "<<pAddr.sin_port<<"\n";
    return receivevalue;
}
int UDPSocket::readFromSocketWithTimeout (char * buffer, int maxBytes, int timeoutSec, int timeoutMilli)
{
    int receivevalue,size=sizeof(peerAddr);
    if (!enabled)
    {
        perror("Receiving from disabled socket");
        return -1;
    }
    struct timeval timeout;
    timeout.tv_sec = timeoutSec;
    timeout.tv_usec = timeoutMilli;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,sizeof(struct timeval));
    if(receivevalue=recvfrom(sock, buffer, maxBytes, 0, (struct sockaddr *)&peerAddr,(socklen_t*)&size)<0)
    {
        cout<<" message From peer with ip: "<<inet_ntoa(peerAddr.sin_addr)<<" TIMED OUT \n";
        return -1;
    }
    //else cout<<"Received message: "<<buffer<<" From peer with ip: "<<inet_ntoa(peerAddr.sin_addr)<<"\n";
    return receivevalue;
}
int UDPSocket::readFromSocketWithTimeout (char * buffer, int maxBytes, int timeoutSec, int timeoutMilli,struct sockaddr_in  &pAddr)
{
    pAddr.sin_family = AF_INET;
    int receivevalue,size=sizeof(pAddr);
    if (!enabled)
    {
        perror("Receiving from disabled socket");
        return -1;
    }
    struct timeval timeout;
    timeout.tv_sec = timeoutSec;
    timeout.tv_usec = timeoutMilli;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,sizeof(struct timeval));
    if(receivevalue=recvfrom(sock, buffer, maxBytes, 0, (struct sockaddr *)&pAddr,(socklen_t*)&size)<0)
    {
        cout<<" message  From peer with ip: "<<inet_ntoa(pAddr.sin_addr)<<" TIMED OUT \n";
        return -1;
    }
    //else cout<<"Received message: "<<buffer<<" From peer with ip: "<<inet_ntoa(pAddr.sin_addr)<<" and port "<<pAddr.sin_port<<"\n";
    return receivevalue;
}
int UDPSocket::getMyPort ()
{
    return myPort;
}
int UDPSocket::getPeerPort ()
{
    return peerPort;
}
void UDPSocket::enable()
{
    enabled=true;
}
void UDPSocket::disable()
{
    enabled=false;
}
bool UDPSocket::isEnabled()
{
    return enabled;
}
void UDPSocket::lock()
{
    //to do
}
void UDPSocket::unlock()
{
    //to do
}
UDPSocket::~UDPSocket()
{
    close(sock);
}
