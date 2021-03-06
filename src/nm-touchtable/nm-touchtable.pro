TEMPLATE = app

QT += qml quick

QT += gui
QT += network
QT += testlib
#QT += console
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = nm-touchtable

SOURCES += main.cpp \
    camera.cpp \
    DeviceAcquisitionCamera.cpp \
    DeviceAcquisition.cpp \
    MainWindow.cpp \
    QmlHandler.cpp \
    CustomImage.cpp \
    DeviceAcquisitionDemo.cpp \
    DeviceAcquisitionTcpServer.cpp \
    ../DeviceAcquisitionTcpClient/devicemessage.cpp \
    ../DeviceAcquisitionTcpClient/devicemessageobject.cpp

RESOURCES += qml.qrc


target.path = /home/guillaume/sandbox/qt5-test/nm-touchtable
INSTALLS += target

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    camera.h \
    DeviceAcquisitionCamera.h \
    DeviceAcquisition.h \
    MainWindow.h \
    QmlHandler.h \
    CustomImage.h \
    DeviceAcquisitionDemo.h \
    DeviceAcquisitionTcpServer.h \
    ../DeviceAcquisitionTcpClient/devicemessage.h \
    ../DeviceAcquisitionTcpClient/devicemessageobject.h


raspi {
    LIBS += \
        /mnt/rasp-pi-rootfs/usr/lib/libopencv_core.so \
        /mnt/rasp-pi-rootfs/usr/lib/libopencv_highgui.so \
        /mnt/rasp-pi-rootfs/usr/lib/libopencv_imgproc.so \
        /mnt/rasp-pi-rootfs/usr/lib/libopencv_calib3d.so
}else {
    LIBS += `pkg-config opencv --libs`
}

FORMS += \
    mainwindow.ui
