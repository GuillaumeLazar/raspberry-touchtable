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
    qDebug("run()");

    while(1){
        msleep(5);

        mMutexList.lock();

        if (!mListMessage.isEmpty()){
            //qDebug() << "list size is: " << mListMessage.size();

            DeviceMessage message = mListMessage.takeFirst();

            objects = vector<Rect>(message.objects.length());

            for (int i = 0; i < message.objects.length(); ++i) {
                DeviceMessageObject messageObject = message.objects.at(i);
                objects[i].x = messageObject.x;
                objects[i].y = messageObject.y;
                objects[i].width = messageObject.width;
                objects[i].height = messageObject.height;
            }

            emit newFrame(&objects);

        }else{
            //emit newFrame(&objectsEmpty);
        }

        mMutexList.unlock();
    }
}

void DeviceAcquisitionTcpServer::onNewConnection()
{
    qDebug("onNewConnection()");
    mTcpSocket = mTcpServer->nextPendingConnection();
    mTcpSocket->setSocketOption(QAbstractSocket::LowDelayOption, 1);
    connect(mTcpSocket, &QTcpSocket::readyRead, this, &DeviceAcquisitionTcpServer::onSocketReadyRead);
    emit newFrame(&objectsEmpty);
}

void DeviceAcquisitionTcpServer::onSocketReadyRead()
{
    //qDebug("onSocketReadyRead()");
    QByteArray data = mTcpSocket->readAll();
    QString jsonDoc = QString(data);
    //qDebug() << jsonDoc;

    QStringList jsonDocList = QString(data).split('*', QString::SkipEmptyParts);
    foreach (QString jsonDoc, jsonDocList) {

        DeviceMessage message(jsonDoc);

        mMutexList.lock();
        mListMessage.append(message);
        mMutexList.unlock();

        //qDebug("-> %s", jsonDoc.toStdString().c_str());
    }

}
