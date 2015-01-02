#include "QmlHandler.h"

#include <QTest>
#include <QApplication>


QmlHandler::QmlHandler(bool isFakeMode)
{
    mIsFakeMode = isFakeMode;

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

    mCptUpdate = 0;

    mIsPositionUpdated = false;
    mPositionX = 0;
    mPositionY = 0;

    // QML timer
    //mTimer.start(10);

    // Start device aquisition
    //mDeviceAcquisition = new DeviceAcquisitionCamera(mIsFakeMode, this);
    //mDeviceAcquisition = new DeviceAcquisitionDemo(this);
    mDeviceAcquisition = new DeviceAcquisitionTcpServer(this);

    connect(mDeviceAcquisition, &DeviceAcquisition::touchPress, this, &QmlHandler::onTouchPress);
    connect(mDeviceAcquisition, &DeviceAcquisition::touchMove, this, &QmlHandler::onTouchMove);
    connect(mDeviceAcquisition, &DeviceAcquisition::touchRelease, this, &QmlHandler::onTouchRelease);
    connect(mDeviceAcquisition, &DeviceAcquisition::newFrame, this, &QmlHandler::onCameraNewFrame);
    mDeviceAcquisition->start();
}

void QmlHandler::onTouchPress(int x, int y)
{
    //qDebug() <<  "\nonTouchPress: " << x << " x " << y;
    //QTest::mousePress((QWindow*)qmlWindow, Qt::LeftButton, Qt::NoModifier, QPoint(x, y));
}

void QmlHandler::onTouchMove(int x, int y)
{
    //qDebug() <<  "...onTouchMove: " << x << " x " << y;
    //QTest::mouseMove((QWindow*)qmlWindow, QPoint(x, y));
}

void QmlHandler::onTouchRelease(int x, int y)
{
    //qDebug() <<  "onTouchRelease: " << x << " x " << y;
    //QTest::mouseRelease((QWindow*)qmlWindow, Qt::LeftButton, Qt::NoModifier, QPoint(x, y));
}

void QmlHandler::onCameraNewFrame(vector<Rect>* objects)
{
    textinfo->setProperty("text", QString("%1").arg(objects->size()));

    // first is processed by mouse way (wrong -> old slow way)
    for (int i = 0; i < listVisualItems.size(); ++i) {

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
        visualItem->setProperty("emitter_emitRate", 100); //100
    }else{
        visualItem->setProperty("emitter_enabled", false);
        visualItem->setProperty("emitter_emitRate", 0);
    }
}
