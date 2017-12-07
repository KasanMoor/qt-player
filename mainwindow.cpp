#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "transmitter.h"
#include <QtDebug>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMutex>
#include <QEventLoop>
#include <QTimer>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    message = "Welcome to the Goofy Glasses toolkit\n";
    ui->message->setText(message);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connect_clicked()
{
    QByteArray data;
    qDebug() << "begining";
    transmitter = new QSerialPort();
    QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();
    QSerialPortInfo port;
    bool foundDevice = false;
    for(QSerialPortInfo p : availablePorts)
    {
        qDebug() << p.description();
        qDebug() << p.manufacturer();
        if(p.manufacturer() == "FTDI")
        {
            port = p;
            foundDevice = true;
        }
    }
    if(!foundDevice)
    {
        ui->message->setText(message.append("Error: no ftdi devices found\n"));
        qDebug() << "Error: no ftdi devices found";
    }
    transmitter->setPort(port);
    if(!transmitter->setBaudRate(57600))
    {
        ui->message->setText(message.append("Error: unable to set baud rate\n"));
        qDebug() << "Error: unable to set baud rate";
    }
    if(!transmitter->setDataBits(QSerialPort::Data8))
    {
        ui->message->setText(message.append("Error: unable to set number of bits\n"));
        qDebug() << "Error: unable to set number of bits";
    }

    if(!transmitter->setParity(QSerialPort::NoParity))
    {
        ui->message->setText(message.append("Error: unable to set parity\n"));
        qDebug() << "Error: unable to set parity";
    }
    if(!transmitter->open(QIODevice::WriteOnly))
    {
        ui->message->setText(message.append("Error: unable to open port\n"));
        qDebug() << "Error: unable to open port";
    } else
    {
        ui->message->setText(message.append("Info: port opened succesfully\n"));
        qDebug() << "Info: port opened succesfully";
    }
    data.resize(32);
    makeDark();
//    QTimer *timer = new QTimer();
//    connect(timer, SIGNAL(timeout()), this, SLOT(writeLoop));
//    timer->start(50);

}

void MainWindow::write(QByteArray data)
{
//    QMutex mutex;
//        mutex.lock();
        transmitter->write(data);
//        transmitter->waitForBytesWritten(32);
//        mutex.unlock();
}

//QTimer::singleShot(200, this, SLOT(updateCaption()));


void MainWindow::makeWhite()
{
    QByteArray data;
    for(int i=0; i<32; i++)
    {
        data[i] = 0xff;
    }
    write(data);
}

void MainWindow::makeDark()
{
    QByteArray data;
    for(int i=0; i<32; i++)
    {
        data[i] = 0x00;
    }
    write(data);
}

void MainWindow::on_white_clicked()
{
    makeWhite();
}

void MainWindow::on_dark_clicked()
{
    makeDark();
}
