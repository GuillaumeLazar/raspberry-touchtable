#ifndef DEVICEACQUISITIONTCPSERVER_H
#define DEVICEACQUISITIONTCPSERVER_H

#include <QtNetwork>
#include <QMutex>
#include <QList>

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

    QMutex mMutexList;
    QList<DeviceMessage> mListMessage;


private slots:
    void onNewConnection();
    void onSocketReadyRead();


};

#endif // DEVICEACQUISITIONTCPSERVER_H
