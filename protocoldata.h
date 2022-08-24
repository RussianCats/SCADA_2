#ifndef PROTOCOLDATA_H
#define PROTOCOLDATA_H


#include <QObject>
#include <QDebug>
#include <QString>

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

//для технологии pipe
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


//#define NAMEDPIPE_NAME "/tmp/pipe_60870" "/tmp/pipe_opcua" "/tmp/pipe_61850"

//#define BUFSIZE 50



//#define QUANTITY_TRANSFER 96 * 3

class ProtocolData : public QObject
{
    Q_OBJECT
    //переменная по которой будем выходить из цикла и завершать выполнение метода
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged);



public:
    //константы которые будут свои для каждого объекта класса
    char NAMEDPIPE_NAME[16];
    int BUFSIZE = 50;



    explicit ProtocolData(QObject *parent = nullptr);
    bool running() const;
    void setRunning(bool newRunning);

signals:
    //чтобы завершить поток
    void emitStop();
    //отправлять данные с протокола
    void emitSendData(float temperature, float humidity, float pressure);

    void runningChanged();

public slots:
    // слот создает pipe и берет данные из pipe
    void run();

private:
    bool m_running;
};

#endif // PROTOCOLDATA_H
