#include "devicemessage.h"

DeviceMessage::DeviceMessage()
{
}

void DeviceMessage::fromJson(const QJsonObject &jsonObject)
{
    this->id = jsonObject["id"].toInt();
    this->x = jsonObject["x"].toInt();
    this->y = jsonObject["y"].toInt();
    this->state = jsonObject["state"].toInt();
}

void DeviceMessage::toJson(QJsonObject &jsonObject) const
{
    jsonObject["id"] = this->id;
    jsonObject["x"] = this->x;
    jsonObject["y"] = this->y;
    jsonObject["state"] = this->state;
}


QString DeviceMessage::serializeToJson() const
{
    QJsonObject jsonObject;
    this->toJson(jsonObject);
    QJsonDocument deviceMessageJsonDoc(jsonObject);
    return QString(deviceMessageJsonDoc.toJson(QJsonDocument::Compact));
}
