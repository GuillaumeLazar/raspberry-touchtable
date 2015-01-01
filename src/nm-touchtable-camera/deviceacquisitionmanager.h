#ifndef DEVICEACQUISITIONMANAGER_H
#define DEVICEACQUISITIONMANAGER_H

#include <QObject>
#include <QDebug>
#include <QTcpSocket>

#include "DeviceAcquisition.h"
#include "DeviceAcquisitionDemo.h"
#include "DeviceAcquisitionCamera.h"

#include "../DeviceAcquisitionTcpClient/devicemessage.h"

class DeviceAcquisitionManager : public QObject
{
    Q_OBJECT
public:
    DeviceAcquisitionManager(int argc, char *argv[]);

protected:
    void sendDataToServer(QString data);

    DeviceAcquisition* mDeviceAcquisition;
    QTcpSocket mTcpClient;
    int mMessageId;

public slots:
    void onTouchPress(int x, int y);
    void onTouchMove(int x, int y);
    void onTouchRelease(int x, int y);
    void onNewFrame(vector<Rect>* objects);

    void onConnected();

};

#endif // DEVICEACQUISITIONMANAGER_H
