#include "MainWindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QMoveEvent>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mMessageId = 0;

    //connect(&mTimer, &QTimer::timeout, this, &MainWindow::onTimer);
    connect(&mTimer, &QTimer::timeout, this, &MainWindow::onTimer);
    connect(&mTcpClient, &QTcpSocket::connected, this, &MainWindow::onConnected);

    qDebug() << "Try to connect...";

    // Tower
    //QString serverIp = "192.168.1.21";

    // Raspberry (nm-touchable-display)
    QString serverIp = "192.168.1.108";

    // Laptop
    //QString serverIp = "192.168.1.10";

    mTcpClient.connectToHost(serverIp, 20140);
    mTcpClient.setSocketOption(QAbstractSocket::LowDelayOption, 1);


    //mTimer.start(20);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onTimer()
{
    //qDebug() << "onTimer !";
    //mTcpClient.flush();
}

void MainWindow::onConnected()
{
    qDebug() << "Connected to Server!";
}


void MainWindow::moveEvent(QMoveEvent * event)
{
    //qDebug() << event->pos();
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
    int x = event->x();
    int y = event->y();

    //secure cap
    if (x < 0){ x = 0;}
    if (y < 0){ y = 0;}

    DeviceMessage deviceMessage;
    deviceMessage.id = mMessageId;

    DeviceMessageObject obj1;
    obj1.x = x;
    obj1.y = y;
    obj1.width = 0;
    obj1.height = 0;
    obj1.state = 1;
    deviceMessage.objects.append(obj1);

    sendDataToServer(deviceMessage.serializeToJson());
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    int x = event->x();
    int y = event->y();

    //secure cap
    if (x < 0){ x = 0;}
    if (y < 0){ y = 0;}

    DeviceMessage deviceMessage;
    deviceMessage.id = mMessageId;

    DeviceMessageObject obj1;
    obj1.x = x;
    obj1.y = y;
    obj1.width = 0;
    obj1.height = 0;
    obj1.state = 2;
    deviceMessage.objects.append(obj1);

    sendDataToServer(deviceMessage.serializeToJson());
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{

    int x = event->x();
    int y = event->y();

    //secure cap
    if (x < 0){ x = 0;}
    if (y < 0){ y = 0;}

    DeviceMessage deviceMessage;
    deviceMessage.id = mMessageId;

    sendDataToServer(deviceMessage.serializeToJson());
}

void MainWindow::sendDataToServer(QString data)
{
    QString dataAndSeparator;
    dataAndSeparator = QString("%1*").arg(data);
    qint64 returnValue = mTcpClient.write(dataAndSeparator.toStdString().c_str());
    qDebug() << qPrintable(dataAndSeparator) << " (" << returnValue << "/" << dataAndSeparator.size() << ")";
    mMessageId++;

}



