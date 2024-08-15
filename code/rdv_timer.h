#pragma once

#include "rdv_objects.h"

class rdv_timer : public QGraphicsTextItem
{
public:
    explicit rdv_timer(QGraphicsItem *parent = nullptr);
    ~rdv_timer();
    void decrease();
    void timerEvent(QTimerEvent *);

    int getTime() const     {return timeCount;}

private:
    int timeCount;
};
