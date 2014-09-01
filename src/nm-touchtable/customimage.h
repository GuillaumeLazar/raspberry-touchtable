#ifndef CUSTOMIMAGE_H
#define CUSTOMIMAGE_H

#include <QtQuick/QQuickPaintedItem>
#include <QImage>
#include <QPainter>

class CustomImage : public QQuickPaintedItem
{
    Q_OBJECT
    // Q_PROPERTY(QImage* image READ image WRITE setImage)

public:
    CustomImage(QQuickItem *parent = 0);
    void paint(QPainter *painter);
    //void setImage(QImage *image);

    QImage* image();
    void setImage(QImage* image, bool deleteCurrent);


private:
    QImage *mImage;

};

#endif // CUSTOMIMAGE_H
