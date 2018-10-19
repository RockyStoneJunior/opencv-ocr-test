#include "mainwindow.h"
#include <QApplication>
#include <opencv2/core/core.hpp>

Q_DECLARE_METATYPE(cv::Mat)

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qRegisterMetaType<cv::Mat>();

    MainWindow w;
    w.show();

    return a.exec();
}
