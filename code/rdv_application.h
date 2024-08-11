#pragma once

#include "rdv_objects.h"

class rdv_application
{
public:
	explicit rdv_application(int _argc, char** _argv);
	~rdv_application();
	void run();

private:
	int m_argc;
	char** m_argv;
};
