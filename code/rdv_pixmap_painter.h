#pragma once

#include "rdv_objects.h"

class rdv_pixmap_painter : public QGraphicsPixmapItem
{
public:
    explicit rdv_pixmap_painter(const QPixmap &pixmap, QGraphicsItem *parent = 0);

public:
    virtual QPainterPath shape() const;
};
