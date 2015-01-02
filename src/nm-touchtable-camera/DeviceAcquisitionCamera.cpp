#include "DeviceAcquisitionCamera.h"

#include <QDebug>

DeviceAcquisitionCamera::DeviceAcquisitionCamera(bool isFakeMode, QObject *parent) :
    DeviceAcquisition(parent)
{
    mIsFakeMode = isFakeMode;
}


void DeviceAcquisitionCamera::run()
{




    // initialization
    if (!mIsFakeMode){
        initCamera();
    }else{
        initFakeCamera();
    }



    // main loop
    while(1){


        bool isNewFrame = false;
        isNewFrame = acqFrameFromCamera();



        if (isNewFrame){

//            QTime timer;
//            timer.start();

            // 15-20ms
             processFrame(0, 0);

//             int v = timer.elapsed();
//             qDebug() << qPrintable( QString("elapsed: %1 ms").arg(v) );

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

                 mTouchX = (int)(objCenterX * xRatio);
                 mTouchY = (int)(objCenterY * yRatio);

                 if (!mIsTouchPressed){
                     mIsTouchPressed = true;
                     emit touchPress(mTouchX, mTouchY);
                 }else{
                     emit touchMove(mTouchX, mTouchY);
                 }
             }else{
                  if (mIsTouchPressed){
                      mIsTouchPressed = false;
                      emit touchRelease(mTouchX, mTouchY);
                  }
             }

             emit newFrame(objects);


        }
    }
}
