#ifndef PROTOCOLCLIENT_H
#define PROTOCOLCLIENT_H

#include <QThread>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class ProtocolClient :  public QThread
{
    Q_OBJECT
public:


    string PATH;
    string VALUE_IP, VALUE_PORT;

    public slots:
    void run();
};

#endif // PROTOCOLCLIENT_H


