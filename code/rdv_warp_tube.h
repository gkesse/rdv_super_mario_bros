#pragma once

#include "rdv_objects.h"

class rdv_warp_tube : public QGraphicsItem
{
public:
	explicit rdv_warp_tube(QGraphicsItem *parent = nullptr);
	~rdv_warp_tube();
    void nextFrame();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    int type() const    {return UserType + warpTubeType;}

private:
    int mCurrentFrame;
    QPixmap mPixmap;
};
