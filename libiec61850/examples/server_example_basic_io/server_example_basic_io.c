#include "iec61850_server.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "static_model.h"
#include <pthread.h>

//Расширение и дополнение функций модуля
extern IedModel iedModel;
static IedServer iedServer = NULL;
int Count = 1;

int main(int argc, char **argv)
{
    printf("Сервер запущен\n");
    //Инициализация конфигов
    IedServerConfig config = IedServerConfig_create();
    iedServer = IedServer_createWithConfig(&iedModel, NULL, config);
    IedServerConfig_destroy(config);
    IedServer_start(iedServer, 4040); // здесь порт
    //Проверка запущен ли сервер
    if (!IedServer_isRunning(iedServer))
    {
        printf("Сервер уже защущен, проверьте процессы\n");
        IedServer_destroy(iedServer);
        exit(-1);
    }
    //Работа сервера
    while (1)
    {
        printf("День %i \n", Count);
        system("python3 gen.py");
        FILE *file;
        file = fopen("gen.txt", "r");
        float num1, num2, num3;
        //Считвание данных  из файла
        while (fscanf(file, "%f%f%f", &num1, &num2, &num3) != EOF)
        {
            uint64_t timestamp = Hal_getTimeInMs();
            //Отправка данных на клиента
            IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_GenericIO_GGIO1_AnIn1_mag_f, num1);
            IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_GenericIO_GGIO1_AnIn2_mag_f, num2);
            IedServer_updateFloatAttributeValue(iedServer, IEDMODEL_GenericIO_GGIO1_AnIn3_mag_f, num3);
            IedServer_unlockDataModel(iedServer);
            Thread_sleep(1000);
        }

        Count++;
        file = fclose(file);
    }
    IedServer_stop(iedServer);
    IedServer_destroy(iedServer);
    return 0;
}
