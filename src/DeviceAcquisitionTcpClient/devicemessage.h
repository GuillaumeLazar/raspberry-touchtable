#ifndef DEVICEMESSAGE_H
#define DEVICEMESSAGE_H

#include <QString>
#include <QJsonObject>
#include <QJsonDocument>

class DeviceMessage
{
public:
    DeviceMessage();
    DeviceMessage(const QString &json);

    int id;
    int x;
    int y;

    //0: unknown
    //1: press
    //2: move
    //3: release
    int state;

    void fromJson(const QJsonObject &jsonObject);
    void toJson(QJsonObject &jsonObject) const;

    QString serializeToJson() const;

};

#endif // DEVICEMESSAGE_H
