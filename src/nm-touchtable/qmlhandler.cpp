#include "qmlhandler.h"


QmlHandler::QmlHandler(bool isFakeMode)
{
    mIsFakeMode = isFakeMode;
    connect(&mTimer, &QTimer::timeout, this, &QmlHandler::onTimer);

    qmlRegisterType<CustomImage>("CustomImage", 1, 0, "CustomImage");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    qmlWindow = engine.rootObjects().at(0);

    cursor = qmlWindow->findChild<QObject*>("cursor");
    emitter = qmlWindow->findChild<QObject*>("emitter");

    //customImageFrame = (CustomImage*) qmlWindow->findChild<QObject*>("frame");
    //customImageFrameDebug = (CustomImage*) qmlWindow->findChild<QObject*>("frameDebug");

    mCptUpdate = 0;


    // 40 : rect moyen / emitter ok
    // 35 : rect moyen / emitter ok
    // 33 : rect ok / emitter KO
    // 25 : rect ok / emitter slow
    int timerInterval = 33;

    if (!mIsFakeMode){

        isCameraFound = initCamera();

        if (isCameraFound){
            // 100ms -> 54% CPU
            // 100ms -> 67% CPU
            mTimer.start(timerInterval);
        }
    }else{

        isCameraFound = initFakeCamera();

        if(!isCameraFound){
            qmlWindow->setProperty("newX", 1280/2);
            qmlWindow->setProperty("newY", 800/2);
        }

        mTimer.start(timerInterval);
    }
}

void QmlHandler::onTimer()
{
    //printf("onTimer() \n");
    bool isNewFrame = acqFrameFromCamera();

    if( isNewFrame){

        mCptUpdate++;

        if (mCptUpdate >= 0){
            mCptUpdate = 0;

            //printf("---> processFrame()\n");
            processFrame(0, 0);


            //---------------------------------------
            //find objects
            int objectsCount = getBoundCount();
            vector<Rect>* objects = getBoundRect();

            if (objectsCount > 0){
                Rect objectBounds = objects->at(0);

                float xRatio = 4.0f;
                float yRatio = 3.33f;

                int objCenterX = objectBounds.x + objectBounds.width/2.0;
                int objCenterY = objectBounds.y + objectBounds.height/2.0;

                cursor->setProperty("x", (int)(objCenterX * xRatio));
                cursor->setProperty("y", (int)(objCenterY * yRatio));

                emitter->setProperty("x", (int)(objCenterX * xRatio));
                emitter->setProperty("y", (int)(objCenterY * yRatio));

                emitter->setProperty("emitRate", 40);


                //qmlWindow->setProperty("newX", (int)(objCenterX * xRatio));
                //qmlWindow->setProperty("newY", (int)(objCenterY * yRatio));

            }else{
                //qmlWindow->setProperty("newX", -1);
                //qmlWindow->setProperty("newY", -1);

                emitter->setProperty("emitRate", 0);
            }

        }

    }
}

