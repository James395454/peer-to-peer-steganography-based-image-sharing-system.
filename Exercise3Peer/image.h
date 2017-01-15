#ifndef IMAGE_H
#define IMAGE_H
#include <arpa/inet.h>
#include <QByteArray>
#include <QFile>
#include <string>
#include <fstream>
#include <sstream>
#include <QImage>
using namespace std;
class Image
{
private:
    int maxviewcount;
    string ownerusername;
    QString name;
    QString path;
    int size;
public:
    Image(string ownerusername,QString name,QString path);
    Image (){}
    int getimageID();
    int getsize();
    string getownerusername();
    QString  getname();
    QString getpath();
    void setownerusername(string);
    void setname(QString);
    void setpath(QString);
    bool marshal (char* marshalledinfo,char* marshalledimage);
    QImage unmarshal (char * marshalledinfo,char* marshalledimage);
    ~Image ();
};

#endif // IMAGE_H
