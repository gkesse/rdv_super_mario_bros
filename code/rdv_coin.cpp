#include "rdv_coin.h"

rdv_coin::rdv_coin(QGraphicsItem *parent)
: QGraphicsItem     (parent)
, mCurrentFrame2    (0)
, mPixmap2          (":images/coin.png")
{
    setFlag(ItemClipsToShape);
}

rdv_coin::~rdv_coin()
{

}

void rdv_coin::nextFrame2()
{
    mCurrentFrame2 += 38;
    if (mCurrentFrame2 >= 300 )
    {
        mCurrentFrame2 = 0;
    }
}

QRectF rdv_coin::boundingRect() const
{
    return QRectF(0, 0, 39, 41);
}

void rdv_coin::paint(QPainter *painter, [[maybe_unused]] const QStyleOptionGraphicsItem *option, [[maybe_unused]] QWidget *widget)
{
    painter->drawPixmap(0, 0, mPixmap2, mCurrentFrame2, 0,39, 41);
    setTransformOriginPoint(boundingRect().center());
}
