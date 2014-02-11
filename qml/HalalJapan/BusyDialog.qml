import QtQuick 2.0

Item {
    id: dialog

    property alias message : message.text
    property string size: "small"

    width: size == "small" ? message.width + 70 : message.width + 100
    height: size == "small" ? 60 : 100
    opacity: dialog.visible ? 1 : 0

    Behavior on opacity { PropertyAnimation { properties: "opacity"; duration: 300 } }

    Image {
        id: busyIndicator

        width: size == "small" ? 30 : 60
        height: size == "small" ? 30 : 60
//        width: message.contentHeight
//        height: message.contentHeight
        anchors { left: dialog.left; leftMargin: 10; verticalCenter: dialog.verticalCenter }
        source: "images/busy.png"
        sourceSize.width: width
        sourceSize.height: height
        smooth: true

        NumberAnimation on rotation {
            running: dialog.opacity > 0; from: 0; to: 360; loops: Animation.Infinite; duration: 1500
        }
    }

    Label {
        id: message

        anchors { left: busyIndicator.right; leftMargin: 10; verticalCenter: dialog.verticalCenter }
        font.pixelSize: size == "small" ? _STANDARD_FONT_SIZE : _LARGE_FONT_SIZE
        font.bold: size == "large"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        smooth: true
        text: qsTr("Loading...")
    }
}
