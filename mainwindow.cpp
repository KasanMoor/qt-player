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
#include <windows.h>
#include <QFileDialog>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    message = "Welcome to the Goofy Glasses toolkit\n";
    ui->message->setText(message);
    transmitter = new QSerialPort();
    playing = false;
    data.resize(32);
    setColor(0x00);
    on_connect_clicked();
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(write()));
    timer->start(100);
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
}

MainWindow::~MainWindow()
{
    transmitter->close();
    delete ui;
}

void MainWindow::write()
{
    transmitter->write(data);
    transmitter->waitForBytesWritten(32);
}

void MainWindow::setColor(qint8 color)
{
    QMutex mutex;
    mutex.lock();
    for(int i=0; i<32; i++)
    {
        data[i] = color;
    }
    mutex.unlock();
}

void MainWindow::setColor(qint8 color1, qint8 color2, qint8 color3)
{
    QMutex mutex;
    mutex.lock();
    for(int i=0; i<32; i+=3)
    {
        data[i] = color1;
        data[i+1] = color2;
        data[i+2] = color3;
    }
    mutex.unlock();
}

void MainWindow::on_white_clicked()
{
    setColor(0xff);
}

void MainWindow::on_dark_clicked()
{
    playing = false;
    setColor(0x00);
}

void MainWindow::on_disconnect_clicked()
{
    if(transmitter->isOpen())
    {
        transmitter->close();
        info("Closed serial port");
    } else
    {
        error("No port connected");
    }
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



void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open effect"), "/", tr("Tan Files (*.tan2)"));
}

void MainWindow::on_gold_clicked()
{
    setColor(255, 223, 0);
}

void MainWindow::on_red_clicked()
{
    setColor(0xff, 0, 0);
}

void MainWindow::on_green_clicked()
{
    setColor(0, 0xff, 0);
}
