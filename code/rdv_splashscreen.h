#pragma once

#include "rdv_objects.h"

class rdv_splashscreen
{
public:
	explicit rdv_splashscreen(const QString& _pixmap);
	~rdv_splashscreen();
	void run();

private:
	QString m_pixmap;
	QSplashScreen* m_splashscreen;
};
