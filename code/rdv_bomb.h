#pragma once

#include "rdv_objects.h"

class rdv_bomb : public QGraphicsItem
{
public:
	explicit rdv_bomb(QRectF platformRect, int direction, QGraphicsItem *parent = nullptr);
	~rdv_bomb();
    void nextFrame();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    int type() const    {return UserType + bombType;}

private:
    int mCurrentFrame;
    QPixmap mPixmap;
    QRectF mPlatform;
    int mDirection;
};
