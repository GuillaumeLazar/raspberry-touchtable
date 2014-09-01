#include "customimage.h"

CustomImage::CustomImage(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
    this->setRenderTarget(QQuickPaintedItem::Image);
    mImage = new QImage(320, 240, QImage::Format_RGB888);
}

void CustomImage::paint(QPainter *painter)
{

    if (mImage != 0){
        painter->drawImage(0, 0, *mImage);

  }

}


QImage* CustomImage::image()
{
    return mImage;
}

void CustomImage::setImage(QImage *image, bool deleteCurrent)
{

    if (deleteCurrent && mImage != 0){
        delete mImage;
    }

    mImage = image;
    this->update();
}

