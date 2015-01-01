#include "devicemessageobject.h"

DeviceMessageObject::DeviceMessageObject()
{
    this->x = 0;
    this->y = 0;
    this->width = 0;
    this->height = 0;
    this->state = 0;
}

DeviceMessageObject::DeviceMessageObject(const QString &json)
{
    QJsonDocument document = QJsonDocument::fromJson(json.toUtf8());
    QJsonObject jsonObj = document.object();
    this->fromJson(jsonObj);
}

DeviceMessageObject::DeviceMessageObject(const QJsonObject &jsonObject)
{
    this->fromJson(jsonObject);
}

void DeviceMessageObject::fromJson(const QJsonObject &jsonObject)
{
    this->x = jsonObject["x"].toInt();
    this->y = jsonObject["y"].toInt();
    this->width = jsonObject["width"].toInt();
    this->height = jsonObject["height"].toInt();
    this->state = jsonObject["state"].toInt();
}

void DeviceMessageObject::toJson(QJsonObject &jsonObject) const
{
    jsonObject["x"] = this->x;
    jsonObject["y"] = this->y;
    jsonObject["width"] = this->width;
    jsonObject["height"] = this->height;
    jsonObject["state"] = this->state;
}

QString DeviceMessageObject::serializeToJson() const
{
    QJsonObject jsonObject;
    this->toJson(jsonObject);
    QJsonDocument deviceMessageJsonDoc(jsonObject);
    return QString(deviceMessageJsonDoc.toJson(QJsonDocument::Compact));
}
