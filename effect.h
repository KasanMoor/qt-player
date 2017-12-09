#ifndef EFFECT_H
#define EFFECT_H

#include <QObject>
#include <QLinkedList>
#include <QTimer>

#include "frame.h"

class Effect : public QObject
{
    Q_OBJECT
public:
    explicit Effect(QObject *parent = nullptr);
    bool playing;
    QLinkedList<Frame*> *frameList;
    QLinkedList<Frame*>::iterator currentFrame;
    void playEffect();
    void playFrame(Frame *frame);


signals:
//    void playNextFrame(Frame *frame);

public slots:
    void playNextFrame();
    void stopPlaying();
};

#endif // EFFECT_H
