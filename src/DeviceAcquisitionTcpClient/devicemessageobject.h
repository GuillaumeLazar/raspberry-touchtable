#ifndef DEVICEMESSAGEOBJECT_H
#define DEVICEMESSAGEOBJECT_H

#include <QString>
#include <QJsonObject>
#include <QJsonDocument>

class DeviceMessageObject
{
public:
    DeviceMessageObject();
    DeviceMessageObject(const QString &json);
    DeviceMessageObject(const QJsonObject &jsonObject);

    void fromJson(const QJsonObject &jsonObject);
    void toJson(QJsonObject &jsonObject) const;
    QString serializeToJson() const;

    int x;
    int y;
    int width;
    int height;

    //0: unknown
    //1: press
    //2: move
    //3: release
    int state;
};

#endif // DEVICEMESSAGEOBJECT_H
