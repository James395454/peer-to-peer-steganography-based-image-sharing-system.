#include "message.h"
#include <iostream>
#include <cstring>

Message::Message(int operation,void * p_message,size_t p_message_size,int p_rpc_id)
{
    this->operation=operation;
    this->message=p_message;
    this->message_size=p_message_size;
    this->rpc_id=p_rpc_id;
}
void Message::copy (Message* m)
{
    this->operation=m->getOperation();
    this->message=m->getMessage();
    this->message_size=m->getMessageSize();
    this->rpc_id=m->getRPCId();
    this->message_type=m->getMessageType();
}
void Message::marshal(char *marshalledmessage)
{
    string type = message_type==Request?"Request":"Reply",t="";

    t = to_string (operation)+"\n"+to_string (rpc_id)+"\n" +type+"\n"+ to_string(message_size)+"\n"+string((char*)message);
    memcpy(marshalledmessage,(char*)t.c_str(),t.size()+1);

}
void Message::unmarshal(char  *m ,int type)
{
    stringstream ss(m);
    string _operation,_rpc_id,_message_size,_message,_message_type,_entiremessagesize,temp2;
    char *temp;
    getline(ss,_operation,'\n');
    getline(ss,_rpc_id,'\n');
    getline(ss,_message_type,'\n');
    getline(ss,_message_size,'\n');
    while (getline(ss,temp2,'\n'))
    {
        if (type==0)
            _message+=temp2+"\n";
        else _message+=temp2;
    }
    if (type==0)
        _message=_message.substr(0, _message.size()-1);
    //cout<<"message\n"<<_operation<<"\n"<<_rpc_id<<"\n"<<_message_size<<"\n"<<_message_type<<"\n"<<_message<<"\n";
    rpc_id=stol(_rpc_id);
    message_size=stol(_message_size);
    operation=stol(_operation);
    message_type=_message_type=="Request"? Request:Reply;

    //cout<<"message\n"<<operation<<"\n"<<rpc_id<<"\n"<<message_size<<"\n"<<message_type<<"\n";
    temp = new char [message_size+1];
    memcpy(temp,(char*)_message.c_str(),message_size+1);//cout<<"fake\n\n"<<temp;
    message=temp;
}
void Message::setOperation (int _operation)
{
    operation=_operation;
}
void Message::setRPCId(int rpcid)
{
    rpc_id=rpcid;
}
void Message::setMessage (void * message,size_t message_size)
{
    this->message_size=message_size;
    this->message=message;
}
void Message::setMessageType (MessageType message_type)
{
    this->message_type=message_type;
}
MessageType Message::getMessageType()
{
    return message_type;
}
void * Message::getMessage()
{
    return message;
}
size_t Message::getMessageSize()
{
    return message_size;
}
int Message::getOperation ()
{
    return operation;
}
int Message::getRPCId()
{
    return rpc_id;
}
Message::~Message()
{

}
