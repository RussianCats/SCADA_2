

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

#include "cs104_slave.h"

#include "hal_thread.h"

//для рандома
#include <time.h>
#include <stdlib.h>

//для технологии pipe
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define BUFSIZE 50
//#define NAMEDPIPE_NAME "/tmp/pipe_processing_60870"
#include <math.h>

static bool running = true;

void sigint_handler(int signalId)
{
    running = false;
}

static bool
connectionRequestHandler(void *parameter, const char *ipAddress)
{
    printf("New connection request from %s\n", ipAddress);
    return true;
}

static void
connectionEventHandler(void *parameter, IMasterConnection con, CS104_PeerConnectionEvent event)
{
    if (event == CS104_CON_EVENT_CONNECTION_OPENED)
    {
        printf("Connection opened (%p)\n", con);
    }
    else if (event == CS104_CON_EVENT_CONNECTION_CLOSED)
    {
        printf("Connection closed (%p)\n", con);
    }
    else if (event == CS104_CON_EVENT_ACTIVATED)
    {
        printf("Connection activated (%p)\n", con);
    }
    else if (event == CS104_CON_EVENT_DEACTIVATED)
    {
        printf("Connection deactivated (%p)\n", con);
    }
}

int main(int argc, char **argv)
{
    /* Add Ctrl-C handler */
    signal(SIGINT, sigint_handler);

    /* create a new slave/server instance with default connection parameters and
     * default message queue size */
    CS104_Slave slave = CS104_Slave_create(10, 10);
    //if (argc > 1)
       // CS104_Slave_setLocalPort(slave, atoi(argv[1]));
    CS104_Slave_setLocalPort(slave, 4850);


    CS104_Slave_setLocalAddress(slave, "0.0.0.0");

    /* Set mode to a single redundancy group
     * NOTE: library has to be compiled with CONFIG_CS104_SUPPORT_SERVER_MODE_SINGLE_REDUNDANCY_GROUP enabled (=1)
     */
    CS104_Slave_setServerMode(slave, CS104_MODE_SINGLE_REDUNDANCY_GROUP);

    /* /* получить параметры подключения - они нужны нам для создания правильных ASDUS -
     * вы также можете изменить параметры здесь, когда параметры по умолчанию не должны использоваться */
    CS101_AppLayerParameters alParams = CS104_Slave_getAppLayerParameters(slave);

    /* установить обработчик для обработки запросов на подключение. New connection request from [ip]*/
    CS104_Slave_setConnectionRequestHandler(slave, connectionRequestHandler, NULL);

    /* установить обработчик для отслеживания событий подключения. activated/closed */
    CS104_Slave_setConnectionEventHandler(slave, connectionEventHandler, NULL);

    CS104_Slave_start(slave);

    if (CS104_Slave_isRunning(slave) == false)
    {
        printf("Starting server failed!\n");
        goto exit_program;
    }

    float arr_value[96][3];

    // float var[3][4] = {{30, 25, 35, 0.01}, {60, 30, 90, 0.05}, {760, 650, 1030, 0.5}}; //{{переменная, нижний_край, верхний_край, шаг_изменения}}

    while (running)
    {
        printf("\nшторка и полив\n\n");

        int fd, len;
        char buf[BUFSIZE];
        float floatData = 0;
        int num_point = 0;
        char NAMEDPIPE_NAME[] = "/tmp/pipe_processing_60870";

        for (int j = 0; j < 2; j++)
        {
            floatData = 0;

            mkfifo(NAMEDPIPE_NAME, 0777);
            fd = open(NAMEDPIPE_NAME, O_RDONLY);
            memset(buf, '\0', BUFSIZE);
            len = read(fd, buf, BUFSIZE - 1);
            close(fd);
            remove(NAMEDPIPE_NAME);

            //хитровыебанная функция перевода char в float
            for (int k = 0; k < strlen(buf); k++)
            {
                if (buf[k] == '.')
                    num_point = k;
            }

            for (int k = 0; k < num_point; k++)
            {
                floatData += ((int)(buf[k]) - 48) * pow(10, (num_point - k - 1));
            };

            for (int k = 0; k < strlen(buf) - num_point - 1; k++)
            {
                floatData += ((int)(buf[k + num_point + 1]) - 48) / pow(10, (k + 1));
            }

            CS101_ASDU newAsdu = CS101_ASDU_create(alParams, false, CS101_COT_PERIODIC, 0, 1, false, false);
            // var[i][0] = greenhouse_variables(var[i][0], var[i][1], var[i][2], var[i][3]);

            InformationObject io = (InformationObject)ParameterFloatValue_create(NULL, 110 + j, floatData, IEC60870_QUALITY_GOOD); // тип данных float

            CS101_ASDU_addInformationObject(newAsdu, io);

            InformationObject_destroy(io);

            /* Add ASDU to slave event queue */
            CS104_Slave_enqueueASDU(slave, newAsdu);

            CS101_ASDU_destroy(newAsdu);

            // Thread_sleep(10000); // время задержки данных
        }

        if (CS104_CON_EVENT_CONNECTION_OPENED)
            running = false;
    }

    CS104_Slave_stop(slave);

exit_program:
    CS104_Slave_destroy(slave);

    Thread_sleep(10);
}
