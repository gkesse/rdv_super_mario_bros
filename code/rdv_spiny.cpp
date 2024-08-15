#include "rdv_spiny.h"

rdv_spiny::rdv_spiny(QRectF platformRect, int direction, QGraphicsItem *parent)
: QGraphicsItem     (parent)
, mCurrentFrame     (0)
, mPixmap           (":images/spiny.png")
, mPlatform         (platformRect)
, mDirection        (direction)
{
    setFlag(ItemClipsToShape);
}

rdv_spiny::~rdv_spiny()
{

}

void rdv_spiny::nextFrame()
{
    mCurrentFrame += 238;
    if (mCurrentFrame >= 3569)
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

QRectF rdv_spiny::boundingRect() const
{
    return QRectF(0, 0, 120, 93);
}

void rdv_spiny::paint(QPainter *painter, [[maybe_unused]] const QStyleOptionGraphicsItem *option, [[maybe_unused]] QWidget *widget)
{
    painter->drawPixmap(0, 0, mPixmap, mCurrentFrame, 0, 120, 93);
    setTransformOriginPoint(boundingRect().center());
}
