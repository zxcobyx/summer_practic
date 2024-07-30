#ifndef CUSTOM_VIEW_H
#define CUSTOM_VIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWheelEvent>

class Custom_View : public QGraphicsView
{
    Q_OBJECT

public:
    explicit Custom_View(QWidget *parent = nullptr);

signals:
    void zoom(double scaleF);
    void scroll(int dx, int dy);

protected:
    void wheelEvent(QWheelEvent *event);
    void scrollContentsBy(int dx, int dy);

    using QGraphicsView::QGraphicsView;
};

#endif // CUSTOM_VIEW_H
