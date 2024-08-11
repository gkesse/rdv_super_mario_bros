#pragma once

#include "rdv_window.h"

class rdv_window_startup
{
public:
	explicit rdv_window_startup();
	~rdv_window_startup();
	void run();

private:
	rdv_window* m_window;
};
