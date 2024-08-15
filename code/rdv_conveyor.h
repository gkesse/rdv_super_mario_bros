#pragma once

#include "rdv_objects.h"

class rdv_conveyor : public QGraphicsItem
{
public:
	explicit rdv_conveyor(QGraphicsItem *parent = nullptr);
	~rdv_conveyor();
    void nextFrame();
    QRectF boundingRect() const;
    void paint(QPainter *painter, [[maybe_unused]] const QStyleOptionGraphicsItem *option, [[maybe_unused]] QWidget *widget);

private:
    int mCurrentFrame;
    QPixmap mPixmap;
};
