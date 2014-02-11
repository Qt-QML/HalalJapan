import QtQuick 2.0

Item {
    id: root

    width: 15
    height: 15

    Rectangle {
        anchors.fill: parent
        color: Settings.activeColor
        opacity: 0.5
        rotation: 45
    }

    Rectangle {
        height: 20
        width: 30
        anchors { horizontalCenter: parent.horizontalCenter; bottom: parent.verticalCenter }
        color: _BACKGROUND_COLOR
    }
}
