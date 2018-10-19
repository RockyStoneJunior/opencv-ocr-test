#include "ocr.h"

#include <iostream>
#include <string>
using std::string;
#include <leptonica/allheaders.h>
#include <tesseract/baseapi.h>

Ocr::Ocr(cv::Mat video_frame)
{
    frame = video_frame;
}

void Ocr::process_ocr()
{
    string outText;

    tesseract::TessBaseAPI *ocr = new tesseract::TessBaseAPI();
    ocr->Init(NULL, "eng", tesseract::OEM_LSTM_ONLY);
    ocr->SetPageSegMode(tesseract::PSM_AUTO);

    ocr->SetImage(frame.data, frame.cols, frame.rows, 3, frame.step);
    outText = string(ocr->GetUTF8Text());
    QString str = QString::fromStdString(outText);

    emit finish_ocr(str);
}

Ocr::~Ocr()
{

}
