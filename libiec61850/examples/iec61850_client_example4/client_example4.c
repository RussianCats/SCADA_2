#include "iec61850_client.h"
#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "hal_thread.h"


static void
printDataSetValues(MmsValue *dataSet)
{
    int i, n;
    float value;
    char echo[] = "echo '";
    char tmp[] = "' > /tmp/pipe_iec61850  ";
    for (i = 0; i < 3; i++)
    {

        printf("  GGIO1.AnIn%i.mag.f: %f\n", i, MmsValue_toFloat(MmsValue_getElement(MmsValue_getElement(MmsValue_getElement(dataSet, i), 0), 0)));

        char buff[64];
        value = MmsValue_toFloat(MmsValue_getElement(MmsValue_getElement(MmsValue_getElement(dataSet, i), 0), 0));

        int ret = snprintf(buff, sizeof buff, "%f", value);

        char all[255];

        for (int var = 0; var < 6; var++) all[var] = echo[var];
        for (int var = 0; var < strlen(buff); var++) all[var + 6] = buff[var];
        for (int var = 0; var < 24; var++) all[var + 6 + strlen(buff)] = tmp[var];






        //отправка данных на iec60870.cpp через pipe
        system(all);
    }
}

int main(int argc, char **argv)
{

    char *hostname;
    int tcpPort = 4040;
    if (argc > 1)
        hostname = argv[1];
    else
        hostname = "localhost";

    if (argc > 2)
        tcpPort = atoi(argv[2]);

    IedClientError error;

    IedConnection con = IedConnection_create();
    while (1)
    {
        IedConnection_connect(con, &error, hostname, tcpPort);
        Thread_sleep(1000);
        if (error == IED_ERROR_OK)
        {

            LinkedList newDataSetEntries = LinkedList_create();

            LinkedList_add(newDataSetEntries, "simpleIOGenericIO/GGIO1.AnIn1[MX]");
            LinkedList_add(newDataSetEntries, "simpleIOGenericIO/GGIO1.AnIn2[MX]");
            LinkedList_add(newDataSetEntries, "simpleIOGenericIO/GGIO1.AnIn3[MX]");
            IedConnection_createDataSet(con, &error, "simpleIOGenericIO/LLN0.AnalogueValues", newDataSetEntries);

            LinkedList_destroyStatic(newDataSetEntries);

            if (error == IED_ERROR_OK)
            {

                ClientDataSet clientDataSet;

                clientDataSet = IedConnection_readDataSetValues(con, &error, "simpleIOGenericIO/LLN0.AnalogueValues", NULL);

                if (error == IED_ERROR_OK)
                {
                    printDataSetValues(ClientDataSet_getValues(clientDataSet));

                    ClientDataSet_destroy(clientDataSet);
                }
                else
                {
                    printf("Failed to read data set (error code: %d)\n", error);
                }

                IedConnection_deleteDataSet(con, &error, "simpleIOGenericIO/LLN0.AnalogueValues");
            }
            else
            {
                printf("Failed to create data set (error code: %d)\n", error);
            }

            IedConnection_close(con);
        }
        else
        {
            printf("Failed to connect to %s:%i\n", hostname, tcpPort);
        }
    }
    IedConnection_destroy(con);
}
