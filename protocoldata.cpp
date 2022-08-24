#include "protocoldata.h"




ProtocolData::ProtocolData(QObject *parent)
    : QObject{parent}
{

}



void ProtocolData::run()
{
    int fd, len;
    char buf[BUFSIZE];
    float floatData[3] = {0, 0, 0};
    int num_point = 0;

    while(m_running)
    {



        for (int i = 0; i < 96; i++)
        {

            for (int j = 0; j < 3; j++)
            {
                mkfifo(NAMEDPIPE_NAME, 0777);
                // perror("mkfifo");
                // return 1;

                // printf("%s is created\n", NAMEDPIPE_NAME);

                fd = open(NAMEDPIPE_NAME, O_RDONLY);
                // perror("open");
                // return 1;
                // printf("%s is opened\n", NAMEDPIPE_NAME);


                memset(buf, '\0', BUFSIZE);
                len = read(fd, buf, BUFSIZE - 1);

                // perror("read");
                close(fd);
                remove(NAMEDPIPE_NAME);

                printf("Incomming message (%d): %s\n", len, buf);




                //хитровыебанная функция перевода char в float
                for (int k = 0; k < strlen(buf); k++)
                {
                    if (buf[k] == '.')
                        num_point = k;
                }

                for (int k = 0; k < num_point; k++)
                {
                    floatData[j] += ((int)(buf[k]) - 48) * pow(10, (num_point - k - 1));
                };

                for (int k = 0; k < strlen(buf) - num_point - 1; k++)
                {
                    floatData[j] += ((int)(buf[k + num_point + 1]) - 48) / pow(10, (k + 1));
                }
            }

            printf("floatData %f %f %f \n", floatData[0], floatData[1], floatData[2]);

            //отправка данных в основной поток через connent
            emit emitSendData(floatData[0], floatData[1], floatData[2]);
            floatData[0] = 0;
            floatData[1] = 0;
            floatData[2] = 0;

        }
    }

    //остановка потока
    emit emitStop();
};

bool ProtocolData::running() const
{
    return m_running;
}

void ProtocolData::setRunning(bool newRunning)
{
    if (m_running == newRunning)
        return;
    m_running = newRunning;
    emit runningChanged();
}
