#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTimer>
#include <QLabel>
#include <QMutex>

#include "camera.h"
#include "DeviceAcquisition.h"
#include "DeviceAcquisitionCamera.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(bool isFakeMode, QWidget *parent = 0);
    ~MainWindow();

private:
    void updateFrameLabel(Mat &mFrame, QLabel *label, QImage *image);

    Ui::MainWindow *ui;

    QTimer mTimer;

    QImage *imgFramePhaseA;
    QImage *imgFramePhaseB;
    QImage *imgFramePhaseC;

    Mat mFrame;
    Mat mFramePhaseB;
    Mat mFramePhaseC;

    DeviceAcquisition *mDeviceAcquisition;
    QMutex mMutexPoisition;
    bool mIsPositionUpdated;
    bool mIsFakeMode;


public slots:
    void onTimer();
    void onCameraNewFrame(vector<Rect>* objects);
};

#endif // MAINWINDOW_H
