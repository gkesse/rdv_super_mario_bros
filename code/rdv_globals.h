#pragma once

#include "rdv_objects.h"

class rdv_globals
{
public:
	explicit rdv_globals();
	~rdv_globals();
	static bool isValidEmail(const QString& _username);
	static bool isValidPassword(const QString& _password);
};
