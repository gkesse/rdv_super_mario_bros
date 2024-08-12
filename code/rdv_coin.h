#pragma once

#include "rdv_objects.h"

class rdv_coin : public QGraphicsItem
{
public:
	explicit rdv_coin(QGraphicsItem *parent = nullptr);
	~rdv_coin();
    void nextFrame2();
    QRectF boundingRect() const;
    void paint(QPainter *painter, [[maybe_unused]] const QStyleOptionGraphicsItem *option, [[maybe_unused]] QWidget *widget);

    int type() const    {return UserType + coinType;}

private:
    int mCurrentFrame2;
    QPixmap mPixmap2;
};
