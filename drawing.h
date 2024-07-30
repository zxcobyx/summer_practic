#ifndef DRAWING_H
#define DRAWING_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>

class drawing : public QGraphicsScene {
    Q_OBJECT

public:
    enum DrawMode { None, Line, Rectangle, Highlighter };

    explicit drawing(QObject *parent = nullptr);
    ~drawing();
    void setDrawMode(DrawMode mode);

signals:
    void lineDrawn(qreal x1, qreal y1, qreal x2, qreal y2);

    void rectDrawn(QPointF pos2Rect);
    void startPointRect(QPointF pos1Rect);

    void highDrawn(QPointF pos2High);
    void startPointHigh(QPointF pos1High);

private:
    QPointF previousPoint;
    DrawMode currentDrawMode;
    bool drawing_;
    QPointF startPoint;
    QGraphicsRectItem *currentRectItem;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseWheel(QGraphicsSceneMouseEvent *event);

    void startDrawRectangle(const QPointF &scenePos);
    void startDrawLine(const QPointF &scenePos);
    void startDrawHighlighter(const QPointF &scenePos);

    void updateRectangle(const QPointF &scenePos);
    void drawLineSegment(const QPointF &scenePos);
    void updateHighlighter(const QPointF &scenePos);
};

#endif // DRAWING_H
