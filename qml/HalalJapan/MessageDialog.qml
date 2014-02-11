import QtQuick 2.0

Item {
    id: root

    z: 100
    anchors.fill: parent
    visible: HalalJapanAPI.busyMessage !== ""

    Rectangle {
        anchors.fill: parent
        color: !theme.inverted ? "white" : "black"
        opacity: 0.8
    }

    BusyDialog {
        anchors.centerIn: parent
        size: "small"
        message: HalalJapanAPI.busyMessage
    }

    MouseArea {
//        z: -1
        anchors.fill: parent
        onPressAndHold: HalalJapanAPI.clearBusyMessage();
    }
}
