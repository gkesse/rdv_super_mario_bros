#pragma once

#include "rdv_objects.h"

class rdv_fire_ball : public QObject, public QGraphicsItem
{
    Q_OBJECT

private:
    enum State
    {
        notBouncing = 0,
        bouncing,
    };

public:
    explicit rdv_fire_ball(int standingDirection, QGraphicsItem *parent = nullptr);
    ~rdv_fire_ball();
    void nextFrame();
    QRectF boundingRect() const;
    void paint(QPainter *painter, [[maybe_unused]] const QStyleOptionGraphicsItem *option, [[maybe_unused]] QWidget *widget);

    int type() const    {return UserType + fireBallType;}

signals:
    void increaseTheScore(int);
    void changeFireball(int);
    void fireballCollision();
    void collideGoomba();

public slots:
    void moveBullet();

    private:
    int m_StandingDirection;
    State mState;
    int mCurrentFrame;
    QPixmap mPixmap;
    QPixmap mBouncingPixmap;
    QRectF mPlatform;
    int m_CrouchingDirection;
    bool inPosition;
    QTimer *timer;
};
