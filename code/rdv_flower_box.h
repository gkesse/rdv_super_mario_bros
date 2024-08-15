#pragma once

#include "rdv_objects.h"

class rdv_flower_box : public QGraphicsItem
{
public:
	explicit rdv_flower_box(int length, QGraphicsItem *parent = nullptr);
	~rdv_flower_box();
    void nextFrame();
    QRectF boundingRect() const;
    void paint(QPainter *painter, [[maybe_unused]] const QStyleOptionGraphicsItem *option, [[maybe_unused]] QWidget *widget);

    int type() const    {return UserType + flowerQuestBoxType;}

private:
    int mCurrentFrame;
    QPixmap mPixmap;
    int mLength;
};
