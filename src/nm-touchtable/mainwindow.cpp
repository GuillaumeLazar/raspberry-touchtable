#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(bool isFakeMode, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&mTimer, &QTimer::timeout, this, &MainWindow::onTimer);

    mIsFakeMode = isFakeMode;

    imgFramePhaseA = NULL;
    imgFramePhaseB = NULL;
    imgFramePhaseC = NULL;

    mIsPositionUpdated = false;
    mTimer.start(10);

    // Camera position aquisition
    mCameraWorker = new CameraWorker(mIsFakeMode, this);
    connect(mCameraWorker, &CameraWorker::newFrame, this, &MainWindow::onCameraNewFrame);
    mCameraWorker->start();
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

void MainWindow::onCameraNewFrame(vector<Rect> * objects)
{

    mMutexPoisition.lock();

    mFrame = getFrameROI();
    mFramePhaseB = getFrameDebugBalance();
    mFramePhaseC = getFrameDebug();
    mIsPositionUpdated = true;

    mMutexPoisition.unlock();
}

void MainWindow::onTimer()
{
    bool updatedRequired = false;
    Mat frame;
    Mat framePhaseB;
    Mat framePhaseC;

    mMutexPoisition.lock();

    updatedRequired = mIsPositionUpdated;
    mIsPositionUpdated = false;

    if(updatedRequired){
        frame = mFrame;
        framePhaseB = mFramePhaseB;
        framePhaseC = mFramePhaseC;
    }

    mMutexPoisition.unlock();

    if (updatedRequired){
        updateFrameLabel(frame, ui->labelFramePhaseA, imgFramePhaseA);
        updateFrameLabel(framePhaseB, ui->labelFramePhaseB, imgFramePhaseB);
        updateFrameLabel(framePhaseC, ui->labelFramePhaseC, imgFramePhaseC);
    }
}


