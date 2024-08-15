#include "rdv_pixmap_painter.h"

rdv_pixmap_painter::rdv_pixmap_painter(const QPixmap &pixmap, QGraphicsItem * parent)
: QGraphicsPixmapItem(pixmap, parent)
{

}

QPainterPath rdv_pixmap_painter::shape() const
{
    return QPainterPath();
}
