#include "DeviceAcquisitionDemo.h"

#include <QDebug>

DeviceAcquisitionDemo::DeviceAcquisitionDemo(QObject *parent) :
    DeviceAcquisition(parent)
{
    mMode = 0;
    objects = vector<Rect>(3);
}


void DeviceAcquisitionDemo::run()
{
    int step = 10;

    int minX = 200;
    int minY = 200;
    int maxX = 500;
    int maxY = 500;

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

        objects[1].x = (mTouchX + 300) / 4.0f;
        objects[1].y = (mTouchY) / 3.33f;

        objects[2].x = (mTouchX + 600) / 4.0f;
        objects[2].y = (mTouchY) / 3.33f;

        emit touchMove(mTouchX, mTouchY);
        emit newFrame(&objects);

        msleep(10);
    }

}
