#pragma once

#include "rdv_objects.h"

class rdv_coin_counter : public QGraphicsTextItem
{
public:
    explicit rdv_coin_counter(QGraphicsItem *parent = nullptr);
    ~rdv_coin_counter();
    void increase();

    int getCount() const    {return coinCount;}

private:
    int coinCount;
};
