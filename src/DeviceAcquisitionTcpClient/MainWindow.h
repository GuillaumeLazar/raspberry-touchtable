#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>

#include "devicemessage.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void moveEvent(QMoveEvent * event);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

private:
    void sendDataToServer(QString data);

    Ui::MainWindow *ui;
    QTimer mTimer;
    QTcpSocket mTcpClient;
    int mMessageId;

public slots:
    void onTimer();
    void onConnected();
};

#endif // MAINWINDOW_H
