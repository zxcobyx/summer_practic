#ifndef STUDENT_H
#define STUDENT_H

#include "drawing.h"

#include <QMainWindow>
#include <QWidget>
#include <QPixmap>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>

namespace Ui { class student; }

class student : public QMainWindow
{
    Q_OBJECT

public:
    explicit student(QWidget *parent = nullptr);
    ~student();

public slots:

    // Drawing
    void handleDrawLine(qreal x1, qreal y1, qreal x2, qreal y2);

    void startDrawRectangle(QPointF pos1Rect);
    void handleDrawRectangle(QPointF pos2Rect);

    void startDrawHighlighter(QPointF pos1High);
    void handleDrawHighlighter(QPointF pos2High);

    // MainWindow
    void handleClearAll();
    void handleUploadImage(QString filePath);

    // Zoom
    void zoom(double scaleF);
    void scroll_(int dx, int dy);

private:
    Ui::student *ui;
    drawing *scene;
    QGraphicsPixmapItem *pixmapItem;

    QPointF startPosRect;
    QPointF startPosHigh;
    QGraphicsRectItem *currentRectItem;
};

#endif // STUDENT_H
