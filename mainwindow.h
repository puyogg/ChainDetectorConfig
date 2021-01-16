#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QPixmap>
#include <QCloseEvent>
#include <QMessageBox>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <json/json.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startPreview_clicked();

private:
    Ui::MainWindow *ui;

    QGraphicsPixmapItem pixmap;
    cv::VideoCapture video;

    struct PlayerData {
        int gameField_x;
        int gameField_y;
        int gameField_width;
        int gameField_height;
        int nextWindow_x;
        int nextWindow_y;
        int nextWindow_width;
        int nextWindow_height;
        int score_x;
        int score_y;
        int score_width;
        int score_height;
    };
    PlayerData p1;
    PlayerData p2;

    void drawBoundingBoxes(cv::Mat &frame);
};
#endif // MAINWINDOW_H
