#ifndef CAMERAWORKER_H
#define CAMERAWORKER_H

#include <stdio.h>
#include <QThread>

#include "camera.h"


class CameraWorker : public QThread
{
    Q_OBJECT
public:
    explicit CameraWorker(bool isFakeMode, QObject *parent = 0);

    void run() Q_DECL_OVERRIDE;

private:
    bool mIsFakeMode;
    bool mIsTouchPressed;
    int mTouchX;
    int mTouchY;

signals:  
    void newPosition(int x, int y);

    void touchPress(int x, int y);
    void touchRelease(int x, int y);
    void touchMove(int x, int y);

public slots:

};

#endif // CAMERAWORKER_H
