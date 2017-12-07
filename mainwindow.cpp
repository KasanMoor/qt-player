#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "transmitter.h"
#include <QtDebug>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMutex>
#include <QEventLoop>
#include <QTimer>
#include <QScrollBar>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    message = "Welcome to the Goofy Glasses toolkit\n";
    ui->message->setText(message);
    transmitter = new QSerialPort();
    on_connect_clicked();
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(write));
    timer->start(50);
}

void MainWindow::on_connect_clicked()
{
    qDebug() << "begining";
    if(transmitter->isOpen())
    {
        error("Device already connected");
        return;
    }
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
        error("No ftdi devices found");
        qDebug() << "Error: no ftdi devices found";
    }
    transmitter->setPort(port);
    if(!transmitter->setBaudRate(57600))
    {
        error("Unable to set baud rate");
        qDebug() << "Error: unable to set baud rate";
    }
    if(!transmitter->setDataBits(QSerialPort::Data8))
    {
        error("Unable to set number of bits");
        qDebug() << "Error: unable to set number of bits";
    }

    if(!transmitter->setParity(QSerialPort::NoParity))
    {
        error("unable to set parity");
        qDebug() << "Error: unable to set parity";
    }
    if(!transmitter->open(QIODevice::WriteOnly))
    {
        error("Unable to open port");
        qDebug() << "Error: unable to open port";
    } else
    {
        info("port opened succesfully");
        qDebug() << "Info: port opened succesfully";
    }
//    data.resize(32);
//    setColor(0x00);
//    QTimer *timer = new QTimer();
//    connect(timer, SIGNAL(timeout()), this, SLOT(writeLoop));
//    timer->start(50);
}

MainWindow::~MainWindow()
{
    transmitter->close();
    delete ui;
}



void MainWindow::write(QByteArray data)
{
//    QMutex mutex;
//        mutex.lock();
        transmitter->write(data);
        transmitter->waitForBytesWritten(32);
//        mutex.unlock();
}

//QTimer::singleShot(200, this, SLOT(updateCaption()));


void MainWindow::setColor(qint8 color)
{
    QByteArray data;
    data.resize(32);
    for(int i=0; i<32; i++)
    {
        data[i] = color;
    }
    write(data);
}

void MainWindow::on_white_clicked()
{
    setColor(0xff);
}

void MainWindow::on_dark_clicked()
{
    setColor(0x00);
}

void MainWindow::on_disconnect_clicked()
{
    transmitter->close();
    info("Closed serial port");
}

void MainWindow::info(QString text)
{
    ui->message->setText(this->message.append("Info: " + text + "\n"));
    ui->message->verticalScrollBar()->setValue(
    ui->message->verticalScrollBar()->maximum());
}

void MainWindow::error(QString text)
{
    ui->message->setText(this->message.append("Error: " + text + "\n"));
    ui->message->verticalScrollBar()->setValue(
    ui->message->verticalScrollBar()->maximum());
}

void MainWindow::playEffect(/*Effect effect*/)
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(write()));
    //for(Frame frames : effect)
    while(playing)
    {
        //for(Frame frames : effect.Frames)
        {
            timer->singleShot()
        }
    }
}

