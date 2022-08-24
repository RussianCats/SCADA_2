#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>


#include "protocoldata.h"
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



private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void updateTextEditIec60870(float,float,float);

private:
    Ui::MainWindow *ui;



};
#endif // MAINWINDOW_H
