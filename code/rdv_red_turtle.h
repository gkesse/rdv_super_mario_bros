#pragma once

#include "rdv_objects.h"

class rdv_red_turtle : public QGraphicsItem
{
public:
	explicit rdv_red_turtle(QRectF platformRect, int direction, QGraphicsItem *parent = nullptr);
	~rdv_red_turtle();
    void nextFrame();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    int type() const    {return UserType + redTurtleType;}

private:
    int mCurrentFrame;
    QPixmap mPixmap;
    QRectF mPlatform;
    int mDirection;
};
