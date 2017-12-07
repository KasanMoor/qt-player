#include <QtDebug>
#include "transmitter.h"

Transmitter::Transmitter(QSerialPortInfo port)
{
    this->setPort(port);
    if(!this->setBaudRate(57600))
    {
        qDebug() << "Error: unable to set baud rate";
    }
    if(!this->setDataBits(QSerialPort::Data8))
    {
        qDebug() << "Error: unable to set number of bits";
    }
    //this->setParity();
    //this->setStopBits(); //defaults to 1
    //this->setFlowControl();
    if(!this->open(QIODevice::WriteOnly))
    {
        qDebug() << "Error: unable to open port";
    } else
    {
        qDebug() << "Info: port opened succesfully";
    }

    QByteArray data;
    data.resize(32);
    for(int i=0; i<32; i++)
    {
        data[i] = 0xff;
    }

    for(;;)
    {
        qDebug() << this->write(data);
    }

    this->close();
}
