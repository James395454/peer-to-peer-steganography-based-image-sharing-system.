#include "getimage.h"
#include <string>
#include <netdb.h>
#include <cstring>
#include <QByteArray>
#include <QFile>
#include <unistd.h>
static int rpcpeer=0,rpc=1;

QImage getimage:: executeimage(Message * _message,UDPClientSocket *udpClientSocket,int & y)
{

    int size=4000;
    char *marshalledmessage =new char[size],*reply=new char[size];
    _message->marshal(marshalledmessage);
    int x=-1,c=0;
    do
    {
        udpClientSocket->writeToSocket(marshalledmessage,size);
        cout<<"\n wrote\n"<<string(marshalledmessage);
        x= udpClientSocket->readFromSocketWithTimeout(reply,size,2,0);
        c++;
    }while ((x<0)&&(c<10));
    if (c<10)
    {
        Message *r = new Message();
        r->unmarshal(reply,0);
        stringstream ss ((char*)r->getMessage()),dd(marshalledmessage);
        string name,ownerusername,ip,_port,path;

        for (int i=0;i<7;i++)
            getline(dd,name,'\n');
        for (int i=0;i<3;i++)
            getline(dd,ownerusername,'\n');

        getline(ss,ip,'\n');
        if ((ip!="0")&&(ip!="1"))
        {
            getline(ss,_port,'\n');
            getline(ss,path,'\n');
            cout<<"\n reply is \n"<<reply;
            delete []marshalledmessage;
            y=1;
            int b=0;
            QImage img =  getImage(name,ownerusername,ip,stoi(_port),path,b);
            if (b)
                return img;
            else y=0;
        }
        else  if (ip=="1")
        {
            getline(ss,path,'\n');
            cout<<"\n reply is \n"<<reply;
            cout<<"i own it \n";
            delete []marshalledmessage;
            y=1;
            QImage img = QImage(QString::fromStdString(path));
            if (!img.isNull())
                return QImage(QString::fromStdString(path));

        }
    }
    QImage dummy;
    return dummy;
}
void getimage::initialize(char * _hostname,int _port)
{
    udpClientSocket=new UDPClientSocket();
    struct hostent *ip;
    struct sockaddr_in temp;
    ip=gethostbyname(_hostname);
    if (!ip)
        perror("invalid host name \n");
    memcpy(&temp.sin_addr, ip->h_addr_list[0], ip->h_length);
    udpClientSocket->initializeClient (inet_ntoa(temp.sin_addr),_port);
}
void getimage::setuser(UserAccount user)
{
    this->user=user;
}
UserAccount getimage::getuser()
{
    return user;
}
void getimage:: sendimagerequest(QString name,QString ownerusername,UDPClientSocket *udpClientSocket)
{
    QString temp=QCoreApplication::arguments().at(1);
    QString temp2=QCoreApplication::arguments().at(2);
    initialize((char*)temp.toStdString().c_str(),stoi(temp2.toStdString()));
    int x=0;
    QImage i=(executeimage(getimageinfo(name.toStdString(),ownerusername.toStdString()),udpClientSocket,x));
    close(this->udpClientSocket->sock);
    emit this->operate(i,x);
}
Message*  getimage::getimageinfo (string name,string ownerusername) //operation 13
{
    string message=user.getusername()+"\n"+to_string(user.gettoken())+"\n"+name+"\n"+ownerusername;
    char * temp = new char [message.size()+1];
    memcpy(temp,(char*)message.c_str(),message.size()+1);
    Message *m=new Message(13,temp,message.size()+1,rpc++);
    m->setMessageType(Request);
    return m;
}
QImage getimage::getImage (string name,string ownerusername,string ip,int port,string path,int &b)  //operation 0
{
    string t=name+"\n"+user.getusername()+"\n"+ownerusername+"\n"+path;
    char msg [600],reply[5000];
    Message *newRequest=new Message(0,(char*)t.c_str(),t.size(),rpcpeer++),*n=new Message();
    newRequest->setMessageType(Request);
    newRequest->marshal(msg);
    struct sockaddr_in  pAddr;
    pAddr.sin_family = AF_INET;
    pAddr.sin_port = port;
    inet_pton(AF_INET, (char*)ip.c_str(), &(pAddr.sin_addr));
    int x,c=0,maxtimeout=10;
    do{
        udpClientSocket->writeToSocket(msg,sizeof(msg),pAddr);
        x=udpClientSocket->readFromSocketWithTimeout(reply,sizeof(reply),2,0,pAddr);
        c++;

    }while((x<0)&&(c<maxtimeout));
    string re=reply;
    cout<<"recieved "<<re<<" "<<re.size()<<"\n";
    if ((re.size()!=1)&&(c<maxtimeout))
    {
        cout<<"b is 1\n";
        Image i;
        vector <Message> fragments;
        int infosize=201,ssize=201,messagesize=4001;
        char *marshalledinfo =new char[infosize],*s=new char[ssize];
        char* marshalledmessage;
        Message m,*size=new Message(),*info=new Message();
        c=0;
        x=0;
        do
        {
            x=udpClientSocket->readFromSocketWithTimeout(s,ssize,2,0,pAddr);
            c++;
        }while ((x<0)&&(c<maxtimeout));
        cout<<"recieved size "<<s<<"\n";
        if (c<maxtimeout)
        {


            n->unmarshal(s,0);
            n->setMessageType(Reply);
            n->marshal(reply);
            udpClientSocket->writeToSocket(reply,ssize,pAddr);
            memset(reply, 0, sizeof (reply));
            size->unmarshal(s,1);
            c=0;
            x=0;
            do{
                x=udpClientSocket->readFromSocketWithTimeout(marshalledinfo,infosize,2,0,pAddr);
                c++;
            }while((x<0)&&(c<maxtimeout));
            if (c<maxtimeout)
            {

                n->unmarshal(marshalledinfo,0);
                n->setMessageType(Reply);
                n->marshal(reply);
                udpClientSocket->writeToSocket(reply,infosize,pAddr);
                memset(reply, 0, sizeof (reply));
                info->unmarshal(marshalledinfo,0);
                int a=1;
                for (int i=0;i<stol((char*)size->getMessage());i++)
                {

                    marshalledmessage = new char[4001];
                    c=0;
                    x=0;
                    do
                    {
                        x=udpClientSocket->readFromSocketWithTimeout(marshalledmessage,messagesize,2,0,pAddr);
                        c++;
                    }while ((x<0)&&(c<maxtimeout));
                    if (c>=maxtimeout)
                    {
                        a=0;
                        break;
                    }
                    n->unmarshal(marshalledmessage,0);
                    n->setMessageType(Reply);
                    n->marshal(reply);
                    udpClientSocket->writeToSocket(reply,messagesize,pAddr);
                    memset(reply, 0, sizeof (reply));
                    m.unmarshal(marshalledmessage,1);
                    fragments.push_back(m);
                    //cout<<"\n in client"<<i<<"\n"<<marshalledmessage<<"\n";
                }
                if (a)
                {
                    Messagehandler gatheredmessage ;
                    //Message *final;
                    string final;
                    final=gatheredmessage.gathermessages(fragments);
                    //cout<<"recieved "<<final<<"\n"<<final.size()<<"\n";
                    QImage image;
                    image=i.unmarshal((char*)info->getMessage(),(char*)final.c_str());
                    delete []marshalledinfo;
                    delete []s;
                    delete [] marshalledmessage;
                    b=1;
                    return image;
                }
            }
        }
    }
    rpcpeer--;
    QImage dummy;
    return dummy;
}
