#ifndef USERACCOUNT_H
#define USERACCOUNT_H
#include <string>
#include "image.h"
#include <vector>
using namespace std;

class UserAccount
{
private:
    string username;
    string password;
    int token;
public:
    UserAccount(){}
    UserAccount(string username,string password);
    void setusername (string username);
    void setpassword (string password);
    string getusername ();
    string getpassword ();
    int gettoken ();
    void settoken(int);
    ~UserAccount();
};

#endif // USERACCOUNT_H
