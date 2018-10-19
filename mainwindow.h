#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/core/core.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void VideoTest();
    void OcrTest();

public slots:
    void DisplayVideoOnLabel(cv::Mat frame);
    void onStartOcrButtonClicked();
    void dispalyOcrResult(QString str);

private:
    Ui::MainWindow *ui;
    bool start_ocr;
    bool ocr_finish;
};

#endif // MAINWINDOW_H
