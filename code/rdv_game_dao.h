#pragma once

#include "rdv_objects.h"

class rdv_game_dao
{
public:
	explicit rdv_game_dao();
	~rdv_game_dao();
	QString getUsername() const;
};
