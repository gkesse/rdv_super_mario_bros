#include "rdv_flower.h"
#include "rdv_player.h"
#include "rdv_small_mario.h"
#include "rdv_fire_mario.h"

rdv_flower::rdv_flower(QRectF platformRect, int direction, QGraphicsItem *parent)
: QGraphicsItem     (parent)
, mCurrentFrame     (0)
, mPixmap           (":images/flower.png")
, mPlatform         (platformRect)
, mDirection        (direction)
, up                (true)
, down              (true)
, right             (true)
, right2            (false)
{
    setFlag(ItemClipsToShape);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    timer->start(100);
}

rdv_flower::~rdv_flower()
{

}

void rdv_flower::nextFrame()
{
    if(up)
    {
        if(this->pos().y() > mPlatform.y()-40)
        {
            setPos(this->pos().x(), this->pos().y() - (mDirection *5));
        }
    }
    if(right)
    {
        if(this->pos().y() == mPlatform.y() -42)
        {
            up = false;
        }
    }

    //Collision Detection
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        if (typeid(*(colliding_items[i])) == typeid(rdv_player))
        {
            emit marioSizeStatus(4);
            delete colliding_items[i];
            delete this;
            return;
        }
    }

    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        if (typeid(*(colliding_items[i])) == typeid(rdv_fire_mario))
        {
            emit marioSizeStatus(5);
            //delete colliding_items[i];
            delete this;
            return;
        }
    }
}

QRectF rdv_flower::boundingRect() const
{
    return QRectF(0, 0, 70, 50);
}

void rdv_flower::paint(QPainter *painter, [[maybe_unused]] const QStyleOptionGraphicsItem *option, [[maybe_unused]] QWidget *widget)
{
    painter->drawPixmap(0, 0, mPixmap, mCurrentFrame, 0, 70, 50);
    setTransformOriginPoint(boundingRect().center());
}
