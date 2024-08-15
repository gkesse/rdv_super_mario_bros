#include "rdv_player.h"

rdv_player::rdv_player(QGraphicsItem *parent)
: QGraphicsItem         (parent)
, m_direction           (0)
, mCurrentFrame         (0)
, m_StandingDirection   (0)
, mState                (Standing)
, mWalkPixmap           (":images/mario.png")
, mStandingPixmap       (":images/mariostop.png")
, mJumpPixmap           (":images/mario_jump.png")
, standShootPixmap      (":images/mariostop.png")
, mPixmap               (mWalkPixmap)
{
    setFlag(ItemClipsToShape);
}

rdv_player::~rdv_player()
{

}

void rdv_player::stand()
{
    mPixmap = mStandingPixmap;
    mCurrentFrame = 0;
    mState = Standing;
}

void rdv_player::jump()
{
    mState = Jumping;
}

void rdv_player::standShoot()
{
    mPixmap = standShootPixmap;
    mCurrentFrame = 0;
    mState = StandShoot;
}

void rdv_player::walk()
{
    if(mState == Walking)
    {
        return;
    }

    mPixmap = mWalkPixmap;
    mCurrentFrame = 0;
    mState = Walking;
}

void rdv_player::fall()
{
    mState = Falling;
}

bool rdv_player::isFalling()
{
    return mState == Falling;
}

void rdv_player::nextFrame()
{
    mCurrentFrame += 57;
    if (mCurrentFrame >= 1191)
    {
        mCurrentFrame = 0;
    }
}

QRectF rdv_player::boundingRect() const
{
    return QRectF(0, 0, 45, 73);
}

void rdv_player::paint(QPainter *painter, [[maybe_unused]] const QStyleOptionGraphicsItem *option, [[maybe_unused]] QWidget *widget)
{
    painter->drawPixmap(0,0, mPixmap, mCurrentFrame, 0, 45, 73);
    setTransformOriginPoint(boundingRect().center());
}

void rdv_player::addDirection(int direction)
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

void rdv_player::addStandingDirection(int standingDirection)
{
    m_StandingDirection = standingDirection;
}

bool rdv_player::isTouchingFoot(QGraphicsItem *item)
{
    QRectF rect(pos().x(), (pos().y() + boundingRect().height()) - 5, boundingRect().width(), 5);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());
    return rect.intersects(otherRect);
}

bool rdv_player::isTouchingHead(QGraphicsItem *item)
{
    QRectF rect(pos().x(), pos().y(), boundingRect().width(), 5);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());
    return rect.intersects(otherRect);
}

bool rdv_player::isTouchingPlatform(QGraphicsItem *item)
{
    QRectF rect(pos().x(), (pos().y() + boundingRect().height()) - 5, boundingRect().width(), 10);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());
    return rect.intersects(otherRect);
}
