#include "rdv_question_box.h"

rdv_question_box::rdv_question_box(int length, QGraphicsItem *parent)
: QGraphicsItem     (parent)
, mCurrentFrame4    (0)
, mPixmap4          (":images/questbox.png")
, mLength           (length)
{
    setFlag(ItemClipsToShape);
}

rdv_question_box::~rdv_question_box()
{

}

void rdv_question_box::nextFrame4()
{
    mCurrentFrame4 += 50;
    if (mCurrentFrame4 >= 800 )
    {
        mCurrentFrame4 = 0;
    }
}

QRectF rdv_question_box::boundingRect() const
{
    return QRectF(0, 0, 48* mLength, 48);
}

void rdv_question_box::paint(QPainter *painter, [[maybe_unused]] const QStyleOptionGraphicsItem *option, [[maybe_unused]] QWidget *widget)
{
    for(int i = 0; i < 48*mLength; ++i)
    {
        painter->drawPixmap(i*48, 0, mPixmap4, mCurrentFrame4, 0, 48, 48);
    }
    setTransformOriginPoint(boundingRect().center());
}
