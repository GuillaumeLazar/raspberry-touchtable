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

        // 1000 : 53% : emitter fluide
        // 100  : 56% : emitter fluide
        // 40   : 74% : emitter fluide
        // 33   : 76% : emitter fluide : cursor slow
        // 25   : 78% : emitter fluide : cursor slow
        // none :
        //msleep(10);
    }
}
