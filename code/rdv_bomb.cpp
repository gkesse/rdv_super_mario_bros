#include "rdv_bomb.h"

rdv_bomb::rdv_bomb(QRectF platformRect, int direction, QGraphicsItem *parent)
: QGraphicsItem     (parent)
, mCurrentFrame     (0)
, mPixmap           (":images/bomb.png")
, mPlatform         (platformRect)
, mDirection        (direction)
{
    setFlag(ItemClipsToShape);
}

rdv_bomb::~rdv_bomb()
{

}

void rdv_bomb::nextFrame()
{
    mCurrentFrame += 129;
    if (mCurrentFrame >= 2579)
    {
        mCurrentFrame = 0;
    }
    if(pos().x() < mPlatform.x() || pos().x() > mPlatform.x()+ mPlatform.width())
    {
        mDirection = -mDirection;
        setTransform(QTransform(-mDirection, 0, 0, 1, boundingRect().width(), 0));
    }
    setPos(pos().x() + (mDirection*7), pos().y());
}

QRectF rdv_bomb::boundingRect() const
{
    return QRectF(0, 0, 130, 123);
}

void rdv_bomb::paint(QPainter *painter, [[maybe_unused]] const QStyleOptionGraphicsItem *option, [[maybe_unused]] QWidget *widget)
{
    painter->drawPixmap(0, 0, mPixmap, mCurrentFrame, 0, 130, 123);
    setTransformOriginPoint(boundingRect().center());
}
