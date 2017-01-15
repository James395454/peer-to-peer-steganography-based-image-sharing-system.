#include "server.h"
#include <netdb.h>
#include <cstring>
#include <QByteArray>
#include <map>
map<string,int>lastrpc;
Server::Server(char * _listen_hostname,int _listen_port)
{
    udpServerSocket=new UDPServerSocket();
    struct hostent *ip;
    struct sockaddr_in temp;
    exitmessage=0;
    ip=gethostbyname(_listen_hostname);
    if (!ip)
        perror("invalid host name \n");
    memcpy(&temp.sin_addr, ip->h_addr_list[0], ip->h_length);
    udpServerSocket->initializeServer (inet_ntoa(temp.sin_addr),_listen_port);
    serverdatabase.createtables();
    end=false;
    srand(time(0));
}


void Server::listen()
{
    for (int i=0;i<requesthandlercount;i++)
        requesthandler.push_back(thread(&Server::getRequest,this));
    for (int i=0;i<requesthandlercount;i++)
        requesthandler[i].join();
}

Message * Server::getRequest()
{   
    int buffersize=4000;
    char *buffer = new char[buffersize];
    struct sockaddr_in  pAddr;

    while (1)
    {
        udpServerSocket->readFromSocketWithBlock(buffer,buffersize,pAddr);
        Message *m=new Message();
        Message *reply= new Message();
        m->unmarshal(buffer,0);
        cout<<"message is \n"<<(char*)m->getMessage()<<"\n";
        string ip=inet_ntoa(pAddr.sin_addr);
        if (m->getOperation()==5)
        {

            reply->copy(makeimageavailable(m,ip));

        }
        else if (m->getOperation()==2)
        {
            reply->copy(createaccount(m));
        }
        else if (m->getOperation()==3)
        {
            reply->copy(authenticate(m,ip));
        }
        else if (m->getOperation()==4)
        {
            reply->copy(getlistofimages(m));
        }
        else if (m->getOperation()==6)
        {
            reply->copy(getlistofusers(m));
        }
        else if (m->getOperation()==7)
        {
            reply->copy(getlistofownedimages(m));
        }
        else if (m->getOperation()==8)
        {
            reply->copy(deletelistofimages(m));
        }
        else if (m->getOperation()==9)
        {
            reply->copy(getlistofallowedviewers(m));
        }
        else if (m->getOperation()==10)
        {
            reply->copy(addviewer(m));
        }
        else if (m->getOperation()==11)
        {
            reply->copy(removeviewer(m));
        }
        else if (m->getOperation()==12)
        {
            reply->copy(editviewcount(m));
        }
        else if (m->getOperation()==13)
        {
            reply->copy(sendimage(m));
        }
        else if (m->getOperation()==14)
        {
            reply->copy(authenticateuser(m));
        }
        else if (m->getOperation()==15)
        {
            reply->copy(decrementview(m,pAddr));
        }
        reply->setMessageType(Reply);
        sendReply (reply,pAddr);
        buffer = new char[buffersize];
    }

    doOperation();
    delete [] buffer;
    //return reply; //just return the last reply (will be changed in exercise 2)
}

Message * Server::createaccount (Message *m) //2
{
    string username,password;
    stringstream ss((char*)m->getMessage());
    getline(ss,username,'\n');
    getline(ss,password,'\n');
    int token,result;
    do{
        token=rand()%100000+1;
    }while (serverdatabase.selectuser(token));
    if(!serverdatabase.selectuser(username))
    {
        result=1;
        serverdatabase.insertuser(username,password,token);
    }
    else
    {
        result=0;
        cout<<"user already exists\n";
    }
    string t;
    Message *reply;
    if (result)
    {
        t=to_string(token);
        char *temp=new char [t.size()];
        memcpy(temp,(char*)t.c_str(),t.size());
        reply=new Message(m->getOperation(),temp,t.size(),m->getRPCId());
    }
    else
    {
        t=to_string(result);
        char *temp=new char [t.size()+1];
        memcpy(temp,(char*)t.c_str(),t.size()+1);
        reply=new Message(m->getOperation(),temp,t.size()+1,m->getRPCId());
    }
    return reply;
}
Message * Server::authenticate (Message *m,string ip) //3
{
    int result;
    string username,password,_port;
    stringstream ss((char*)m->getMessage());
    getline(ss,username,'\n');
    getline(ss,password,'\n');
    getline(ss,_port,'\n');
    int port=stoi(_port);
    int token;
    do{
        token=rand()%100000+1;
    }while (serverdatabase.selectuser(token));
    if(serverdatabase.selectuser(username,password))
    {
        serverdatabase.updateuser(username,token);
        cout<<username<<" "<<password<<" "<<ip<<" "<<port<<"\n";
        serverdatabase.updateimage(username,ip,port);
        result=1;
    }
    else result=0;
    string t;
    Message *reply;
    if (result)
    {
        t=to_string(token);
        char *temp=new char [t.size()+1];
        memcpy(temp,(char*)t.c_str(),t.size()+1);
        reply=new Message(m->getOperation(),temp,t.size()+1,m->getRPCId());
    }
    else
    {
        t=to_string(result);
        char *temp=new char [t.size()+1];
        memcpy(temp,(char*)t.c_str(),t.size()+1);
        reply=new Message(m->getOperation(),temp,t.size()+1,m->getRPCId());
    }
    return reply;
}
Message *Server::getlistofimages (Message *m)//4
{
    string ownerusername,_token,username;
    stringstream ss((char*)m->getMessage());
    getline(ss,ownerusername,'\n');
    getline(ss,_token,'\n');
    getline(ss,username,'\n');
    int token = stoi(_token),k=0,l=0;
    string t="";
    if (serverdatabase.selectuser(ownerusername,token))
    {
        vector<string>allowedimages;
        vector<int>viewcounts;
        vector<int>imageID;
        serverdatabase.selectallowedviewer(imageID,ownerusername,allowedimages,viewcounts);
        string s="";
        //s+=to_string(allowedimages.size()*2)+"\n";
        cout<<"printing stuff\n";
        for (int i=0;i<allowedimages.size();i++)
        {
            if (serverdatabase.selectimage(username,imageID[i]))
            {
                t+=allowedimages[i]+"\n";
                cout<<allowedimages[i]<<"\n";
                k=1;
                l++;
            }
        }
        if (k)
        {
            s=to_string(l*2)+"\n"+t;
            cout<<"printing other stuff\n";
            cout<<l<<"\n";
            for (int i=0;i<viewcounts.size();i++)
            {
                if (serverdatabase.selectimage(username,imageID[i]))
                {
                    s+=to_string(viewcounts[i])+"\n";
                    cout<<viewcounts[i]<<"\n";
                }

            }
            s=s.substr(0, s.size()-1);
            char *temp=new char [s.size()+1];
            memcpy(temp,(char*)s.c_str(),s.size()+1);
            Message *reply=new Message(m->getOperation(),temp,s.size()+1,m->getRPCId());
            reply->setMessageType(Reply);
            return reply;
        }
        else
        {
            string t="0";
            char *t2=new char [t.size()+1];
            memcpy(t2,(char*)t.c_str(),t.size()+1);
            return new Message (m->getOperation(),t2,t.size()+1,m->getRPCId());
        }
    }
    else
    {
        string t="0";
        char *t2=new char [t.size()+1];
        memcpy(t2,(char*)t.c_str(),t.size()+1);
        return new Message (m->getOperation(),t2,t.size()+1,m->getRPCId());
    }
}
Message * Server::makeimageavailable (Message *m,string ip)//5
{
    vector<string> allowedviewers;
    vector<int>viewcounts;
    int n=0;
    string imagename,path,ownerusername,_token,total[4000],temp,_port;
    stringstream ss((char*)m->getMessage());
    getline(ss,imagename,'\n');
    getline(ss,path,'\n');
    getline(ss,_port,'\n');
    getline(ss,ownerusername,'\n');
    getline(ss,_token,'\n');
    int port=stoi(_port);
    int token=stoi(_token);
    if ((serverdatabase.selectuser(ownerusername,token))&&(!serverdatabase.selectimage(imagename,ownerusername)))
    {   cout<<"imagename "<<imagename<<" "<<"ownerusername "<<ownerusername<<"\n";
        while (getline(ss,temp,'\n'))
        {
            total[n++]=temp;
        }
        for (int i=0;i<n/2;i++)
        {
            allowedviewers.push_back(total[i]);
            viewcounts.push_back(stoi(total[int(i+float(n/2))]));
        }
        serverdatabase.insertimage(imagename,ownerusername,ip,port,path);
        int id;
        serverdatabase.selectimage(id,imagename,ownerusername);

        for (int i=0;i<n/2;i++)
        {
            cout<<allowedviewers[i]<<" "<<id<<" "<<imagename<<" "<<viewcounts[i]<<"\n";
            serverdatabase.insertallowedviewer(allowedviewers[i],id,imagename,viewcounts[i]);
        }

        return m;
    }
    else
    {

        string t="0";
        char *t2=new char [t.size()+1];
        memcpy(t2,(char*)t.c_str(),t.size()+1);
        return new Message (m->getOperation(),t2,t.size()+1,m->getRPCId());
    }

}
Message*  Server::getlistofusers(Message *m)  //6
{
    string _token;
    stringstream ss((char*)m->getMessage());
    getline(ss,_token,'\n');
    int token = stoi(_token);
    string ownerusername=serverdatabase.selectauser(token);
    if ((serverdatabase.selectuser(ownerusername,token))&&(ownerusername!=""))
    {
        string users;
        serverdatabase.selectallusers(users,ownerusername);
        char *t2=new char [users.size()+1];
        memcpy(t2,(char*)users.c_str(),users.size()+1);
        return new Message (m->getOperation(),t2,users.size()+1,m->getRPCId());
    }
    else
    {
        string t="0";
        char *t2=new char [t.size()+1];
        memcpy(t2,(char*)t.c_str(),t.size()+1);
        return new Message (m->getOperation(),t2,t.size()+1,m->getRPCId());
    }
}
Message*  Server::getlistofownedimages(Message *m)   //7
{
    string ownerusername,_token;
    stringstream ss((char*)m->getMessage());
    getline(ss,ownerusername,'\n');
    getline(ss,_token,'\n');
    int token = stoi(_token);
    if (serverdatabase.selectuser(ownerusername,token))
    {
        vector<string>allowedimages;
        serverdatabase.selectimage(allowedimages,ownerusername);
        string s="";
        for (int i=0;i<allowedimages.size();i++)
        {
            s+=allowedimages[i]+"\n";
        }
        s=s.substr(0, s.size()-1);
        char *temp=new char [s.size()+1];
        memcpy(temp,(char*)s.c_str(),s.size()+1);
        Message *reply=new Message(m->getOperation(),temp,s.size()+1,m->getRPCId());
        reply->setMessageType(Reply);
        return reply;
    }
    else
    {
        string t="0";
        char *t2=new char [t.size()+1];
        memcpy(t2,(char*)t.c_str(),t.size()+1);
        return new Message (m->getOperation(),t2,t.size()+1,m->getRPCId());
    }
}
Message*  Server::deletelistofimages(Message *m)  //8
{
    string _token,username,imagename;
    stringstream ss((char*)m->getMessage());
    getline(ss,username,'\n');
    getline(ss,_token,'\n');
    int token = stoi(_token),imageid;
    if (serverdatabase.selectuser(username,token))
    {
        while (getline(ss,imagename,'\n'))
        {
            imageid;
            serverdatabase.selectimage(imageid,imagename,username);
            serverdatabase.deleteimage(imagename,username);
            serverdatabase.deleteallowedviewer(imageid);
        }
        return m;
    }
    else
    {
        string t="0";
        char *t2=new char [t.size()+1];
        memcpy(t2,(char*)t.c_str(),t.size()+1);
        return new Message (m->getOperation(),t2,t.size()+1,m->getRPCId());
    }
}
Message *Server::getlistofallowedviewers (Message *m)//9
{
    string ownerusername,_token,image;
    stringstream ss((char*)m->getMessage());
    getline(ss,ownerusername,'\n');
    getline(ss,_token,'\n');
    getline(ss,image,'\n');
    int token = stoi(_token),k=0;
    if (serverdatabase.selectuser(ownerusername,token))
    {
        vector<string>allowedviewers;
        vector<int>viewcounts;
        int ID;
        serverdatabase.selectimage(ID,image,ownerusername);
        serverdatabase.selectallowedviewer(ID,allowedviewers,viewcounts);
        string s="";
        s+=to_string(allowedviewers.size()*2)+"\n";
        for (int i=0;i<allowedviewers.size();i++)
        {
            s+=allowedviewers[i]+"\n";
            k=1;
        }
        if (k)
        {
            for (int i=0;i<viewcounts.size();i++)
            {
                s+=to_string(viewcounts[i])+"\n";

            }
            s=s.substr(0, s.size()-1);
            char *temp=new char [s.size()+1];
            memcpy(temp,(char*)s.c_str(),s.size()+1);
            Message *reply=new Message(m->getOperation(),temp,s.size()+1,m->getRPCId());
            reply->setMessageType(Reply);
            return reply;
        }
        else
        {
            string t="0";
            char *t2=new char [t.size()+1];
            memcpy(t2,(char*)t.c_str(),t.size()+1);
            return new Message (m->getOperation(),t2,t.size()+1,m->getRPCId());
        }
    }
    else
    {
        string t="0";
        char *t2=new char [t.size()+1];
        memcpy(t2,(char*)t.c_str(),t.size()+1);
        return new Message (m->getOperation(),t2,t.size()+1,m->getRPCId());
    }
}
Message*  Server::addviewer (Message *m) //10
{
    string ownerusername,_token,image,viewer,_viewcount;
    stringstream ss((char*)m->getMessage());
    getline(ss,ownerusername,'\n');
    getline(ss,_token,'\n');
    getline(ss,image,'\n');
    getline(ss,viewer,'\n');
    getline(ss,_viewcount,'\n');
    int token = stoi(_token),viewcount=stoi(_viewcount);
    if (serverdatabase.selectuser(ownerusername,token))
    {
        int ID;
        serverdatabase.selectimage(ID,image,ownerusername);
        serverdatabase.insertallowedviewer(viewer,ID,image,viewcount);
        return m;
    }
    else
    {
        string t="0";
        char *t2=new char [t.size()+1];
        memcpy(t2,(char*)t.c_str(),t.size()+1);
        return new Message (m->getOperation(),t2,t.size()+1,m->getRPCId());
    }
}
Message*  Server::removeviewer (Message *m) //11
{
    string ownerusername,_token,image,viewer;
    stringstream ss((char*)m->getMessage());
    getline(ss,ownerusername,'\n');
    getline(ss,_token,'\n');
    getline(ss,image,'\n');
    getline(ss,viewer,'\n');
    int token = stoi(_token);
    if (serverdatabase.selectuser(ownerusername,token))
    {
        int ID;
        serverdatabase.selectimage(ID,image,ownerusername);
        serverdatabase.deleteallowedviewer(ID,viewer);
        return m;
    }
    else
    {
        string t="0";
        char *t2=new char [t.size()+1];
        memcpy(t2,(char*)t.c_str(),t.size()+1);
        return new Message (m->getOperation(),t2,t.size()+1,m->getRPCId());
    }
}
Message*  Server::editviewcount (Message *m) //12
{
    string ownerusername,_token,image,viewer,_viewcount;
    stringstream ss((char*)m->getMessage());
    getline(ss,ownerusername,'\n');
    getline(ss,_token,'\n');
    getline(ss,image,'\n');
    getline(ss,viewer,'\n');
    getline(ss,_viewcount,'\n');
    int token = stoi(_token),viewcount=stoi(_viewcount);
    if (serverdatabase.selectuser(ownerusername,token))
    {
        int ID;
        serverdatabase.selectimage(ID,image,ownerusername);
        serverdatabase.updateallowedviewer(viewcount,viewer,ID);
        return m;
    }
    else
    {
        string t="0";
        char *t2=new char [t.size()+1];
        memcpy(t2,(char*)t.c_str(),t.size()+1);
        return new Message (m->getOperation(),t2,t.size()+1,m->getRPCId());
    }
}
Message * Server::sendimage (Message *m)
{
    int port;
    string ip,path;
    string username,_token,name,ownerusername;
    stringstream ss((char*)m->getMessage());
    getline(ss,username,'\n');
    getline(ss,_token,'\n');
    getline(ss,name,'\n');
    getline(ss,ownerusername,'\n');
    int token = stoi(_token),ID;

    if ( !serverdatabase.selectimage(name,ownerusername))
    {
        string t="0";
        char *t2=new char [t.size()+1];
        memcpy(t2,(char*)t.c_str(),t.size()+1);
        return new Message (m->getOperation(),t2,t.size()+1,m->getRPCId());
    }
    else
    {
        serverdatabase.selectimage(ID,name,ownerusername);
        if ((serverdatabase.selectuser(username,token))&&((serverdatabase.selectallowedviewer(username,ID))||(serverdatabase.selectimage(username,ID))))
        {
            serverdatabase.selectimage(port,ip,path,name,ownerusername);
            if (serverdatabase.selectimage(username,ID))
            {
                string t="1\n"+path;
                char *t2=new char [t.size()+1];
                memcpy(t2,(char*)t.c_str(),t.size()+1);
                return new Message (m->getOperation(),t2,t.size()+1,m->getRPCId());
            }
            else
            {
                string s=ip+"\n"+to_string(port)+"\n"+path;
                cout<<"ip: "<<ip<<"\n port"<<port<<"\n path"<<path<<"\n";
                //getchar();
                char *temp=new char [s.size()+1];
                memcpy(temp,(char*)s.c_str(),s.size()+1);
                Message *reply=new Message(m->getOperation(),temp,s.size()+1,m->getRPCId());
                reply->setMessageType(Reply);
                return reply;
            }
        }
        else
        {
            string t="0";
            char *t2=new char [t.size()+1];
            memcpy(t2,(char*)t.c_str(),t.size()+1);
            return new Message (m->getOperation(),t2,t.size()+1,m->getRPCId());
        }
    }
}
Message * Server::authenticateuser (Message *m)
{
    string user,image, username,_token,ownerusername;
    stringstream ss((char*)m->getMessage());
    getline(ss,username,'\n');
    getline(ss,_token,'\n');
    getline(ss,user,'\n');
    getline(ss,image,'\n');
    getline(ss,ownerusername,'\n');
    int token = stoi(_token),ID;
    serverdatabase.selectimage(ID,image,ownerusername);
    if ((serverdatabase.selectuser(username,token))&&(serverdatabase.selectallowedviewer(user,ID)))
    {
        string t="11";
        char *t2=new char [t.size()+1];
        memcpy(t2,(char*)t.c_str(),t.size()+1);

        return new Message (m->getOperation(),t2,t.size()+1,m->getRPCId());
    }
    else
    {
        string t="0";
        char *t2=new char [t.size()+1];
        memcpy(t2,(char*)t.c_str(),t.size()+1);
        return new Message (m->getOperation(),t2,t.size()+1,m->getRPCId());
    }
}
Message * Server::decrementview(Message *m,struct sockaddr_in pAddr)
{
    string user,image, username,_token,ownerusername;
    stringstream ss((char*)m->getMessage());
    getline(ss,username,'\n');
    getline(ss,_token,'\n');
    getline(ss,user,'\n');
    getline(ss,image,'\n');
    getline(ss,ownerusername,'\n');
    int token=stoi(_token),ID;
    serverdatabase.selectimage(ID,image,ownerusername);
    if(lastrpc[inet_ntoa(pAddr.sin_addr)]!=m->getRPCId())
    {
        if (serverdatabase.selectuser(username,token))
        {
            cout<<"UDATINGGGG \n";
            serverdatabase.updateallowedviewer(user,ID);

        }
        else
        {
            string t="0";
            char *t2=new char [t.size()+1];
            memcpy(t2,(char*)t.c_str(),t.size()+1);
            return new Message (m->getOperation(),t2,t.size()+1,m->getRPCId());
        }
        lastrpc[inet_ntoa(pAddr.sin_addr)]=m->getRPCId();
    }
    else
    {
        string t="0";
        char *t2=new char [t.size()+1];
        memcpy(t2,(char*)t.c_str(),t.size()+1);
        return new Message (m->getOperation(),t2,t.size()+1,m->getRPCId());
    }
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

Server::~Server()
{

}
