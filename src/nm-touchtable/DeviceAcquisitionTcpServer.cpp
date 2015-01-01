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
        //qDebug("unstack...");

        mMutexList.lock();



        if (!mListMessage.isEmpty()){
            qDebug() << "list size is: " << mListMessage.size();

            DeviceMessage message = mListMessage.takeFirst();

            objects = vector<Rect>(message.objects.length());

            for (int i = 0; i < message.objects.length(); ++i) {
                DeviceMessageObject messageObject = message.objects.at(i);
                objects[i].x = messageObject.x / 4.0f;
                objects[i].y = messageObject.y / 3.33f;
                objects[i].width = messageObject.width;
                objects[i].height = messageObject.height;
            }

            emit newFrame(&objects);

            /*
            switch (message.state) {
                case 1:

                    //TODO : bad hardcoded 0 here, it should be message.id
                    objects[0].x = message.x / 4.0f;
                    objects[0].y = message.y / 3.33f;

//                    objects[1].x = (message.x - 50) / 4.0f;
//                    objects[1].y = message.y / 3.33f;

//                    objects[2].x = (message.x + 50) / 4.0f;
//                    objects[2].y = message.y / 3.33f;

//                    objects[3].x = message.x / 4.0f;
//                    objects[3].y = (message.y + 50) / 3.33f;

//                    objects[4].x = message.x / 4.0f;
//                    objects[4].y = (message.y - 50) / 3.33f;

                    emit touchPress(message.x, message.y);
                    emit newFrame(&objects);
                    break;

                case 2:

                    //TODO : bad hardcoded 0 here, it should be message.id
                    objects[0].x = message.x / 4.0f;
                    objects[0].y = message.y / 3.33f;

//                    objects[1].x = (message.x + 50) / 4.0f;
//                    objects[1].y = message.y / 3.33f;

//                    objects[2].x = (message.x + 100) / 4.0f;
//                    objects[2].y = message.y / 3.33f;

//                    objects[3].x = message.x / 4.0f;
//                    objects[3].y = (message.y + 50) / 3.33f;

//                    objects[4].x = message.x / 4.0f;
//                    objects[4].y = (message.y - 50) / 3.33f;

                    emit touchPress(message.x, message.y);
                    emit newFrame(&objects);
                    break;

                case 3:
                    emit touchRelease(message.x, message.y);
                    emit newFrame(&objectsEmpty);
                    //emit newFrame(&objects);
                    break;

                default:
                    break;
            }*/


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
    qDebug() << jsonDoc;
    /*
    QString jsonDoc = QString(data);
    qDebug() << jsonDoc;
    DeviceMessage message(jsonDoc);

    mMutexList.lock();
    mListMessage.append(message);
    mMutexList.unlock()
    */


    QStringList jsonDocList = QString(data).split('*', QString::SkipEmptyParts);
    foreach (QString jsonDoc, jsonDocList) {
        //jsonDoc += "}"; // append the '}' used as separator

        DeviceMessage message(jsonDoc);

        mMutexList.lock();
        mListMessage.append(message);
        mMutexList.unlock();

        qDebug("-> %s", jsonDoc.toStdString().c_str());
    }

}
