#include "mainwindow.h"
#include "./ui_mainwindow.h"





MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);


    connect(&threadiec60870, &QThread::started, &iec60870, &ProtocolData::run);
    //если вызвался сигнал emitStop, то поток завершается
    connect(&iec60870, &ProtocolData::emitStop, &threadiec60870, &QThread::terminate);
    // передать объект в поток
    iec60870.moveToThread(&threadiec60870);

    connect(&threadiec61850, &QThread::started, &iec61850, &ProtocolData::run);
    connect(&iec61850, &ProtocolData::emitStop, &threadiec61850, &QThread::terminate);
    iec61850.moveToThread(&threadiec61850);

    connect(&threadopcua, &QThread::started, &opcua, &ProtocolData::run);
    connect(&opcua, &ProtocolData::emitStop, &threadopcua, &QThread::terminate);
    opcua.moveToThread(&threadopcua);

}

MainWindow::~MainWindow()
{
    delete ui;
}


/*---------------------------------------------------iec60870-------------------------------------------------------*/

void MainWindow::updateTextEditIec60870(float temperature, float humidity, float pressure)
{
    QString string = QString::number(temperature) + "\t" + QString::number(humidity) + "\t" + QString::number(pressure) + "\n";
    qDebug() << string;
    ui->textEdit->setText(string);
}

void MainWindow::on_pushButton_clicked()
{


    //чтобы выполнялся цикл
    iec60870.setRunning(true);
    strcpy(iec60870.NAMEDPIPE_NAME, str_iec60870.toStdString().c_str());

    //запустить поток
    threadiec60870.start();

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

    ui->textEdit->setText("");

}



/*---------------------------------------------------iec61850-------------------------------------------------------*/

void MainWindow::updateTextEditIec61850(float temperature, float humidity, float pressure)
{
    QString string = QString::number(temperature) + "\t" + QString::number(humidity) + "\t" + QString::number(pressure) + "\n";
    qDebug() << string;
    ui->textEdit_7->setText(string);
}


void MainWindow::on_pushButton_13_clicked()
{
    //чтобы выполнялся цикл
    iec61850.setRunning(true);
    strcpy(iec61850.NAMEDPIPE_NAME, str_iec61850.toStdString().c_str());

    //запустить поток
    threadiec61850.start();

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

    ui->textEdit_7->setText("");
}



