#include "rdv_brick_platform.h"

rdv_brick_platform::rdv_brick_platform(int length, QGraphicsItem *parent)
: QGraphicsItem     (parent)
, mCurrentFrame     (0)
, mPixmap           (":images/brick3.png")
, mLength           (length)
{
    setFlag(ItemClipsToShape);
}

rdv_brick_platform::~rdv_brick_platform()
{

}

void rdv_brick_platform::nextFrame()
{
    mCurrentFrame += 48;
    if (mCurrentFrame >= 768 )
    {
        mCurrentFrame = 0;
    }
}

QRectF rdv_brick_platform::boundingRect() const
{
    return QRectF(0, 0, 48*mLength, 48);
}

void rdv_brick_platform::paint(QPainter *painter, [[maybe_unused]] const QStyleOptionGraphicsItem *option, [[maybe_unused]] QWidget *widget)
{
    for(int i = 0; i < 48*mLength; ++i)
    {
        painter->drawPixmap(i*48, 0, mPixmap, mCurrentFrame, 0, 48, 48);
    }
    setTransformOriginPoint(boundingRect().center());
}
