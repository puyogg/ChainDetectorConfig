#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->graphicsView->setScene(new QGraphicsScene(this));
    ui->graphicsView->scene()->addItem(&pixmap);

    ui->gameField_x->setValue(100);
    ui->gameField_y->setValue(100);
    ui->gameField_width->setValue(200);
    ui->gameField_height->setValue(200);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//void drawPlayerBBs(cv::Mat &frame) {
//    cv::rectangle(frame, cv::Rect(ui->gameField_x))
//}

void MainWindow::drawBoundingBoxes(cv::Mat &frame) {
    cv::rectangle(frame,
                  cv::Rect(
                        ui->gameField_x->value(),
                        ui->gameField_y->value(),
                        ui->gameField_width->value(),
                        ui->gameField_height->value()
                  ),
                  cv::Scalar(255, 0, 0),
                  3);
}

void MainWindow::on_startPreview_clicked()
{
    // If the video capture is already open, then the user
    // is clicking the button to stop it.
    if (video.isOpened()) {
        ui->startPreview->setText("Start");
        video.release();
        return;
    }

    // Check if the user gave an ID integer, or a path string.
    bool isCameraID;
    int cameraIndex = ui->cameraValue->text().toInt(&isCameraID);

    if(isCameraID) {
        // Use the cameraIndex to open the video feed,
        // and also record whether it was successful or not.
        bool openSuccessful = video.open(cameraIndex, cv::CAP_DSHOW);
        if (!openSuccessful) {
            QMessageBox::critical(this, "Capture Error", "Enter the correct index <br> or make sure the video capture isn't being used by another program.");
            return;
        }
    }

    // Set video to default to 1920x1080
    video.set(cv::CAP_PROP_FRAME_HEIGHT, 1080);
    video.set(cv::CAP_PROP_FRAME_WIDTH, 1920);

    ui->startPreview->setText("Stop");

    cv::Mat frame;
    while(video.isOpened()) {
        video >> frame;
        drawBoundingBoxes(frame);
        cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
        if (!frame.empty()) {
            // std::cout << "Got frame of type: " << frame.type() << ", " << CV_8UC3 << std::endl;
            QImage qimg(frame.data,
                        frame.cols,
                        frame.rows,
                        frame.step,
                        QImage::Format_RGB888);
            pixmap.setPixmap(QPixmap::fromImage(qimg));
            ui->graphicsView->fitInView(&pixmap, Qt::KeepAspectRatio);

        }
        qApp->processEvents();
    }

    video.release();
    ui->startPreview->setText("Start");
}
