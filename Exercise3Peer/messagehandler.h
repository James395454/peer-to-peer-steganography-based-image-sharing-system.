#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H
#include "message.h"
#include <vector>
class Messagehandler
{
    Message  *message;
    int fragmentsize;
    int numberoffragments;
public:
    Messagehandler(){fragmentsize=2048;numberoffragments=0;}
    Messagehandler(Message * message);
    void splitmessage (vector <Message> &);
    string  gathermessages (vector <Message>);
    void setmessage (Message *message);
    void setfragmentsize (int fragmentsize);
    Message *getmessage ();
    int getfragmentsize ();
    int getnumberoffragments ();
    ~Messagehandler();
};

#endif // MESSAGEhandler_H
