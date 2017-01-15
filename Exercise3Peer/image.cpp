#include "image.h"
#include <iostream>
#include <fstream>
#include <QTextStream>
using namespace std;
Image::Image(string ownerusername,QString name,QString path)
{
    this->ownerusername=ownerusername;
    this->name=name;
    this->path=path;
    srand(time(0));
}
bool Image::marshal (char* marshalledinfo,char* marshalledimage)
{
    string fakepath="fake.jpg";
    string p=path.toStdString();
    string password=to_string(rand()%100000);
    string call="steghide embed -cf "+fakepath+" -ef "+p+" -p "+password+" -f ";
    system (call.c_str());
    QFile file (QString::fromStdString(fakepath));
    if(!file.open(QIODevice::ReadOnly))
    {
        cout<<"Failed to open file \n";
        return false;
    }
    QByteArray bytearr = file.readAll().toBase64();
    string call2="steghide extract -sf "+fakepath+" -p "+password+" -f ";
    system(call2.c_str());
    size=bytearr.size();
    memcpy(marshalledimage,bytearr.data(),bytearr.size());
    string t = (ownerusername+"\n"+name.toStdString()+"\n"+to_string(bytearr.size()))+"\n"+password;
    memcpy(marshalledinfo,(char*)t.c_str(),t.size()+1);
    return true;
}
QImage Image::unmarshal (char * marshalledinfo,char* marshalledimage)
{
    string _name;
    stringstream ss(marshalledinfo);
    string _size;
    string _password;
    getline(ss,ownerusername,'\n');
    getline(ss,_name,'\n');
    getline(ss,_size,'\n');
    getline(ss,_password,'\n');
    size=stol(_size);
    char *data = new char [size];
    memcpy(data,marshalledimage,size);
    name=QString::fromStdString(_name);
    //cout<<imageID<<"\n"<<extension<<"\n"<<maxviewcount<<"\n"<<ownerusername<<"\n"<<_name<<"\n"<<size<<"\n"<<data<<"\n";
    QByteArray bytearr(data,size);
    bytearr=QByteArray::fromBase64(bytearr);
    size=bytearr.size();
    QString fakepath="fake2.jpg";
    QFile file2(fakepath);
    file2.open(QIODevice::WriteOnly);
    file2.write(bytearr);
    file2.close();
    cout<<"password: "<<_password<<"\n";
    string call="steghide extract -sf "+fakepath.toStdString()+" -p "+_password+" -f ";
    cout<<call;
    system(call.c_str());
    path=name;
    QFile file (path);
    if(!file.open(QIODevice::ReadOnly))
    {
        cout<<"Failed to open file \n";
    }
    QByteArray bytearr2 = file.readAll();
    //path=QString::fromStdString(temp);
    cout<<path.toStdString()<<"\n";
    QFile::remove(path);
    QImage image=QImage::fromData(bytearr2,"JPG");
    return image;
}
int Image::getsize()
{
    return size;
}
string Image::getownerusername()
{
    return ownerusername;
}
QString Image::getname()
{
    return name;
}
QString Image::getpath()
{
    return path;
}
void Image::setownerusername(string username)
{
    ownerusername=username;
}
void Image::setname(QString name)
{
    this->name=name;
}
void Image::setpath(QString path)
{
    this->path=path;
}
Image::~Image ()
{

}
