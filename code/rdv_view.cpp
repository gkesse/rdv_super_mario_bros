#include "rdv_view.h"

rdv_view::rdv_view(QWidget* _parent)
: QGraphicsView(_parent)
{
	setFixedSize(QSize(RDV_WINDOW_WIDTH, RDV_WINDOW_HEIGHT));
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

rdv_view::~rdv_view()
{

}

void rdv_view::setScene(QGraphicsScene *scene) {

    QGraphicsView::setScene(scene);
    emit sceneChanged();
}

