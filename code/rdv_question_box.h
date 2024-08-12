#pragma once

#include "rdv_objects.h"

class rdv_question_box : public QGraphicsItem
{
public:
	explicit rdv_question_box(int length, QGraphicsItem *parent = nullptr);
	~rdv_question_box();
    void nextFrame4();
    QRectF boundingRect() const;
    void paint(QPainter *painter, [[maybe_unused]] const QStyleOptionGraphicsItem *option, [[maybe_unused]] QWidget *widget);

    int type() const    {return UserType + questBoxType;}

private:
    int mCurrentFrame4;
    QPixmap mPixmap4;
    int mLength;
};
