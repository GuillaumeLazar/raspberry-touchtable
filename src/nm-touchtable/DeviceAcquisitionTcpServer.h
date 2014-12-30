#ifndef DEVICEACQUISITIONTCPSERVER_H
#define DEVICEACQUISITIONTCPSERVER_H

#include <QtNetwork>

#include "DeviceAcquisition.h"
#include "../DeviceAcquisitionTcpClient/devicemessage.h"

class DeviceAcquisitionTcpServer : public DeviceAcquisition
{
    Q_OBJECT
public:
    explicit DeviceAcquisitionTcpServer(QObject *parent = 0);
    void run() Q_DECL_OVERRIDE;
    QHostAddress findIpAddress();

protected:
    QTcpServer *mTcpServer;
    QTcpSocket *mTcpSocket;
    vector<Rect> objects;
    vector<Rect> objectsEmpty;

private slots:
    void onNewConnection();
    void onSocketReadyRead();


};

#endif // DEVICEACQUISITIONTCPSERVER_H
