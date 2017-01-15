#ifndef MESSAGE_H
#define MESSAGE_H
#include <string.h>
#include <arpa/inet.h>
#include <sstream>
using namespace std;
enum MessageType { Request, Reply};
class Message
{
private:
MessageType message_type;
int operation;
void * message;
size_t message_size;
int rpc_id;
public:
Message(int operation,void * p_message,size_t p_message_size,int p_rpc_id);
Message(char * marshalled_base64);
void copy (Message*);
Message(){}
int entiremessagesize;
void marshal(char *);
void unmarshal(char * ,int type);
int getOperation ();
int getRPCId();
void * getMessage();
size_t getMessageSize();
MessageType getMessageType();
void setOperation (int _operation);
void setRPCId(int);
void setMessage (void * message,size_t message_size);
void setMessageType (MessageType message_type);
~Message();
};
#endif // MESSAGE_H
