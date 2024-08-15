#include "rdv_warp_tube.h"

rdv_warp_tube::rdv_warp_tube(QGraphicsItem *parent)
: QGraphicsItem     (parent)
, mCurrentFrame     (0)
, mPixmap           (":images/Warp.png")
{
    setFlag(ItemClipsToShape);
}

rdv_warp_tube::~rdv_warp_tube()
{

}

void rdv_warp_tube::nextFrame()
{
    mCurrentFrame += 54;
    if (mCurrentFrame >= 862)
    {
        mCurrentFrame = 0;
    }
}

QRectF rdv_warp_tube::boundingRect() const
{
    return QRectF(0, 0, 70, 100);
}

void rdv_warp_tube::paint(QPainter *painter, [[maybe_unused]] const QStyleOptionGraphicsItem *option, [[maybe_unused]] QWidget *widget)
{
    painter->drawPixmap(0, 0, mPixmap, mCurrentFrame, 0, 70, 100);
    setTransformOriginPoint(boundingRect().center());
}
