#ifndef QMLHANDLER_H
#define QMLHANDLER_H

#include <QQmlApplicationEngine>
#include <QObject>
#include <QTimer>
#include <QMutex>

#include "camera.h"
#include "customimage.h"
#include "cameraworker.h"


class QmlHandler : public QObject
{
Q_OBJECT

public:
    QmlHandler(bool idFakeMode);

private:
    QQmlApplicationEngine engine;
    QTimer mTimer;

    QObject *cursor;
    QObject *emitter;
    QObject *qmlWindow;

    //CustomImage *customImageFrame;
    //CustomImage *customImageFrameRoi;
    //CustomImage *customImageFrameDebug;

    bool isCameraFound;
    bool mIsFakeMode;

    int mCptUpdate;

    CameraWorker *mCameraWorker;

    int mPositionX;
    int mPositionY;
    bool mIsPositionUpdated;
    QMutex mMutexPoisition;



public slots:
    void onTimer();
    void onCameraNewPosition(int x, int y);
};

#endif // QMLHANDLER_H
