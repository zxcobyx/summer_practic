#include "drawing.h"

drawing::drawing(QObject *parent) :
    QGraphicsScene(parent),
    currentDrawMode(None),
    drawing_(false),
    currentRectItem(nullptr) {}

drawing::~drawing() {}

void drawing::setDrawMode(DrawMode mode) { currentDrawMode = mode; }

void drawing::mousePressEvent (QGraphicsSceneMouseEvent *event)
{
    if (currentDrawMode == Rectangle){

        startDrawRectangle(event->scenePos());

    } else if (currentDrawMode == Line) {

        startDrawLine(event->scenePos());

    } else if (currentDrawMode == Highlighter) {

        startDrawHighlighter(event->scenePos());
    }
}

void drawing::mouseMoveEvent (QGraphicsSceneMouseEvent *event)
{
    if (drawing_ && currentDrawMode == Rectangle) {

        updateRectangle(event->scenePos());

    } else if (drawing_ && currentDrawMode == Line) {

        drawLineSegment(event->scenePos());

    } else if (drawing_ && currentDrawMode == Highlighter) {

        updateHighlighter(event->scenePos());
    }
}

void drawing::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (drawing_ && currentDrawMode == Rectangle) {

        // Завершаем рисование прямоугольника
        drawing_ = false;

    } else if (drawing_ && currentDrawMode == Line) {

        // Завершаем рисование линии
        drawing_ = false;

    } else if (drawing_ && currentDrawMode == Highlighter) {

        // Завершаем рисование маркером
        drawing_ = false;
    }
}

void drawing::startDrawRectangle (const QPointF &scenePos) {

    startPoint = scenePos;
    currentRectItem = addRect(QRectF(startPoint, QSizeF()),
                              QPen(Qt::red, 0),
                              QBrush(Qt::NoBrush));

    emit startPointRect(scenePos); // startDrawRectangle

    drawing_ = true;
}

void drawing::updateRectangle(const QPointF &scenePos) {

    QPointF endPoint = scenePos;
    QRectF newRect(startPoint, endPoint);
    currentRectItem->setRect(newRect);

    emit rectDrawn(endPoint); // handleDrawRectangle

    previousPoint = scenePos;
}

void drawing::startDrawLine (const QPointF &scenePos){

    // Сохраняем координаты точки нажатия
    previousPoint = scenePos;
    drawing_ = true;
}

void drawing::drawLineSegment(const QPointF &scenePos) {

    addLine(previousPoint.x(),
            previousPoint.y(),
            scenePos.x(),
            scenePos.y(),
            QPen(Qt::red, 20, Qt::SolidLine, Qt::SquareCap));

    emit lineDrawn(previousPoint.x(), previousPoint.y(),
                   scenePos.x(), scenePos.y());

    previousPoint = scenePos;
}

void drawing::startDrawHighlighter(const QPointF &scenePos) {

    startPoint = scenePos;
    currentRectItem = addRect(QRectF(startPoint, QSizeF()),
                              QPen(Qt::NoPen),
                              QBrush(QColor(255, 255, 0, 100)));

    // Сохраняем координаты точки нажатия
    previousPoint = scenePos;

    emit startPointHigh(scenePos); // startDrawHighlighter

    drawing_ = true;
}

void drawing::updateHighlighter(const QPointF &scenePos) {

    QPointF endPoint = scenePos;
    QRectF newRect(startPoint, endPoint);
    currentRectItem->setRect(newRect);

    emit highDrawn(endPoint); // handleDrawHighlighter

    previousPoint = scenePos;
}
