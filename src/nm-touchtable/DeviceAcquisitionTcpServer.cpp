#include "DeviceAcquisitionTcpServer.h"

#include <QDebug>


DeviceAcquisitionTcpServer::DeviceAcquisitionTcpServer(QObject *parent) :
    DeviceAcquisition(parent)
{
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
}

void DeviceAcquisitionTcpServer::onSocketReadyRead()
{
    qDebug("onSocketReadyRead()");
    QByteArray data = mTcpSocket->readAll();
    qDebug("%s", QString(data).toStdString().c_str());
}
