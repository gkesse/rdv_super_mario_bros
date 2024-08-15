#pragma once

#include "rdv_objects.h"

class rdv_score : public QGraphicsTextItem
{
public:
    explicit rdv_score(QGraphicsItem *parent = nullptr);
    ~rdv_score();
    void increase();

    int getScore() const    {return scoreCount;}

private:
    int scoreCount;
};
