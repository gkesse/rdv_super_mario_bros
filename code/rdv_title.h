#pragma once

#include "rdv_objects.h"

class rdv_view;
class rdv_pixmap_item;
class rdv_title;
class rdv_sound_manager;
class rdv_user_registration;

class rdv_pixmap_item : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
};

class rdv_title : public QGraphicsScene
{
	Q_OBJECT

public:
	explicit rdv_title(rdv_view* _view, QWidget* _parent = nullptr);
	~rdv_title();

private slots:
     void login();
     void developerLogin();
     void quitProgram();
     void newUser();
     void on_radioButton_toggled([[maybe_unused]] bool checked);

signals:
    void playSound(QString);

private:
	rdv_view *viewer;
	QScrollBar *scroll;
	rdv_pixmap_item *background;
	QGraphicsPixmapItem *foreground;
	QGraphicsPixmapItem *logo;
	QPropertyAnimation *animation;

	QPushButton *loginButton;
	QPushButton *developerButton;
	QPushButton *quitButton;
	QPushButton *newUserButton;

	QLineEdit *userLine;
	QLabel *userName;
	QLineEdit *passLine;
	QLabel *password;
	QRadioButton *radioButton;
	QLabel *radioText;
	rdv_sound_manager *soundManager;

    rdv_user_registration *loginWindow;
};
