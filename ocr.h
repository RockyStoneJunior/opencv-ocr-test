#ifndef OCR_H
#define OCR_H

#include <QObject>
#include <opencv2/core/core.hpp>

class Ocr : public QObject{
    Q_OBJECT

public:
    Ocr(cv::Mat);
    ~Ocr();

public slots:
    void process_ocr();

signals:
    void start_ocr();
    void finish_ocr(QString str);

private:
    cv::Mat frame;
};

#endif // OCR_H
