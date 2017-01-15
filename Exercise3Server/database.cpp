#include "database.h"
typedef vector<vector<string> > table_type;

database::database()
{
    int rc = sqlite3_open("databasefile.db", &db);
    if( rc )
        cout<<"Can't open database: \n";
    else
        cout<<"Opened database successfully\n";
}
database::database(string filename)
{
    int rc = sqlite3_open((char*)filename.c_str(), &db);
    if( rc )
        cout<<"Can't open database: \n";
    else
        cout<<"Opened database successfully\n";
}
void database::createtables ()
{
    char *sql1 = "CREATE TABLE user("  \
                 "username       TEXT PRIMARY KEY     NOT NULL," \
                 "hashedpassword           TEXT    NOT NULL," \
                 "token            INT     NOT NULL);";

    char *sql2 = "CREATE TABLE image("  \
                 "ID       INTEGER PRIMARY KEY NOT NULL," \
                 "name           TEXT    NOT NULL," \
                 "ownerusername            TEXT    FOREIGN_KEY REFERENCES user(username),"\
                 "ipaddress            TEXT     NOT NULL,"\
                 "port            INT     NOT NULL,"\
                 "path            TEXT     NOT NULL);";

    char *sql3 = "CREATE TABLE allowedviewer("  \
                 "ID       INTEGER PRIMARY KEY NOT NULL," \
                 "username           TEXT   FOREIGN_KEY REFERENCES user(username)," \
                 "imageID            INT   FOREIGN_KEY REFERENCES image(ID),"\
                 "imagename            TEXT    FOREIGN_KEY REFERENCES image(name),"\
                 "viewcount            INT     NOT NULL);";

    int rc1 = sqlite3_exec(db, sql1, 0, 0, 0);
    int rc2 = sqlite3_exec(db, sql2, 0, 0, 0);
    int rc3 = sqlite3_exec(db, sql3, 0, 0, 0);

    if( rc1 != SQLITE_OK )
        cout<<"error creating table 1, it may already exist\n";
    else
        cout<<"Table 1 created successfully\n";
    if( rc2 != SQLITE_OK )
        cout<<"error creating table 2, it may already exist\n";
    else
        cout<<"Table 2 created successfully\n";
    if( rc3 != SQLITE_OK )
        cout<<"error creating table 3, it may already exist\n";
    else
        cout<<"Table 3 created successfully\n";

}
void database::insertuser (string username,string hashedpassword,int token)
{

    string t = "INSERT INTO user (username,hashedpassword,token) " \
               "VALUES ('"+username+"', '"+hashedpassword+"', "+to_string(token)+");";

    char *sql=new char [t.size()+1];
    memcpy(sql,(char*)t.c_str(),t.size()+1);

    int rc = sqlite3_exec(db, sql, 0,  0,  0);
    if( rc != SQLITE_OK )
    {
        cout<<rc<<"error inserting into table user \n";
    }
    else
        cout<<"inserted into table user successfully\n";
}
void database::insertimage(string name,string ownerusername,string ipaddress,int port,string path)
{
    path="'"+path+"'";
    string t = "INSERT INTO image (name,ownerusername,ipaddress,port,path) " \
               "VALUES ( '"+name+"', '"+ownerusername+"', '"+ipaddress+"', "+to_string(port)+", "+path+" );";
    char *sql=new char [t.size()+1];
    memcpy(sql,(char*)t.c_str(),t.size()+1);
    cout<<"\n"<<sql<<"\n";
    int rc = sqlite3_exec(db, sql, 0, 0, 0);
    if( rc != SQLITE_OK )
        cout<<rc<<"error inserting into table image \n";
    else
        cout<<"inserted into table image successfully\n";
}
void database::insertallowedviewer(string username,int imageID,string imagename,int viewcount)
{
    string t = "INSERT INTO allowedviewer (username,imageID,imagename,viewcount) " \
               "VALUES ('"+username+"', "+to_string(imageID)+", '"+imagename+"', "+to_string(viewcount)+");";

    char *sql=new char [t.size()+1];
    memcpy(sql,(char*)t.c_str(),t.size()+1);
    cout<<sql;
    int rc = sqlite3_exec(db, sql, 0, 0, 0);
    if( rc != SQLITE_OK )
        cout<<"error inserting into table allowedviewer \n";
    else
        cout<<"inserted into table allowedviewer successfully\n";
}
void database::deleteuser(string username)
{

}
void database::deleteimage(string name,string username)
{
    string t = "delete from image where name= '"+name+"' and ownerusername='"+username+"';";

    char *sql=new char [t.size()+1];
    memcpy(sql,(char*)t.c_str(),t.size()+1);
    cout<<sql;
    int rc = sqlite3_exec(db, sql, 0, 0, 0);
    if( rc != SQLITE_OK )
        cout<<"error deleting from table image \n";
    else
        cout<<"deleted from table image successfully\n";
}
void database::deleteallowedviewer(int imageID)
{
    string t = "delete from allowedviewer where imageID="+to_string(imageID)+";";

    char *sql=new char [t.size()+1];
    memcpy(sql,(char*)t.c_str(),t.size()+1);
    cout<<sql;
    int rc = sqlite3_exec(db, sql, 0, 0, 0);
    if( rc != SQLITE_OK )
        cout<<"error deleting from table image \n";
    else
        cout<<"deleted from table image successfully\n";
}
bool database::selectuser(int token)    //check if username exists
{
    sqlite3_stmt * stmt;
    string t = "SELECT * from user " \
               "WHERE token ="+to_string(token)+""+";";

    char *sql=new char [t.size()+1];
    memcpy(sql,(char*)t.c_str(),t.size()+1);

    //int rc = sqlite3_exec(db, sql, 0, 0, 0);
    int rc = sqlite3_prepare_v2(db, sql,-1, &stmt, NULL);
    cout<<sql;
    if( rc != SQLITE_OK )
        cout<<"error selecting from table user \n";
    else
        cout<<"selected from table user successfully\n";
    int step = sqlite3_step(stmt);;

    if (step == SQLITE_DONE)
    {
        sqlite3_finalize(stmt);
        return false;
    }

    return true;
}
bool database::selectuser(string username)    //check if username exists
{
    sqlite3_stmt * stmt;
    string t = "SELECT * from user " \
               "WHERE username ='"+username+"'"+";";

    char *sql=new char [t.size()+1];
    memcpy(sql,(char*)t.c_str(),t.size()+1);

    //int rc = sqlite3_exec(db, sql, 0, 0, 0);
    int rc = sqlite3_prepare_v2(db, sql,-1, &stmt, NULL);
    cout<<sql;
    if( rc != SQLITE_OK )
        cout<<"error selecting from table user \n";
    else
        cout<<"selected from table user successfully\n";
    int step = sqlite3_step(stmt);;

    if (step == SQLITE_DONE)
    {
        sqlite3_finalize(stmt);
        return false;
    }
    return true;
}
bool database::selectuser(string username,int token)    //check if username exists
{
    sqlite3_stmt * stmt;
    string t = "SELECT * from user " \
               "WHERE username ='"+username+"' AND token="+to_string(token)+";";

    char *sql=new char [t.size()+1];
    memcpy(sql,(char*)t.c_str(),t.size()+1);

    //int rc = sqlite3_exec(db, sql, 0, 0, 0);
    int rc = sqlite3_prepare_v2(db, sql,-1, &stmt, NULL);
    cout<<sql;
    if( rc != SQLITE_OK )
        cout<<"error selecting from table user \n";
    else
        cout<<"selected from table user successfully\n";
    int step = sqlite3_step(stmt);;

    if (step == SQLITE_DONE)
    {
        sqlite3_finalize(stmt);
        return false;
    }

    return true;
}
string database::selectauser(int token)    //check if username exists
{
    sqlite3_stmt * stmt;
    string t = "SELECT * from user " \
               "WHERE token="+to_string(token)+";";

    char *sql=new char [t.size()+1];
    memcpy(sql,(char*)t.c_str(),t.size()+1);

    //int rc = sqlite3_exec(db, sql, 0, 0, 0);
    int rc = sqlite3_prepare_v2(db, sql,-1, &stmt, NULL);
    cout<<sql;
    if( rc != SQLITE_OK )
        cout<<"error selecting from table user \n";
    else
        cout<<"selected from table user successfully\n";
    int step = sqlite3_step(stmt);
    string s;
    if (step == SQLITE_ROW)
        s= reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    else s="";
    sqlite3_finalize(stmt);
    return s;
}
bool database::selectuser(string username,string hashedpassword)    //authenticate user
{
    sqlite3_stmt * stmt;
    string t = "SELECT * from user " \
               "WHERE username ='"+username+"'"
                                            "AND hashedpassword='"+hashedpassword+"'" +";";

    char *sql=new char [t.size()+1];
    memcpy(sql,(char*)t.c_str(),t.size()+1);

    //int rc = sqlite3_exec(db, sql, 0, 0, 0);
    int rc = sqlite3_prepare_v2(db, sql,-1, &stmt, NULL);
    if( rc != SQLITE_OK )
        cout<<"error selecting from table user \n";
    else
        cout<<"selected from table user successfully\n";
    int step = sqlite3_step(stmt);

    if (step == SQLITE_DONE)
    {
        sqlite3_finalize(stmt);
        return false;
    }

    return true;
}
void database::selectallusers(string & users,string ownerusername)
{
    users="";
    sqlite3_stmt * stmt;
    string t = "SELECT * from user ;";


    char *sql=new char [t.size()+1];
    memcpy(sql,(char*)t.c_str(),t.size()+1);

    int rc = sqlite3_prepare_v2(db, sql,-1, &stmt, NULL);
    if( rc != SQLITE_OK )
        cout<<"error selecting from table user \n";
    else
        cout<<"selected from table user successfully\n";

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        string username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        if (username!=ownerusername)
            users+=username+"\n";
    }
    users=users.substr(0, users.size()-1);

    sqlite3_finalize(stmt);

}
void database::selectimage(int & ID,string name,string ownerusername)   //select image's ID for editing views
{
    sqlite3_stmt * stmt;
    string t = "SELECT * from image " \
               "WHERE name ='"+name+"'"\
                                    " AND ownerusername='"+ownerusername+"'"+";";

    char *sql=new char [t.size()+1];
    memcpy(sql,(char*)t.c_str(),t.size()+1);
    cout<<sql;
    //int rc = sqlite3_exec(db, sql, 0, 0, 0);
    int rc = sqlite3_prepare_v2(db, sql,-1, &stmt, NULL);
    if( rc != SQLITE_OK )
        cout<<"error selecting from table image \n";
    else
        cout<<"selected from table image successfuly\n";
    int step = sqlite3_step(stmt);
    if (step == SQLITE_ROW)
        ID=sqlite3_column_int(stmt, 0);
    cout<<"ID="<<ID<<"\n";
    sqlite3_finalize(stmt);
}
void database::selectimage(int & port,string & ipaddress,string & path,string name,string ownerusername)   //select image's info for sending images
{
    sqlite3_stmt * stmt;
    string t = "SELECT * from image " \
               "WHERE name ='"+name+"'"\
                                    " AND ownerusername='"+ownerusername+"'"+";";

    char *sql=new char [t.size()+1];
    memcpy(sql,(char*)t.c_str(),t.size()+1);

    //int rc = sqlite3_exec(db, sql, 0, 0, 0);
    int rc = sqlite3_prepare_v2(db, sql,-1, &stmt, NULL);
    if( rc != SQLITE_OK )
        cout<<"error selecting from table image \n";
    else
        cout<<"selected from table image successfuly\n";
    int step = sqlite3_step(stmt);

    if (step == SQLITE_ROW)
    {
        ipaddress=reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        port=sqlite3_column_int(stmt, 4);
        path=reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
    }
    sqlite3_finalize(stmt);
}
bool database::selectimage(vector <string> &allowedimages,string ownerusername)   //select image's names for get list
{
    sqlite3_stmt * stmt;
    string t = "SELECT * from image " \
               "WHERE ownerusername='"+ownerusername+"'"+";";

    char *sql=new char [t.size()+1];
    memcpy(sql,(char*)t.c_str(),t.size()+1);

    int rc = sqlite3_prepare_v2(db, sql,-1, &stmt, NULL);
    if( rc != SQLITE_OK )
        cout<<"error selecting from table image \n";
    else
        cout<<"selected from table image successfully\n";



    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        allowedimages.push_back(name);
    }

    sqlite3_finalize(stmt);
    return true;
}
bool database::selectimage(string name,string ownerusername)   //select image's info for sending images
{
    sqlite3_stmt * stmt;
    string t = "SELECT * FROM image " \
               "WHERE name ='"+name+"'"\
                                    " AND ownerusername='"+ownerusername+"'"+";";

    char *sql=new char [t.size()+1];
    memcpy(sql,(char*)t.c_str(),t.size()+1);

    int rc = sqlite3_prepare_v2(db, sql,-1, &stmt, NULL);
    if( rc != SQLITE_OK )
        cout<<"error selecting from table image \n";
    else
        cout<<"selected from table image successfuly\n";
    int step = sqlite3_step(stmt);

    if (step == SQLITE_DONE)
    {
        sqlite3_finalize(stmt);
        return false;
    }
    else
    {
        return true;
    }
    sqlite3_finalize(stmt);
}
bool database::selectimage(string user,int imageID)   //select image's info for sending images
{
    sqlite3_stmt * stmt;
    string t = "SELECT * FROM image " \
               "WHERE ID ="+to_string(imageID)+""\
                                               " AND ownerusername='"+user+"'"+";";

    char *sql=new char [t.size()+1];
    memcpy(sql,(char*)t.c_str(),t.size()+1);
    cout<<sql<<"\n";
    //int rc = sqlite3_exec(db, sql, 0, 0, 0);
    int rc = sqlite3_prepare_v2(db, sql,-1, &stmt, NULL);
    if( rc != SQLITE_OK )
        cout<<"error selecting from table image \n";
    else
        cout<<"selected from table image successfuly\n";
    int step = sqlite3_step(stmt);

    if (step == SQLITE_DONE)
    {
        sqlite3_finalize(stmt);
        return false;
    }
    return true;
    sqlite3_finalize(stmt);
}
bool database::selectallowedviewer(string user,int imageID)   //select image's info for sending images
{
    sqlite3_stmt * stmt;
    string t = "SELECT * FROM allowedviewer " \
               "WHERE imageID ="+to_string(imageID)+""\
                                                    " AND username='"+user+"'"+";";

    char *sql=new char [t.size()+1];
    memcpy(sql,(char*)t.c_str(),t.size()+1);
    cout<<sql<<"\n";
    //int rc = sqlite3_exec(db, sql, 0, 0, 0);
    int rc = sqlite3_prepare_v2(db, sql,-1, &stmt, NULL);
    if( rc != SQLITE_OK )
        cout<<"error selecting from table allowedviewer \n";
    else
        cout<<"selected from table allowedviewer successfully\n";
    int step = sqlite3_step(stmt);


    if ((step != SQLITE_DONE)&&(sqlite3_column_int(stmt, 4)!=0))
    {
        sqlite3_finalize(stmt);
        return true;
    }
    sqlite3_finalize(stmt);
    return false;
}
void database::selectallowedviewer(string username,vector<string> &imagenames,vector<int> &viewcounts)   //get list of images
{
    sqlite3_stmt * stmt;
    string t = "SELECT * from allowedviewer " \
               "WHERE username='"+username+"'"+";";

    char *sql=new char [t.size()+1];
    memcpy(sql,(char*)t.c_str(),t.size()+1);
    cout<<sql;
    //int rc = sqlite3_exec(db, sql, 0, 0, 0);
    int rc = sqlite3_prepare_v2(db, sql,-1, &stmt, NULL);
    if( rc != SQLITE_OK )
        cout<<"error selecting from table allowedviewer \n";
    else
        cout<<"selected from table allowedviewer successfully\n";
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        int number = sqlite3_column_int(stmt, 4);
        cout<<"in database"<<name<<" "<<number<<"\n";
        imagenames.push_back(name);
        viewcounts.push_back(number);
    }
    sqlite3_finalize(stmt);
}
void database::selectallowedviewer(int imageID,vector<string> &allowedviewers,vector<int> &viewcounts)   //get list of images
{
    sqlite3_stmt * stmt;
    string t = "SELECT * from allowedviewer " \
               "WHERE imageID="+to_string(imageID)+";";

    char *sql=new char [t.size()+1];
    memcpy(sql,(char*)t.c_str(),t.size()+1);
    cout<<sql;
    //int rc = sqlite3_exec(db, sql, 0, 0, 0);
    int rc = sqlite3_prepare_v2(db, sql,-1, &stmt, NULL);
    if( rc != SQLITE_OK )
        cout<<"error selecting from table allowedviewer \n";
    else
        cout<<"selected from table allowedviewer successfully\n";
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        int number = sqlite3_column_int(stmt, 4);
        cout<<"in database"<<name<<" "<<number<<"\n";
        allowedviewers.push_back(name);
        viewcounts.push_back(number);
    }
    sqlite3_finalize(stmt);
}
void database::selectallowedviewer(vector<int> &imageID,string username,vector<string> &imagenames,vector<int> &viewcounts)   //get list of images
{
    sqlite3_stmt * stmt;
    string t = "SELECT * from allowedviewer " \
               "WHERE username='"+username+"'"+";";

    char *sql=new char [t.size()+1];
    memcpy(sql,(char*)t.c_str(),t.size()+1);
    cout<<sql;
    //int rc = sqlite3_exec(db, sql, 0, 0, 0);
    int rc = sqlite3_prepare_v2(db, sql,-1, &stmt, NULL);
    if( rc != SQLITE_OK )
        cout<<"error selecting from table allowedviewer \n";
    else
        cout<<"selected from table allowedviewer successfully\n";
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        int ID= sqlite3_column_int(stmt, 2);
        string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        int number = sqlite3_column_int(stmt, 4);
        cout<<"in database"<<name<<" "<<number<<"\n";
        imagenames.push_back(name);
        viewcounts.push_back(number);
        imageID.push_back(ID);
    }
    sqlite3_finalize(stmt);
}
void database::updateuser(string username,int token)    //creating new token
{
    string t = "UPDATE user " \
               "SET token ="+to_string(token)+" "\
                                              "WHERE username='"+username+"'"+";";
    char *sql=new char [t.size()+1];
    memcpy(sql,(char*)t.c_str(),t.size()+1);
    cout<<sql;
    int rc = sqlite3_exec(db, sql, 0, 0, 0);
    if( rc != SQLITE_OK )
        cout<<"error updating table user \n";
    else
        cout<<"updated table user successfuly\n";

}
void database::updateimage(string username,string ipaddress,int port)   //for change of port and ip address
{
    string t = "UPDATE image " \
               "SET ipaddress='"+ipaddress+"'"+", port="+to_string(port)+""\
                                                                         " WHERE ownerusername='"+username+"'"+";";
    char *sql=new char [t.size()+1];
    memcpy(sql,(char*)t.c_str(),t.size()+1);
    cout<<sql;
    int rc = sqlite3_exec(db, sql, 0, 0, 0);
    if( rc != SQLITE_OK )
        cout<<"error updating table image \n";
    else
        cout<<"updated table image successfuly\n";
}
void database::updateallowedviewer(int viewcount,string username,int imageID)   //update view count for each user for a certain image ID
{
    string t = "UPDATE allowedviewer " \
               "SET viewcount ="+to_string(viewcount)+""\
                                                      " WHERE imageID ="+to_string(imageID)+""\
                                                                                            " AND username='"+username+"'"+";";

    char *sql=new char [t.size()+1];
    memcpy(sql,(char*)t.c_str(),t.size()+1);

    int rc = sqlite3_exec(db, sql, 0, 0, 0);
    if( rc != SQLITE_OK )
        cout<<"error updating table allowedviewer \n";
    else
        cout<<"updated table allowedviewer successfuly\n";
}
void database::updateallowedviewer(string username,int imageID)   //update view count for each user for a certain image ID
{
    string t = "UPDATE allowedviewer " \
               "SET viewcount = viewcount-1"\
                                             " WHERE imageID ="+to_string(imageID)+""\
                                                                                   " AND username='"+username+"'"+";";

    char *sql=new char [t.size()+1];
    memcpy(sql,(char*)t.c_str(),t.size()+1);

    int rc = sqlite3_exec(db, sql, 0, 0, 0);
    if( rc != SQLITE_OK )
        cout<<"error updating table allowedviewer \n";
    else
        cout<<"updated table allowedviewer successfuly\n";
}
void database::deleteallowedviewer(int imageID,string username)   //update view count for each user for a certain image ID
{
    string t = "delete from allowedviewer where imageID="+to_string(imageID)+" AND username='"+username+"';";

    char *sql=new char [t.size()+1];
    memcpy(sql,(char*)t.c_str(),t.size()+1);
    cout<<sql;
    int rc = sqlite3_exec(db, sql, 0, 0, 0);
    if( rc != SQLITE_OK )
        cout<<"error deleting from table image \n";
    else
        cout<<"deleted from table image successfully\n";
}
database::~database()
{
    sqlite3_close(db);
}
