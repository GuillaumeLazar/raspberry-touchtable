#include "DeviceAcquisition.h"

DeviceAcquisition::DeviceAcquisition(bool isFakeMode, QObject *parent) :
    QThread(parent)
{
    mIsFakeMode = isFakeMode;
}
