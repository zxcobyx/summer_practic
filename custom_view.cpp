#include "custom_view.h"
#include <qevent.h>

Custom_View::Custom_View(QWidget *parent) : QGraphicsView(parent) {}

void Custom_View::wheelEvent(QWheelEvent *event) {
    setTransformationAnchor(AnchorUnderMouse);
    double scalefactor;

    if (event->delta() > 0 ) {
        scalefactor = 1.5;
    } else {
        scalefactor = 1/1.5;
    }

    scale(scalefactor, scalefactor);
    emit zoom(scalefactor);
}

void Custom_View::scrollContentsBy(int dx, int dy) {
    QGraphicsView::scrollContentsBy(dx, dy);
    emit scroll(dx, dy);
}
