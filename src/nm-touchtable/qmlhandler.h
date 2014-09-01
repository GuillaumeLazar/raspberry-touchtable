#ifndef QMLHANDLER_H
#define QMLHANDLER_H

#include <QQmlApplicationEngine>
#include <QObject>
#include <QTimer>

#include "camera.h"
#include "customimage.h"


class QmlHandler : public QObject
{
Q_OBJECT

public:
    QmlHandler(bool idFakeMode);

private:
    QQmlApplicationEngine engine;
    QTimer mTimer;

    QObject *rect;
    QObject *rectText;
    QObject *framePreview;
    QObject *qmlWindow;
    CustomImage *customImageFrame;
    CustomImage *customImageFrameRoi;
    CustomImage *customImageFrameDebug;
    bool isCameraFound;
    bool mIsFakeMode;



public slots:
    void onTimer();
};

#endif // QMLHANDLER_H
