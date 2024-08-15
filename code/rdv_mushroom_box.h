#pragma once

#include "rdv_objects.h"

class rdv_mushroom_box : public QGraphicsItem
{
public:
	explicit rdv_mushroom_box(int length, QGraphicsItem *parent = nullptr);
	~rdv_mushroom_box();
    void nextFrame();
    QRectF boundingRect() const;
    void paint(QPainter *painter, [[maybe_unused]] const QStyleOptionGraphicsItem *option, [[maybe_unused]] QWidget *widget);

    int type() const    {return UserType + mushroomQuestBoxType;}

private:
    int mCurrentFrame;
    QPixmap mPixmap;
    int mLength;
};
