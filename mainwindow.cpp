#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtDebug>
#include <QString>
#include <QtConcurrent>
#include <QFuture>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <string>
using std::string;
#include <leptonica/allheaders.h>
#include <tesseract/baseapi.h>

using namespace std;
using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFuture<void> QtConcurrent::run(DisplayVideoOnLabel);
}

void MainWindow::VideoTest()
{
    cv::namedWindow("Video", cv::WND_PROP_AUTOSIZE);
    cv::VideoCapture cap;
    cap.open("http://admin:12345@192.168.31.14:8081");

    cv::Mat frame;
    for(;;){
        cap >> frame;
        if(frame.empty()) break;
        cv::imshow("Video", frame);
        if(cv::waitKey(33) >= 0) break;
    }
}

void MainWindow::DisplayVideoOnLabel()
{
    cv::VideoCapture cap;
    cap.open("http://admin:12345@192.168.31.14:8081");

    cv::Mat frame;
    for(;;){
        cap >> frame;
        if(frame.empty()) break;
        cvtColor(frame, frame, CV_BGR2RGB);
        ui->image_lbl->setPixmap(QPixmap::fromImage(QImage(frame.data,
            frame.cols, frame.rows, frame.step, QImage::Format_RGB888)));
        if(cv::waitKey(33) >= 0) break;
    }
}

void MainWindow::OcrTest()
{
    string outText;
    string imPath = "cv3.jpg";

    tesseract::TessBaseAPI *ocr = new tesseract::TessBaseAPI();
    ocr->Init(NULL, "eng", tesseract::OEM_LSTM_ONLY);
    ocr->SetPageSegMode(tesseract::PSM_AUTO);

    Mat im = imread(imPath, IMREAD_COLOR);

    ocr->SetImage(im.data, im.cols, im.rows, 3, im.step);
    outText = string(ocr->GetUTF8Text());
    QString str = QString::fromStdString(outText);
    qDebug()<< str;
}

MainWindow::~MainWindow()
{
    delete ui;
}
