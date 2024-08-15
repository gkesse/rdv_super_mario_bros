#include "rdv_mushroom.h"
#include "rdv_player.h"
#include "rdv_small_mario.h"

rdv_mushroom::rdv_mushroom(QRectF platformRect, int direction, QGraphicsItem *parent)
: QGraphicsItem     (parent)
, mCurrentFrame     (0)
, mPixmap           (":images/m40.png")
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

rdv_mushroom::~rdv_mushroom()
{

}

void rdv_mushroom::nextFrame()
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
            setPos(this->pos().x() + (mDirection *5), this->pos().y());
        }
    }

    if(down)
    {
        if(this->pos().x() > mPlatform.x() + mPlatform.width()+20)
        {
            right = false;
            setPos(this->pos().x() , this->pos().y() + (mDirection *25));
        }
    }

    if(this->pos().y() > 619)
    {
        down =false;
        setPos(this->pos().x() + (mDirection *5), 620);
    }

    //Collision Detection
    QList<QGraphicsItem *> colliding_items = collidingItems();

    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        if (typeid(*(colliding_items[i])) == typeid(rdv_player))
        {
            scene()->removeItem(this);
            emit marioSizeStatus(3);
            delete this;
            return;
        }
    }
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(rdv_small_mario))
        {
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            emit marioSizeStatus(2);
            delete colliding_items[i];
            delete this;
            return;
        }
    }
}

QRectF rdv_mushroom::boundingRect() const
{
    return QRectF(0, 0, 70, 50);
}

void rdv_mushroom::paint(QPainter *painter, [[maybe_unused]] const QStyleOptionGraphicsItem *option, [[maybe_unused]] QWidget *widget)
{
    painter->drawPixmap(0, 0, mPixmap, mCurrentFrame, 0, 70, 50);
    setTransformOriginPoint(boundingRect().center());
}
