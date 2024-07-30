#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "drawing.h"
#include "student.h"

#include <QFileDialog>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::SummerProject),
    pixmapItem(new QGraphicsPixmapItem())
{
    ui->setupUi(this);

    // создание сцены
    scene = new drawing();
    ui->image_viewer->setScene(scene);

    // Создание объектов Student1
    student_ = new student();
    student_->show();

    // Связывание сигналов с слотами
    connect(this, &MainWindow::uploadImage, student_, &student::handleUploadImage);
    connect(this, &MainWindow::clearAll, student_, &student::handleClearAll);

    // Сигнал для отрисовки линии
    connect(scene, &drawing::lineDrawn, student_, &student::handleDrawLine);

    // Сигнал для рисования прямоугольника
    connect(scene, &drawing::startPointRect, student_, &student::startDrawRectangle);
    connect(scene, &drawing::rectDrawn, student_, &student::handleDrawRectangle);

    // Сигнал для рисования выделителя
    connect(scene, &drawing::startPointHigh, student_, &student::startDrawHighlighter);
    connect(scene, &drawing::highDrawn, student_, &student::handleDrawHighlighter);

    // connect(ui->image_viewer, &Custom_View::zoom, student_, &student::zoom);
    // connect(ui->image_viewer, &Custom_View::scroll, student_, &student::scroll_);
}

MainWindow::~MainWindow() { delete ui; }

// Обработка кнопки для загрузки изображений
void MainWindow::on_upload_btn_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
    if (!filePath.isEmpty())
    {
        QPixmap pixmap(filePath);
        pixmapItem->setPixmap(pixmap);
        scene->addItem(pixmapItem);
        ui->image_viewer->fitInView(pixmapItem, Qt::KeepAspectRatio);

        ui->draw_line->setEnabled(true);
        ui->draw_rectangle->setEnabled(true);
        ui->draw_highlighter->setEnabled(true);

        emit uploadImage(filePath);
    }
}

// Линия
void MainWindow::on_draw_line_clicked()
{
    if (ui->draw_line->isChecked()) {

        ui->image_viewer->setEnabled(true);
        scene->setDrawMode(drawing::Line);

    } else {

        ui->image_viewer->setEnabled(false);
    }
    ui->image_viewer->setDragMode(QGraphicsView::NoDrag);
}

// Прямоугольник
void MainWindow::on_draw_rectangle_clicked()
{
    if (ui->draw_rectangle->isChecked()) {

        ui->image_viewer->setEnabled(true);
        scene->setDrawMode(drawing::Rectangle);

    } else {

        ui->image_viewer->setEnabled(false);
    }

    ui->image_viewer->setDragMode(QGraphicsView::NoDrag);
}

// Выделитель
void MainWindow::on_draw_highlighter_clicked()
{
    if (ui->draw_highlighter->isChecked()) {

        ui->image_viewer->setEnabled(true);
        scene->setDrawMode(drawing::Highlighter);

    } else {

        ui->image_viewer->setEnabled(false);
    }

    ui->image_viewer->setDragMode(QGraphicsView::NoDrag);
}

// Очистка сцены
void MainWindow::on_clearAll_btn_clicked() {

    QList<QGraphicsItem*> items = scene->items();

    for (QGraphicsItem* item : items) {
        if (item != pixmapItem) {

            scene->removeItem(item);
            delete item;
        }
    }

    ui->image_viewer->setEnabled(false);
    emit clearAll();
}

// Движение картинки
void MainWindow::on_hand_clicked() {
    ui->image_viewer->setDragMode(QGraphicsView::ScrollHandDrag);
    ui->image_viewer->setEnabled(true);
}
