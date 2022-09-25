#include "processing.h"

protocolServer::protocolServer(QObject *parent)
    : QObject{parent}
{

}



void protocolServer::run()
{
    string str = "echo '" + std::to_string(CURTAIN) + ".0001' > "+ NAME_PIPE;
    std::system(str.c_str());
    sleep(1);
    str = "echo '" + std::to_string(POUR) + ".0001' > "+ NAME_PIPE;
    std::system(str.c_str());
    sleep(9);

    QMetaObject::invokeMethod(this, "run", Qt::QueuedConnection);

};


bool protocolServer::running() const
{
    return m_running;
}

void protocolServer::setRunning(bool newRunning)
{
    if (m_running == newRunning)
        return;
    m_running = newRunning;
    emit runningChanged(newRunning);
}

