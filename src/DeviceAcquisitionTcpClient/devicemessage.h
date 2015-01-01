#ifndef DEVICEMESSAGE_H
#define DEVICEMESSAGE_H

#include <QString>
#include <QList>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

#include "devicemessageobject.h"

class DeviceMessage
{
public:
    DeviceMessage();
    DeviceMessage(const QString &json);

    void fromJson(const QJsonObject &jsonObject);
    void toJson(QJsonObject &jsonObject) const;
    QString serializeToJson(QJsonDocument::JsonFormat jsonFormat = QJsonDocument::Compact) const;

    int id;
    QList<DeviceMessageObject> objects;
};

#endif // DEVICEMESSAGE_H
