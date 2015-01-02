import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Particles 2.0
import CustomImage 1.0

Window {
    id: window1
    objectName: "window"
    visible: true  
    width: 1280
    height: 800
    color: "#FF000000"

    VisualItem{
        id: visualItem1
        objectName: "visualItem1"
        anchors.fill: parent
        emitter_x: 0
        emitter_y: 0
        emitter_emitRate: 0
    }

    VisualItem{
        id: visualItem2
        objectName: "visualItem2"
        anchors.fill: parent
        emitter_x: 0
        emitter_y: 0
        emitter_emitRate: 0
    }

    VisualItem{
        id: visualItem3
        objectName: "visualItem3"
        anchors.fill: parent
        emitter_x: 0
        emitter_y: 0
        emitter_emitRate: 0
    }

    VisualItem{
        id: visualItem4
        objectName: "visualItem4"
        anchors.fill: parent
        emitter_x: 0
        emitter_y: 0
        emitter_emitRate: 0
    }

    VisualItem{
        id: visualItem5
        objectName: "visualItem5"
        anchors.fill: parent
        emitter_x: 0
        emitter_y: 0
        emitter_emitRate: 0
    }

    Text {
        id: textinfo
        objectName: "textinfo"
        color: "#ffffff"
        text: "Waiting camera..."
        x: 10
        y: 10
        font.pixelSize: 16
    }
}
