#include "server.h"
#include <netdb.h>
#include <cstring>
#include <QByteArray>
static int rpc=1;
void Server::initialize(char * _listen_hostname,int _listen_port)
{
    udpServerSocket=new UDPServerSocket();
    struct hostent *ip;
    struct sockaddr_in temp;
    ip=gethostbyname(_listen_hostname);
    if (!ip)
        perror("invalid host name \n");
    memcpy(&temp.sin_addr, ip->h_addr_list[0], ip->h_length);
    udpServerSocket->initializeServer (inet_ntoa(temp.sin_addr),_listen_port);
    srand(time(0));
}
void Server::initialize2(char * _hostname,int _port)
{
    udpServerSocket2=new UDPClientSocket();
    struct hostent *ip;
    struct sockaddr_in temp;
    ip=gethostbyname(_hostname);
    if (!ip)
        perror("invalid host name \n");
    memcpy(&temp.sin_addr, ip->h_addr_list[0], ip->h_length);
    udpServerSocket2->initializeClient (inet_ntoa(temp.sin_addr),_port);
}
void Server::listen()
{
    getRequest();
}

Message * Server::getRequest()
{
    int buffersize=4000;
    char *buffer = new char[buffersize];
    char *reply = new char[buffersize];
    char *authenticate = new char[buffersize];
    struct sockaddr_in  pAddr;
    Message *m=new Message(),*n=new Message(),*t = new Message();
    string name,ownerusername,path,username;
    int x,c=0;
    int maxtimeout=3;
    while (1)
    {

        x=udpServerSocket->readFromSocketWithBlock(buffer,buffersize,pAddr);
        if (x>=0)
        {

            m->unmarshal(buffer,0);
            //cout<<"message iss \n"<<(char*)m->getMessage()<<"\n";
            if ((m->getOperation()==0)&&(m->getMessageType()==Request))
            {
                stringstream ss(buffer);
                for (int i=0;i<4;i++)
                    getline (ss,name,'\n');
                getline (ss,name,'\n');
                getline (ss,username,'\n');
                getline (ss,ownerusername,'\n');
                getline (ss,path,'\n');
                cout<<"server got"<<name<<" "<<username<<" "<<ownerusername<<" "<<path<<"\n";
                Image I (ownerusername,QString::fromStdString(name),QString::fromStdString(path));
                t=authenticateuser(username,name,ownerusername);
                reply = new char[buffersize];
                t->setRPCId(rpc);
                t->marshal(authenticate);
                c=0;
                do
                {

                    udpServerSocket2->writeToSocket(authenticate,buffersize);
                    cout<<"RPCCCCCCCCCCCCC "<<t->getRPCId()<<"\n";
                    x=udpServerSocket2->readFromSocketWithTimeout(reply,buffersize,2,0);
                    c++;

                }while((x<0)&&(c<maxtimeout));
                t->unmarshal(reply,0);
                if ((t->getMessageSize()==3)&&(c<maxtimeout))
                    sendImage(I,pAddr,username,name,ownerusername);
                buffer = new char[buffersize];
                authenticate = new char[buffersize];
                m=new Message();
                n=new Message();
                t = new Message();

            }

        }
        close (udpServerSocket->sock);
        initialize("localhost",2000);
        rpc++;
    }
    doOperation();
    delete [] buffer;
    //return reply; //just return the last reply (will be changed in exercise 2)
}
Message * Server::sendImage (Image I,struct sockaddr_in  pAddr,string username,string image,string ownerusername) //operation 14
{cout<<"went in\n";
    int buffersize=4000,maxtimeout=10;
    char marshalledinfo [200],marshalledmessage[4000],s[200],reply[4000];
    char *marshalledimage = new char [30000000];
    bool send = I.marshal(marshalledinfo,marshalledimage);
    Message *n=new Message();
    n->setMessageType(Reply);
    cout<<"value of send"<<send<<"\n";
    if (!send)
    {
        string r="0";
        char *rep = new char [5000];
        memcpy(rep,(char*)r.c_str(),r.size()+1);
        udpServerSocket->writeToSocket(rep,5000,pAddr);
        cout<<"sent "<<rep<<"\n";
        return n;
    }
    string r="11";
    char *rep = new char [5000];
    memcpy(rep,(char*)r.c_str(),r.size()+1);
    udpServerSocket->writeToSocket(rep,5000,pAddr);

    Message *message = new Message(0,marshalledimage,I.getsize(),rpc);
    message->setMessageType(Request);
    Messagehandler splittedmessage (message);
    vector <Message> fragments ;
    splittedmessage.splitmessage(fragments);
    Message* amount=new Message (0,(char*)to_string(splittedmessage.getnumberoffragments()).c_str(),to_string(splittedmessage.getnumberoffragments()).size(),rpc);
    amount->setMessageType(Request);
    amount->marshal(s);
    Message* info=new Message (0, marshalledinfo,strlen(marshalledinfo),0);
    info->marshal(marshalledinfo);
    info->setMessageType(Request);
    int x,c=0,bb=0;
    do{

        udpServerSocket->writeToSocket(s,sizeof(s),pAddr);

        x=udpServerSocket->readFromSocketWithTimeout(reply,buffersize,2,0,pAddr);
        c++;

    }while((x<0)&&(c<maxtimeout));
    if (c<maxtimeout)
    {
        memset(reply, 0, buffersize);
        cout<<"sent size "<<s<<"\n";
        c=0;
        do{
            udpServerSocket->writeToSocket(marshalledinfo,sizeof(marshalledinfo),pAddr);
            x=udpServerSocket->readFromSocketWithTimeout(reply,buffersize,2,0,pAddr);
            c++;
        }while((x<0)&&(c<maxtimeout));
        if (c<maxtimeout)
        {
            memset(reply, 0, buffersize);
            cout<<"sent info "<<marshalledinfo<<"\n";
            for (int i=0;i<splittedmessage.getnumberoffragments();i++)
            {
                c=0;
                fragments.at(i).marshal(marshalledmessage);
                do{
                    udpServerSocket->writeToSocket(marshalledmessage,sizeof(marshalledmessage),pAddr);
                    x=udpServerSocket->readFromSocketWithTimeout(reply,buffersize,2,0,pAddr);
                    c++;
                }while ((x<0)&&(c<maxtimeout));
                if (c>=maxtimeout)
                {
                    bb=1;
                    rpc--;
                    break;
                }
                memset(marshalledmessage, 0, buffersize);
                memset(reply, 0, buffersize);

                //cout<<"\n in server "<<i<<"\n"<<marshalledmessage<<"\n";
            }
            if (!bb)
                decrementview(username,image,ownerusername);

        }else rpc--;
    }else rpc--;
    delete [] marshalledimage;

}
Message*  Server::authenticateuser (string username,string image,string ownerusername) //operation 14
{
    string message=user.getusername()+"\n"+to_string(user.gettoken())+"\n"+username+"\n"+image+"\n"+ownerusername;
    char * temp = new char [message.size()+1];
    memcpy(temp,(char*)message.c_str(),message.size()+1);
    Message *m=new Message(14,temp,message.size()+1,rpc);
    m->setMessageType(Request);
    return m;
}
Message*  Server::decrementview (string username,string image,string ownerusername) //operation 15
{
    string message=user.getusername()+"\n"+to_string(user.gettoken())+"\n"+username+"\n"+image+"\n"+ownerusername;
    char * temp = new char [message.size()+1];
    memcpy(temp,(char*)message.c_str(),message.size()+1);
    Message *m=new Message(15,temp,message.size()+1,rpc);
    m->setMessageType(Request);
    int x,c=0;
    char *dec = new char[4000];
    char *reply = new char[4000];
    m->marshal(dec);
    do
    {

        udpServerSocket2->writeToSocket(dec,4000);
        x=udpServerSocket2->readFromSocketWithTimeout(reply,4000,2,0);
        c++;

    }while((x<0)&&(c<5));
    return m;
}
void Server::setuser(UserAccount user)
{
    this->user=user;
}
UserAccount Server::getuser()
{
    return user;
}
Message * Server::doOperation()
{
    //for exercise 2(char*)_message->getMessage())
}
void Server::sendReply (Message * _message,struct sockaddr_in pAddr)
{
    char *Reply =new char[4000];
    _message->marshal(Reply);
    cout<<"reply is\n"<<Reply<<"\n";

    udpServerSocket->writeToSocket (Reply,  4000,pAddr );
    //cout<<"Server sending reply message: "<<Reply<<"\n";

    //delete []Reply;
}
