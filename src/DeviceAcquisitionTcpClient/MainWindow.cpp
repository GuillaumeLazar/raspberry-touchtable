#include "MainWindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QMoveEvent>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //connect(&mTimer, &QTimer::timeout, this, &MainWindow::onTimer);
    connect(&mTimer, &QTimer::timeout, this, &MainWindow::onTimer);
    connect(&mTcpClient, &QTcpSocket::connected, this, &MainWindow::onConnected);

    qDebug() << "Try to connect...";
    mTcpClient.connectToHost("192.168.1.21", 20140);


    //mTimer.start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onTimer()
{
    qDebug() << "onTimer !";
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
    deviceMessage.id = 0;
    deviceMessage.x = x;
    deviceMessage.y = y;
    deviceMessage.state = 1;

    qDebug();
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
    deviceMessage.id = 0;
    deviceMessage.x = x;
    deviceMessage.y = y;
    deviceMessage.state = 2;

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
    deviceMessage.id = 0;
    deviceMessage.x = x;
    deviceMessage.y = y;
    deviceMessage.state = 3;

    sendDataToServer(deviceMessage.serializeToJson());
}

void MainWindow::sendDataToServer(QString data)
{
    qDebug() << qPrintable(data);
    mTcpClient.write(data.toStdString().c_str());
}



