#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTimer>
#include <QLabel>

#include "camera.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void updateFrameLabel(Mat &frame, QLabel *label, QImage *image);

    Ui::MainWindow *ui;

    QTimer mTimer;

    QImage *imgFramePhaseA;
    QImage *imgFramePhaseB;
    QImage *imgFramePhaseC;


public slots:
    void onTimer();
};

#endif // MAINWINDOW_H
