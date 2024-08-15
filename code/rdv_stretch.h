#pragma once

#include "rdv_objects.h"

class rdv_stretch : public QGraphicsItem
{
public:
	explicit rdv_stretch(QGraphicsItem *parent = nullptr);
	~rdv_stretch();
    void nextFrame();
    QRectF boundingRect() const;
    void paint(QPainter *painter, [[maybe_unused]] const QStyleOptionGraphicsItem *option, [[maybe_unused]] QWidget *widget);

    int type() const    {return UserType + stretchType;}

private:
    int mCurrentFrame;
    QPixmap mPixmap;
};
