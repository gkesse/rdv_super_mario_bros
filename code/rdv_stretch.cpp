#include "rdv_stretch.h"

rdv_stretch::rdv_stretch(QGraphicsItem *parent)
: QGraphicsItem     (parent)
, mCurrentFrame    (0)
, mPixmap          (":images/ustretch.png")
{
    setFlag(ItemClipsToShape);
}

rdv_stretch::~rdv_stretch()
{

}

void rdv_stretch::nextFrame()
{
    mCurrentFrame += 141;
    if (mCurrentFrame >= 8180)
    {
        mCurrentFrame = 0;
    }
}

QRectF rdv_stretch::boundingRect() const
{
    return QRectF(0, 0, 135, 112);
}

void rdv_stretch::paint(QPainter *painter, [[maybe_unused]] const QStyleOptionGraphicsItem *option, [[maybe_unused]] QWidget *widget)
{
    painter->drawPixmap(0, 0, mPixmap, mCurrentFrame, 0, 135, 112);
    setTransformOriginPoint(boundingRect().center());
}
