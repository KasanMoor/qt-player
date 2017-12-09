#include "frame.h"

Frame::Frame(QObject *parent) : QObject(parent)
{
    data.resize(32);
}
