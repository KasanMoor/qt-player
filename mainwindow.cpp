#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "transmitter.h"
#include <QtDebug>
#include <QSerialPort>
#include <QSerialPortInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    qDebug() << "begining";
    Transmitter *transmitter;
    QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();
    for(QSerialPortInfo port : availablePorts)
    {
        qDebug() << port.description();
        qDebug() << port.manufacturer();
        if(port.manufacturer() == "FTDI")
        {
            transmitter = new Transmitter(port);
        }
    }
}

//QTimer::singleShot(200, this, SLOT(updateCaption()));
