#pragma once

#include "rdv_objects.h"

class rdv_settings : public QDialog
{
	Q_OBJECT

public:
	explicit rdv_settings(QWidget* _parent = nullptr);
	~rdv_settings();
	void readSettings();
};
