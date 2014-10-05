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
    textinfo = qmlWindow->findChild<QObject*>("textinfo");


    visualItem1 = qmlWindow->findChild<QObject*>("visualItem1");
    visualItem2 = qmlWindow->findChild<QObject*>("visualItem2");
    visualItem3 = qmlWindow->findChild<QObject*>("visualItem3");
    visualItem4 = qmlWindow->findChild<QObject*>("visualItem4");
    visualItem5 = qmlWindow->findChild<QObject*>("visualItem5");
    listVisualItems.append(visualItem1);
    listVisualItems.append(visualItem2);
    listVisualItems.append(visualItem3);
    listVisualItems.append(visualItem4);
    listVisualItems.append(visualItem5);

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
    connect(mCameraWorker, &CameraWorker::newFrame, this, &QmlHandler::onCameraNewFrame);
    mCameraWorker->start();
}

void QmlHandler::onTouchPress(int x, int y)
{
    //qDebug() <<  "\nonTouchPress: " << x << " x " << y;
    QTest::mousePress((QWindow*)qmlWindow, Qt::LeftButton, Qt::NoModifier, QPoint(x, y));
}

void QmlHandler::onTouchMove(int x, int y)
{
    //qDebug() <<  "...onTouchMove: " << x << " x " << y;
    QTest::mouseMove((QWindow*)qmlWindow, QPoint(x, y));
}

void QmlHandler::onTouchRelease(int x, int y)
{
    //qDebug() <<  "onTouchRelease: " << x << " x " << y;
    QTest::mouseRelease((QWindow*)qmlWindow, Qt::LeftButton, Qt::NoModifier, QPoint(x, y));
}

void QmlHandler::onCameraNewFrame(vector<Rect>* objects)
{
    textinfo->setProperty("text", QString("objects count: %1").arg(objects->size()));

    // first is processed by mouse way
    for (int i = 1; i < listVisualItems.size(); ++i) {

        QObject *visualItem = listVisualItems.at(i);

        if (objects->size() > i){
            Rect objectBounds = objects->at(i);

            updateVisualItem(visualItem, true, &objectBounds);
        }else{
            updateVisualItem(visualItem, false, NULL);
        }
    }
}


void QmlHandler::updateVisualItem(QObject *visualItem, bool visible, Rect *objectBounds)
{
    if(visible){
        float xRatio = 4.0f;
        float yRatio = 3.33f;

        int objCenterX = objectBounds->x + objectBounds->width/2.0;
        int objCenterY = objectBounds->y + objectBounds->height/2.0;

        int x = (int)(objCenterX * xRatio);
        int y = (int)(objCenterY * yRatio);

        visualItem->setProperty("emitter_x", x);
        visualItem->setProperty("emitter_y", y);
        visualItem->setProperty("emitter_enabled", true);
        visualItem->setProperty("emitter_emitRate", 100);
    }else{
        visualItem->setProperty("emitter_enabled", false);
        visualItem->setProperty("emitter_emitRate", 0);
    }
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
