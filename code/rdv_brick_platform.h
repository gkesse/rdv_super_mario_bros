#pragma once

#include "rdv_objects.h"

class rdv_brick_platform : public QGraphicsItem
{
public:
	explicit rdv_brick_platform(int length, QGraphicsItem *parent = nullptr);
	~rdv_brick_platform();
    void nextFrame();
    QRectF boundingRect() const;
    void paint(QPainter *painter, [[maybe_unused]] const QStyleOptionGraphicsItem *option, [[maybe_unused]] QWidget *widget);

    int type() const    {return UserType + brickPlatformType;}

private:
    int mCurrentFrame;
    QPixmap mPixmap;
    int mLength;
};
