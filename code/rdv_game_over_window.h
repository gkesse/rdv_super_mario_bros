#pragma once

#include "rdv_objects.h"

class rdv_game_over_window : public QDialog
{
    Q_OBJECT

public:
	explicit rdv_game_over_window(QWidget *parent = nullptr);
	~rdv_game_over_window();
};
