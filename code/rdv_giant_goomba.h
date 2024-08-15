#pragma once

#include "rdv_objects.h"

class rdv_giant_goomba : public QGraphicsItem
{
public:
	explicit rdv_giant_goomba(QGraphicsItem *parent = nullptr);
	~rdv_giant_goomba();
    void nextFrame4();
    QRectF boundingRect() const;
    void paint(QPainter *painter, [[maybe_unused]] const QStyleOptionGraphicsItem *option, [[maybe_unused]] QWidget *widget);

    int type() const    {return UserType + giantGoombaType;}

private:
    int mCurrentFrame;
    QPixmap mPixmap;
};
