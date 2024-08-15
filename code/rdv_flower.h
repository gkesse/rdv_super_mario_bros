#pragma once

#include "rdv_objects.h"

class rdv_flower : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    explicit rdv_flower(QRectF platformRect, int direction, QGraphicsItem *parent = nullptr);
    ~rdv_flower();
    QRectF boundingRect() const;
    void paint(QPainter *painter, [[maybe_unused]] const QStyleOptionGraphicsItem *option, [[maybe_unused]] QWidget *widget);

    int type() const    {return UserType + flowerType;}

public slots:
    void nextFrame();

signals:
    void marioSizeStatus(int);

private:
    int mCurrentFrame;
    QPixmap mPixmap;
    QRectF mPlatform;
    int mDirection;
    bool up;
    bool right;
    bool down;
    bool right2;
};
