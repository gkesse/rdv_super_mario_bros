#include "rdv_stair_block.h"

rdv_stair_block::rdv_stair_block(int length, QGraphicsItem *parent)
: QGraphicsItem     (parent)
, mCurrentFrame     (0)
, mPixmap           (":images/stairblock.png")
, mLength           (length)
{
    setFlag(ItemClipsToShape);
}

rdv_stair_block::~rdv_stair_block()
{

}

void rdv_stair_block::nextFrame()
{
    mCurrentFrame += 48;
    if (mCurrentFrame >= 768)
    {
        mCurrentFrame = 0;
    }
}

QRectF rdv_stair_block::boundingRect() const
{
    return QRectF(0, 0, 48*mLength, 48);
}

void rdv_stair_block::paint(QPainter *painter, [[maybe_unused]] const QStyleOptionGraphicsItem *option, [[maybe_unused]] QWidget *widget)
{
    for(int i = 0; i < 48*mLength; ++i)
    {
        painter->drawPixmap(i*48, 0, mPixmap, mCurrentFrame, 0, 48, 48);
    }
    setTransformOriginPoint(boundingRect().center());
}
