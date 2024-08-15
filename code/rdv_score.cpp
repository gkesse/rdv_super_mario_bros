#include "rdv_score.h"

rdv_score::rdv_score(QGraphicsItem *parent)
: QGraphicsTextItem (parent)
, scoreCount        (0)
{
    int id = QFontDatabase::addApplicationFont(":font/CoinCount2.ttf");
    QFontDatabase::applicationFontFamilies(id);
    setPlainText(QString("") + QString::number(scoreCount));
    setDefaultTextColor(Qt::black);
    setFont(QFont("CoinCount2", 30));
}

rdv_score::~rdv_score()
{

}

void rdv_score::increase()
{
    scoreCount++;
    setPlainText(QString("") + QString::number(scoreCount * 15));
}

