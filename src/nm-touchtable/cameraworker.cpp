#include "cameraworker.h"

#include <QDebug>

CameraWorker::CameraWorker(bool isFakeMode, QObject *parent) :
    QThread(parent)
{
    mIsFakeMode = isFakeMode;
}


void CameraWorker::run()
{

    qDebug() << "CameraWorker::run() : init";
    if (!mIsFakeMode){
        initCamera();
    }else{
        initFakeCamera();
    }
    qDebug() << "CameraWorker::run() : init......[done]";

    while(1){

        //qDebug() << "CameraWorker::run()... do it!";
        bool isNewFrame = false;
        isNewFrame = acqFrameFromCamera();

        if (isNewFrame){
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

                 emit newPosition((int)(objCenterX * xRatio), (int)(objCenterY * yRatio));

             }
        }

        // 1000 : 53% : emitter fluide
        // 100  : 56% : emitter fluide
        // 40   : 74% : emitter fluide
        // 33   : 76% : emitter fluide : cursor slow
        // 25   : 78% : emitter fluide : cursor slow
        // none :
        msleep(1);
    }
}
