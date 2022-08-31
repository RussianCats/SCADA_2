#ifndef PROTOCOLCLIENT_H
#define PROTOCOLCLIENT_H

#include <QObject>
#include <QString>

class ProtocolClient  : public QObject
{
    Q_OBJECT
public:

    QString PATH;

    public slots:
    void run();
};

#endif // PROTOCOLCLIENT_H


