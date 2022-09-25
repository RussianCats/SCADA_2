#ifndef PROTOCOLCLIENT_H
#define PROTOCOLCLIENT_H

#include <QObject>
#include <string>
#include <fstream>
#include <vector>	
#include "settings.h"


using namespace std;

class ProtocolClient : public QObject, public Settings
{
    Q_OBJECT
public:

    string PATH;
    string VALUE_IP, VALUE_PORT;

    public slots:
    void run();
    void runServ();
};

#endif // PROTOCOLCLIENT_H


