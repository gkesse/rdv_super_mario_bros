#include "rdv_window.h"

rdv_window::rdv_window(QWidget* _parent)
: QMainWindow(_parent)
{
	createActions();
	createMenus();
	createScene();
	setCentralWidget(view);
	setWindowTitle(RDV_APPLICATION_TITLE);
}

rdv_window::~rdv_window()
{

}

void rdv_window::initSize()
{
    setFixedSize(RDV_WINDOW_WIDTH, RDV_WINDOW_HEIGHT);
    int x = ((QApplication::primaryScreen()->geometry().width() - width()) / 2);
    int y = ((QApplication::primaryScreen()->geometry().height() - height()) / 2);
    move(x, y);
}

void rdv_window::createActions()
{
    returnAction = new QAction(tr("&Return to Title"), this);
    returnAction->setShortcut(tr("Ctrl+R"));
    returnAction->setStatusTip(tr("Return to the title screen"));

    for(int i = 0; i < RDV_MAX_STATE; ++i)
    {
        saveStateAction[i] = new QAction("-Empty-", this);
        loadStateAction[i] = new QAction("-Empty-", this);
    }

    quitAction = new QAction(tr("&Quit"), this);
    quitAction->setShortcut(tr("Ctrl+Q"));
    quitAction->setStatusTip(tr("Quit"));
    connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));

    weatherStationAction = new QAction(tr("&Date and Time"), this);
    weatherStationAction->setShortcut(tr("Ctrl+w"));
    weatherStationAction->setStatusTip(tr("Date and Time"));
    connect(weatherStationAction , SIGNAL(triggered()), this, SLOT(showWeather()));

    fullScreenAction = new QAction(tr("Full Screen"), this);
    fullScreenAction->setShortcut(tr("F11"));
    fullScreenAction->setStatusTip(tr("Fullscreen View"));
    connect(fullScreenAction, SIGNAL(triggered()), this, SLOT(alterScreen()));

    settingsAction = new QAction(tr("&Settings"), this);
    settingsAction->setStatusTip(tr("Change Game Settings"));
    connect(settingsAction, SIGNAL(triggered()), this, SLOT(showSettings()));

    aboutAction = new QAction(tr("&About"), this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(showAbout()));

    setting = new rdv_settings(this);
    setting->readSettings();
}

void rdv_window::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(returnAction);
    saveSubMenu = fileMenu->addMenu(tr("&Save"));
    loadSubMenu = fileMenu->addMenu(tr("&Load"));

    for(int i=0; i < RDV_MAX_STATE; i++)
    {
        saveSubMenu->addAction(saveStateAction[i]);
        loadSubMenu->addAction(loadStateAction[i]);
    }

    fileMenu->addAction(quitAction);

    viewMenu = menuBar()->addMenu(tr("&View"));
    viewMenu->addAction(fullScreenAction);

    toolMenu = menuBar()->addMenu(tr("&Tools"));
    toolMenu->setToolTip("Game Settings");
    toolMenu->addAction(settingsAction);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->setToolTip("Developer Info");
    helpMenu->addAction(aboutAction);

    weatherMenu = menuBar()->addMenu(tr("&UDP"));
    weatherMenu->setToolTip("UDP ");
    weatherMenu->addAction(weatherStationAction);
}

void rdv_window::createScene()
{
    view = new rdv_view;
    title = new rdv_title(view);
}

void rdv_window::showWeather()
{

}

void rdv_window::alterScreen()
{

}

void rdv_window::showSettings()
{

}

void rdv_window::showAbout()
{

}
