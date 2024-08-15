#pragma once

#include "rdv_objects.h"

class rdv_piranha : public QGraphicsItem
{
public:
	explicit rdv_piranha(QGraphicsItem *parent = nullptr);
	~rdv_piranha();
    void nextFrame();
    QRectF boundingRect() const;
    void paint(QPainter *painter, [[maybe_unused]] const QStyleOptionGraphicsItem *option, [[maybe_unused]] QWidget *widget);

    int type() const    {return UserType + piranhaType;}

private:
    int mCurrentFrame;
    QPixmap mPixmap;
};
