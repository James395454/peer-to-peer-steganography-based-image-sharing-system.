#include "useraccount.h"

UserAccount::UserAccount (string username,string password)
{
    this->username=username;
    this->password=password;
}
void UserAccount::setusername (string username)
{
    this->username=username;
}
void UserAccount::setpassword (string password)
{
    this->password=password;
}
string UserAccount::getusername ()
{
    return username;
}
string UserAccount::getpassword ()
{
    return password;
}
int UserAccount::gettoken ()
{
    return token;
}
void UserAccount::settoken(int token)
{
    this->token=token;
}
UserAccount::~UserAccount()
{


}
