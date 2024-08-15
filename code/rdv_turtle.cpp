#include "rdv_turtle.h"
#include "rdv_player.h"
#include "rdv_small_mario.h"
#include "rdv_fire_mario.h"

rdv_turtle::rdv_turtle(QRectF platformRect, int direction, QGraphicsItem *parent)
: QGraphicsItem     (parent)
, mCurrentFrame     (0)
, mPixmap           (":images/turtle.png")
, mPlatform         (platformRect)
, mDirection        (direction)
{
    setFlag(ItemClipsToShape);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    timer->start(100);
}

rdv_turtle::~rdv_turtle()
{

}

void rdv_turtle::nextFrame()
{
    mCurrentFrame += 72;
    if (mCurrentFrame >= 1420)
    {
        mCurrentFrame = 0;
    }

    if(pos().x() < mPlatform.x() || pos().x() > mPlatform.x()+ mPlatform.width())
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

QRectF rdv_turtle::boundingRect() const
{
    return QRectF(0, 0, 68, 60);
}

void rdv_turtle::paint(QPainter *painter, [[maybe_unused]] const QStyleOptionGraphicsItem *option, [[maybe_unused]] QWidget *widget)
{
    painter->drawPixmap(0, 0, mPixmap, mCurrentFrame, 0, 68, 60);
    setTransformOriginPoint(boundingRect().center());
}
