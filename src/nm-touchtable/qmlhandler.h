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

    void updateVisualItem(QObject *visualItem, bool visible, Rect *objectBounds);

    QQmlApplicationEngine engine;
    QTimer mTimer;

    QObject *cursor;
    QObject *emitter;
    QObject *qmlWindow;
    QObject *mouseArea;

    QObject *visualItem1;
    QObject *visualItem2;
    QObject *visualItem3;
    QObject *visualItem4;
    QList<QObject*> listVisualItems;

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
    //void onTimer();
    //void onCameraNewPosition(int x, int y);

    void onTouchPress(int x, int y);
    void onTouchMove(int x, int y);
    void onTouchRelease(int x, int y);
    void onCameraNewFrame(vector<Rect>* objects);
};

#endif // QMLHANDLER_H
