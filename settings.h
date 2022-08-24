#ifndef SETTINGS_H
#define SETTINGS_H
#include <QString>

class Settings {
protected:
    QString str_iec60870 = "/tmp/pipe_60870";
    QString str_opcua    = "/tmp/pipe_opcua";
    QString str_iec61850 = "/tmp/pipe_61850";
};

#endif // SETTINGS_H
