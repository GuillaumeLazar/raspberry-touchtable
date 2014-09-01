#include "qmlhandler.h"


QmlHandler::QmlHandler(bool isFakeMode)
{
    mIsFakeMode = isFakeMode;
    connect(&mTimer, &QTimer::timeout, this, &QmlHandler::onTimer);

    qmlRegisterType<CustomImage>("CustomImage", 1, 0, "CustomImage");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    qmlWindow = engine.rootObjects().at(0);
    rect = qmlWindow->findChild<QObject*>("rect");
    rectText = qmlWindow->findChild<QObject*>("rectText");



    if (!mIsFakeMode){

        isCameraFound = initCamera();

        if (isCameraFound){
            // 100ms -> 54% CPU
            // 100ms -> 67% CPU
            mTimer.start(100);
        }
    }else{

        isCameraFound = initFakeCamera();

        if(!isCameraFound){
            qmlWindow->setProperty("newX", 1280/2);
            qmlWindow->setProperty("newY", 800/2);
        }

        mTimer.start(100);
    }
}

void QmlHandler::onTimer()
{
    bool isNewFrame = acqFrameFromCamera();

    if( isNewFrame){

        //find objects
        processFrame(0, 0);
        int objectsCount = getBoundCount();
        vector<Rect>* objects = getBoundRect();

        if (objectsCount > 0){
            Rect objectBounds = objects->at(0);

            float xRatio = 4.0f;
            float yRatio = 3.33f;

            int objCenterX = objectBounds.x + objectBounds.width/2.0;
            int objCenterY = objectBounds.y + objectBounds.height/2.0;

            qmlWindow->setProperty("newX", (int)(objCenterX * xRatio));
            qmlWindow->setProperty("newY", (int)(objCenterY * yRatio));

        }else{
            qmlWindow->setProperty("newX", -1);
            qmlWindow->setProperty("newY", -1);
        }
    }
}

