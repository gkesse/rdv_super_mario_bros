#include "rdv_window_startup.h"

rdv_window_startup::rdv_window_startup()
{
	m_window = new rdv_window;
}

rdv_window_startup::~rdv_window_startup()
{
	delete m_window;
}

void rdv_window_startup::run()
{
	m_window->initSize();
	QTimer::singleShot(RDV_SPLASHSCREEN_TIMER, m_window, SLOT(show()));
}
