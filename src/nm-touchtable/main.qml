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

    MouseArea {
        id: mouseArea
        objectName: "mouseArea"
        anchors.fill: parent
    }

    VisualItem{
        id: visualItem1
        objectName: "visualItem1"
        anchors.fill: parent
        emitter_x: mouseArea.mouseX
        emitter_y: mouseArea.mouseY
        emitter_emitRate: mouseArea.pressed ? 100 : 0
//        emitter_x: 0
//        emitter_y: 0
//        emitter_emitRate: 0
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



    Rectangle {
        id: menuBar
        width: parent.width
        height: 53
        color: "#ffffff"
        opacity: 0.7
        z: 1
        anchors.top: parent.top
        anchors.topMargin: 0

        Rectangle {
            id: exitButton
            x: 0
            y: 380
            width: 150
            height: 40
            color: "#9d9999"
            anchors.verticalCenter: parent.verticalCenter
            z: 2
            border.color: "#000000"

            Text {
                id: exitButton_text
                text: "Quit"
                anchors.fill: parent
                styleColor: "#000000"
                anchors.top: parent.top
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 12
            }

            MouseArea {
                id: exitButton_mouseArea
                anchors.fill: parent
                onClicked: {
                    Qt.quit();
                }
            }
        }

        Rectangle {
            id: testButtonDrag
            x: 320
            y: 7
            width: 150
            height: 40
            color: "#9d9999"
            z: 5
            border.color: "#000000"

            Text {
                text: "Drag me"
                anchors.fill: parent
                styleColor: "#000000"
                anchors.top: parent.top
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 12
            }

            MouseArea {
                anchors.fill: parent

                drag.target: parent
                drag.axis: Drag.XandYAxis

                onPressed: {
                    testButtonDrag.color = "#ff0000"
                }

                onReleased: {
                    testButtonDrag.color = "#9d9999"
                }
            }
        }

        Rectangle {
            id: testButton
            x: 160
            y: 0
            width: 150
            height: 40
            color: "#9d9999"
            anchors.verticalCenter: parent.verticalCenter
            z: 3
            border.color: "#000000"

            Text {
                text: "Click me"
                anchors.fill: parent
                styleColor: "#000000"
                anchors.top: parent.top
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 12
            }

            MouseArea {
                anchors.fill: parent

                onPressed: {
                    testButton.color = "#ff0000"
                }

                onReleased: {
                    testButton.color = "#9d9999"
                    testButtonDrag.x = 320;
                    testButtonDrag.y = 0;
                }
            }
        }

        Text {
            id: textinfo
            objectName: "textinfo"
            x: 502
            y: 20
            text: "Loading..."
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 16
        }
    }


}
