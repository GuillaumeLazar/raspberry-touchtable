#include <QCoreApplication>
#include <QDebug>

#include "deviceacquisitionmanager.h";

int main(int argc, char *argv[])
{
    qDebug() << "+--------------------------+";
    qDebug() << "|   nm-touchtable-camera   |";
    qDebug() << "+--------------------------+";
    qDebug();

    QCoreApplication a(argc, argv);
    DeviceAcquisitionManager manager(argc, argv);

    return a.exec();
}
