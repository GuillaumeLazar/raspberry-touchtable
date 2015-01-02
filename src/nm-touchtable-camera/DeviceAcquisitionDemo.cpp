#include "DeviceAcquisitionDemo.h"

#include <QDebug>

DeviceAcquisitionDemo::DeviceAcquisitionDemo(QObject *parent) :
    DeviceAcquisition(parent)
{
    mMode = 0;
    objects = vector<Rect>(1);
}


void DeviceAcquisitionDemo::run()
{
    int step = 5;

    int minX = 50;
    int minY = 50;
    int maxX = 150;
    int maxY = 150;

    mTouchX = minX;
    mTouchY = minY;

    //mIsTouchPressed = true;
    emit touchPress(mTouchX, mTouchY);

    while(1){

        switch (mMode) {
            case 0:
                if (mTouchX < maxX)
                {
                    mTouchX += step;
                }else{
                    mMode = 1;
                }
                break;

             case 1:
                 if (mTouchY < maxY){
                     mTouchY += step;
                 }else{
                     mMode = 2;
                 }
                 break;

            case 2:
                if (mTouchX > minX)
                {
                    mTouchX -= step;
                }else{
                    mMode = 3;
                }
                break;

            case 3:
                if (mTouchY > minY){
                    mTouchY -= step;
                }else{
                    mMode = 0;
                }
                break;
        }


        objects[0].x = mTouchX;
        objects[0].y = mTouchY;

        emit touchMove(mTouchX, mTouchY);
        emit newFrame(&objects);

        msleep(50);
    }

}
