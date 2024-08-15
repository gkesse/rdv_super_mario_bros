#include "rdv_red_turtle.h"

rdv_red_turtle::rdv_red_turtle(QRectF platformRect, int direction, QGraphicsItem *parent)
: QGraphicsItem     (parent)
, mCurrentFrame     (0)
, mPixmap           (":images/redt.png")
, mPlatform         (platformRect)
, mDirection        (direction)
{
    setFlag(ItemClipsToShape);
}

rdv_red_turtle::~rdv_red_turtle()
{

}

void rdv_red_turtle::nextFrame()
{
    mCurrentFrame += 179;
    if (mCurrentFrame >= 3521)
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

QRectF rdv_red_turtle::boundingRect() const
{
    return QRectF(0, 0, 130, 146);
}

void rdv_red_turtle::paint(QPainter *painter, [[maybe_unused]] const QStyleOptionGraphicsItem *option, [[maybe_unused]] QWidget *widget)
{
    painter->drawPixmap(0, 0, mPixmap, mCurrentFrame, 0, 130, 146);
    setTransformOriginPoint(boundingRect().center());
}
