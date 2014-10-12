#ifndef DEVICEACQUISITIONDEMO_H
#define DEVICEACQUISITIONDEMO_H

#include "DeviceAcquisition.h"

class DeviceAcquisitionDemo : public DeviceAcquisition
{
    Q_OBJECT
public:
    explicit DeviceAcquisitionDemo(QObject *parent = 0);
    void run() Q_DECL_OVERRIDE;

    int mMode;
    vector<Rect> objects;

};

#endif // DEVICEACQUISITIONDEMO_H
