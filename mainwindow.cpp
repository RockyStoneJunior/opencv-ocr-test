#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtDebug>
#include <QString>
#include <QThread>

#include "worker.h"
#include "ocr.h"

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

    start_ocr = false;
    ocr_finish = true;

    QThread* thread = new QThread();

    Worker* worker = new Worker();
    worker->moveToThread(thread);

    connect(thread, SIGNAL(started()), worker, SLOT(process()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(worker, SIGNAL(display(cv::Mat)), this, SLOT(DisplayVideoOnLabel(cv::Mat)));
    thread->start();

    connect(ui->start_ocr_button, SIGNAL(released()), this, SLOT(onStartOcrButtonClicked()));
}

void MainWindow::DisplayVideoOnLabel(cv::Mat frame)
{
    cv::Mat display_frame, trans_frame;

    cvtColor(frame, display_frame, CV_BGR2RGB);
    ui->image_lbl->setPixmap(QPixmap::fromImage(QImage(display_frame.data,
    display_frame.cols, display_frame.rows, display_frame.step, QImage::Format_RGB888)));

    if(!start_ocr)
    {
        ui->trans_lbl->setPixmap(QPixmap::fromImage(QImage(display_frame.data,
        display_frame.cols, display_frame.rows, display_frame.step, QImage::Format_RGB888)));
    }else{

        if(ocr_finish)
        {
            QThread* thread = new QThread();
            Ocr* ocr = new Ocr(frame);
            ocr->moveToThread(thread);

            connect(thread, SIGNAL(started()), ocr, SLOT(process_ocr()));
            connect(ocr, SIGNAL(finish_ocr(QString)), this, SLOT(dispalyOcrResult(QString)));
            thread->start();

            ocr_finish = false;
            ui->start_ocr_button->setDisabled(true);
        }
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

void MainWindow::onStartOcrButtonClicked()
{
    if(start_ocr)
    {
        start_ocr = false;
        ui->start_ocr_button->setText("Start OCR");
        ui->ocr_result->clear();
    }else{
        start_ocr = true;
        ocr_finish = true;
        ui->start_ocr_button->setText("Stop OCR");
    }
}

void MainWindow::dispalyOcrResult(QString str)
{
    ui->ocr_result->setPlainText(str);
    ui->start_ocr_button->setDisabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}
