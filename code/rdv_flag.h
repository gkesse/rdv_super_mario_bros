#pragma once

#include "rdv_objects.h"

class rdv_flag : public QGraphicsItem
{
public:
	explicit rdv_flag(QGraphicsItem *parent = nullptr);
	~rdv_flag();
	void nextFrame();
    QRectF boundingRect() const;
    void paint(QPainter *painter, [[maybe_unused]] const QStyleOptionGraphicsItem *option, [[maybe_unused]] QWidget *widget);

    int type() const    {return UserType + flagType;}

private:
    int mCurrentFrame;
    QPixmap mPixmap;
};
