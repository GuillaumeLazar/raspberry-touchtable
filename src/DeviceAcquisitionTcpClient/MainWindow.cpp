#include "MainWindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QMoveEvent>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::moveEvent(QMoveEvent * event)
{
    qDebug() << event->pos();
}
