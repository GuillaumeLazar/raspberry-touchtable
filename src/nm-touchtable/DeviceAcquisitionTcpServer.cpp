#include "DeviceAcquisitionTcpServer.h"

#include <QDebug>


DeviceAcquisitionTcpServer::DeviceAcquisitionTcpServer(QObject *parent) :
    DeviceAcquisition(parent)
{
    objects = vector<Rect>(1);
    objectsEmpty = vector<Rect>(0);

    mTcpServer = new QTcpServer();

    int port = 20140;
    if (!mTcpServer->listen(findIpAddress(), port)){
        qDebug() << "DeviceAcquisitionTcpServer failed to start!";
        return;

    }else{
        QHostAddress ip = mTcpServer->serverAddress();
        qDebug("DeviceAcquisitionTcpServer listen on %s:%d...", ip.toString().toStdString().c_str(), mTcpServer->serverPort());
    }

    connect(mTcpServer, &QTcpServer::newConnection, this, &DeviceAcquisitionTcpServer::onNewConnection);
}

QHostAddress DeviceAcquisitionTcpServer::findIpAddress(){
    QHostAddress ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();

    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i);
            return ipAddress;
        }
    }

    // if we did not find one, use IPv4 localhost
    ipAddress = QHostAddress(QHostAddress::LocalHost);
    return ipAddress;
}

void DeviceAcquisitionTcpServer::run()
{

}

void DeviceAcquisitionTcpServer::onNewConnection()
{
    qDebug("onNewConnection()");
    mTcpSocket = mTcpServer->nextPendingConnection();
    connect(mTcpSocket, &QTcpSocket::readyRead, this, &DeviceAcquisitionTcpServer::onSocketReadyRead);
    emit newFrame(&objectsEmpty);
}

void DeviceAcquisitionTcpServer::onSocketReadyRead()
{
    qDebug("onSocketReadyRead()");
    QByteArray data = mTcpSocket->readAll();

    QStringList jsonDocList = QString(data).split('}', QString::SkipEmptyParts);

    foreach (QString jsonDoc, jsonDocList) {
        jsonDoc += "}"; // append the '}' used as separator

        DeviceMessage message(jsonDoc);


        switch (message.state) {
            case 1:

                //TODO : bad hardcoded 0 here, it should be message.id
                objects[0].x = message.x;
                objects[0].y = message.y;

                emit touchPress(message.x, message.y);
                emit newFrame(&objects);
                break;

            case 2:

                //TODO : bad hardcoded 0 here, it should be message.id
                objects[0].x = message.x;
                objects[0].y = message.y;

                emit touchPress(message.x, message.y);
                emit newFrame(&objects);
                break;

            case 3:
                emit touchRelease(message.x, message.y);
                emit newFrame(&objectsEmpty);
                break;

            default:
                break;
        }

        //qDebug("%s", jsonDoc.toStdString().c_str());
    }

}
