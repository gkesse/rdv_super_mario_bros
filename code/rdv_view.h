#pragma once

#include "rdv_objects.h"

class rdv_view : public QGraphicsView
{
	Q_OBJECT

public:
	explicit rdv_view(QWidget* _parent = nullptr);
	~rdv_view();
	void setScene(QGraphicsScene *scene);

signals:
	void sceneChanged();

private:
	//QMediaPlaylist *bgm;
};
