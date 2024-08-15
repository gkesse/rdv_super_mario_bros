#include "rdv_piranha.h"

rdv_piranha::rdv_piranha(QGraphicsItem *parent)
: QGraphicsItem     (parent)
, mCurrentFrame     (0)
, mPixmap           (":images/piranha.png")
{
    setFlag(ItemClipsToShape);
}

rdv_piranha::~rdv_piranha()
{

}

void rdv_piranha::nextFrame()
{
    mCurrentFrame += 387;
    if (mCurrentFrame >= 9286)
    {
        mCurrentFrame = 0;
    }
}

QRectF rdv_piranha::boundingRect() const
{
    return QRectF(0, 0, 130, 165);
}

void rdv_piranha::paint(QPainter *painter, [[maybe_unused]] const QStyleOptionGraphicsItem *option, [[maybe_unused]] QWidget *widget)
{
    painter->drawPixmap(0, 0, mPixmap, mCurrentFrame, 0, 130, 165);
    setTransformOriginPoint(boundingRect().center());
}
