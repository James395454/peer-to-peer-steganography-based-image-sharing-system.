#include "messagehandler.h"
#include <iostream>
#include <math.h>
Messagehandler::Messagehandler(Message * message)
{
    this->message=message;
    fragmentsize=2048;
    numberoffragments=0;
}
void  Messagehandler::splitmessage (vector <Message> &fragments )
{
    string t,k[50000];
    t=string((char*)message->getMessage());
    long long remainingsize=message->getMessageSize(),i=0,diff,in=0;
    numberoffragments=ceil(float(remainingsize)/fragmentsize);
    char *temp;
    while (remainingsize>0)
    {
        //cout<<in<<"\n";
        diff=min(remainingsize,(long long) (fragmentsize));
        k[in]="";
        for (int j=i;j<i+diff;j++)
            k[in]+=t[j];
        temp=new char [k[in].size()+1];
        memcpy(temp,(char*)k[in].c_str(),k[in].size()+1);
        fragments.push_back(Message(message->getOperation(),temp,k[in].size(),message->getRPCId()));
        fragments.at(in).setMessageType(message->getMessageType());
        remainingsize-=diff;
        i+=diff;
        in++;
    }
}
string  Messagehandler::gathermessages (vector <Message> v)
{
    string t="";
    Message m;
    for (int i=0;i<v.size();i++)
    {
        m =v.at(i);
        t+=string((char*)m.getMessage());
    }

    m=v.at(0);//cout<<"\n the message is "<<(char*)t.c_str()<<"\n";
    /*message->setMessage((char*)t.c_str(),t.size());
    //cout<<"itsize "<<message->getMessage()<<"\n";
    message->setOperation(m.getOperation());
    message->setRPCId(m.getRPCId());
    message->setMessageType(m.getMessageType());*/

    return t;
}
void Messagehandler::setmessage (Message *message)
{
    this->message=message;
}
void Messagehandler::setfragmentsize (int fragmentsize)
{
    this->fragmentsize=fragmentsize;
}
Message * Messagehandler::getmessage ()
{
    return message;
}
int Messagehandler::getfragmentsize ()
{
    return fragmentsize;
}
int Messagehandler::getnumberoffragments ()
{
    return numberoffragments;
}
Messagehandler::~Messagehandler()
{

}
