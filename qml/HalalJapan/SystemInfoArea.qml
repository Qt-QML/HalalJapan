import QtQuick 2.0

Item {
    id: root

    width: childrenRect.width + 20
    height: titleArea.height

    Label {
        id: timeLabel

        anchors { left: parent.left; leftMargin: 10; verticalCenter: parent.verticalCenter }
        verticalAlignment: Text.AlignVCenter

        text: Utils.currentTime
    }

//    BatteryIndicator {
//        id: batteryIndicator

//        anchors { left: timeLabel.right; leftMargin: 10; verticalCenter: parent.verticalCenter }
//    }

    Rectangle {
        id: infoSeparator

        width: 1
        height: 40
        anchors { left: timeLabel.right; leftMargin: 10; verticalCenter: parent.verticalCenter }
        color: Settings.activeColor
        opacity: 0.5
    }
}
