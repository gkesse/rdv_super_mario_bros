#pragma once

#include "rdv_objects.h"

class rdv_wall_platform : public QGraphicsItem
{
public:
	explicit rdv_wall_platform(int length, QGraphicsItem *parent = nullptr);
	~rdv_wall_platform();
    void nextFrame();
    QRectF boundingRect() const;
    void paint(QPainter *painter, [[maybe_unused]] const QStyleOptionGraphicsItem *option, [[maybe_unused]] QWidget *widget);

    int type() const    {return UserType + wallPlatformType;}

private:
    int mCurrentFrame;
    QPixmap mPixmap;
    int mLength;
};
