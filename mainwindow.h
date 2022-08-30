#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>


#include "protocoldata.h"
#include "protocolclient.h"
#include "settings.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public Settings
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QThread threadiec60870;
    ProtocolData iec60870;
    QThread threadiec60870client;
    ProtocolClient iec60870client;

    QThread threadiec61850;
    ProtocolData iec61850;
    QThread threadiec61850client;
    ProtocolClient iec61850client;

    QThread threadopcua;
    ProtocolData opcua;
    QThread threadopcuaclient;
    ProtocolClient opcuaclient;



private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void updateTextEditIec60870(float,float,float);

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void updateTextEditIec61850(float,float,float);

    void on_pushButton_25_clicked();

    void on_pushButton_26_clicked();

    void updateTextEditOpcua(float, float, float);

private:
    Ui::MainWindow *ui;



};
#endif // MAINWINDOW_H
