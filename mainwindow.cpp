#include "mainwindow.h"
#include "./ui_mainwindow.h"





MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);

    // iec60870
    connect(&threadiec60870, &QThread::started, &iec60870, &ProtocolData::run);
    //если вызвался сигнал emitStop, то поток завершается
    connect(&iec60870, &ProtocolData::emitStop, &threadiec60870, &QThread::terminate);
    // передать объект в поток
    iec60870.moveToThread(&threadiec60870);

    connect(&threadiec60870client, &QThread::started, &iec60870client, &ProtocolClient::run);
    iec60870client.moveToThread(&threadiec60870client);


    // iec61850
    connect(&threadiec61850, &QThread::started, &iec61850, &ProtocolData::run);
    connect(&iec61850, &ProtocolData::emitStop, &threadiec61850, &QThread::terminate);
    iec61850.moveToThread(&threadiec61850);

    connect(&threadiec61850client, &QThread::started, &iec61850client, &ProtocolClient::run);
    iec61850client.moveToThread(&threadiec61850client);


    // opcua
    connect(&threadopcua, &QThread::started, &opcua, &ProtocolData::run);
    connect(&opcua, &ProtocolData::emitStop, &threadopcua, &QThread::terminate);
    opcua.moveToThread(&threadopcua);

    connect(&threadopcuaclient, &QThread::started, &opcuaclient, &ProtocolClient::run);
    opcuaclient.moveToThread(&threadopcuaclient);
}

MainWindow::~MainWindow()
{
    delete ui;
}


/*---------------------------------------------------iec60870-------------------------------------------------------*/

void MainWindow::updateTextEditIec60870(float temperature, float humidity, float pressure)
{
    QString string = QString::number(temperature) + "\t" + QString::number(humidity) + "\t" + QString::number(pressure) + "\n";
    //qDebug() << string;
    ui->textEdit->setText(string);
}

void MainWindow::on_pushButton_clicked()
{


    //присваиваем константы
    iec60870.NAMEDPIPE_NAME = str_iec60870;
    iec60870client.PATH = path_client_iec60870;

    //чтобы выполнялся цикл
    iec60870.setRunning(true);

    //запустить поток
    threadiec60870.start();
    threadiec60870client.start();

    qDebug() << "Кнопка нажата для iec60870";

    //при вызове сигнала emitSendData данные выводятся в gui через метод updateTextEdit
    connect(&iec60870, SIGNAL(emitSendData(float,float,float)), this, SLOT(updateTextEditIec60870(float,float,float)));
}


void MainWindow::on_pushButton_2_clicked()
{
    //чтобы остановился цикл
    iec60870.setRunning(false);

    //отключает соеденение с сигнала emitSendData и данных которые выводятся в gui через метод updateTextEdit
    disconnect(&iec60870, SIGNAL(emitSendData(float, float, float)), this, SLOT(updateTextEditIec60870(float, float, float)));

    threadiec60870.quit();
    threadiec60870client.quit();

    ui->textEdit->setText("");

}



/*---------------------------------------------------iec61850-------------------------------------------------------*/

void MainWindow::updateTextEditIec61850(float temperature, float humidity, float pressure)
{
    QString string = QString::number(temperature) + "\t" + QString::number(humidity) + "\t" + QString::number(pressure) + "\n";
    //qDebug() << string;
    ui->textEdit_7->setText(string);
}


void MainWindow::on_pushButton_13_clicked()
{

    //присваиваем константы
    iec61850.NAMEDPIPE_NAME = str_iec61850;
    iec61850client.PATH = path_client_iec61850;

    //чтобы выполнялся цикл
    iec61850.setRunning(true);

    //запустить поток
    threadiec61850.start();
    threadiec61850client.start();

    qDebug() << "Кнопка нажата для iec61850";

    //при вызове сигнала emitSendData данные выводятся в gui через метод updateTextEdit
    connect(&iec61850, SIGNAL(emitSendData(float,float,float)), this, SLOT(updateTextEditIec61850(float,float,float)));
}


void MainWindow::on_pushButton_14_clicked()
{

    //чтобы остановился цикл
    iec61850.setRunning(false);

    //отключает соеденение с сигнала emitSendData и данных которые выводятся в gui через метод updateTextEdit
    disconnect(&iec61850, SIGNAL(emitSendData(float, float, float)), this, SLOT(updateTextEditIec61850(float, float, float)));

    threadiec61850.quit();
    threadiec61850client.quit();

    ui->textEdit_7->setText("");
}



/*---------------------------------------------------opcua-------------------------------------------------------*/


void MainWindow::updateTextEditOpcua(float temperature, float humidity, float pressure)
{
    QString string = QString::number(temperature) + "\t" + QString::number(humidity) + "\t" + QString::number(pressure) + "\n";
    //qDebug() << string;
    ui->textEdit_13->setText(string);
};

void MainWindow::on_pushButton_25_clicked()
{
    //присваиваем константы
    opcua.NAMEDPIPE_NAME = str_opcua;
    opcuaclient.PATH = path_client_opcua;

    //чтобы выполнялся цикл
    opcua.setRunning(true);

    //запустить поток
    threadopcua.start();
    threadopcuaclient.start();

    qDebug() << "Кнопка нажата для opcua";

    //при вызове сигнала emitSendData данные выводятся в gui через метод updateTextEdit
    connect(&opcua, SIGNAL(emitSendData(float,float,float)), this, SLOT(updateTextEditOpcua(float,float,float)));

}


void MainWindow::on_pushButton_26_clicked()
{
    //чтобы остановился цикл
    opcua.setRunning(false);

    //отключает соеденение с сигнала emitSendData и данных которые выводятся в gui через метод updateTextEdit
    disconnect(&opcua, SIGNAL(emitSendData(float, float, float)), this, SLOT(updateTextEditOpcua(float, float, float)));

    threadopcua.quit();
    threadopcuaclient.quit();

    ui->textEdit_13->setText("");

}

