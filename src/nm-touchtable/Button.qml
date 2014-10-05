import QtQuick 2.0


Item {
    width: 100
    height: 40

    Rectangle {
        id: rectangle
        color: "#ffffff"
        anchors.fill: parent
    }

    Text {
        id: text
        text: qsTr("Button")
        anchors.fill: parent
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 12
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
    }


}
