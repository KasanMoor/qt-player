#ifndef FRAME_H
#define FRAME_H

#include <QObject>

class Frame : public QObject
{
    Q_OBJECT
public:
    explicit Frame(QObject *parent = nullptr);
    int duration;
    QByteArray data;

signals:

public slots:
};

#endif // FRAME_H
