#ifndef SETTINGS_H
#define SETTINGS_H
#include <QString>

class Settings {
protected:
    QString str_iec60870 = "/tmp/pipe_60870";
    QString str_opcua    = "/tmp/pipe_opcua";
    QString str_iec61850 = "/tmp/pipe_61850";
    QString path_client_iec60870 = "lib60870-C/examples/cs104_client/simple_client";
    QString path_client_iec61850 = "libiec61850/examples/iec61850_client_example4/iec61850_client_example4";
    QString path_client_opcua = "cd opc_ua; python client.py"; // i don't know

};
//сделать txt файл с указанием скокрости приема протоколов и все клиенты будут брать там инфу

#endif // SETTINGS_H
