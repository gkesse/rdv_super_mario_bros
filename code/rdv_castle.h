 #pragma once

#include "rdv_objects.h"

class rdv_castle : public QGraphicsPixmapItem
{
public:
	explicit rdv_castle(QGraphicsItem *parent = nullptr);
	~rdv_castle();

    int type() const    {return UserType + castleType;}
};
