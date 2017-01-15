#include <iostream>
#include <cstring>
#include <thread>
#include "server.h"
#include "message.h"
using namespace std;

int main(int argc, char *argv[])
{  
    string port=argv[2];
    Server server (argv[1],stoi(port));
    server.listen();
    cout<<"done\n";
    return 0;
}
