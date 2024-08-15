#include "rdv_goomba.h"
#include "rdv_player.h"
#include "rdv_small_mario.h"
#include "rdv_fire_mario.h"

rdv_goomba::rdv_goomba(QRectF platformRect, int direction, QGraphicsItem *parent)
: QGraphicsItem     (parent)
, mCurrentFrame     (0)
, mPixmap           (":images/goombas.png")
, mPlatform         (platformRect)
, mDirection        (direction)
{
    setFlag(ItemClipsToShape);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    timer->start(100);
}

rdv_goomba::~rdv_goomba()
{

}

void rdv_goomba::nextFrame()
{
    mCurrentFrame += 54;
    if (mCurrentFrame >= 862)
    {
        mCurrentFrame = 0;
    }

    if(pos().x() < mPlatform.x() || pos().x() > mPlatform.x() + mPlatform.width())
    {
        mDirection = -mDirection;
        setTransform(QTransform(-mDirection, 0, 0, 1, boundingRect().width(), 0));
    }
    setPos(pos().x() + (mDirection*7), pos().y());

    //Collision Detection
    QList<QGraphicsItem*> colliding_items = collidingItems();

    //If one of the colliding items is an Enemy, destroy both the bullet and the enemy
    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        if (typeid(*(colliding_items[i])) == typeid(rdv_player))
        {

            emit marioSizeStatus(0);
            delete colliding_items[i];
            qDebug()<<"Mario deleted small mario added";
            delete this;
            return;
        }
    }
    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        if (typeid(*(colliding_items[i])) == typeid(rdv_small_mario))
        {

            emit marioSizeStatus(1);
            delete colliding_items[i];
            qDebug()<<"small mario dead";
            delete this;
            return;
        }
    }
    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        if (typeid(*(colliding_items[i])) == typeid(rdv_fire_mario))
        {

            emit marioSizeStatus(6);
            delete colliding_items[i];
            qDebug()<<"Fire mario deleted small mario added";
            delete this;
            return;
        }
    }
}

QRectF rdv_goomba::boundingRect() const
{
    return QRectF(0, 0, 50, 50);
}

void rdv_goomba::paint(QPainter *painter, [[maybe_unused]] const QStyleOptionGraphicsItem *option, [[maybe_unused]] QWidget *widget)
{
    painter->drawPixmap(0, 0, mPixmap, mCurrentFrame, 0, 52, 50);
    setTransformOriginPoint(boundingRect().center());
}
