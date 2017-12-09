#include "effect.h"

Effect::Effect(QObject *parent) : QObject(parent)
{
    frameList = new QLinkedList<Frame*>;
    currentFrame = frameList->begin();
    playing = false;
}

void Effect::playEffect()
{
    currentFrame = frameList->begin();
    playFrame(*currentFrame);
}

void Effect::playFrame(Frame *frame)
{
    //drawFrame
    QTimer::singleShot(frame->duration, this, SLOT(playNextFrame()));
}

void Effect::stopPlaying()
{
    playing = false;
}

void Effect::playNextFrame()
{
    if(playing)
    {
        currentFrame++;
        playFrame(*currentFrame);
    }
}

