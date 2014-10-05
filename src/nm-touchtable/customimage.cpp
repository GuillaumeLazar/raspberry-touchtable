#include "customimage.h"

CustomImage::CustomImage(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
    //this->setRenderTarget(QQuickPaintedItem::FramebufferObject);
    this->setRenderTarget(QQuickPaintedItem::Image);
    mImage = new QImage(320, 240, QImage::Format_RGB888);
    mIsPainted = false;
}

void CustomImage::paint(QPainter *painter)
{
    if (mImage != 0){
        mMutex.lock();

        printf("drawImage()\n");
        painter->drawImage(0, 0, *mImage);

        mMutex.unlock();
    }
}


QImage* CustomImage::image()
{
    return mImage;
}

void CustomImage::setImage(QImage *image, bool deleteCurrent)
{
    mMutex.lock();

    if (deleteCurrent && mImage != 0){
        delete mImage;
    }

    mImage = image;

    mMutex.unlock();

    this->update();
}

