#pragma once

#include "rdv_objects.h"

class rdv_stair_block : public QGraphicsItem
{
public:
	explicit rdv_stair_block(int length, QGraphicsItem *parent = nullptr);
	~rdv_stair_block();
    void nextFrame();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    int type() const    {return UserType + stairBlockType;}

private:
    int mCurrentFrame;
    QPixmap mPixmap;
    int mLength;
};
