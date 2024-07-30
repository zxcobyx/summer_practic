#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

#include "drawing.h"
#include "student.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SummerProject; }
QT_END_NAMESPACE

//    class student;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void clearAll();
    void uploadImage(QString filePath);

private slots:
    void on_upload_btn_clicked();
    void on_draw_line_clicked();
    void on_clearAll_btn_clicked();
    void on_draw_rectangle_clicked();
    void on_draw_highlighter_clicked();
    void on_hand_clicked();

private:
    Ui::SummerProject *ui;
    drawing *scene;
    QGraphicsPixmapItem *pixmapItem;

    student *student_;
};

#endif // MAINWINDOW_H
