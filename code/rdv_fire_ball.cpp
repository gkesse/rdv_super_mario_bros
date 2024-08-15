#include "rdv_fire_ball.h"
#include "rdv_goomba.h"
#include "rdv_warp_tube.h"
#include "rdv_turtle.h"

rdv_fire_ball::rdv_fire_ball(int standingDirection, QGraphicsItem *parent)
: QGraphicsItem         (parent)
, m_StandingDirection   (standingDirection)
, mState                (notBouncing)
, mCurrentFrame         (0)
, mPixmap               (":images/fireBall.png")
, mBouncingPixmap       (":images/fireballx2.png")
, m_CrouchingDirection  (0)
, inPosition            (false)
{
    setFlag(ItemClipsToShape);

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(moveBullet()));
    timer->start(100);
}

rdv_fire_ball::~rdv_fire_ball()
{

}

void rdv_fire_ball::moveBullet()
{
    if(pos().y() > 600)
    {
        inPosition = true;
    }
    else
    {
        inPosition = false;
    }

    if(inPosition)
    {
        mPixmap = mBouncingPixmap;
        mCurrentFrame += 23;
        if (mCurrentFrame >= 322)
        {
            mCurrentFrame = 0;
        }

        if(m_StandingDirection == -1)
        {
            setTransform(QTransform(-1, 0, 0, 1, boundingRect().width(),0));
            setPos(pos().x() + (m_StandingDirection * 100), pos().y());
        }
        else if(m_StandingDirection == 1)
        {
            setPos(pos().x() + (m_StandingDirection * 100), pos().y());
        }
        else
        {
            setPos(pos().x() + (m_StandingDirection * 100), pos().y());
        }

        QList<QGraphicsItem *> colliding_items = collidingItems();

        for (int i = 0, n = colliding_items.size(); i < n; ++i)
        {
            if (typeid(*(colliding_items[i])) == typeid(rdv_goomba))
            {
                emit increaseTheScore(1);
                emit collideGoomba();
                delete colliding_items[i];
                delete this;
                return;
            }
        }
        for (int i = 0, n = colliding_items.size(); i < n; ++i)
        {
            if (typeid(*(colliding_items[i])) == typeid(rdv_warp_tube))
            {
                emit increaseTheScore(1);
                emit fireballCollision();
                delete this;
                return;
            }
        }
        if ((pos().x() + boundingRect().width() > 8000)||(pos().x() + boundingRect().width() < 0))
        {
            scene()->removeItem(this);
            delete this;
            qDebug()<<"Fireball deleted";
        }
    }
    else if(!inPosition)
    {
        inPosition = false;

        if(m_StandingDirection == -1)
        {
            setTransform(QTransform(-1, 0, 0, 1, boundingRect().width(),0));
            setPos(pos().x() + (m_StandingDirection*80), pos().y() - (m_StandingDirection*80));
        }
        else if(m_StandingDirection == 1)
        {
            setPos(pos().x() + (m_StandingDirection*80), pos().y() + (m_StandingDirection*80));
        }
        else
        {
            setPos(pos().x() + (m_StandingDirection*80), pos().y() + (m_StandingDirection*80));
        }

        QList<QGraphicsItem *> colliding_items = collidingItems();

        for (int i = 0, n = colliding_items.size(); i < n; ++i)
        {
            if (typeid(*(colliding_items[i])) == typeid(rdv_goomba))
            {
                emit increaseTheScore(1);
                emit collideGoomba();
                delete colliding_items[i];
                delete this;
                return;
            }
        }
        for (int i = 0, n = colliding_items.size(); i < n; ++i){
            if (typeid(*(colliding_items[i])) == typeid(rdv_turtle))
            {
                emit increaseTheScore(1);
                emit collideGoomba();
                delete colliding_items[i];
                delete this;
                return;
            }
        }
        for (int i = 0, n = colliding_items.size(); i < n; ++i)
        {
            if (typeid(*(colliding_items[i])) == typeid(rdv_warp_tube))
            {
                emit increaseTheScore(1);
                emit fireballCollision();
                delete this;
                return;
            }
        }

        if ((pos().x() + boundingRect().width() > 8000)||(pos().x() + boundingRect().width() < 0))
        {
            scene()->removeItem(this);
            delete this;
            qDebug()<<"Fireball deleted";
        }
    }
}

QRectF rdv_fire_ball::boundingRect() const
{
    return QRectF(0, 0, 23, 81);
}

void rdv_fire_ball::paint(QPainter *painter, [[maybe_unused]] const QStyleOptionGraphicsItem *option, [[maybe_unused]] QWidget *widget)
{
    painter->drawPixmap(0,0, mPixmap, mCurrentFrame, 0,23, 81);
    setTransformOriginPoint(boundingRect().center());
}


