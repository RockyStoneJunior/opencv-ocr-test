#include "worker.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <string>
using std::string;
#include <leptonica/allheaders.h>
#include <tesseract/baseapi.h>

Worker::Worker()
{

}

Worker::~Worker()
{

}

void Worker::process()
{
    cv::VideoCapture cap;
    cap.open("http://admin:12345@192.168.31.14:8081");

    cv::Mat frame;
    for(;;){
        cap >> frame;
        if(frame.empty()) break;

        emit display(frame);

        if(cv::waitKey(33) >= 0) break;
    }

    emit finished();
    qDebug("Video thread finished!");
}
