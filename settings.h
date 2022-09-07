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
    QString path_client_opcua = "cd opc_ua; python client.py";
    QString time = "time";

    //для обнаружения нужных настроек в файле settings.txt
    QString ip_iec60870 = "ip_iec60870";
    QString port_iec60870 = "port_iec60870";
    QString ip_iec61850 = "ip_iec61850";
    QString port_iec61850 = "port_iec61850";
    QString ip_opc_ua = "ip_opc_ua";
    QString port_opc_ua = "port_opc_ua";


};


#endif // SETTINGS_H
