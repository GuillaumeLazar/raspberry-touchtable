#include "devicemessage.h"

DeviceMessage::DeviceMessage()
{
    this->id = 0;
}

DeviceMessage::DeviceMessage(const QString &json)
{
    QJsonDocument document = QJsonDocument::fromJson(json.toUtf8());
    QJsonObject jsonObj = document.object();
    this->fromJson(jsonObj);
}

void DeviceMessage::fromJson(const QJsonObject &jsonObject)
{
    this->id = jsonObject["id"].toInt();
    this->objects.clear();

    QJsonArray jsonArray = jsonObject["objects"].toArray();

    for (int i = 0; i < jsonArray.size(); ++i) {
        QJsonObject jsonObject = jsonArray.at(i).toObject();
        DeviceMessageObject object(jsonObject);

        this->objects.append(object);
    }
}

void DeviceMessage::toJson(QJsonObject &jsonObject) const
{
    jsonObject["id"] = this->id;

    QJsonArray jsonArray;

    for (int i = 0; i < this->objects.size(); ++i) {
        DeviceMessageObject object = this->objects.at(i);
        QJsonObject jsonObject;
        object.toJson(jsonObject);

        jsonArray.append(jsonObject);
    }

    jsonObject["objects"] = jsonArray;


//    jsonObject["x"] = this->x;
//    jsonObject["y"] = this->y;
//    jsonObject["state"] = this->state;
}


QString DeviceMessage::serializeToJson(QJsonDocument::JsonFormat jsonFormat) const
{
    QJsonObject jsonObject;
    this->toJson(jsonObject);
    QJsonDocument deviceMessageJsonDoc(jsonObject);
    return QString(deviceMessageJsonDoc.toJson(jsonFormat));
}
