#ifndef TRANSMITTER_H
#define TRANSMITTER_H

#include<QSerialPort>
#include<QSerialPortInfo>

class Transmitter : public QSerialPort
{
public:
    Transmitter(QSerialPortInfo port);
};

#endif // TRANSMITTER_H
