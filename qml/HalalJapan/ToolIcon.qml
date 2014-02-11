import QtQuick 2.0

Item {
    id: root

    property string iconSource
    property bool enabled: true
    property bool pressed: mouseArea.pressed

    signal clicked
    signal pressAndHold

    width: 56
    height: 56
    opacity: enabled ? 1 : 0.3

    Rectangle {
        anchors { fill: parent; margins: 5 }
        color: Settings.activeColor
        opacity: 0.5
        radius: 10
        visible: mouseArea.pressed
    }

    Image {
        id: icon

        width: 40
        height: 40
        anchors.centerIn: parent
        source: iconSource == "" ? "" : "../" + iconSource
        sourceSize.width: width
        sourceSize.height: height
    }

    MouseArea {
        id: mouseArea

        anchors.fill: parent
        enabled: root.enabled
        onClicked: parent.clicked()
        onPressAndHold: parent.pressAndHold()
    }
}
