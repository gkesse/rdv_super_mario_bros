#include "rdv_flower_box.h"

rdv_flower_box::rdv_flower_box(int length, QGraphicsItem *parent)
: QGraphicsItem     (parent)
, mCurrentFrame     (0)
, mPixmap           (":images/questbox.png")
, mLength           (length)
{
    setFlag(ItemClipsToShape);
}

rdv_flower_box::~rdv_flower_box()
{

}

void rdv_flower_box::nextFrame()
{
    mCurrentFrame += 50;
    if (mCurrentFrame >= 800 )
    {
        mCurrentFrame = 0;
    }
}

QRectF rdv_flower_box::boundingRect() const
{
    return QRectF(0, 0, 48* mLength, 48);
}

void rdv_flower_box::paint(QPainter *painter, [[maybe_unused]] const QStyleOptionGraphicsItem *option, [[maybe_unused]] QWidget *widget)
{
    for(int i = 0; i < 48*mLength; ++i)
    {
        painter->drawPixmap(i*48, 0, mPixmap, mCurrentFrame, 0, 48, 48);
    }
    setTransformOriginPoint(boundingRect().center());
}
