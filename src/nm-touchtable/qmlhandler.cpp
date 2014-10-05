#include "qmlhandler.h"

#include <QTest>
#include <QApplication>

QmlHandler::QmlHandler(bool isFakeMode)
{
    mIsFakeMode = isFakeMode;
    //connect(&mTimer, &QTimer::timeout, this, &QmlHandler::onTimer);

    qmlRegisterType<CustomImage>("CustomImage", 1, 0, "CustomImage");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    qmlWindow = engine.rootObjects().at(0);

    cursor = qmlWindow->findChild<QObject*>("cursor");
    emitter = qmlWindow->findChild<QObject*>("emitter");
    mouseArea = qmlWindow->findChild<QObject*>("mouseArea");

    //customImageFrame = (CustomImage*) qmlWindow->findChild<QObject*>("frame");
    //customImageFrameDebug = (CustomImage*) qmlWindow->findChild<QObject*>("frameDebug");

    mCptUpdate = 0;

    mIsPositionUpdated = false;
    mPositionX = 0;
    mPositionY = 0;

    // QML timer
    //mTimer.start(10);


    // Camera position aquisition
    mCameraWorker = new CameraWorker(mIsFakeMode, this);
    //connect(mCameraWorker, &CameraWorker::newPosition, this, &QmlHandler::onCameraNewPosition);
    connect(mCameraWorker, &CameraWorker::touchPress, this, &QmlHandler::onTouchPress);
    connect(mCameraWorker, &CameraWorker::touchMove, this, &QmlHandler::onTouchMove);
    connect(mCameraWorker, &CameraWorker::touchRelease, this, &QmlHandler::onTouchRelease);
    mCameraWorker->start();
}

void QmlHandler::onTouchPress(int x, int y)
{
    qDebug() <<  "\nonTouchPress: " << x << " x " << y;
    QTest::mousePress((QWindow*)qmlWindow, Qt::LeftButton, Qt::NoModifier, QPoint(x, y));
}

void QmlHandler::onTouchMove(int x, int y)
{
    qDebug() <<  "...onTouchMove: " << x << " x " << y;
    QTest::mouseMove((QWindow*)qmlWindow, QPoint(x, y));
}

void QmlHandler::onTouchRelease(int x, int y)
{
    qDebug() <<  "onTouchRelease: " << x << " x " << y;
    QTest::mouseRelease((QWindow*)qmlWindow, Qt::LeftButton, Qt::NoModifier, QPoint(x, y));
}

/*
void QmlHandler::onCameraNewPosition(int x, int y)
{
    //printf("onCameraNewPosition(%d; %d) \n", x, y);
    mMutexPoisition.lock();
    mIsPositionUpdated = true;
    mPositionX = x;
    mPositionY = y;
    mMutexPoisition.unlock();
}

void QmlHandler::onTimer()
{
    int x = 0;
    int y = 0;
    bool positionUpdated = false;

    mMutexPoisition.lock();

    positionUpdated = mIsPositionUpdated;
    x = mPositionX;
    y = mPositionY;
    mIsPositionUpdated = false;

    mMutexPoisition.unlock();

    //if (positionUpdated){

    QPoint pos(x, y);
    QTest::mouseClick((QWindow*)qmlWindow, Qt::LeftButton, Qt::NoModifier, pos);

        //cursor->setProperty("x", x);
        //cursor->setProperty("y", y);

        //emitter->setProperty("x", x);
        //emitter->setProperty("y", y);
    //}
}
*/
