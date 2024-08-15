#include "rdv_timer.h"

rdv_timer::rdv_timer(QGraphicsItem *parent)
: QGraphicsTextItem (parent)
, timeCount         (400)
{
    int id = QFontDatabase::addApplicationFont(":font/CoinCount2.ttf");
    QFontDatabase::applicationFontFamilies(id);
    setPlainText(QString("") + QString::number(timeCount));
    setDefaultTextColor(Qt::black);
    setFont(QFont("CoinCount2", 30));
    startTimer(1000);
}

rdv_timer::~rdv_timer()
{

}

void rdv_timer::timerEvent(QTimerEvent *)
{
    decrease();
}

void rdv_timer::decrease()
{
    if(0 != timeCount)
    {
        timeCount--;
        setPlainText(QString("") + QString::number(timeCount));
    }
}


