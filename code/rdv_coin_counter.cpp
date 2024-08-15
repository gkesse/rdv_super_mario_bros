#include "rdv_coin_counter.h"

rdv_coin_counter::rdv_coin_counter(QGraphicsItem *parent)
: QGraphicsTextItem (parent)
, coinCount         (0)
{
    int id = QFontDatabase::addApplicationFont(":font/CoinCount2.ttf");
    QFontDatabase::applicationFontFamilies(id);
    setPlainText(QString("") + QString::number(coinCount));
    setDefaultTextColor(Qt::black);
    setFont(QFont("CoinCount2", 40));
}

rdv_coin_counter::~rdv_coin_counter()
{

}

void rdv_coin_counter::increase()
{
    coinCount++;
    setPlainText(QString("") + QString::number(coinCount));
}
