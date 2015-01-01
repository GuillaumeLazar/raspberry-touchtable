#include "deviceacquisitionmanager.h"

DeviceAcquisitionManager::DeviceAcquisitionManager(int argc, char *argv[])
{
    qDebug() << "arg count: " << argc;
    for (int i = 0; i < argc; ++i) {
        qDebug() << QString(" [%1] %2").arg(i).arg(argv[i]);
    }

    QString serverIp = "192.168.1.18";
    mTcpClient.connectToHost(serverIp, 20140);
    mTcpClient.setSocketOption(QAbstractSocket::LowDelayOption, 1);

    //mDeviceAcquisition = new DeviceAcquisitionDemo();
    mDeviceAcquisition = new DeviceAcquisitionCamera(false);

    connect(mDeviceAcquisition, &DeviceAcquisition::touchPress, this, &DeviceAcquisitionManager::onTouchPress);
    connect(mDeviceAcquisition, &DeviceAcquisition::touchMove, this, &DeviceAcquisitionManager::onTouchMove);
    connect(mDeviceAcquisition, &DeviceAcquisition::touchRelease, this, &DeviceAcquisitionManager::onTouchRelease);
    connect(mDeviceAcquisition, &DeviceAcquisition::newFrame, this, &DeviceAcquisitionManager::onNewFrame);
    mDeviceAcquisition->start();
}

void DeviceAcquisitionManager::onTouchPress(int x, int y)
{
     //qDebug() << "onTouchPress: " << x << " x " << y;
}

void DeviceAcquisitionManager::onTouchMove(int x, int y)
{
    //qDebug() << "onTouchMove: " << x << " x " << y;
}

void DeviceAcquisitionManager::onTouchRelease(int x, int y)
{
    //qDebug() << "onTouchRelease: " << x << " x " << y;
}

void DeviceAcquisitionManager::onNewFrame(vector<Rect>* objects)
{
    //qDebug() << "onNewFrame";

    /*
    for (int i = 0; i < objects->size(); ++i) {
        Rect objectBounds = objects->at(i);
        qDebug() << QString("[%1] %2 x %3").arg(i).arg(objectBounds.x).arg(objectBounds.y);
    }
    */

    if (objects->size() > 0){
        Rect objectBounds = objects->at(0);

        DeviceMessage deviceMessage;
        deviceMessage.id = mMessageId;
        deviceMessage.state = 2;
        deviceMessage.x = objectBounds.x;
        deviceMessage.y = objectBounds.y;

        sendDataToServer(deviceMessage.serializeToJson());
    }else{

        DeviceMessage deviceMessage;
        deviceMessage.id = mMessageId;
        deviceMessage.state = 3;
        deviceMessage.x = 0;
        deviceMessage.y = 0;

        sendDataToServer(deviceMessage.serializeToJson());
    }

    //qDebug();
}

void DeviceAcquisitionManager::onConnected()
{
    qDebug() << "we're now connected to nm-touchable-display!";

}

void DeviceAcquisitionManager::sendDataToServer(QString data)
{
    qint64 returnValue = mTcpClient.write(data.toStdString().c_str());
    qDebug() << qPrintable(data) << " (" << returnValue << "/" << data.size() << ")";
    mMessageId++;
}
