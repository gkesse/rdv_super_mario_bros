#include "rdv_giant_goomba.h"

rdv_giant_goomba::rdv_giant_goomba(QGraphicsItem *parent)
: QGraphicsItem     (parent)
, mCurrentFrame    (0)
, mPixmap          (":images/goomba.png")
{
    setFlag(ItemClipsToShape);
}

rdv_giant_goomba::~rdv_giant_goomba()
{

}

void rdv_giant_goomba::nextFrame4()
{
    mCurrentFrame += 121;
    if (mCurrentFrame >= 1899)
    {
        mCurrentFrame = 0;
    }
}

QRectF rdv_giant_goomba::boundingRect() const
{
    return QRectF(0, 0, 110, 97);
}

void rdv_giant_goomba::paint(QPainter *painter, [[maybe_unused]] const QStyleOptionGraphicsItem *option, [[maybe_unused]] QWidget *widget)
{
    painter->drawPixmap(0, 0, mPixmap, mCurrentFrame, 0, 110, 97);
    setTransformOriginPoint(boundingRect().center());
}
