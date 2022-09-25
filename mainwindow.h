#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>


#include "protocoldata.h"
#include "protocolclient.h"
#include "processing.h"
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

    bool sign_iec60870 = false, sign_iec61850 = false, sign_opcua = false;

    QThread threadiec60870;
    ProtocolData iec60870;
    QThread threadiec60870client;
    ProtocolClient iec60870client;
    // для отправки данных на iedы
    QThread threadiec60870server;
    ProtocolClient iec60870server;
    QThread threadiec60870Handler;
    protocolServer iec60870Handler;


    QThread threadiec61850;
    ProtocolData iec61850;
    QThread threadiec61850client;
    ProtocolClient iec61850client;

    QThread threadopcua;
    ProtocolData opcua;
    QThread threadopcuaclient;
    ProtocolClient opcuaclient;

    // для шторки и полива

signals:
    void emitServer60870Curtain(int);
    void emitServer60870Pour(int);
    void emitServer61850Curtain(int);
    void emitServer61850Pour(int);
    void emitServerOpcuaCurtain(int);
    void emitServerOpcuaPour(int);





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

    bool check(int, bool);

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();



private:
    Ui::MainWindow *ui;



};
#endif // MAINWINDOW_H
