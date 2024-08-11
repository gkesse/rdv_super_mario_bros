#include "rdv_application.h"
#include "rdv_startup.h"
#include "rdv_splashscreen.h"
#include "rdv_window_startup.h"

rdv_application::rdv_application(int _argc, char** _argv)
: m_argc(_argc)
, m_argv(_argv)
{

}

rdv_application::~rdv_application()
{

}

void rdv_application::run()
{
	// création de l'application
	QApplication app(m_argc, m_argv);
	app.setWindowIcon(QIcon(RDV_WINDOW_ICON));

	// démarrage de l'application
	rdv_startup startup;
	startup.run();

	// affichage de l'écran d'accueil
	rdv_splashscreen splashscreen(RDV_SPLASHSCREEN_IMAGE);
	splashscreen.run();

	// affichage de la fenêtre principale
	rdv_window_startup window;
	window.run();

	app.exec();
}
