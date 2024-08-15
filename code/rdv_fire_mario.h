#pragma once

#include "rdv_objects.h"

class rdv_fire_mario : public QGraphicsItem
{
private:
    enum State
    {
        Standing = 0,
        StandShoot,
        Walking,
        Jumping,
        Falling
    };

public:
    explicit rdv_fire_mario(QGraphicsItem *parent = nullptr);
    ~rdv_fire_mario();
    void addStandingDirection(int standingDirection);
    void addDirection(int direction);
    void nextFrame();
    QRectF boundingRect() const;
    void paint(QPainter *painter, [[maybe_unused]] const QStyleOptionGraphicsItem *option, [[maybe_unused]] QWidget *widget);
    bool isTouchingFoot(QGraphicsItem *item);
    bool isTouchingHead(QGraphicsItem *item);
    bool isTouchingPlatform(QGraphicsItem *item);

    void stand();
    void jump();
    void standShoot();
    void walk();
    void fall();
    bool isFalling();

    int direction() const           {return m_direction;}
    int standingDirection() const  {return m_StandingDirection;}

private:
    int m_direction;
    int mCurrentFrame;
    int m_StandingDirection;
    State mState;
    QPixmap mWalkPixmap;
    QPixmap mStandingPixmap;
    QPixmap mJumpPixmap;
    QPixmap standShootPixmap;
    QPixmap mPixmap;
};
