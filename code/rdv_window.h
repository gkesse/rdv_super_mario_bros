#pragma once

#include "rdv_settings.h"
#include "rdv_view.h"
#include "rdv_title.h"

class rdv_window : public QMainWindow
{
	Q_OBJECT

public:
	explicit rdv_window(QWidget* _parent = nullptr);
	~rdv_window();
	void initSize();
	void createActions();
	void createMenus();
	void createScene();

private slots:
	void showWeather();
    void alterScreen();
	void showSettings();
    void showAbout();

private:
	QAction* returnAction;
	QAction *saveStateAction[RDV_MAX_STATE];
	QAction *loadStateAction[RDV_MAX_STATE];
	QAction *quitAction;
	QAction *weatherStationAction;
	QAction *fullScreenAction;
	QAction *settingsAction;
	QAction *aboutAction;

	rdv_settings *setting;

	QMenu *fileMenu;
	QMenu *saveSubMenu;
	QMenu *loadSubMenu;
	QMenu *viewMenu;
	QMenu *toolMenu;
	QMenu *helpMenu;
	QMenu *weatherMenu;

	rdv_view *view;
    rdv_title *title;
};
