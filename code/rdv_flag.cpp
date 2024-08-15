#include "rdv_flag.h"

rdv_flag::rdv_flag(QGraphicsItem *parent)
: QGraphicsItem     (parent)
, mCurrentFrame     (0)
, mPixmap           (":images/mflag.png")
{
    setFlag(ItemClipsToShape);
}

rdv_flag::~rdv_flag()
{

}

void rdv_flag::nextFrame()
{
    mCurrentFrame += 322;
    if (mCurrentFrame >= 5439)
    {
        mCurrentFrame = 0;
    }
}

QRectF rdv_flag::boundingRect() const
{
    return QRectF(0, 0, 115, 84);
}

void rdv_flag::paint(QPainter *painter, [[maybe_unused]] const QStyleOptionGraphicsItem *option, [[maybe_unused]] QWidget *widget)
{
    painter->drawPixmap(0, 0, mPixmap, mCurrentFrame, 0, 115, 84);
    setTransformOriginPoint(boundingRect().center());
}
