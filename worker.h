#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <opencv2/core/core.hpp>

class Worker : public QObject
{
    Q_OBJECT

public:
    Worker();
    ~Worker();

public slots:
    void process();

signals:
    void display(cv::Mat frame);
    void finished();
    void error(QString err);
private:
};

#endif // WORKER_H
