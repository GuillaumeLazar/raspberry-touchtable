#ifndef QMLHANDLER_H
#define QMLHANDLER_H

#include <QQmlApplicationEngine>
#include <QObject>
#include <QTimer>
#include <QMutex>

#include "camera.h"
#include "CustomImage.h"
#include "DeviceAcquisition.h"
#include "DeviceAcquisitionCamera.h"
#include "DeviceAcquisitionDemo.h"
#include "DeviceAcquisitionTcpServer.h"


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
    QObject *textinfo;

    QObject *visualItem1;
    QObject *visualItem2;
    QObject *visualItem3;
    QObject *visualItem4;
    QObject *visualItem5;
    QList<QObject*> listVisualItems;

    //CustomImage *customImageFrame;
    //CustomImage *customImageFrameRoi;
    //CustomImage *customImageFrameDebug;

    bool isCameraFound;
    bool mIsFakeMode;

    int mCptUpdate;

    DeviceAcquisition *mDeviceAcquisition;

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
