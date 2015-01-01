#ifndef DEVICEACQUISITIONCAMERA_H
#define DEVICEACQUISITIONCAMERA_H

#include <stdio.h>
#include <QThread>

#include "DeviceAcquisition.h"

class DeviceAcquisitionCamera : public DeviceAcquisition
{
    Q_OBJECT
public:
    explicit DeviceAcquisitionCamera(bool isFakeMode, QObject *parent = 0);
    void run() Q_DECL_OVERRIDE;

protected:
    bool mIsFakeMode;
};

#endif // CAMERAWORKER_H
