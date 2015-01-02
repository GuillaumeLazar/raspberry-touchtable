#include "deviceacquisitionmanager.h"

DeviceAcquisitionManager::DeviceAcquisitionManager(int argc, char *argv[])
{
    qDebug() << "arg count: " << argc;
    for (int i = 0; i < argc; ++i) {
        qDebug() << QString(" [%1] %2").arg(i).arg(argv[i]);
    }

    mMessageId = 0;
    mRatioX = 1280.0f / 320.0f;
    mRatioY = 800.0f / 240.0f;

    // Tower
    //QString serverIp = "192.168.1.21";

    // Raspberry (nm-touchable-display)
    QString serverIp = "192.168.1.107";

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

    DeviceMessage deviceMessage;
    deviceMessage.id = mMessageId;

    for (int i = 0; i < objects->size(); ++i) {
        DeviceMessageObject deviceObject;
        Rect objectBounds = objects->at(i);

        deviceObject.x = objectBounds.x;
        deviceObject.y = objectBounds.y;
        deviceObject.width = objectBounds.width;
        deviceObject.height = objectBounds.height;

        deviceMessage.objects.append(deviceObject);
    }


    //qDebug() << deviceMessage.serializeToJson();
    sendDataToServer(deviceMessage.serializeToJson());
}

void DeviceAcquisitionManager::onConnected()
{
    qDebug() << "we're now connected to nm-touchable-display!";

}

void DeviceAcquisitionManager::sendDataToServer(QString data)
{
    QString dataAndSeparator;
    dataAndSeparator = QString("%1*").arg(data);
    qint64 returnValue = mTcpClient.write(dataAndSeparator.toStdString().c_str());

    if (returnValue == -1){
        qDebug() << "Error nm-touchtable-display is offline!";
    }
    //qDebug() << qPrintable(dataAndSeparator) << " (" << returnValue << "/" << dataAndSeparator.size() << ")";
    mMessageId++;

}
