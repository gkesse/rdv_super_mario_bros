#include "rdv_conveyor.h"

rdv_conveyor::rdv_conveyor(QGraphicsItem *parent)
: QGraphicsItem     (parent)
, mCurrentFrame    (0)
, mPixmap          (":images/conveyorR.png")
{
    setFlag(ItemClipsToShape);
}

rdv_conveyor::~rdv_conveyor()
{

}

void rdv_conveyor::nextFrame()
{
    mCurrentFrame += 193;
    if (mCurrentFrame >= 1544)
    {
        mCurrentFrame = 0;
    }
}

QRectF rdv_conveyor::boundingRect() const
{
    return QRectF(0, 0, 190, 56);
}

void rdv_conveyor::paint(QPainter *painter, [[maybe_unused]] const QStyleOptionGraphicsItem *option, [[maybe_unused]] QWidget *widget)
{
    painter->drawPixmap(0, 0, mPixmap, mCurrentFrame, 0, 190, 56);
    setTransformOriginPoint(boundingRect().center());
}
