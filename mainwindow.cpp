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

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::updateTextEditIec60870(float temperature, float humidity, float pressure)
{
    QString string = QString::number(temperature) + "\t" + QString::number(humidity) + "\t" + QString::number(pressure) + "\n";
    qDebug() << string;
    ui->textEdit->insertPlainText(string);
}

void MainWindow::on_pushButton_clicked()
{

    //начальный текст
    ui->textEdit->insertPlainText("temperature\thumidity\tpressure\n");

    //чтобы выполнялся цикл
    iec60870.setRunning(true);
    strcpy(iec60870.NAMEDPIPE_NAME, str_iec60870.toStdString().c_str());

    //запустить поток
    threadiec60870.start();

    qDebug() << "Кнопка нажата";

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

