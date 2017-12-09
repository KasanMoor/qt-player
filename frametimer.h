#ifndef FRAMETIMER_H
#define FRAMETIMER_H

#include <QObject>
#include <QTimer>

class FrameTimer : public QTimer
{
    Q_OBJECT
public:
    explicit FrameTimer(QObject *parent = nullptr);
    Frame *frame;

signals:
    void timeout(Frame* frame);
public slots:
};

#endif // FRAMETIMER_H
