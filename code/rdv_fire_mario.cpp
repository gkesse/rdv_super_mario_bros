#include "rdv_fire_mario.h"

rdv_fire_mario::rdv_fire_mario(QGraphicsItem *parent)
: QGraphicsItem         (parent)
, m_direction           (0)
, mCurrentFrame         (0)
, m_StandingDirection   (0)
, mState                (Standing)
, mWalkPixmap           (":images/firemario.png")
, mStandingPixmap       (":images/firemariostop.png")
, mJumpPixmap           (":images/mario_jump.png")
, standShootPixmap      (":images/firemariostop.png")
, mPixmap               (mWalkPixmap)
{
    setFlag(ItemClipsToShape);
}

rdv_fire_mario::~rdv_fire_mario()
{

}

void rdv_fire_mario::stand()
{
    mPixmap = mStandingPixmap;
    mCurrentFrame = 0;
    mState = Standing;
}

void rdv_fire_mario::jump()
{
    mState = Jumping;
}

void rdv_fire_mario::standShoot()
{
    mPixmap = standShootPixmap;
    mCurrentFrame = 0;
    mState = StandShoot;
}

void rdv_fire_mario::walk()
{
    if(mState == Walking)
    {
        return;
    }

    mPixmap = mWalkPixmap;
    mCurrentFrame = 0;
    mState = Walking;
}

void rdv_fire_mario::fall()
{
    mState = Falling;
}

bool rdv_fire_mario::isFalling()
{
    return mState == Falling;
}

void rdv_fire_mario::nextFrame()
{
    mCurrentFrame += 57;
    if (mCurrentFrame >= 1191)
    {
        mCurrentFrame = 0;
    }
}

QRectF rdv_fire_mario::boundingRect() const
{
    return QRectF(0, 0, 45, 73);
}

void rdv_fire_mario::paint(QPainter *painter, [[maybe_unused]] const QStyleOptionGraphicsItem *option, [[maybe_unused]] QWidget *widget)
{
    painter->drawPixmap(0,0, mPixmap, mCurrentFrame, 0, 45, 73);
    setTransformOriginPoint(boundingRect().center());
}

void rdv_fire_mario::addDirection(int direction)
{
    if (direction == m_direction)
        return;

    m_direction += direction;

    if (0 != m_direction)
    {
        if (-1 == m_direction)
            setTransform(QTransform(-1, 0, 0, 1, boundingRect().width(), 0));
        else
            setTransform(QTransform());
    }
}

void rdv_fire_mario::addStandingDirection(int standingDirection)
{
    m_StandingDirection = standingDirection;
}

bool rdv_fire_mario::isTouchingFoot(QGraphicsItem *item)
{
    QRectF rect(pos().x(), (pos().y() + boundingRect().height()) -5, boundingRect().width(), 5);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());
    return rect.intersects(otherRect);
}

bool rdv_fire_mario::isTouchingHead(QGraphicsItem *item)
{
    QRectF rect(pos().x(), pos().y(), boundingRect().width(), 5);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());
    return rect.intersects(otherRect);
}

bool rdv_fire_mario::isTouchingPlatform(QGraphicsItem *item)
{
    QRectF rect(pos().x(), (pos().y() + boundingRect().height()) - 5, boundingRect().width(), 10);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());
    return rect.intersects(otherRect);
}
