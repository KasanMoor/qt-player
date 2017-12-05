#include <QtDebug>
#include "transmitter.h"

Transmitter::Transmitter(QSerialPortInfo port)
{
    this->setPort(port);
//    if(!this->setBaudRate(57600))
//    {
//        qDebug() << "Error: unable to set baud rate";
//    }
//    if(!this->setDataBits(QSerialPort::Data8))
//    {
//        qDebug() << "Error: unable to set number of bits";
//    }
    //this->setParity();
    //this->setStopBits(); //defaults to 1
    //this->setFlowControl();
    if(!this->open(QIODevice::WriteOnly))
    {
        qDebug() << "Error: unable to open port";
    }
}
