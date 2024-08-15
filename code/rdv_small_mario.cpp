#include "rdv_small_mario.h"

rdv_small_mario::rdv_small_mario(QGraphicsItem *parent)
: QGraphicsItem         (parent)
, m_direction           (0)
, mCurrentFrame         (0)
, m_StandingDirection   (0)
, mState                (Standing)
, mWalkPixmap           (":images/shrink.png")
, mStandingPixmap       (":images/smallMarioStop.png")
, mJumpPixmap           (":images/mario_jump.png")
, standShootPixmap      (":images/smallMarioStop.png")
, mShrinkPixmap         (":images/shrink.png")
, mPixmap               (mWalkPixmap)
{
    setFlag(ItemClipsToShape);
}

rdv_small_mario::~rdv_small_mario()
{

}

void rdv_small_mario::stand()
{
    mPixmap = mStandingPixmap;
    mCurrentFrame = 0;
    mState = Standing;
}

void rdv_small_mario::jump()
{
    mState = Jumping;
}

void rdv_small_mario::standShoot()
{
    mPixmap = standShootPixmap;
    mCurrentFrame = 0;
    mState = StandShoot;
}

void rdv_small_mario::walk()
{
    if(mState == Walking)
    {
        return;
    }

    mPixmap = mWalkPixmap;
    mCurrentFrame = 0;
    mState = Walking;
}

void rdv_small_mario::fall()
{
    mState = Falling;
}

bool rdv_small_mario::isFalling()
{
    return mState == Falling;
}

void rdv_small_mario::nextFrame()
{
    mCurrentFrame += 57;
    if (mCurrentFrame >= 1191)
    {
        mCurrentFrame = 0;
    }
}

QRectF rdv_small_mario::boundingRect() const
{
    return QRectF(0, 0, 45, 45);
}

void rdv_small_mario::paint(QPainter *painter, [[maybe_unused]] const QStyleOptionGraphicsItem *option, [[maybe_unused]] QWidget *widget)
{
    painter->drawPixmap(0,0, mPixmap, mCurrentFrame, 0, 45, 45);
    setTransformOriginPoint(boundingRect().center());
}

void rdv_small_mario::addDirection(int direction)
{
    if (direction == m_direction)
        return;

    m_direction += direction;

    if (0 != m_direction) {
        if (-1 == m_direction)
            setTransform(QTransform(-1, 0, 0, 1, boundingRect().width(), 0));
        else
            setTransform(QTransform());
    }
}

void rdv_small_mario::addStandingDirection(int standingDirection)
{
    m_StandingDirection = standingDirection;
}

bool rdv_small_mario::isTouchingFoot(QGraphicsItem *item)
{
    QRectF rect(pos().x(), (pos().y() + boundingRect().height()) -5, boundingRect().width(), 5);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());
    return rect.intersects(otherRect);
}

bool rdv_small_mario::isTouchingHead(QGraphicsItem *item)
{
    QRectF rect(pos().x(), pos().y(), boundingRect().width(), 5);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());
    return rect.intersects(otherRect);
}

bool rdv_small_mario::isTouchingPlatform(QGraphicsItem *item)
{
    QRectF rect(pos().x(), (pos().y() + boundingRect().height()) - 5, boundingRect().width(), 10);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());
    return rect.intersects(otherRect);
}
