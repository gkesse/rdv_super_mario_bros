#pragma once

#include "rdv_objects.h"

class rdv_spiny : public QGraphicsItem
{
public:
	explicit rdv_spiny(QRectF platformRect, int direction, QGraphicsItem *parent = nullptr);
	~rdv_spiny();
    void nextFrame();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    int type() const    {return UserType + spinyType;}

private:
    int mCurrentFrame;
    QPixmap mPixmap;
    QRectF mPlatform;
    int mDirection;
};
