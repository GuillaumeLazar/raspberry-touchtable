#-------------------------------------------------
#
# Project created by QtCreator 2015-01-01T15:57:46
#
#-------------------------------------------------

QT       += core
QT       -= gui
QT       += network

TARGET = nm-touchtable-camera
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    camera.cpp \
    DeviceAcquisitionCamera.cpp \
    DeviceAcquisitionDemo.cpp \
    DeviceAcquisition.cpp \
    deviceacquisitionmanager.cpp \
    ../DeviceAcquisitionTcpClient/devicemessage.cpp \
    ../DeviceAcquisitionTcpClient/devicemessageobject.cpp

OTHER_FILES += \
    nm-touchtable-camera.pro.user

HEADERS += \
    camera.h \
    DeviceAcquisitionCamera.h \
    DeviceAcquisitionDemo.h \
    DeviceAcquisition.h \
    deviceacquisitionmanager.h \
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
