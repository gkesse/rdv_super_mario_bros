#include "rdv_note_box.h"

rdv_note_box::rdv_note_box(int length, QGraphicsItem *parent)
: QGraphicsItem     (parent)
, mCurrentFrame     (0)
, mPixmap           (":images/notebox.png")
, mLength           (length)
{
    setFlag(ItemClipsToShape);
}

rdv_note_box::~rdv_note_box()
{

}

void rdv_note_box::nextFrame()
{
    mCurrentFrame += 65;
    if (mCurrentFrame >= 518)
    {
        mCurrentFrame = 0;
    }
}

QRectF rdv_note_box::boundingRect() const
{
    return QRectF(0, 0, 63*mLength, 63);
}

void rdv_note_box::paint(QPainter *painter, [[maybe_unused]] const QStyleOptionGraphicsItem *option, [[maybe_unused]] QWidget *widget)
{
    for(int i = 0; i < 48*mLength; ++i)
    {
        painter->drawPixmap(i*63, 0, mPixmap, mCurrentFrame, 0, 63, 63);
    }
    setTransformOriginPoint(boundingRect().center());
}
