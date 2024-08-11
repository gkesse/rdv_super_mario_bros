#include "rdv_splashscreen.h"

rdv_splashscreen::rdv_splashscreen(const QString& _pixmap)
: m_pixmap(_pixmap)
{
	m_splashscreen = new QSplashScreen;
}

rdv_splashscreen::~rdv_splashscreen()
{
	delete m_splashscreen;
}

void rdv_splashscreen::run()
{
	m_splashscreen->setPixmap(QPixmap(m_pixmap));
	m_splashscreen->show();
    QTimer::singleShot(RDV_SPLASHSCREEN_TIMER, m_splashscreen, SLOT(close()));
}
