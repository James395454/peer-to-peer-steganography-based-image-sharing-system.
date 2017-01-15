#ifndef DATABASE_H
#define DATABASE_H
#include <sqlite3.h>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
using namespace std;
class database
{
    sqlite3 *db;
public:
    database();
    database(string filename);
    void createtables ();
    void insertuser (string username,string hashedpassword,int token);
    void insertimage(string name,string ownerusername,string ipaddress,int port,string path);
    void insertallowedviewer(string username,int imageID,string imagename,int viewcount);
    void deleteuser(string username);
    void deleteimage(string name,string username);
    void deleteallowedviewer(int ID);
    bool selectuser(int token);
    bool selectuser(string username);
    bool selectuser(string username,string hashedpassword);
    bool selectuser(string username,int token);
    string selectauser(int token);
    void selectallusers(string &,string ownerusername);
    void selectimage(int & ID,string name,string ownerusername);
    void selectimage(int & port,string & ipaddress,string & path,string name,string ownerusername);
    bool selectimage(vector <string> &allowedimages,string ownerusername);
    bool selectimage(string name,string ownerusername);
    bool selectimage(string user,int imageID);
    bool selectallowedviewer(string user,int imageID);
    void selectallowedviewer(string username,vector<string> &imagenames,vector<int> &viewcounts);
    void selectallowedviewer(vector<int> &imageID,string username,vector<string> &imagenames,vector<int> &viewcounts);
    void selectallowedviewer(int imageID,vector<string> &allowedviewers,vector<int> &viewcounts);
    void updateuser(string username,int token);
    void updateimage(string username,string ipaddress,int port);
    void updateallowedviewer(int viewcount,string username,int imageID);
    void updateallowedviewer(string username,int imageID);
    void deleteallowedviewer(int imageID,string username);
    ~database();
};

#endif // DATABASE_H
