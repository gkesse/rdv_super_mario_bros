#pragma once

#include "rdv_objects.h"

class rdv_level_complete_window : public QDialog
{
    Q_OBJECT

public:
	explicit rdv_level_complete_window(QWidget *parent = nullptr);
	~rdv_level_complete_window();
};
