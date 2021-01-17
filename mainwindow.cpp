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

    // Set some default data
    currentPlayer = 0;
    player.at(0) = { 0, 0, 100, 100, 200, 200, 100, 100, 100, 400, 100, 100 };
    player.at(1) = { 500, 222, 100, 100, 700, 200, 100, 100, 500, 400, 100, 100 };

    setDataToFields(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setDataToFields(int p) {
    ui->gameField_x->setValue(player.at(p).gameField_x);
    ui->gameField_y->setValue(player.at(p).gameField_y);
    ui->gameField_width->setValue(player.at(p).gameField_width);
    ui->gameField_height->setValue(player.at(p).gameField_height);
    ui->nextWindow_x->setValue(player.at(p).nextWindow_x);
    ui->nextWindow_y->setValue(player.at(p).nextWindow_y);
    ui->nextWindow_width->setValue(player.at(p).nextWindow_width);
    ui->nextWindow_height->setValue(player.at(p).nextWindow_height);
    ui->score_x->setValue(player.at(p).score_x);
    ui->score_y->setValue(player.at(p).score_y);
    ui->score_width->setValue(player.at(p).score_width);
    ui->score_height->setValue(player.at(p).score_height);
    return;
}

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

// There's probably a more efficient way to map all these events but
// I'm too tired to figure it out right now lol.
void MainWindow::on_gameField_x_valueChanged(int arg1)
{
    player.at(currentPlayer).gameField_x = arg1;
}
void MainWindow::on_gameField_y_valueChanged(int arg1)
{
    player.at(currentPlayer).gameField_y = arg1;
}
void MainWindow::on_gameField_width_valueChanged(int arg1)
{
    player.at(currentPlayer).gameField_width = arg1;
}
void MainWindow::on_gameField_height_valueChanged(int arg1)
{
    player.at(currentPlayer).gameField_height = arg1;
}
void MainWindow::on_nextWindow_x_valueChanged(int arg1)
{
    player.at(currentPlayer).nextWindow_x = arg1;
}
void MainWindow::on_nextWindow_y_valueChanged(int arg1)
{
    player.at(currentPlayer).nextWindow_y = arg1;
}
void MainWindow::on_nextWindow_width_valueChanged(int arg1)
{
    player.at(currentPlayer).nextWindow_width = arg1;
}
void MainWindow::on_nextWindow_height_valueChanged(int arg1)
{
    player.at(currentPlayer).nextWindow_height = arg1;
}
void MainWindow::on_score_x_valueChanged(int arg1)
{
    player.at(currentPlayer).score_x = arg1;
}
void MainWindow::on_score_y_valueChanged(int arg1)
{
    player.at(currentPlayer).score_y = arg1;
}
void MainWindow::on_score_width_valueChanged(int arg1)
{
    player.at(currentPlayer).score_width = arg1;
}
void MainWindow::on_score_height_valueChanged(int arg1)
{
    player.at(currentPlayer).score_height = arg1;
}

void MainWindow::on_currentPlayer_currentIndexChanged(int index)
{
//    std::cout << "Dropdown box index: " << index << std::endl;
    currentPlayer = index;
    setDataToFields(index);
}
