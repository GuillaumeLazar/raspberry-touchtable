#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&mTimer, &QTimer::timeout, this, &MainWindow::onTimer);

    imgFramePhaseA = NULL;
    imgFramePhaseB = NULL;
    imgFramePhaseC = NULL;


    initCamera();

    mTimer.start(33);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateFrameLabel(Mat &frame, QLabel *label, QImage *image)
{
    cvtColor(frame, frame, CV_GRAY2RGB);
    if (image != NULL){
        delete image;
    }
    image = new QImage(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
    QPixmap pixmap = QPixmap::fromImage(*image);
    label->setPixmap(pixmap);
}

void MainWindow::onTimer()
{
    bool isNewFrame = acqFrameFromCamera();
    if( isNewFrame){

        processFrame(0, 0);

        Mat frame = getFrameROI();
        updateFrameLabel(frame, ui->labelFramePhaseA, imgFramePhaseA);

        Mat framePhaseB = getFrameDebugBalance();
        updateFrameLabel(framePhaseB, ui->labelFramePhaseB, imgFramePhaseB);

        Mat framePhaseC = getFrameDebug();
        updateFrameLabel(framePhaseC, ui->labelFramePhaseC, imgFramePhaseC);

    }
}
