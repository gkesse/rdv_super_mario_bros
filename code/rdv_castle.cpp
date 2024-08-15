#include "rdv_castle.h"

rdv_castle::rdv_castle(QGraphicsItem *parent)
: QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":images/hcastle.png"));
}

rdv_castle::~rdv_castle()
{

}
