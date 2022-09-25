#ifndef PROCESSING_H
#define PROCESSING_H

#include <QObject>
#include <string>
#include <fstream>
#include <vector>
#include <unistd.h>

using namespace std;

class protocolServer : public QObject
{
    Q_OBJECT
    //переменная по которой будем выходить из цикла и завершать выполнение метода
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged);

    bool m_running;

public:
    int CURTAIN = 0;
    int POUR = 0;
    string NAME_PIPE;

    explicit protocolServer(QObject *parent = nullptr);
    bool running() const;

signals:
    void runningChanged(bool newRunning);

public slots:
    void run();

    void setRunning(bool newRunning);



};

#endif // PROCESSING_H
