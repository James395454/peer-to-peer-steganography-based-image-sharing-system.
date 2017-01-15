#include "client.h"
#include <string>
#include <netdb.h>
#include <cstring>
#include <QByteArray>
#include <QFile>
#include <unistd.h>
using namespace std;
static int rpc=1;
Client::Client(char * _hostname,int _port)
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
void Client::setuser(UserAccount user)
{
    this->user=user;
}
UserAccount Client::getuser()
{
    return user;
}
Message* Client:: execute(Message * _message)
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

    }while ((x<0)&&(c<3));
    Message *r = new Message();
    if (c<3)
    {
        r->unmarshal(reply,0);
        if ((r->getOperation()==2)||(r->getOperation()==3))
        {
            int result=stoi((char*)r->getMessage());
            if (result)
            {
                user.settoken(result);
                cout<<"token set to "<<user.gettoken()<<"\n\n";
            }
            else
            {
                if (r->getOperation()==2)
                    cout<<"user already exists\n";
                else cout<<"username or password incorrect\n";
            }

        }
        cout<<"\n reply is \n"<<(char*)r->getMessage();
    }
    else
    {
        string t="4444";
        char *t2=new char[t.size()+1];
        memcpy(t2,(char*)t.c_str(),t.size()+1);
        r=new Message (_message->getOperation(),t2,t.size()+1,_message->getRPCId());

    }
    delete []marshalledmessage;
    return r;
}

Message* Client:: sendrequesttoserver(int operation)
{
    Message *m;

    if (operation==2)
    {
        m=createaccount ();
    }
    else if (operation==3)
    {
        m=authenticate ();
    }
    else if (operation==6)
    {
        m=getlistofusers ();
    }
    else if (operation==7)
    {
        m=getlistofownedimages();
    }
    return execute(m);
}
Message* Client:: sendrequesttoserver(Image I,string request)
{
    return execute(editallowedviewers(I,request));
}

Message* Client:: sendrequesttoserver(string imagename)
{
    return execute(getlistofallowedviewers(imagename));
}
Message* Client:: sendrequesttoserverimage(string imagenames)
{
    return execute(deletelistofimages(imagenames));
}
Message* Client:: sendrequesttoservername(string username)
{
    return execute(getlistofimages(username));
}
Message* Client:: sendrequesttoserveradd(string imagename,string viewer,int viewcount)
{
    return execute(addviewer(imagename,viewer,viewcount));
}
Message* Client:: sendrequesttoserverremove(string imagename,string viewer)
{
    return execute(removeviewer(imagename,viewer));
}

Message* Client:: sendrequesttoserver(string imagename,string viewer,int newcount)
{
    return execute(editviewcount(imagename,viewer,newcount));
}
Message* Client:: sendrequesttoserver(Image I,string allowedviewers,string viewcounts)
{
    Message *m=new Message(),*s=new Message();
    m->copy(makeimageavailable(I,allowedviewers,viewcounts));
    s->copy(execute(m));
    return s;
}


Message*  Client::editallowedviewers (Image I,string usernames) //operation 1
{
    string message=I.getname().toStdString()+"\n"+usernames+"\n"+to_string(user.gettoken());
    char * temp = new char [message.size()+1];
    memcpy(temp,(char*)message.c_str(),message.size()+1);
    Message *m=new Message(1,temp,message.size()+1,rpc++);
    m->setMessageType(Request);
    return m;
}
Message*  Client::createaccount () //operation 2
{
    string message=user.getusername()+"\n"+user.getpassword();
    char * temp = new char [message.size()+1];
    memcpy(temp,(char*)message.c_str(),message.size()+1);
    Message *m=new Message(2,temp,message.size()+1,rpc++);
    m->setMessageType(Request);
    return m;
}
Message*  Client::authenticate () //operation 3
{
    string message=user.getusername()+"\n"+user.getpassword()+"\n"+to_string(2000);
    char * temp = new char [message.size()+1];
    memcpy(temp,(char*)message.c_str(),message.size()+1);
    Message *m=new Message(3,temp,message.size()+1,rpc++);
    m->setMessageType(Request);
    return m;
}
Message*  Client::getlistofimages (string username) //operation 4
{
    string message=user.getusername()+"\n"+to_string(user.gettoken())+"\n"+username;
    char * temp = new char [message.size()+1];
    memcpy(temp,(char*)message.c_str(),message.size()+1);
    Message *m=new Message(4,temp,message.size()+1,rpc++);
    m->setMessageType(Request);
    return m;
}
Message*  Client::makeimageavailable (Image I,string allowedviewers,string viewcounts) //operation 5
{
    string message=I.getname().toStdString()+"\n"+I.getpath().toStdString()+"\n"+to_string(2000)+"\n"+(I.getownerusername())+"\n"+to_string(user.gettoken())+"\n"+allowedviewers+"\n"+viewcounts+"\n";
    char * temp = new char [message.size()+1];
    memcpy(temp,(char*)message.c_str(),message.size()+1);
    Message *m=new Message(5,temp,message.size()+1,rpc++);
    m->setMessageType(Request);
    return m;
}
Message*  Client::getlistofusers()  //operation 6
{
    string message=to_string(user.gettoken());
    char * temp = new char [message.size()+1];
    memcpy(temp,(char*)message.c_str(),message.size()+1);
    Message *m=new Message(6,temp,message.size()+1,rpc++);
    m->setMessageType(Request);
    return m;
}
Message*  Client::getlistofownedimages () //operation 7
{
    string message=user.getusername()+"\n"+to_string(user.gettoken());
    char * temp = new char [message.size()+1];
    memcpy(temp,(char*)message.c_str(),message.size()+1);
    Message *m=new Message(7,temp,message.size()+1,rpc++);
    m->setMessageType(Request);
    return m;
}
Message*  Client::deletelistofimages (string imagenames) //operation 8
{
    string message=user.getusername()+"\n"+to_string(user.gettoken())+"\n"+imagenames;
    char * temp = new char [message.size()+1];
    memcpy(temp,(char*)message.c_str(),message.size()+1);
    Message *m=new Message(8,temp,message.size()+1,rpc++);
    m->setMessageType(Request);
    return m;
}
Message*  Client::getlistofallowedviewers (string imagename) //operation 9
{
    string message=user.getusername()+"\n"+to_string(user.gettoken())+"\n"+imagename;
    char * temp = new char [message.size()+1];
    memcpy(temp,(char*)message.c_str(),message.size()+1);
    Message *m=new Message(9,temp,message.size()+1,rpc++);
    m->setMessageType(Request);
    return m;
}
Message*  Client::addviewer (string imagename,string viewer,int viewcount) //operation 10
{
    string message=user.getusername()+"\n"+to_string(user.gettoken())+"\n"+imagename+"\n"+viewer+"\n"+to_string(viewcount);
    char * temp = new char [message.size()+1];
    memcpy(temp,(char*)message.c_str(),message.size()+1);
    Message *m=new Message(10,temp,message.size()+1,rpc++);
    m->setMessageType(Request);
    return m;
}
Message*  Client::removeviewer (string imagename,string viewer) //operation 11
{
    string message=user.getusername()+"\n"+to_string(user.gettoken())+"\n"+imagename+"\n"+viewer;
    char * temp = new char [message.size()+1];
    memcpy(temp,(char*)message.c_str(),message.size()+1);
    Message *m=new Message(11,temp,message.size()+1,rpc++);
    m->setMessageType(Request);
    return m;
}
Message*  Client::editviewcount (string imagename,string viewer,int newcount) //operation 12
{
    string message=user.getusername()+"\n"+to_string(user.gettoken())+"\n"+imagename+"\n"+viewer+"\n"+to_string(newcount);
    char * temp = new char [message.size()+1];
    memcpy(temp,(char*)message.c_str(),message.size()+1);
    Message *m=new Message(12,temp,message.size()+1,rpc++);
    m->setMessageType(Request);
    return m;
}

Message *Client::getRequest()
{
    udpClientSocket->readFromSocketWithBlock(buffer,sizeof(buffer));

}
Message* Client::getReply ()
{
    udpClientSocket->readFromSocketWithBlock(buffer,sizeof(buffer));
    Message *reply=new Message(0,buffer,sizeof(buffer),0);
    reply->setMessageType(Reply);
    memset(&buffer[0], 0, sizeof(buffer));
    return reply;

}
Message* Client::executewithtimeout(Message * _message)
{
    udpClientSocket->writeToSocket((char*)(_message->getMessage()),_message->getMessageSize());
    int x= udpClientSocket->readFromSocketWithTimeout(buffer,sizeof(buffer),2,0);
    if (x<0)
        cout<<(char*)_message->getMessage()<<" timed out and buffer"<<buffer<<"\n";
    Message *reply=new Message(0,buffer,sizeof(buffer),0);
    reply->setMessageType(Reply);
    memset(&buffer[0], 0, sizeof(buffer));
    return reply;

}
Client::~Client()
{

}
