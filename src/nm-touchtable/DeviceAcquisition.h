#ifndef DEVICEACQUISITION_H
#define DEVICEACQUISITION_H

#include <QThread>

#include "camera.h"

class DeviceAcquisition : public QThread
{
    Q_OBJECT

public:
    DeviceAcquisition(QObject *parent = 0);
    virtual void run() Q_DECL_OVERRIDE = 0;

protected:
    bool mIsTouchPressed;
    int mTouchX;
    int mTouchY;

signals:
    void newFrame(vector<Rect>*);

    void touchPress(int x, int y);
    void touchRelease(int x, int y);
    void touchMove(int x, int y);

public slots:
};



#endif // DEVICEACQUISITION_H
