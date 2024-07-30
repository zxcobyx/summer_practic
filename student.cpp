#include "student.h"
#include "ui_student.h"
#include "drawing.h"

#include <QDebug>
#include <QScrollBar>

student::student(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::student),
    pixmapItem(new QGraphicsPixmapItem()),
    currentRectItem(nullptr)
{
    ui->setupUi(this);

    scene = new drawing(this);
    ui->studentView->setScene(scene);
}

student::~student() { delete ui; }

void student::handleDrawLine(qreal x1, qreal y1, qreal x2, qreal y2) {
    qDebug() << "Student: Draw line" << x1 << y1 << x2 << y2;
    scene->addLine(x1, y1, x2, y2,
                   QPen(Qt::red, 20,
                        Qt::SolidLine,
                        Qt::SquareCap));
}

void student::startDrawRectangle(QPointF pos1Rect) {
    qDebug() << "rectangle" << pos1Rect;

    startPosRect = pos1Rect;
    currentRectItem = scene->addRect(QRectF(startPosRect, QSizeF()),
                                     QPen(Qt::red, 0),
                                     QBrush(Qt::NoBrush));
}

void student::handleDrawRectangle(QPointF pos2Rect) {
    qDebug() << "Student: Draw rectangle" << pos2Rect;

    QRectF newRect(startPosRect, pos2Rect);
    currentRectItem->setRect(newRect);
}

void student::startDrawHighlighter(QPointF pos1High) {
    qDebug() << "highlighter" << pos1High;

    startPosHigh = pos1High;
    currentRectItem = scene->addRect(QRectF(startPosHigh, QSizeF()),
                                     QPen(Qt::NoPen),
                                     QBrush(QColor(255, 255, 0, 100)));
}

void student::handleDrawHighlighter(QPointF pos2High) {
    qDebug() << "Student: Draw highlighter" << pos2High;

    QRectF newRectHigh(startPosHigh, pos2High);
    currentRectItem->setRect(newRectHigh);
}

void student::handleClearAll() {
    qDebug() << "Student: Clear all";
    QList<QGraphicsItem*> items = scene->items();
    for (QGraphicsItem* item : items) {
        if (item != pixmapItem) {
            scene->removeItem(item);
            delete item;
        }
    }
}

void student::handleUploadImage(QString filePath) {
    qDebug() << "Student: Upload image" << filePath;

    QPixmap pixmap(filePath);
    pixmapItem->setPixmap(pixmap);
    scene->addItem(pixmapItem);
    ui->studentView->fitInView(pixmapItem, Qt::KeepAspectRatio);
}

void student::zoom(double scaleF) {
    ui->studentView->scale(scaleF, scaleF);
}

void student::scroll_(int dx, int dy) {
    qDebug() << dx << dy;

    QScrollBar *scrollBar = ui->studentView->horizontalScrollBar();
    scrollBar->setValue(scrollBar->value() - dx);

    scrollBar = ui->studentView->verticalScrollBar();
    scrollBar->setValue(scrollBar->value() - dy);
}
